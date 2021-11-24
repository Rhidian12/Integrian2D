#include "RigidbodyComponent.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../GameObject/GameObject.h"

#include <box2d.h>

namespace Integrian2D
{
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner)
		: Component{ pOwner }
		, m_RigidbodyType{ RigidbodyType::None }
		, m_RigidbodyShape{ RigidbodyShape::None }
		, m_pBox2DBody{}
	{}

	Component* RigidbodyComponent::Clone(GameObject* const pOwner) noexcept
	{
		RigidbodyComponent* const pRigidbody{ new RigidbodyComponent{pOwner} };

		pRigidbody->m_pBox2DBody = m_pBox2DBody;
		pRigidbody->m_RigidbodyShape = m_RigidbodyShape;
		pRigidbody->m_RigidbodyType = m_RigidbodyType;

		return pRigidbody;
	}

	void RigidbodyComponent::RootStart() noexcept
	{
		if (m_pBox2DBody)
			m_pBox2DBody->SetTransform(b2Vec2{ m_pOwner->pTransform->GetWorldPosition().x, m_pOwner->pTransform->GetWorldPosition().y }, 0.f);
	}
}
