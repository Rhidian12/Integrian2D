#include "ThreadManager.h"
#include "../Utils/Utils.h"

#include <iostream>
#include <algorithm>

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

	void ThreadManager::AssignThreadTask(const ThreadJob& task, const int id) noexcept
	{
		{
			std::unique_lock<std::mutex> lock{ m_Mutex }; // acquire the mutex
			m_Tasks.push_back(ThreadTask{ task, static_cast<int>(m_Tasks.size() - 1), id, false });
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

	const std::vector<ThreadTask>& ThreadManager::GetThreadTasks() const noexcept
	{
		return m_Tasks;
	}

	bool ThreadManager::IsJobBeingExecuted(const int userID) const noexcept
	{
		const auto it = std::find_if(m_Tasks.cbegin(), m_Tasks.cend(), [this, userID](const ThreadTask& t)->bool
			{
				return userID == t.userID;
			});

		if (it != m_Tasks.cend())
			return it->isBusy;
		else
			return false;
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
			ThreadTask* pTask{};
			{
				std::unique_lock<std::mutex> lock{ m_Mutex }; // acquire lock

				m_CV.wait(lock, [this]()
					{
						return !g_IsLooping || std::find_if(m_Tasks.cbegin(), m_Tasks.cend(), [this](const ThreadTask& t)->bool
							{
								return !t.isBusy;
							}) != m_Tasks.cend(); // Wait until the program has ended OR there is a task to be executed
					});

				if (!g_IsLooping)
					break; // if the program has ended, break out of the task

				if (!m_Tasks.empty()) // safety check
				{
					m_AreJobsDone[index] = false; // Flag that we're doing a task

					for (ThreadTask& t : m_Tasks)
					{
						if (!t.isBusy)
						{
							pTask = &t;
							break;
						}
					}
					
					//m_Tasks.pop(); // remove the task from the queue
					pTask->isBusy = true; // flag that the task is being done
					pTask->threadIndex = index;
				}
			} // let the lock go out of scope

			if (pTask) // if we have a task
				if (pTask->job)
					pTask->job(); // execute the task

			{ // the job has been finished
				std::unique_lock<std::mutex> lock{ m_Mutex }; // re-acquire lock
				m_AreJobsDone[index] = true; // flag the job to be complete

				m_Tasks.erase(std::remove_if(m_Tasks.begin(), m_Tasks.end(), [this, pTask](const ThreadTask& t)->bool
					{
						return *pTask == t;
					}), m_Tasks.end());
			}
		}
	}
}