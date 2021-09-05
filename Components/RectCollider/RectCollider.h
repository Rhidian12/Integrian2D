#pragma once

#include "../Component/Component.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	class RectCollider final : public Component
	{
	public:
		RectCollider(GameObject* const pOwner);
		RectCollider(GameObject* const pOwner, const PRectf collider);
		RectCollider(GameObject* const pOwner, const PRectf collider, const bool render);

		// TODO: Implement Fixed Update Collision!

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