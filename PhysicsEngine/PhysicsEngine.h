#pragma once

#include "../Math/TypeDefines.h"
#include "PhysicsInfo/PhysicsInfo.h"

#include <unordered_map>

namespace Integrian2D
{
	class GameObject;

	class PhysicsEngine final
	{
	public:
		void AddGameObject(GameObject* const pGameObject, const float mass, const Vector2f velocity) noexcept;

	private:
		PhysicsEngine() = default;

		std::unordered_map<GameObject*, PhysicsInfo> m_pGameObjects;
	};
}