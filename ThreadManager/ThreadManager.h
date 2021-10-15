#pragma once

// Reference: https://stackoverflow.com/questions/15752659/thread-pooling-in-c11

#include <thread> // std::thread
#include <vector> // std::vector
#include <mutex> // std::mutex, std::unique_lock
#include <queue> // std::queue
#include <functional> // std::function
#include <type_traits> // std::is_assignable_v

namespace Integrian2D
{
	class ThreadManager final
	{
	public:
		using ThreadTask = std::function<void()>;

		~ThreadManager();

		static void CreateThreadManager(const int amountOfThreads) noexcept;
		static ThreadManager* const GetInstance() noexcept;
		static void Cleanup() noexcept;

		void AssignThreadTask(const ThreadTask& task) noexcept;

		bool AreAllTasksCompleted() const noexcept;
		const std::queue<ThreadTask>& GetThreadTasks() const noexcept;

	private:
		ThreadManager(const int amountOfThreads);
		void InfiniteLoop(const int index) noexcept;

		std::vector<std::thread> m_Threads;
		std::vector<bool> m_AreJobsDone;
		std::queue<ThreadTask> m_Tasks;
		std::mutex m_Mutex;
		std::condition_variable m_CV;

		inline static ThreadManager* m_pInstance{};
	};
}