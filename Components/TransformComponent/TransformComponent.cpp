#include "TransformComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Timer/Timer.h"
#include "../../TransformManager/TransformManager.h"

namespace Integrian2D
{
	TransformComponent::TransformComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_TransformChanged{}
		, m_HasWorldPositionChanged{}
		, m_TransformationMatrix{}
		, m_WorldPosition{}
		, m_Scale{ 1.f, 1.f }
		, m_Angle{}
		, m_pTransformManager{}
	{
		const Matrix3x3 translationMatrix{ GetIdentityMatrix<3,3,float>() };

		const Matrix3x3 rotationMatrix{ GetIdentityMatrix<3,3,float>() };

		Matrix3x3 scaleMatrix{ GetIdentityMatrix<3,3,float>() };
		scaleMatrix(0, 0) = m_Scale.x;
		scaleMatrix(1, 1) = m_Scale.y;

		m_TransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	}

	Component* TransformComponent::Clone(GameObject* pOwner) noexcept
	{
		TransformComponent* pTransform{ new TransformComponent{pOwner} };
		pTransform->m_Scale = m_Scale;
		pTransform->m_Angle = m_Angle;
		pTransform->m_TransformChanged = m_TransformChanged;
		pTransform->m_HasWorldPositionChanged = m_HasWorldPositionChanged;
		pTransform->m_TransformationMatrix = m_TransformationMatrix;
		pTransform->m_WorldPosition = m_WorldPosition;

		return pTransform;
	}

	void TransformComponent::FixedUpdate()
	{
		RecalculateTransformationMatrix();
	}

	void TransformComponent::Translate(const Vector2f& velocity) noexcept
	{
		const float dt{ Timer::GetInstance()->GetFixedElapsedSeconds() };
		m_TransformationMatrix(0, 2) += velocity.x * dt;
		m_TransformationMatrix(1, 2) += velocity.y * dt;
	}

	void TransformComponent::Rotate(const float angleRadians) noexcept
	{
		m_Angle += angleRadians;

		m_TransformChanged = true;
	}

	void TransformComponent::Scale(const Point2f& scale) noexcept
	{
		m_Scale += scale;

		m_TransformChanged = true;
	}

	void TransformComponent::SetLocalPosition(const Point2f& position) noexcept
	{
		m_TransformationMatrix(0, 2) = position.x;
		m_TransformationMatrix(1, 2) = position.y;
	}

	void TransformComponent::SetWorldPosition(const Point2f& position) noexcept
	{
		m_WorldPosition = position;

		m_HasWorldPositionChanged = true;

		if (m_pTransformManager)
			m_pTransformManager->NotifyRecalculation();
	}

	void TransformComponent::SetScale(const Point2f& scale) noexcept
	{
		m_Scale = scale;

		m_TransformChanged = true;
	}

	void TransformComponent::SetAngle(const float angle) noexcept
	{
		m_Angle = angle;

		m_TransformChanged = true;
	}

	void TransformComponent::SetHasMoved(const bool hasMoved) noexcept
	{
		m_HasWorldPositionChanged = hasMoved;
	}

	const Point2f& TransformComponent::GetWorldPosition() noexcept
	{
		if (m_HasWorldPositionChanged)
			if (m_pTransformManager)
				m_pTransformManager->ForceImmediateRecalculation(this);

		return m_WorldPosition;
	}

	const Point2f TransformComponent::GetLocalPosition() const noexcept
	{
		return Point2f{ m_TransformationMatrix(0,2), m_TransformationMatrix(1,2) };

		// We can just extract this from the Matrix
	}

	const Point2f& TransformComponent::GetScale() const noexcept
	{
		return m_Scale;

		//return Point2f{ sqrtf(powf(m_TransformationMatrix(0,0), 2) + powf(m_TransformationMatrix(1,0), 2)),
		//				sqrtf(powf(m_TransformationMatrix(0,1), 2) + powf(m_TransformationMatrix(1,1), 2)) };

		// [ V1x		V2x		T1 ]
		// [ V1y		V2y		T2 ]
		// [ 0			0		1  ]

		// Formula to get Scale is:
		// ScaleX = sqrt((V1x)^2 + (V1y)^2)
		// ScaleY = sqrt((V2x)^2 + (V2y)^2)
	}

	const float TransformComponent::GetAngle() const noexcept
	{
		return m_Angle;
		// return Utils::RoundToZero(atan2(m_TransformationMatrix(1, 0), m_TransformationMatrix(0, 0)));

		// [ V1x		V2x		T1 ]
		// [ V1y		V2y		T2 ]
		// [ 0			0		1  ]

		// Formula to get Angle is:
		// Angle = arctan2(V1y / V1x)
	}

	const bool TransformComponent::GetHasMoved() const noexcept
	{
		return m_HasWorldPositionChanged;
	}

	void TransformComponent::RecalculateTransformationMatrix() noexcept
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

			m_TransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		}
	}

	void TransformComponent::CalculateNewWorldPosition() noexcept
	{
		if (m_HasWorldPositionChanged)
		{
			/* Cache our local position, which we need to calculate the world position */
			Point2f newWorldPosition{ GetLocalPosition() };

			/* Get our GameObject's parent */
			GameObject* pParent{ m_pOwner->GetParent() };

			/* Check if the current parent has a parent */
			while (pParent)
			{
				/* Check if the World Position in the current parent has been updated */
				if (pParent->pTransform->m_HasWorldPositionChanged)
					return; /* If it doesn't, delay this calculation by a frame */

				/* Add the parents local position to our new world position */
				newWorldPosition += pParent->pTransform->GetLocalPosition();

				/* As soon as we reach the root, add the world position */
				if (!pParent->GetParent())
					newWorldPosition += pParent->pTransform->GetWorldPosition();

				/* Set the new parent */
				pParent = pParent->GetParent();
			}

			/* newWorldPosition is the world position from all the parent transforms
				while m_WorldPosition should be the world position set by the user */
			m_WorldPosition = Point2f{ newWorldPosition + m_WorldPosition };

			/* Flag that we've calculated our new world position */
			m_HasWorldPositionChanged = false;
		}
	}
}
