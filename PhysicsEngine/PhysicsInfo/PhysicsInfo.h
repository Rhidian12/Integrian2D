#pragma once

#include "../../Utils/Utils.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	class ColliderComponent;

	class PhysicsInfo final
	{
	public:
		PhysicsInfo(const float _mass, const Vector2f _velocity, ColliderComponent* const _pHitbox);
		~PhysicsInfo();

#pragma region Rule Of 5
		PhysicsInfo(const PhysicsInfo& other) noexcept;
		PhysicsInfo(PhysicsInfo&& other) noexcept;
		PhysicsInfo& operator=(const PhysicsInfo& other) noexcept;
		PhysicsInfo& operator=(PhysicsInfo&& other) noexcept;
#pragma endregion

		float mass;
		Vector2f velocity;
		ColliderComponent* pHitbox;
	};
}