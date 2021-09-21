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
		const float elapsedSeconds{ Timer::GetInstance()->GetElapsedSeconds() };

		for (size_t i{}; i < m_pComponents.size(); ++i)
		{
			const PhysicsInfo& physicsInfo{ m_pComponents[i]->GetPhysicsInfo() };

			if (!physicsInfo.pHitbox) // If the object does not have a hitbox, it will not be used in the physics engine
				continue;

			// == Cache The Transform ==
			TransformComponent* pTransform{ m_pComponents[i]->GetOwner()->pTransform };

			// == Apply Gravity ==
			if (physicsInfo.gravity)
				m_pComponents[i]->AddForce(Vector2f{ 0.f, -m_Gravity * elapsedSeconds * physicsInfo.mass });

			// == Apply Velocity ==
			pTransform->Translate(physicsInfo.velocity * elapsedSeconds);

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

				if (m_pComponents[i]->CheckCollision(m_pComponents[j]))
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

						m_pComponents[i]->SetVelocity(Vector2f{ outgoingVelocityOneX, outgoingVelocityOneY });
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
		else
			Logger::LogWarning("PhysicsEngine::AddPhysicsComponent() > Component was already added!");
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