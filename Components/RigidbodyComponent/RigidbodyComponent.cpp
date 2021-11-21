#include "RigidbodyComponent.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../GameObject/GameObject.h"

#include <box2d.h>

namespace Integrian2D
{
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner)
		: Component{ pOwner }
	{
		//Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this);
	}

	Component* RigidbodyComponent::Clone(GameObject* const pOwner) noexcept
	{
		return new RigidbodyComponent{ pOwner };
	}
}
