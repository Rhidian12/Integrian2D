#pragma once

#include "../../Utils/Utils.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	class ColliderComponent;

	/* TODO: Document this once PhysicsEngine is complete */
	class PhysicsInfo final
	{
	public:
		PhysicsInfo(const float _mass, const Vector2f _velocity, ColliderComponent* const _pHitbox, const bool _gravity = true);

#pragma region Rule Of 5
		PhysicsInfo(const PhysicsInfo& other) = default;
		PhysicsInfo(PhysicsInfo&& other) = default;
		PhysicsInfo& operator=(const PhysicsInfo& other) = default;
		PhysicsInfo& operator=(PhysicsInfo&& other) = default;
#pragma endregion

		bool gravity;
		float mass;
		Vector2f velocity;
		ColliderComponent* pHitbox;
	};
}