#include "TransformComponent.h"

namespace Integrian2D
{
	TransformComponent::TransformComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_TransformChanged{}
		, m_DestRect{}
		, m_Scale{ 1.f, 1.f }
		, m_Angle{}
	{
	}

	Component* TransformComponent::Clone(GameObject* pOwner) noexcept
	{
		TransformComponent* pTransform{ new TransformComponent{pOwner} };
		pTransform->m_DestRect = m_DestRect;
		pTransform->m_Scale = m_Scale;
		pTransform->m_Angle = m_Angle;
		pTransform->m_TransformChanged = m_TransformChanged;

		return pTransform;
	}

	void TransformComponent::FixedUpdate()
	{
		if (m_TransformChanged)
		{
			m_TransformChanged = false;


		}
	}

	void TransformComponent::Translate(const Vector2f& velocity) noexcept
	{
		m_DestRect.xy += velocity;
		m_TransformChanged = true;
	}

	void TransformComponent::Rotate(const float angleRadians) noexcept
	{
		m_Angle += angleRadians;
		m_TransformChanged = true;
	}

	void TransformComponent::RotateAroundPoint(const float angleRadians, const Point2f& pointToRotateAround) noexcept
	{
	}

	void TransformComponent::SetPosition(const Rectf destRect) noexcept
	{
		m_DestRect = destRect;
		m_TransformChanged = true;
	}

	void TransformComponent::SetScale(const Point2f scale) noexcept
	{
		m_Scale = scale;
		m_TransformChanged = true;
	}

	void TransformComponent::SetAngle(const float angle) noexcept
	{
		m_Angle = angle;
		m_TransformChanged = true;
	}

	const Rectf& TransformComponent::GetPosition() const noexcept
	{
		return m_DestRect;
	}

	const Point2f& TransformComponent::GetScale() const noexcept
	{
		return m_Scale;
	}

	const float TransformComponent::GetAngle() const noexcept
	{
		return m_Angle;
	}
}
