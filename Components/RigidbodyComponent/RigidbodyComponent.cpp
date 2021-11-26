#include "RigidbodyComponent.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Locator/Locator.h"
#include "../../PhysicsEngine/PhysicsEngine.h"
#include "RigidBodyShape/RigidbodyShape.h"

namespace Integrian2D
{
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner)
		: Component{ pOwner }
		, m_pRigidbody{}
		, m_pBox2DBody{}
	{}

	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, RigidbodyShape* const pRigidBody)
		: Component{ pOwner }
		, m_pRigidbody{ pRigidBody }
		, m_pBox2DBody{}
	{
		m_pBox2DBody = Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this);
	}

	RigidbodyComponent::~RigidbodyComponent()
	{
		Utils::SafeDelete(m_pRigidbody);
	}

	Component* RigidbodyComponent::Clone(GameObject* const pOwner) noexcept
	{
		return new RigidbodyComponent{ pOwner, m_pRigidbody };
	}

	RigidbodyShape* const RigidbodyComponent::GetRigidbodyShape() const noexcept
	{
		return m_pRigidbody;
	}

	void RigidbodyComponent::RootStart() noexcept
	{
		if (m_pBox2DBody)
			m_pBox2DBody->SetTransform(b2Vec2{ m_pOwner->pTransform->GetWorldPosition().x, m_pOwner->pTransform->GetWorldPosition().y }, 0.f);
	}
}
