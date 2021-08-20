#include "Utils.h"

#include <iostream>

namespace Integrian2D
{
	namespace Utils
	{

#ifdef _DEBUG
		void Assert(const bool expression, std::string message)
		{
			if (!expression)
			{
				std::cout << message;
				std::abort();
			}
		}
#else
		void Assert(const bool expression, std::string message)
		{
			(void)expression;
			(void)message;
		}
#endif // _DEBUG
	}
}