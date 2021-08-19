#pragma once

#ifndef INTEGRIAN2D_UTILS_H
#define INTEGRIAN2D_UTILS_H

#include <type_traits>

namespace Integrian2D
{
	namespace Utils
	{
		// == Templated Functions ==
		template<typename Pointer>
		void SafeDelete(Pointer*& pData)
		{
			delete pData;
			pData = nullptr;
		}
	}
}

#endif // !INTEGRIAN2D_UTILS_H