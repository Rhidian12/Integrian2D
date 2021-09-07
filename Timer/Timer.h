#pragma once

#include <chrono>

namespace Integrian2D
{
	class Timer final
	{
	public:
		static Timer* GetInstance() noexcept;
		static void Cleanup() noexcept;

		void Start() noexcept;

		void Update() noexcept;

		int GetFPS() const noexcept;
		float GetElapsedSeconds() const noexcept;
		float GetTimePerFrame() const noexcept;
		float GetTotalElapsedSeconds() const noexcept;

	private:
		Timer();

		inline static Timer* m_pInstance{};

		const float m_MaxElapsedSeconds;
		float m_ElapsedSeconds;
		float m_TotalElapsedSeconds;
		int m_FPS;
		int m_FPSCounter;
		float m_FPSTimer;
		float m_TimePerFrame;

		std::chrono::steady_clock::time_point m_StartTimepoint;
		std::chrono::steady_clock::time_point m_PreviousTimepoint;
	};
}