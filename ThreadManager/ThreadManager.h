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
	/* As with EVERYTHING concerning multi-threading, this is VERY USER-RELIANT
	   This ThreadManager is a combination of a thread pool and a job system 
	   The thread pool is only as large as std::thread::hardware_concurrency() recommends 
	   If you do not know what that means, then I highly recommend you first read what those are before you use this class */
	class ThreadManager final
	{
	public:
		/* This is the signature any job must have */
		using ThreadTask = std::function<void()>;

		~ThreadManager();

		/* Get a ThreadManager instance */
		static ThreadManager* const GetInstance() noexcept;

		/* Internal Usage
		   Do NOT call this function manually */
		static void Cleanup() noexcept;

		/* Assign a job to a thread */
		void AssignThreadTask(const ThreadTask& task) noexcept;

		/* Check if all assigned jobs have been completed */
		bool AreAllTasksCompleted() const noexcept;

		/* Get all jobs that have not been processed yet */
		const std::queue<ThreadTask>& GetThreadTasks() const noexcept;

		void SleepThreadWhile(const std::function<bool()>& predicate) const noexcept;

	private:
		ThreadManager();
		void InfiniteLoop(const int index) noexcept;

		std::vector<std::thread> m_Threads;
		std::vector<bool> m_AreJobsDone;
		std::queue<ThreadTask> m_Tasks;
		std::mutex m_Mutex;
		std::condition_variable m_CV;

		inline static ThreadManager* m_pInstance{};
	};
}