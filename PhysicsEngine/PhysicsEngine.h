#pragma once

#include "../Math/TypeDefines.h"

#include <box2d.h>

#include <vector>

namespace Integrian2D
{
	class RigidbodyComponent;

	/* TODO: Document this class once it's done */
	class PhysicsEngine final
	{
	public:
		~PhysicsEngine();

		void FixedUpdate() noexcept;

		b2Body* const AddPhysicsComponent(RigidbodyComponent* const pComponent) noexcept;
		void RemovePhysicsComponent(RigidbodyComponent* const pComponent) noexcept;

		void SetGravity(const Vector2f& gravity) noexcept;
		const Vector2f& GetGravity() const noexcept;

		inline static float PixelsPerMeter{ 100.f };

	private:
		friend class Scene;

		PhysicsEngine();

		std::vector<RigidbodyComponent*> m_pComponents;
		Vector2f m_Gravity;

		b2World m_PhysicsWorld;
	};
}