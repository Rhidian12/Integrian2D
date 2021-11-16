#include "SceneManager.h"
#include "../Utils/Utils.h"
#include "../Scene/Scene.h"
#include "../Logger/Logger.h"

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
		std::unordered_map<std::string, Scene*>::const_iterator cIt{ m_pScenes.find(pScene->GetSceneName()) };

		if (cIt == m_pScenes.cend())
		{
			m_pScenes.insert(std::make_pair(pScene->GetSceneName(), pScene));

			if (!m_pActiveScene)
				m_pActiveScene = pScene;
		}
	}

	void SceneManager::SetActiveScene(const std::string& sceneName) noexcept
	{
		const std::unordered_map<std::string, Scene*>::const_iterator cIt{ m_pScenes.find(sceneName) };

		if (cIt != m_pScenes.cend())
		{
			/* Let the current active scene exit */
			m_pActiveScene->RootOnSceneExit();
			m_pActiveScene->OnSceneExit();

			m_pActiveScene = cIt->second;

			/* Let the new active scene enter */
			m_pActiveScene->RootOnSceneEnter();
			m_pActiveScene->OnSceneEnter();
		}
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
