#pragma once

#include "../Math/TypeDefines.h"
#include "PhysicsInfo/PhysicsInfo.h"

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

		void SetGravity(const float gravity) noexcept;
		float GetGravity() const noexcept;

	private:
		friend class Scene;

		PhysicsEngine();

		std::vector<PhysicsComponent*> m_pComponents;
		float m_Gravity;
	};
}