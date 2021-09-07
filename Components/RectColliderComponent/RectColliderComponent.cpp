#include "RectColliderComponent.h"
#include "../../Renderer/Renderer.h"

namespace Integrian2D
{
	RectColliderComponent::RectColliderComponent(GameObject* const pOwner, const PRectf collider)
		: RectColliderComponent{ pOwner, collider, true }
	{}

	RectColliderComponent::RectColliderComponent(GameObject* const pOwner, const PRectf collider, const bool render)
		: ColliderComponent{ pOwner, ColliderShape::Rectangle }
		, m_RenderDebugBox{ render }
		, m_Collider{ collider }
		, m_ColliderColour{ 255, 0, 0 }
	{}

	void RectColliderComponent::Render() const
	{
		if (m_RenderDebugBox)
			Renderer::GetInstance()->RenderRectangle(m_Collider, m_ColliderColour);
	}

	void RectColliderComponent::SetRenderDebug(const bool render) noexcept
	{
		m_RenderDebugBox = render;
	}

	void RectColliderComponent::SetRenderDebugColour(const RGBColour colour) noexcept
	{
		m_ColliderColour = colour;
	}

	void RectColliderComponent::SetCollider(const PRectf collider) noexcept
	{
		m_Collider = collider;
	}

	const RGBColour& RectColliderComponent::GetColliderColour() const noexcept
	{
		return m_ColliderColour;
	}

	const PRectf& RectColliderComponent::GetCollider() const noexcept
	{
		return m_Collider;
	}
}