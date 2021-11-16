#include "PhysicsInfo.h"

#include <utility>

namespace Integrian2D
{
	PhysicsInfo::PhysicsInfo(const float _mass, const float _drag, const Vector2f& _velocity, ColliderComponent* const _pHitbox, const bool _gravity)
		: gravity{ _gravity }
		, mass{ _mass }
		, drag{ _drag }
		, velocity{ _velocity }
		, pHitbox{ _pHitbox }
	{}
}