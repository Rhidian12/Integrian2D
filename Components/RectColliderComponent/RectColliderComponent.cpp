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

	Component* RectColliderComponent::Clone(GameObject* const pOwner)
	{
		RectColliderComponent* pC{ new RectColliderComponent{pOwner, m_Collider, m_RenderDebugBox} };
		pC->m_ColliderColour = m_ColliderColour;
		return pC;
	}

	bool RectColliderComponent::CheckCollision(ColliderComponent* const pOtherCollider) noexcept
	{
		switch (pOtherCollider->GetColliderShape())
		{
		case ColliderShape::Rectangle:
			return RectangleCollision(static_cast<RectColliderComponent*>(pOtherCollider));
			break;
		case ColliderShape::Circle:
			break;
		default:
			ASSERT(false, "RectColliderComponent::CheckCollision() > The other shape has no collision available!")
		}

		return false;
	}

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

	bool RectColliderComponent::RectangleCollision(RectColliderComponent* const pRectCollider)
	{
		// If one rectangle is on left side of the other
		if (GetRightBottom(m_Collider).x < GetLeftBottom(pRectCollider->m_Collider).x || GetRightBottom(pRectCollider->m_Collider).x < GetLeftBottom(m_Collider).x)
			return false;

		// If one rectangle is under the other
		if (GetLeftBottom(m_Collider).y > GetLeftTop(pRectCollider->m_Collider).y || GetLeftBottom(pRectCollider->m_Collider).y > GetLeftBottom(m_Collider).y)
			return false;

		return true;
	}
}