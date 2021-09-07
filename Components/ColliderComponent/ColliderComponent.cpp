#include "ColliderComponent.h"

namespace Integrian2D
{
	ColliderComponent::ColliderComponent(GameObject* const pOwner, const ColliderShape shape)
		: Component{ pOwner }
		, m_Shape{ shape }
	{
	}

	ColliderShape ColliderComponent::GetColliderShape() const noexcept
	{
		return m_Shape;
	}
}