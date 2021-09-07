#include "PhysicsInfo.h"

#include <utility>

namespace Integrian2D
{
	PhysicsInfo::PhysicsInfo(const float _mass, const Vector2f _velocity, ColliderComponent* const _pHitbox)
		: mass{ _mass }
		, velocity{ _velocity }
		, pHitbox{ _pHitbox }
	{}

	PhysicsInfo::PhysicsInfo(const PhysicsInfo& other) noexcept
		: mass{ other.mass }
		, velocity{ other.velocity }
		, pHitbox{ other.pHitbox }
	{}

	PhysicsInfo::PhysicsInfo(PhysicsInfo&& other) noexcept
		: mass{ std::move(other.mass) }
		, velocity{ std::move(other.velocity) }
		, pHitbox{ std::move(other.pHitbox) }
	{
		other.pHitbox = nullptr;
	}

	PhysicsInfo& PhysicsInfo::operator=(const PhysicsInfo& other) noexcept
	{
		mass = other.mass;
		velocity = other.velocity;
		pHitbox = other.pHitbox;

		return *this;
	}

	PhysicsInfo& PhysicsInfo::operator=(PhysicsInfo&& other) noexcept
	{
		mass = std::move(other.mass);
		velocity = std::move(other.velocity);
		pHitbox = std::move(other.pHitbox);

		other.pHitbox = nullptr;

		return *this;
	}
}