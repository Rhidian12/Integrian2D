#pragma once

#include "../Component/Component.h"

namespace Integrian2D
{
	enum class ColliderShape
	{
		Rectangle = 0,
		Circle = 1
	};

	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(GameObject* const pOwner, const ColliderShape shape);
		virtual ~ColliderComponent() = default;

		virtual Component* Clone(GameObject* const pOwner) = 0;

		virtual bool CheckCollision(ColliderComponent* const pOtherCollider) noexcept = 0;

		void SetColliderShape(const ColliderShape shape) noexcept;

		ColliderShape GetColliderShape() const noexcept;

	protected:
		ColliderShape m_Shape;
	};
}