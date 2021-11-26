#pragma once

#include "../Component/Component.h"
#include "../../Utils/Utils.h"
#include "RigidBodyShape/RigidbodyShape.h"

#include <box2d.h>

namespace Integrian2D
{
	class RigidbodyComponent final : public Component
	{
	public:
		RigidbodyComponent(GameObject* const pOwner);
		RigidbodyComponent(GameObject* const pOwner, RigidbodyShape* const pRigidBody);
		virtual ~RigidbodyComponent() override;

		Component* Clone(GameObject* const pOwner) noexcept override;

		RigidbodyShape* const GetRigidbodyShape() const noexcept;

	private:
		virtual void RootStart() noexcept override;

		RigidbodyShape* m_pRigidbody;
		b2Body* m_pBox2DBody;
	};
}