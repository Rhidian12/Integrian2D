#pragma once

#include "../Component/Component.h"
#include "../../Utils/Utils.h"
#include "../../Locator/Locator.h"
#include "RigidBodyShape/RigidbodyShape.h"

#include <type_traits>
#include <vector>
#include <box2d.h>

namespace Integrian2D
{
	class RigidbodyComponent final : public Component
	{
	public:
		RigidbodyComponent(GameObject* const pOwner);
		RigidbodyComponent(GameObject* const pOwner, const std::vector<RigidbodyShape*>& rigidBodies);

		Component* Clone(GameObject* const pOwner) noexcept override;

	private:
		virtual void RootStart() noexcept override;

		b2Body* m_pBox2DBody;
	};
}