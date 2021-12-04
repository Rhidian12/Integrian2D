#include "SceneManager.h"
#include "../Utils/Utils.h"
#include "../Scene/Scene.h"
#include "../Logger/Logger.h"
#include "../Core/Core.h"

namespace Integrian2D
{
	SceneManager* const SceneManager::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new SceneManager{};

		return m_pInstance;
	}

	void SceneManager::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	SceneManager::~SceneManager()
	{
		for (std::pair<const std::string, Scene*>& pScene : m_pScenes)
			Utils::SafeDelete(pScene.second);
	}

	void SceneManager::AddScene(Scene* const pScene) noexcept
	{
		const std::string& sceneName{ pScene->GetSceneName() };
		std::unordered_map<std::string, Scene*>::const_iterator cIt{ m_pScenes.find(sceneName) };

		if (cIt == m_pScenes.cend())
		{
			m_pScenes.insert(std::make_pair(sceneName, pScene));

			if (!m_pActiveScene)
				SetActiveScene(sceneName);
		}
	}

	void SceneManager::SetActiveScene(const std::string& sceneName) noexcept
	{
		const std::unordered_map<std::string, Scene*>::const_iterator cIt{ m_pScenes.find(sceneName) };

		if (cIt != m_pScenes.cend())
		{
			/* Let the current active scene exit */
			if (m_pActiveScene)
			{
				m_pActiveScene->m_IsActive = false;

				m_pActiveScene->RootOnSceneExit();
				m_pActiveScene->OnSceneExit();
			}

			m_pActiveScene = cIt->second;

			/* Let the new active scene enter */
			m_pActiveScene->m_IsActive = true;

			m_pActiveScene->RootOnSceneEnter();
			m_pActiveScene->OnSceneEnter();
		}
	}

	void SceneManager::DeactivateAllScenes() noexcept
	{
		for (const std::pair<std::string, Scene*> pair : m_pScenes)
			pair.second->m_IsActive = false;
	}

	Scene* const SceneManager::GetActiveScene() const noexcept
	{
		return m_pActiveScene;
	}

	Scene* const SceneManager::GetScene(const std::string& sceneName) const noexcept
	{
		const std::unordered_map<std::string, Scene*>::const_iterator cIt{ m_pScenes.find(sceneName) };

		if (cIt != m_pScenes.cend())
			return cIt->second;
		else
			return nullptr;
	}

	const std::unordered_map<std::string, Scene*>& SceneManager::GetScenes() const noexcept
	{
		return m_pScenes;
	}

	SceneManager::SceneManager()
		: m_pActiveScene{}
		, m_pScenes{}
	{
	}
}
