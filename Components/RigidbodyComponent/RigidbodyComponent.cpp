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
		return new RigidbodyComponent{ pOwner };
	}

	void RigidbodyComponent::RootStart() noexcept
	{
	}
}
