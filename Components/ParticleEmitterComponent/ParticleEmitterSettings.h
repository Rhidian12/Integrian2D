#pragma once

#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	struct ParticleEmitterSettings final
	{
		/* The minimum size each particle can be when it is spawned */
		float minimumSpawnSize{ 0.1f };

		/* The maximum size each particle can be when it is spawned */
		float maximumSpawnSize{ 2.f };

		/* The minimum lifetime of each particle, measured in seconds */
		float minimumTime{ 1.f };

		/* The maximum lifetime of each particle, measured in seconds */
		float maximumTime{ 2.f };

		/* The starting velocity of the particles, this should be a normalized vector
			Note that the particles will deviate from this velocity */
		Vector2f startingVelocity{};

		/* The maximum radius that the particles are spawned in */
		float minimumEmitterRange{ 9.f };

		/* The maximum radius that the particles are spawned in */
		float maximumEmitterRange{ 10.f };

		/* The percentual minimum change in size during the particle's lifetime */
		float minimumSizeGrow{ 1.f };

		/* The percentual maximum change in size during the particle's lifetime */
		float maximumSizeGrow{ 1.f };

		/* The interval between each spawned particle (ie how many seconds per particle spawn) */
		float spawnInterval{ 1.f };

		/* The maximum amount of particles to spawn */
		int maximumNumberOfParticles{ 50 };

		/* The colour of each particle */
		RGBColour colour{ Colours::White };
	};
}