#include "TransformComponent.h"

namespace Integrian2D
{
	TransformComponent::TransformComponent(GameObject* pOwner)
		: Component{ pOwner }
		, position{}
	{
	}

	Component* TransformComponent::Clone(GameObject* pOwner) noexcept
	{
		TransformComponent* pTransform{ new TransformComponent{pOwner} };
		pTransform->position = position;

		return pTransform;
	}
}
