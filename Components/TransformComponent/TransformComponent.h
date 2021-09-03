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

		void Translate(const Vector2f& velocity) noexcept;
		void Rotate(const float angleRadians) noexcept;

		void SetPosition(const PRectf destRect) noexcept;
		void SetScale(const Point2f scale) noexcept;
		void SetAngle(const float angle) noexcept;

		const PRectf& GetDestRect() const noexcept;
		const Point2f& GetScale() const noexcept;
		const float GetAngle() const noexcept;

	private:
		bool m_TransformChanged;
		PRectf m_DestRect;
		Point2f m_Scale;
		float m_Angle; // Radians
	};
}

