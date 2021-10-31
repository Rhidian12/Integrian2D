#include "Utils.h"

#include <iostream>

namespace Integrian2D
{
	namespace Utils
	{

		void Assert(const bool expression, const std::string& message)
		{
#ifdef _DEBUG
			if (!expression)
			{
				std::cout << message;
				std::abort();
			}
#else
			(void)expression;
			(void)message;
#endif // _DEBUG
		}
	}
}