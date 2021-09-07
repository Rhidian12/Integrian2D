#include "PhysicsEngine.h"
#include "../Logger/Logger.h"
#include "../Components/PhysicsComponent/PhysicsComponent.h"
#include "../GameObject/GameObject.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Timer/Timer.h"

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

			if (!physicsInfo.pHitbox)
				continue;

			// == Cache The Transform ==
			TransformComponent* pTransform{ m_pComponents[i]->GetOwner()->pTransform };

			// == Apply Gravity ==
			pTransform->Translate(Vector2f{ 0.f, -m_Gravity * elapsedSeconds * physicsInfo.mass });

			// == Apply Velocity ==
			pTransform->Translate(physicsInfo.velocity * elapsedSeconds);

			// == Check For Collision With Other GameObjects ==
			for (size_t j{}; j < m_pComponents.size(); ++j)
			{
				if (i == j)
					continue;

				if (!m_pComponents[j]->GetPhysicsInfo().pHitbox)
					continue;

				// TODO: Add broad and narrow collision detection
				// Broad: Check which gameobjects COULD collide
				// Narrow: Check all of those gameobjects with each other

				if (m_pComponents[i]->CheckCollision(m_pComponents[j]))
					pTransform->Translate(Vector2f{ physicsInfo.velocity.x * elapsedSeconds,
						physicsInfo.velocity.y * elapsedSeconds + m_Gravity * elapsedSeconds * physicsInfo.mass });
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