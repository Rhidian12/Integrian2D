#include "Math.h"

namespace Integrian2D::Math
{
	void SetSeed(const size_t seed)
	{
		Detail::Seed = seed;
		Detail::RNGEngine = std::mt19937{ seed };
	}
}