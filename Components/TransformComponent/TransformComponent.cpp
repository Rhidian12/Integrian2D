#include "TransformComponent.h"

namespace Integrian2D
{
	TransformComponent::TransformComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_TransformChanged{}
		, m_TransformationMatrix{}
		, m_Scale{ 1.f, 1.f }
		, m_Angle{}
	{
		const Matrix3x3 translationMatrix{ GetIdentityMatrix<3,3,float>() };

		const Matrix3x3 rotationMatrix{ GetIdentityMatrix<3,3,float>() };

		Matrix3x3 scaleMatrix{ GetIdentityMatrix<3,3,float>() };
		scaleMatrix(0, 0) = m_Scale.x;
		scaleMatrix(1, 1) = m_Scale.y;

		m_TransformationMatrix = scaleMatrix * rotationMatrix * translationMatrix;
	}

	Component* TransformComponent::Clone(GameObject* pOwner) noexcept
	{
		TransformComponent* pTransform{ new TransformComponent{pOwner} };
		pTransform->m_Scale = m_Scale;
		pTransform->m_Angle = m_Angle;
		pTransform->m_TransformChanged = m_TransformChanged;
		pTransform->m_TransformationMatrix = m_TransformationMatrix;

		return pTransform;
	}

	void TransformComponent::FixedUpdate()
	{
		if (m_TransformChanged)
		{
			m_TransformChanged = false;

			Matrix3x3 translationMatrix{ GetIdentityMatrix<3,3,float>() };
			translationMatrix(0, 2) = m_TransformationMatrix(0, 2);
			translationMatrix(1, 2) = m_TransformationMatrix(1, 2);

			const float c{ cos(m_Angle) };
			const float s{ sin(m_Angle) };
			Matrix3x3 rotationMatrix{ GetIdentityMatrix<3,3,float>() };
			rotationMatrix(0, 0) = c;
			rotationMatrix(0, 1) = -s;
			rotationMatrix(1, 0) = s;
			rotationMatrix(1, 1) = c;

			Matrix3x3 scaleMatrix{ GetIdentityMatrix<3,3,float>() };
			scaleMatrix(0, 0) = m_Scale.x;
			scaleMatrix(1, 1) = m_Scale.y;

			m_TransformationMatrix = scaleMatrix * rotationMatrix * translationMatrix;
		}
	}

	void TransformComponent::Translate(const Vector2f& velocity) noexcept
	{
		m_TransformationMatrix(0, 2) += velocity.x;
		m_TransformationMatrix(1, 2) += velocity.y;
	}

	void TransformComponent::Rotate(const float angleRadians) noexcept
	{
		m_Angle = angleRadians + GetAngle();

		m_TransformChanged = true;
	}

	void TransformComponent::Scale(const Point2f scale) noexcept
	{
		m_Scale = Point2f{ GetScale() + scale };

		m_TransformChanged = true;
	}

	void TransformComponent::SetPosition(const Point2f position) noexcept
	{
		m_TransformationMatrix(0, 2) = position.x;
		m_TransformationMatrix(1, 2) = position.y;
	}

	void TransformComponent::SetScale(const Point2f scale) noexcept
	{
		m_TransformationMatrix(0, 0) = scale.x;
		m_TransformationMatrix(1, 1) = scale.y;	

		m_TransformChanged = true;
	}

	void TransformComponent::SetAngle(const float angle) noexcept
	{
		m_Angle = angle;

		m_TransformChanged = true;
	}

	const Point2f TransformComponent::GetPosition() const noexcept
	{
		return Point2f{ m_TransformationMatrix(0,2), m_TransformationMatrix(1,2) };
	}

	const Point2f TransformComponent::GetScale() const noexcept
	{
		return Point2f{ m_TransformationMatrix(0,0), m_TransformationMatrix(1,1) };
	}

	const float TransformComponent::GetAngle() const noexcept
	{
		return atan2(m_TransformationMatrix(0,1), m_TransformationMatrix(0, 0));
	}
}
