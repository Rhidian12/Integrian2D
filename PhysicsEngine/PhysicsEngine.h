#pragma once

#include "../Math/TypeDefines.h"
#include "PhysicsInfo/PhysicsInfo.h"

#include <box2d.h>

#include <vector>

namespace Integrian2D
{
	class PhysicsComponent;

	/* TODO: Document this class once it's done */
	class PhysicsEngine final
	{
	public:
		void FixedUpdate() noexcept;

		void AddPhysicsComponent(PhysicsComponent* const pComponent) noexcept;
		void RemovePhysicsComponent(PhysicsComponent* const pComponent) noexcept;

		void SetGravity(const Vector2f& gravity) noexcept;
		const Vector2f& GetGravity() const noexcept;

	private:
		friend class Scene;

		PhysicsEngine();

		std::vector<PhysicsComponent*> m_pComponents;
		Vector2f m_Gravity;

		b2World m_PhysicsWorld;
	};
}