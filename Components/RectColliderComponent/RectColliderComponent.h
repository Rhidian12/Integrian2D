#pragma once

#include "../ColliderComponent/ColliderComponent.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	/* TODO: Document this class when PhysicsEngine is complete */

	class RectColliderComponent final : public ColliderComponent
	{
	public:
		RectColliderComponent(GameObject* const pOwner, const PRectf& collider);
		RectColliderComponent(GameObject* const pOwner, const PRectf& collider, const bool render);

		virtual Component* Clone(GameObject* const pOwner) noexcept override;

		virtual bool CheckCollision(ColliderComponent* const pOtherCollider) noexcept override;
		bool CheckCollision(const Point2f& point) noexcept;

		virtual void FixedUpdate() override;
		virtual void Render() const override;

		void SetRenderDebug(const bool render) noexcept;
		void SetRenderDebugColour(const RGBColour& colour) noexcept;
		void SetCollider(const PRectf& collider) noexcept;

		const RGBColour& GetColliderColour() const noexcept;
		const PRectf& GetCollider() const noexcept;

	private:
		bool RectangleCollision(RectColliderComponent* const pRectCollider);

		bool m_RenderDebugBox;
		PRectf m_Collider;
		RGBColour m_ColliderColour;
	};
}