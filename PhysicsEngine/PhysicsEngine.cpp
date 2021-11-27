#include "PhysicsEngine.h"
#include "../Logger/Logger.h"
#include "../GameObject/GameObject.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../Timer/Timer.h"
#include "../Utils/Utils.h"
#include "../Components/RigidbodyComponent/RigidbodyComponent.h"

#include <algorithm>

namespace Integrian2D
{
	PhysicsEngine::PhysicsEngine()
		: m_pComponents{}
		, m_Gravity{ 0.f, -9.81f }
		, m_PhysicsWorld{ b2Vec2{ m_Gravity.x, m_Gravity.y } }
	{}

	PhysicsEngine::~PhysicsEngine()
	{
		b2Body* pCurrentBody{ m_PhysicsWorld.GetBodyList() };
		b2Body* pNextBody{ pCurrentBody->GetNext() };

		while (pNextBody)
		{
			pNextBody = pCurrentBody->GetNext();
			m_PhysicsWorld.DestroyBody(pCurrentBody);
		}
	}

	void PhysicsEngine::FixedUpdate() noexcept
	{
		/* Box2D recommends 8 and 3 */
		m_PhysicsWorld.Step(Timer::GetInstance()->GetFixedElapsedSeconds(), 8, 3);
	}

	b2Body* const PhysicsEngine::AddPhysicsComponent(RigidbodyComponent* const pComponent) noexcept
	{
		const std::vector<RigidbodyComponent*>::const_iterator cIt{ std::find(m_pComponents.cbegin(), m_pComponents.cend(), pComponent) };

		if (cIt == m_pComponents.cend())
		{
			const RigidbodyShape* const pRigidbodyShape{ pComponent->GetRigidbodyShape() };
			
			const b2BodyDef bodyDef{ pRigidbodyShape->GetBox2DBodyDefinition() };

			b2Body* const pBody{ m_PhysicsWorld.CreateBody(&bodyDef) };

			for (const b2FixtureDef& fixtureDef : pRigidbodyShape->GetBox2DFixtureDefinitions())
				pBody->CreateFixture(&fixtureDef);

			m_pComponents.push_back(pComponent);

			return pBody;
		}
		else
			return nullptr;
	}

	void PhysicsEngine::RemovePhysicsComponent(RigidbodyComponent* const pComponent) noexcept
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComponent), m_pComponents.end());
	}

	void PhysicsEngine::SetGravity(const Vector2f& gravity) noexcept
	{
		m_Gravity = gravity;

		m_PhysicsWorld.SetGravity(b2Vec2{ gravity.x, gravity.y });
	}

	const Vector2f& PhysicsEngine::GetGravity() const noexcept
	{
		return m_Gravity;
	}
}