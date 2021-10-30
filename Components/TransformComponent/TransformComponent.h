#pragma once

#include "../Component/Component.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pOwner);

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		virtual void FixedUpdate() override;

		/* Return the GameObject's position in World Space */
		const Point2f& GetWorldPosition() noexcept;

		/* Return the GameObject's position in its Local Space */
		const Point2f GetLocalPosition() const noexcept;

		/* Translates the GameObject's position by velocity multiplied by Delta Time. This does not trigger a matrix recalculation */
		void Translate(const Vector2f& velocity) noexcept;

		/* Rotates the GameObject by angleRadians. This triggers a matrix recalculation */
		void Rotate(const float angleRadians) noexcept;

		/* Scales the GameObject by scale. This triggers a matrix recalculation */
		void Scale(const Point2f& scale) noexcept;

		/* Sets the GameObject's position. This neither translates the GameObject nor triggers a matrix recalculation */
		void SetPosition(const Point2f& position) noexcept;

		/* Sets the GameObject's scale. This triggers a matrix recalculation */
		void SetScale(const Point2f& scale) noexcept;

		/* Sets the GameObject's angle. This triggers a matrix recalculation */
		void SetAngle(const float angle) noexcept;

		/* This function should NOT be called manually. It is called internally and calling this manually will only waste CPU cycles. 
		   This function checks if its parent local position has changed. If it has, it must recalculate its world position */
		void CalculateNewWorldPosition() noexcept;

		void SetHasMoved(const bool hasMoved) noexcept;

		const Point2f& GetScale() const noexcept;
		const float GetAngle() const noexcept;
		const bool GetHasMoved() const noexcept;

	private:
		void RecalculateTransformationMatrix() noexcept;

		bool m_TransformChanged;
		bool m_HasWorldPositionChanged;

		Matrix3x3 m_TransformationMatrix;

		Point2f m_WorldPosition;
		
		Point2f m_Scale;
		float m_Angle; // Radians
	};
}

