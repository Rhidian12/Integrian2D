#pragma once

#include <stdint.h>

namespace Integrian2D
{
	class RigidbodyShape;

	struct RigidbodyCollisionFilter final
	{
		/* The collision category bits. Normally the user sets only 1 bit */
		uint16_t categoryBits{ 0x0001 };

		/* The actual collision mask bits. This mask states the categories that the fixture should accept for collision */
		uint16_t maskBits{ 0xFFFF };

		/* Collision groups allows a group of objects to never collide or to always collide
			Zero means there is no collision group, any non-zero group filtering always takes precedence over the mask bits */
		int16_t groupIndex{};
	};

	struct RigidbodyFixture final
	{
	public:
		/* The RigidbodyShape this Fixture is attached to */
		RigidbodyShape* pShape{};

		/* The friction coefficient. This is usually in the range [0, 1] */
		float friction{ 0.2f };

		/* The restitution (elasticity). This is usually in the range [0, 1] */
		float restitution{};

		/* Restitution velocity treshold. This is measured in m/s
			Collisions above this treshold have restitution applied (meaning it will bounce) */
		float restitutionThreshold{ 1.f };

		/* The density. This is measured in kg/m^2 */
		float density{};

		/* If the RigidbodyFixture is a trigger, it will collect data, but will not generate collisions */
		bool isTrigger{};

		/* Contact filter */
		RigidbodyCollisionFilter filter;
	};
}