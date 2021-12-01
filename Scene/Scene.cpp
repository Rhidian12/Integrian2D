#include "Scene.h"
#include "../Utils/Utils.h"
#include "../Logger/Logger.h"
#include "../GameObject/GameObject.h"
#include "../TransformManager/TransformManager.h"
#include "../ThreadManager/ThreadManager.h"

extern bool volatile g_IsLooping;

namespace Integrian2D
{
	Scene::Scene(const std::string& sceneName)
		: m_SceneName{ sceneName }
		, m_pGameObjects{}
		, m_TransformManager{}
	{
		ThreadManager::GetInstance()->AssignThreadTask([this]()
			{
				ThreadManager* const pInstance{ ThreadManager::GetInstance() };

				while (g_IsLooping)
				{
					pInstance->SleepThreadWhile([this]()->bool
						{
							return m_TransformManager.ShouldRecalculate();
						});

					m_TransformManager.UpdateTransforms();
				}
			});
	}

	Scene::~Scene()
	{
		for (std::pair<const std::string, GameObject*>& pG : m_pGameObjects)
			Utils::SafeDelete(pG.second);
	}

	void Scene::RootStart()
	{
		for (const std::pair<const std::string, GameObject*>& pG : m_pGameObjects)
			pG.second->Start();
	}

	void Scene::RootUpdate()
	{
		for (const std::pair<const std::string, GameObject*>& pG : m_pGameObjects)
			pG.second->Update();
	}

	void Scene::RootFixedUpdate()
	{
		for (const std::pair<const std::string, GameObject*>& pG : m_pGameObjects)
			pG.second->FixedUpdate();
	}

	void Scene::RootLateUpdate()
	{
		for (const std::pair<const std::string, GameObject*>& pG : m_pGameObjects)
			pG.second->LateUpdate();
	}

	void Scene::RootRender() const
	{
		for (const std::pair<const std::string, GameObject*>& pG : m_pGameObjects)
			pG.second->Render();
	}

	void Scene::RootOnSceneEnter() noexcept
	{
		inputManager.Activate();
	}

	void Scene::RootOnSceneExit() noexcept
	{
		inputManager.Deactivate();
	}

	void Scene::AddGameObject(const std::string& gameObjectName, GameObject* const pGameObject, const bool shouldAlwaysAdd) noexcept
	{
		const std::unordered_map<std::string, GameObject*>::const_iterator cIt{ m_pGameObjects.find(gameObjectName) };

		if (cIt == m_pGameObjects.cend())
		{
			m_pGameObjects.insert(std::make_pair(gameObjectName, pGameObject));
			m_TransformManager.AddTransformComponent(pGameObject->pTransform);
		}
		else if (shouldAlwaysAdd)
		{
			std::string newName{};
			for (size_t i{}; i < m_pGameObjects.size() + 1; ++i)
			{
				newName = gameObjectName + "(" + std::to_string(i) + ")";

				if (m_pGameObjects.find(newName) == m_pGameObjects.cend())
					break;
			}

			Logger::LogWarning(std::string{ "Scene::AddGameObject() > The Name: " } + gameObjectName + " was already present and has been changed to: "
				+ newName);

			m_pGameObjects.insert(std::make_pair(newName, pGameObject));
			m_TransformManager.AddTransformComponent(pGameObject->pTransform);
		}
	}

	void Scene::SetSceneName(const std::string& sceneName) noexcept
	{
		m_SceneName = sceneName;
	}

	GameObject* const Scene::GetGameObject(const std::string& gameObjectName) const noexcept
	{
		const std::unordered_map<std::string, GameObject*>::const_iterator cIt{ m_pGameObjects.find(gameObjectName) };

		if (cIt != m_pGameObjects.cend())
			return cIt->second;
		else
		{
			Logger::LogWarning(std::string{ "Scene::GetGameObject() > GameObject with name: " } + gameObjectName + " is not present! Returning nullptr!");
			return nullptr;
		}
	}

	const std::unordered_map<std::string, GameObject*> Scene::GetGameObjects() const noexcept
	{
		return m_pGameObjects;
	}

	const std::string& Scene::GetSceneName() const noexcept
	{
		return m_SceneName;
	}
}
