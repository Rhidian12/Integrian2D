#include "SceneManager.h"

namespace Integrian2D
{
	SceneManager::SceneManager()
		: m_Scenes{}
		, m_pActiveScene{}
	{}

	SceneManager::~SceneManager()
	{
		for (Scene* pScene : m_Scenes)
			__DELETE(pScene);

		m_Scenes.Clear();
	}

	SceneManager& SceneManager::GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = std::make_unique<SceneManager>();

		return *m_pInstance.get();
	}

	void SceneManager::AddScene(Scene* pScene)
	{
		m_Scenes.Add(pScene);

		if (!m_pActiveScene)
			m_pActiveScene = pScene;
	}

	void SceneManager::ChangeScene(const std::string_view sceneName)
	{
		const auto cIt{ m_Scenes.Find([sceneName](const Scene* const pScene)->bool
			{
				return pScene->GetSceneName() == sceneName;
			}) };

		__ASSERT(cIt != m_Scenes.cend() && "SceneManager::ChangeScene() > No scene with the specified name was found");

		m_pActiveScene->__OnSceneExit();
		m_pActiveScene->OnSceneExit();

		m_pActiveScene = *cIt;

		m_pActiveScene->__OnSceneEnter();
		m_pActiveScene->OnSceneEnter();
	}

	Scene* const SceneManager::GetScene(const std::string_view sceneName)
	{
		const auto it{ m_Scenes.Find([sceneName](const Scene* const pScene)->bool
			{
				return pScene->GetSceneName() == sceneName;
			}) };

		__ASSERT(it != m_Scenes.cend() && "SceneManager::GetScene() > No scene with the specified name was found");

		return *it;
	}

	const Scene* const SceneManager::GetScene(const std::string_view sceneName) const
	{
		const auto cIt{ m_Scenes.Find([sceneName](const Scene* const pScene)->bool
			{
				return pScene->GetSceneName() == sceneName;
			}) };

		__ASSERT(cIt != m_Scenes.cend() && "SceneManager::ChangeScene() > No scene with the specified name was found");

		return *cIt;
	}
	
	const Array<Scene*>& SceneManager::GetScene() const
	{
		return m_Scenes;
	}
}