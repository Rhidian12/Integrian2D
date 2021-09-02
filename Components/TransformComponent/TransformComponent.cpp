#include "TransformComponent.h"

namespace Integrian2D
{
	TransformComponent::TransformComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_TransformChanged{}
		, m_DestRect{}
		, m_Translation{}
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
		// TODO: If parent changes, this needs to be adjusted as well

		if (m_TransformChanged)
		{
			m_TransformChanged = false;

			Matrix3x3 translationMatrix{ GetIdentityMatrix<3,3,float>() };
			translationMatrix(0, 2) = m_Translation.x;
			translationMatrix(1, 2) = m_Translation.y;

			Matrix3x3 scaleMatrix{ GetIdentityMatrix<3,3,float>() };
			scaleMatrix(0, 0) = m_Scale.x;
			scaleMatrix(1, 1) = m_Scale.y;

			const float c{ cos(m_Angle) };
			const float s{ sin(m_Angle) };
			Matrix3x3 rotationMatrix{ GetIdentityMatrix<3,3,float>() };
			rotationMatrix(0, 0) = c;
			rotationMatrix(0, 1) = -s;
			rotationMatrix(1, 0) = s;
			rotationMatrix(1, 1) = c;

			const Matrix3x3 transformationMatrix{ scaleMatrix * rotationMatrix * translationMatrix };

			Rectf destRect{ m_DestRect };
			destRect.leftBottom = transformationMatrix * destRect.leftBottom;
		}
	}

	void TransformComponent::Translate(const Vector2f& velocity) noexcept
	{
		m_Translation = velocity;
		m_TransformChanged = true;
	}

	void TransformComponent::Rotate(const float angleRadians) noexcept
	{
		m_Angle += angleRadians;
		m_TransformChanged = true;
	}

	void TransformComponent::SetDestRect(const Rectf destRect) noexcept
	{
		m_DestRect = destRect;
		m_TransformChanged = true;
	}

	void TransformComponent::SetPosition(const Point2f position) noexcept
	{
		m_DestRect.leftBottom = position;
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

	const Rectf& TransformComponent::GetDestRect() const noexcept
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
