#include "PhysicsInfo.h"

#include <utility>

namespace Integrian2D
{
	PhysicsInfo::~PhysicsInfo()
	{
		Utils::SafeDelete(pHitbox);
	}

	PhysicsInfo::PhysicsInfo(const PhysicsInfo& other) noexcept
		: mass{ other.mass }
		, velocity{ other.velocity }
		, pHitbox{ new PhysicsInfoImpl{*other.pHitbox} }
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
		pHitbox = new PhysicsInfoImpl{ *other.pHitbox };

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