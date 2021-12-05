#include "AIComponent.h"

namespace Integrian2D
{
	AIComponent::AIComponent(GameObject* const pOwner)
		: Component{ pOwner }
	{
	}

	Component* AIComponent::Clone(GameObject* pOwner) noexcept
	{
		return new AIComponent{ pOwner };
	}
}