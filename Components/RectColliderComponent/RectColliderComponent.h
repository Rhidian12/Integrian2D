#pragma once

#include "../ColliderComponent/ColliderComponent.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	class RectColliderComponent final : public ColliderComponent
	{
	public:
		RectColliderComponent(GameObject* const pOwner, const PRectf collider);
		RectColliderComponent(GameObject* const pOwner, const PRectf collider, const bool render);

		virtual void Render() const override;

		void SetRenderDebug(const bool render) noexcept;
		void SetRenderDebugColour(const RGBColour colour) noexcept;
		void SetCollider(const PRectf collider) noexcept;

		const RGBColour& GetColliderColour() const noexcept;
		const PRectf& GetCollider() const noexcept;

	private:
		bool m_RenderDebugBox;
		PRectf m_Collider;
		RGBColour m_ColliderColour;
	};
}