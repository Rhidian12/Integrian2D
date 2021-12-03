#pragma once

#include "../../../Math/TypeDefines.h"

namespace Integrian2D
{
	class RigidbodyShape;

	enum class RigidbodyType
	{
		Static = 0,
		Kinematic = 1,
		Dynamic = 2,
		None = 3
	};

	struct RigidbodyDefinition final
	{
		/* The RigidbodyShape this Definition is attached to */
		RigidbodyShape* pShape{};

		/* The Rigidbody's type */
		RigidbodyType rigidbodyType{ RigidbodyType::Static };

		/* The Rigidbody's world position. Avoid making many bodies at the origin to prevent overlap issues */
		Point2f position{};

		/* The Rigidbody's world angle in radians */
		float angle{};

		/* The Rigidbody's linear velocity */
		Vector2f linearVelocity{};

		/* The Rigidbody's angular velocity */
		float angularVelocity{};

		/* Linear damping reduces linear velocity 
			This value can be larger than 1.f, but it becomes sensitive to the time step */
		float linearDamping{};

		/* Angular damping reduces angular velocity
			This value can be larger than 1.f, but it becomes sensitive to the time step */
		float angularDamping{};

		/* Set this flag to false if the body should never fall asleep (therefore collision never getting disabled) 
			Note that this decreases performance */
		bool allowSleep{ true };

		/* Is this body awake at start? */
		bool isAwake{ true };

		/* Should the body be allowed to rotate? */
		bool fixedRotation{};

		/* Is the Rigidbody a fast moving body that should be prevented from tunneling through other moving bodies?
			Note that all bodies are prevented from tunneling through kinematic and static bodies.
			This setting is only considered on dynamic bodies
			Note that this decreases performance */
		bool isBullet{};

		/* Is this body enabled at start? */
		bool isEnabled{};

		/* Scale the gravity applied to this Rigidbody */
		float gravityScale{ 1.f };
	};
}