#include "ThreadManager.h"
#include "../Utils/Utils.h"

extern bool volatile g_IsLooping;

namespace Integrian2D
{
	ThreadManager::~ThreadManager()
	{
		m_CV.notify_all(); // alert all threads

		for (std::thread& thread : m_Threads)
			thread.join(); // make the thread finish its job and quit

		m_Threads.clear();
	}

	ThreadManager* const ThreadManager::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new ThreadManager{};

		return m_pInstance;
	}

	void ThreadManager::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	void ThreadManager::AssignThreadTask(const ThreadTask& task) noexcept
	{
		{
			std::unique_lock<std::mutex> lock{ m_Mutex }; // acquire the mutex
			m_Tasks.push(task);
		} // Release the mutex

		m_CV.notify_one(); // alert a waiting thread
	}

	bool ThreadManager::AreAllTasksCompleted() const noexcept
	{
		for (const bool isJobDone : m_AreJobsDone)
			if (!isJobDone)
				return false;

		return true;
	}

	const std::queue<ThreadManager::ThreadTask>& ThreadManager::GetThreadTasks() const noexcept
	{
		return m_Tasks;
	}

	ThreadManager::ThreadManager()
		: m_Threads{}
		, m_AreJobsDone{}
		, m_Tasks{}
		, m_Mutex{}
		, m_CV{}
	{
		for (size_t i{}; i < std::thread::hardware_concurrency(); ++i)
		{
			m_Threads.push_back(std::thread{ std::bind(&ThreadManager::InfiniteLoop, this, static_cast<int>(i)) });
			m_AreJobsDone.push_back(true);
		}
	}

	void ThreadManager::InfiniteLoop(const int index) noexcept
	{
		while (g_IsLooping)
		{
			ThreadTask task{};
			{
				std::unique_lock<std::mutex> lock{ m_Mutex }; // acquire lock

				m_CV.wait(lock, [this]()
					{
						return !g_IsLooping || !m_Tasks.empty(); // Wait until the program has ended OR there is a task to be executed
					});

				if (!g_IsLooping)
					break; // if the program has ended, break out of the task

				if (!m_Tasks.empty()) // safety check
				{
					m_AreJobsDone[index] = false; // Flag that we're doing a task
					task = m_Tasks.front(); // get the task
					m_Tasks.pop(); // remove the task from the queue
				}
			} // let the lock go out of scope

			if (task) // if we have a task
				task(); // execute the task

			{ // the job has been finished
				std::unique_lock<std::mutex> lock{ m_Mutex }; // re-acquire lock
				m_AreJobsDone[index] = true; // flag the job to be complete
			}
		}
	}
}