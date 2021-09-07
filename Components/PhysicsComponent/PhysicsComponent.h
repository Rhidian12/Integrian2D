#pragma once

#include "../Component/Component.h"
#include "../../Math/TypeDefines.h"
#include "../ColliderComponent/ColliderComponent.h"
#include "../../PhysicsEngine/PhysicsInfo/PhysicsInfo.h"

namespace Integrian2D
{
	class PhysicsComponent final : public Component
	{
	public:
		PhysicsComponent(GameObject* pOwner);
		PhysicsComponent(GameObject* pOwner, const float mass);
		PhysicsComponent(GameObject* pOwner, const float mass, const Vector2f velocity);
		PhysicsComponent(GameObject* pOwner, const float mass, const Vector2f velocity, ColliderComponent* const pCollider);

		~PhysicsComponent();

		bool CheckCollision(PhysicsComponent* const pOtherCollider) noexcept;

		void SetMass(const float mass) noexcept;
		void SetVelocity(const Vector2f velocity) noexcept;
		void SetColliderComponent(ColliderComponent* const pCollider, ColliderShape shape) noexcept;

		const PhysicsInfo& GetPhysicsInfo() const noexcept;

	private:
		PhysicsInfo m_PhysicsInfo;
	};
}