#include "Locator.h"
#include "../Utils/Utils.h"
#include "../SceneManager/SceneManager.h"
#include "../Scene/Scene.h"

namespace Integrian2D
{
	Locator* Locator::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new Locator{};

		return m_pInstance;
	}

	void Locator::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	InputManager* const Locator::GetInputManager() const noexcept
	{
		return &SceneManager::GetInstance()->GetActiveScene()->inputManager;
	}

	PhysicsEngine* const Locator::GetPhysicsEngine() const noexcept
	{
		return &SceneManager::GetInstance()->GetActiveScene()->physicsEngine;
	}
	
	EventQueue* const Locator::GetEventQueue() const noexcept
	{
		return &SceneManager::GetInstance()->GetActiveScene()->eventQueue;
	}
}