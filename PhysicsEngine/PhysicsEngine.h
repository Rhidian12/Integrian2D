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
		void FixedUpdate() noexcept;

		void AddPhysicsComponent(RigidbodyComponent* const pComponent, const b2BodyDef& body, const b2FixtureDef& fixture) noexcept;
		void RemovePhysicsComponent(RigidbodyComponent* const pComponent) noexcept;

		void SetGravity(const Vector2f& gravity) noexcept;
		const Vector2f& GetGravity() const noexcept;

	private:
		friend class Scene;

		PhysicsEngine();

		std::vector<RigidbodyComponent*> m_pComponents;
		Vector2f m_Gravity;

		b2World m_PhysicsWorld;
	};
}