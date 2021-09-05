#include "RectCollider.h"
#include "../../Renderer/Renderer.h"

namespace Integrian2D
{
	RectCollider::RectCollider(GameObject* const pOwner)
		: RectCollider{ pOwner, PRectf{} }
	{}

	RectCollider::RectCollider(GameObject* const pOwner, const PRectf collider)
		: RectCollider{ pOwner, collider, true }
	{}

	RectCollider::RectCollider(GameObject* const pOwner, const PRectf collider, const bool render)
		: Component{ pOwner }
		, m_RenderDebugBox{ render }
		, m_Collider{ collider }
		, m_ColliderColour{ 255, 0, 0 }
	{}

	void RectCollider::Render() const
	{
		if (m_RenderDebugBox)
			Renderer::GetInstance()->RenderRectangle(m_Collider, m_ColliderColour);
	}

	void RectCollider::SetRenderDebug(const bool render) noexcept
	{
		m_RenderDebugBox = render;
	}

	void RectCollider::SetRenderDebugColour(const RGBColour colour) noexcept
	{
		m_ColliderColour = colour;
	}

	const RGBColour& RectCollider::GetColliderColour() const noexcept
	{
		return m_ColliderColour;
	}
}