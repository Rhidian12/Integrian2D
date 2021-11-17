#pragma once

#include "../Component/Component.h"
#include "../../Math/TypeDefines.h"
#include "../ColliderComponent/ColliderComponent.h"
#include "../../PhysicsEngine/PhysicsInfo/PhysicsInfo.h"

namespace Integrian2D
{
	/* TODO: Document this class when PhysicsEngine is complete */

	class PhysicsComponent final : public Component
	{
	public:
		PhysicsComponent(GameObject* pOwner);
		PhysicsComponent(GameObject* pOwner, const float mass);
		PhysicsComponent(GameObject* pOwner, const float mass, const float drag);
		PhysicsComponent(GameObject* pOwner, const float mass, const float drag, ColliderComponent* const pCollider);

		~PhysicsComponent();

		virtual Component* Clone(GameObject* const pOwner) noexcept override;

		bool CheckCollision(PhysicsComponent* const pOtherCollider) noexcept;

		void AddForce(const Vector2f& force) noexcept;

		void SetMass(const float mass) noexcept;
		void SetVelocity(const Vector2f& velocity) noexcept;
		void SetIsAffectedByGravity(const bool isAffectedByGravity) noexcept;
		void SetColliderComponent(ColliderComponent* const pCollider, ColliderShape shape) noexcept;

		const PhysicsInfo& GetPhysicsInfo() const noexcept;

	private:
		PhysicsInfo m_PhysicsInfo;
	};
}