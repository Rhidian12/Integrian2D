#include "TransformComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Timer/Timer.h"
#include "../../TransformManager/TransformManager.h"

namespace Integrian2D
{
	TransformComponent::TransformComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_TransformChanged{}
		, m_HasWorldDataChanged{}
		, m_TransformationMatrix{}
		, m_WorldPosition{}
		, m_LocalScale{ 1.f, 1.f }
		, m_LocalAngle{}
		, m_pTransformManager{}
		, m_WorldScale{}
		, m_WorldAngle{}
	{
		const Matrix3x3 translationMatrix{ GetIdentityMatrix<3,3,float>() };

		const Matrix3x3 rotationMatrix{ GetIdentityMatrix<3,3,float>() };

		Matrix3x3 scaleMatrix{ GetIdentityMatrix<3,3,float>() };
		scaleMatrix(0, 0) = m_LocalScale.x;
		scaleMatrix(1, 1) = m_LocalScale.y;

		m_TransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	}

	Component* TransformComponent::Clone(GameObject* pOwner) noexcept
	{
		TransformComponent* pTransform{ new TransformComponent{pOwner} };

		pTransform->m_LocalScale = m_LocalScale;
		pTransform->m_LocalAngle = m_LocalAngle;
		pTransform->m_TransformChanged = m_TransformChanged;
		pTransform->m_HasWorldDataChanged = m_HasWorldDataChanged;
		pTransform->m_TransformationMatrix = m_TransformationMatrix;
		pTransform->m_WorldPosition = m_WorldPosition;
		pTransform->m_WorldAngle = m_WorldAngle;
		pTransform->m_WorldScale = m_WorldScale;

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

		m_HasWorldDataChanged = true;

		if (m_pTransformManager)
			m_pTransformManager->NotifyRecalculation();
	}

	void TransformComponent::Rotate(const float angleRadians) noexcept
	{
		m_LocalAngle += angleRadians;

		m_TransformChanged = true;
		m_HasWorldDataChanged = true;

		if (m_pTransformManager)
			m_pTransformManager->NotifyRecalculation();
	}

	void TransformComponent::Scale(const Point2f& scale) noexcept
	{
		m_LocalScale += scale;

		m_TransformChanged = true;
		m_HasWorldDataChanged = true;

		if (m_pTransformManager)
			m_pTransformManager->NotifyRecalculation();
	}

	void TransformComponent::SetPosition(const Point2f& position) noexcept
	{
		m_TransformationMatrix(0, 2) = position.x;
		m_TransformationMatrix(1, 2) = position.y;

		m_HasWorldDataChanged = true;

		if (m_pTransformManager)
			m_pTransformManager->NotifyRecalculation();
	}

	void TransformComponent::SetScale(const Point2f& scale) noexcept
	{
		m_LocalScale = scale;

		m_TransformChanged = true;
		m_HasWorldDataChanged = true;

		if (m_pTransformManager)
			m_pTransformManager->NotifyRecalculation();
	}

	void TransformComponent::SetAngle(const float angle) noexcept
	{
		m_LocalAngle = angle;

		m_TransformChanged = true;
		m_HasWorldDataChanged = true;

		if (m_pTransformManager)
			m_pTransformManager->NotifyRecalculation();
	}

	void TransformComponent::SetHasMoved(const bool hasMoved) noexcept
	{
		m_HasWorldDataChanged = hasMoved;
	}

	const Point2f& TransformComponent::GetWorldPosition() const noexcept
	{
		return m_WorldPosition;
	}

	const Point2f TransformComponent::GetLocalPosition() const noexcept
	{
		return Point2f{ m_TransformationMatrix(0,2), m_TransformationMatrix(1,2) };

		// We can just extract this from the Matrix
	}

	const Point2f& TransformComponent::GetWorldScale() const noexcept
	{
		return m_WorldScale;
	}

	const float TransformComponent::GetWorldAngle() const noexcept
	{
		return m_WorldAngle;
	}

	const Point2f& TransformComponent::GetLocalScale() const noexcept
	{
		return m_LocalScale;

		//return Point2f{ sqrtf(powf(m_TransformationMatrix(0,0), 2) + powf(m_TransformationMatrix(1,0), 2)),
		//				sqrtf(powf(m_TransformationMatrix(0,1), 2) + powf(m_TransformationMatrix(1,1), 2)) };

		// [ V1x		V2x		T1 ]
		// [ V1y		V2y		T2 ]
		// [ 0			0		1  ]

		// Formula to get Scale is:
		// ScaleX = sqrt((V1x)^2 + (V1y)^2)
		// ScaleY = sqrt((V2x)^2 + (V2y)^2)
	}

	const float TransformComponent::GetLocalAngle() const noexcept
	{
		return m_LocalAngle;
		// return Utils::RoundToZero(atan2(m_TransformationMatrix(1, 0), m_TransformationMatrix(0, 0)));

		// [ V1x		V2x		T1 ]
		// [ V1y		V2y		T2 ]
		// [ 0			0		1  ]

		// Formula to get Angle is:
		// Angle = arctan2(V1y / V1x)
	}

	const bool TransformComponent::GetHasMoved() const noexcept
	{
		return m_HasWorldDataChanged;
	}

	void TransformComponent::RecalculateTransformationMatrix() noexcept
	{
		if (m_TransformChanged)
		{
			m_TransformChanged = false;

			Matrix3x3 translationMatrix{ GetIdentityMatrix<3,3,float>() };
			translationMatrix(0, 2) = m_TransformationMatrix(0, 2);
			translationMatrix(1, 2) = m_TransformationMatrix(1, 2);

			const float c{ cos(m_LocalAngle) };
			const float s{ sin(m_LocalAngle) };
			Matrix3x3 rotationMatrix{ GetIdentityMatrix<3,3,float>() };
			rotationMatrix(0, 0) = c;
			rotationMatrix(0, 1) = -s;
			rotationMatrix(1, 0) = s;
			rotationMatrix(1, 1) = c;

			Matrix3x3 scaleMatrix{ GetIdentityMatrix<3,3,float>() };
			scaleMatrix(0, 0) = m_LocalScale.x;
			scaleMatrix(1, 1) = m_LocalScale.y;

			m_TransformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
		}
	}

	void TransformComponent::RecalculateWorldData() noexcept
	{
		if (m_HasWorldDataChanged)
		{
			/* Cache our local position, which we need to calculate the world position */
			Point2f worldPosition{ GetLocalPosition() };
			Point2f worldScale{ GetLocalScale() };
			float worldAngle{ GetLocalAngle() };

			/* Get our GameObject's parent */
			GameObject* pParent{ m_pOwner->GetParent() };

			/* Check if the current parent has a parent */
			while (pParent)
			{
				/* Check if the World Position in the current parent has been updated */
				if (pParent->pTransform->m_HasWorldDataChanged)
					return; /* If it doesn't, delay this calculation by a frame */

				/* Add the parents local position to our new world position */
				worldPosition += pParent->pTransform->GetLocalPosition();
				worldScale += pParent->pTransform->GetLocalScale();
				worldAngle += pParent->pTransform->GetLocalAngle();

				/* As soon as we reach the root, add the world position */
				// if (!pParent->GetParent())
				// 	worldPosition += pParent->pTransform->GetLocalPosition();

				/* Set the new parent */
				pParent = pParent->GetParent();
			}

			/* newWorldPosition is the world position from all the parent transforms
				while m_WorldPosition should be the world position set by the user */
			m_WorldPosition = worldPosition;
			m_WorldAngle = worldAngle;
			m_WorldScale = worldScale;

			/* Flag that we've calculated our new world position */
			m_HasWorldDataChanged = false;
		}
	}
}
