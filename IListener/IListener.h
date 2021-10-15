#pragma once
namespace Integrian2D
{
	class IListener
	{
	public:
		virtual ~IListener() = default;

		virtual bool OnEvent(const Event&) = 0;

		bool m_IsActive;
	};
}