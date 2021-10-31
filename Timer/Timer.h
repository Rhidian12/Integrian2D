#pragma once

#include <chrono>

namespace Integrian2D
{
	class Timer final
	{
	public:
		/* Get a Timer instance */
		static Timer* GetInstance() noexcept;

		/* Internal Usage
		   Do NOT call this function manually */
		static void Cleanup() noexcept;

		/* Starts the Timer
		   This function gets called automatically on creation of the Timer
		   which happens just before the first Update cycle */
		void Start() noexcept;

		/* Internal Usage
		   Do NOT call this function manually */
		void Update() noexcept;

		/* Get the current FPS */
		int GetFPS() const noexcept;

		/* Get the elapsed seconds from the previous frame
		   To ensure stable code, this will never be more than 0.1f */
		float GetElapsedSeconds() const noexcept;

		/* Get how much time per frame can be spent at most */
		float GetTimePerFrame() const noexcept;

		/* Get the total amount of elapsed seconds since the start of the program */
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