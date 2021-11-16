#include "PhysicsEngine.h"
#include "../Logger/Logger.h"
#include "../Components/PhysicsComponent/PhysicsComponent.h"
#include "../GameObject/GameObject.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Timer/Timer.h"
#include "../Components/RectColliderComponent/RectColliderComponent.h"
#include "../Utils/Utils.h"

#include <algorithm>

namespace Integrian2D
{
	PhysicsEngine::PhysicsEngine()
		: m_pComponents{}
		, m_Gravity{ 98.1f }
	{}

	void PhysicsEngine::FixedUpdate() noexcept
	{
		const float elapsedSeconds{ Timer::GetInstance()->GetFixedElapsedSeconds() };

		for (size_t i{}; i < m_pComponents.size(); ++i)
		{
			PhysicsComponent* const pPhysicsComponent{ m_pComponents[i] };
			const PhysicsInfo& physicsInfo{ pPhysicsComponent->GetPhysicsInfo() };
			TransformComponent* const pPhysicsComponentTransform{ pPhysicsComponent->GetOwner()->pTransform };

			/* apply gravity if gravity is enabled.
				Force of gravity = mass * gravity strength 
				Mass gets added in the AddForce(), so dont add it to the calculation here */
			if (physicsInfo.gravity) 
				pPhysicsComponent->AddForce(Vector2f{ 0.f, -m_Gravity * elapsedSeconds });

			/* Calculate the normal vector. THIS IS NOT A SIMPLE NORMALIZED VECTOR
				It is the reaction force to the gravity and works in a orthogonal way to the surface */
			Vector2f normalForce{};

			if (Utils::AreEqual(pPhysicsComponentTransform->GetAngle(), 0.f)) /* if the angle is 0.f, assume the object is flat */
				normalForce = Vector2f{ 0.f, physicsInfo.mass * m_Gravity }; /* since the angle is 0.f, the normal points straight up */
			else
			{
				const float angle{ pPhysicsComponentTransform->GetAngle() };
				const float c{ cosf(angle) };
				const float s{ sinf(angle) };
				
				/* normal force =  - { cos(theta) * m * g * cos(theta), sin(theta) * m * g * cos(theta) } */

				if (physicsInfo.gravity)
					normalForce = -Vector2f{ c * physicsInfo.mass * m_Gravity * c, s * physicsInfo.mass * m_Gravity * c };
				else
					normalForce = -Vector2f{ c * physicsInfo.mass * c, s * physicsInfo.mass * c };

				/* Rotate the normal vector to match the rotation of the surface */
				normalForce -= Vector2f{ pPhysicsComponentTransform->GetWorldPosition() };
				normalForce = Vector2f{ normalForce.x * c - normalForce.y * s, normalForce.x * s + normalForce.y * c };
				normalForce += Vector2f{ pPhysicsComponentTransform->GetWorldPosition() };
			}

			/* Apply drag */

			// == Apply all previously added velocity ==
			pPhysicsComponentTransform->Translate(physicsInfo.velocity);

			// == Check For Collision With Other GameObjects ==
			for (size_t j{}; j < m_pComponents.size(); ++j)
			{
				if (i == j) // make sure we're not checking ourselves
					continue;

				if (!m_pComponents[j]->GetPhysicsInfo().pHitbox) // If the object does not have a hitbox, it will not be used in the physics engine
					continue;

				const PhysicsInfo& otherPhysicsInfo{ m_pComponents[j]->GetPhysicsInfo() };
				const ColliderShape otherColliderShape{ otherPhysicsInfo.pHitbox->GetColliderShape() };

				// TODO: Add broad and narrow collision detection
				// Broad: Check which gameobjects COULD collide
				// Narrow: Check all of those gameobjects with each other

				if (pPhysicsComponent->CheckCollision(m_pComponents[j]))
				{
					// if the gameobjects are colliding, find the shortest distance to not touch each other
					switch (otherColliderShape)
					{
					case ColliderShape::Rectangle:
					{
						// IncomingInpulse == OutgoingImpulse
						// IncomingKineticEnergy == OutgoingKineticEnergy

						// m1v1 + m2v2 = m1u1 + m2u2
						// 0.5m1(v1)^2 + 0.5m2(v2)^2 = 0.5m1(u1)^2 + 0.5m2(u2)^2 
						// <=>
						// m1v1 - m1u1 = m2u2 - m2v2
						// m1(v1)^2 - m1(u1)^2 = m2(u2)^2 - m2(v2)^2 
						// <=>
						// m1(v1 - u1) = m2(u2 - v2)
						// m1((v1)^2 - (u1)^2) = m2((u2)^2 - (v2)^2)
						// <=>
						// m1(v1 - u1) = m2(u2 - v2)
						// m1(v1 + u1)(v1 - u1) = m2(u2 + v2)(u2 - v2)
						// <=>
						// m1(v1 - u1) = m2(u2 - v2)
						// v1 + u1 = u2 + v2
						// <=>
						// m1(v1 - u1) = m2(u2 - v2)
						// u1 = u2 + v2 - v1
						// <=>
						// m1(v1 - (u2 + v2 - v1)) = m2(u2 - v2)
						// u1 = u2 + v2 - v1
						// <=>
						// m1(v1 - u2 - v2 + v1) = m2(u2 - v2)
						// u1 = u2 + v2 - v1
						// <=> (SUBSTITUTED EQUATION #2 INTO #1)
						// m1v1 - m1u2 - m1v2 + m1v1 = m2u2 - m2v2
						// <=>
						// m1v1 - m1v2 + m1v1 + m2v2 = m2u2 + m1u2
						// <=>
						// u2(m1 + m2) = m1v1 - m1v2 + m1v1 + m2v2
						// <=>
						// u2 = (m1v1 - m1v2 + m1v1 + m2v2) / (m1 + m2)
						// <=>
						// u1 = u2 + v2 - v1

						const float outgoingVelocityTwoX{ ((physicsInfo.velocity.x * physicsInfo.mass - otherPhysicsInfo.velocity.x * physicsInfo.mass +
							physicsInfo.velocity.x * physicsInfo.mass + otherPhysicsInfo.velocity.x * otherPhysicsInfo.mass) / (physicsInfo.mass + otherPhysicsInfo.mass)) };
						const float outgoingVelocityTwoY{ ((physicsInfo.velocity.y * physicsInfo.mass - otherPhysicsInfo.velocity.y * physicsInfo.mass +
							physicsInfo.velocity.y * physicsInfo.mass + otherPhysicsInfo.velocity.y * otherPhysicsInfo.mass) / (physicsInfo.mass + otherPhysicsInfo.mass)) };
						const float outgoingVelocityOneX{ outgoingVelocityTwoX + otherPhysicsInfo.velocity.x - physicsInfo.velocity.x };
						const float outgoingVelocityOneY{ outgoingVelocityTwoY + otherPhysicsInfo.velocity.y - physicsInfo.velocity.y };

						const float coefficientOfRestitution{  };

						pPhysicsComponent->SetVelocity(Vector2f{ outgoingVelocityOneX, outgoingVelocityOneY });
						m_pComponents[j]->SetVelocity(Vector2f{ outgoingVelocityTwoX, outgoingVelocityTwoY });
					}
						break;
					case ColliderShape::Circle:
						break;
					}

					//pTransform->Translate(Vector2f{ physicsInfo.velocity.x * elapsedSeconds,
					//	physicsInfo.velocity.y * elapsedSeconds + m_Gravity * elapsedSeconds * physicsInfo.mass });
					//
					//m_pComponents[i]->SetVelocity(Vector2f{});
				}
			}
		}
	}

	void PhysicsEngine::AddPhysicsComponent(PhysicsComponent* const pComponent) noexcept
	{
		const std::vector<PhysicsComponent*>::const_iterator cIt{ std::find(m_pComponents.cbegin(), m_pComponents.cend(), pComponent) };

		if (cIt == m_pComponents.cend())
			m_pComponents.push_back(pComponent);
	}

	void PhysicsEngine::RemovePhysicsComponent(PhysicsComponent* const pComponent) noexcept
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComponent), m_pComponents.end());
	}

	void PhysicsEngine::SetGravity(const float gravity) noexcept
	{
		m_Gravity = gravity;
	}

	float PhysicsEngine::GetGravity() const noexcept
	{
		return m_Gravity;
	}
}