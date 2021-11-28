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
		RigidbodyComponent(GameObject* const pOwner, RigidbodyShape* const pRigidBody);
		RigidbodyComponent(GameObject* const pOwner, RigidbodyShape* const pRigidBody, const bool shouldDebugRender);

		virtual ~RigidbodyComponent() override;

		Component* Clone(GameObject* const pOwner) noexcept override;

		virtual void FixedUpdate() override;
		virtual void Render() const override;

		void SetDebugRendering(const bool shouldDebugRender) noexcept;

		RigidbodyShape* const GetRigidbodyShape() const noexcept;
		bool IsDebugRendering() const noexcept;

	private:
		virtual void RootStart() noexcept override;

		RigidbodyShape* m_pRigidbody;
		b2Body* m_pBox2DBody;
		bool m_ShouldDebugRender;
	};
}