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
		else
			Logger::LogWarning(std::string{ "SceneManager::AddScene() > Scene with name: " } + pScene->GetSceneName() + " is already present!");
	}

	Scene* const SceneManager::GetActiveScene() const noexcept
	{
		return m_pActiveScene;
	}

	Scene* const SceneManager::GetScene(std::string sceneName) const noexcept
	{
		std::unordered_map<std::string, Scene*>::const_iterator cIt{ m_pScenes.find(sceneName) };

		if (cIt != m_pScenes.cend())
			return cIt->second;
		else
		{
			Logger::LogWarning(std::string{ "SceneManager::GetScene() > Scene with name: " } + sceneName + " is not present!");
			return nullptr;
		}
	}

	SceneManager::SceneManager()
		: m_pActiveScene{}
		, m_pScenes{}
	{
	}
}
