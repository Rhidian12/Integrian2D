#pragma once

#include "../Math/TypeDefines.h"
#include "PhysicsInfo/PhysicsInfo.h"

namespace Integrian2D
{
	class PhysicsEngine final
	{
	public:


	private:
		PhysicsEngine() = default;

		struct PhysicsInfo final
		{
			float mass;
			Vector2f velocity;
		};
	};
}