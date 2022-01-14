#include "Scene.h"
#include "../Utils/Utils.h"
#include "../Logger/Logger.h"
#include "../GameObject/GameObject.h"
#include "../TransformManager/TransformManager.h"
#include "../ThreadManager/ThreadManager.h"
#include "../Input/InputManager/InputManager.h"
#include "../IListener/IListener.h"
#include "../Components/Component/Component.h"

#include <string>
#include <vector>

namespace Integrian2D
{
	struct Scene::SceneImpl final
	{
		std::string m_SceneName;
		std::vector<GameObjectInformation> m_GameObjects;
		std::atomic_bool m_IsActive;

		TransformManager m_TransformManager;
	};

	Scene::Scene(const char* pSceneName)
		: m_pSceneImpl{ new SceneImpl{} }
	{
		m_pSceneImpl->m_SceneName = pSceneName;
	}

	Scene::~Scene()
	{
		m_pSceneImpl->m_IsActive = false;

		for (GameObjectInformation& pG : m_pSceneImpl->m_GameObjects)
			Utils::SafeDelete(pG.pGameObject);

		Utils::SafeDelete(m_pSceneImpl);
	}

	void Scene::RootStart()
	{
		for (GameObjectInformation& pG : m_pSceneImpl->m_GameObjects)
			pG.pGameObject->Start();
	}

	void Scene::RootUpdate()
	{
		for (GameObjectInformation& pG : m_pSceneImpl->m_GameObjects)
			pG.pGameObject->Update();
	}

	void Scene::RootFixedUpdate()
	{
		for (GameObjectInformation& pG : m_pSceneImpl->m_GameObjects)
			pG.pGameObject->FixedUpdate();
	}

	void Scene::RootLateUpdate()
	{
		for (GameObjectInformation& pG : m_pSceneImpl->m_GameObjects)
			pG.pGameObject->LateUpdate();
	}

	void Scene::RootRender() const
	{
		for (const GameObjectInformation& pG : m_pSceneImpl->m_GameObjects)
			pG.pGameObject->Render();
	}

	void Scene::RootOnSceneEnter() noexcept
	{
		m_pSceneImpl->m_IsActive = true;

		InputManager::GetInstance()->Activate(this);

		ThreadManager::GetInstance()->AssignThreadTask([this]()
			{
				using namespace std::chrono_literals;

				ThreadManager* const pInstance{ ThreadManager::GetInstance() };

				while (m_pSceneImpl->m_IsActive.load())
				{
					pInstance->SleepThreadWhile<float, std::micro>([this]()->bool
						{
							return !m_pSceneImpl->m_IsActive.load() || m_pSceneImpl->m_TransformManager.ShouldRecalculate();
						}, 10us);

					m_pSceneImpl->m_TransformManager.UpdateTransforms();
				}
			}, 0);

		for (GameObjectInformation& gameObject : m_pSceneImpl->m_GameObjects)
			for (Component* pC : gameObject.pGameObject->GetComponents())
				if (IListener* pL{ dynamic_cast<IListener*>(pC) }; pL != nullptr)
					pL->m_IsActive = true;
	}

	void Scene::RootOnSceneExit() noexcept
	{
		m_pSceneImpl->m_IsActive = false;

		InputManager::GetInstance()->Deactivate(this);

		for (GameObjectInformation& gameObject : m_pSceneImpl->m_GameObjects)
			for (Component* pC : gameObject.pGameObject->GetComponents())
				if (IListener* pL{ dynamic_cast<IListener*>(pC) }; pL != nullptr)
					pL->m_IsActive = false;
	}

	void Scene::AddGameObject(const char* pGameObjectName, GameObject* const pGameObject, const bool shouldAlwaysAdd) noexcept
	{
		const auto cIt{ std::find_if(m_pSceneImpl->m_GameObjects.cbegin(), m_pSceneImpl->m_GameObjects.cend(), [pGameObjectName](const GameObjectInformation& pG)->bool
			{
				return pG.pName == pGameObjectName;
			}) };

		if (cIt == m_pSceneImpl->m_GameObjects.cend())
		{
			m_pSceneImpl->m_GameObjects.push_back(GameObjectInformation{ pGameObjectName, pGameObject});
			m_pSceneImpl->m_TransformManager.AddTransformComponent(pGameObject->pTransform);
			m_pSceneImpl->m_TransformManager.NotifyRecalculation();
		}
		else if (shouldAlwaysAdd)
		{
			std::string newName{};
			for (size_t i{}; i < m_pSceneImpl->m_GameObjects.size() + 1; ++i)
			{
				newName = std::string{ pGameObjectName } + "(" + std::to_string(i) + ")";

				if (std::find_if(m_pSceneImpl->m_GameObjects.cbegin(), m_pSceneImpl->m_GameObjects.cend(), [&newName](const GameObjectInformation& pG)->bool
					{
						return pG.pName == newName;
					}) == m_pSceneImpl->m_GameObjects.cend())
					break;
			}

			Logger::LogWarning(std::string{ "Scene::AddGameObject() > The Name: " } + pGameObjectName + " was already present and has been changed to: "
				+ newName);

			m_pSceneImpl->m_GameObjects.push_back(GameObjectInformation{ newName.c_str(), pGameObject });
			m_pSceneImpl->m_TransformManager.AddTransformComponent(pGameObject->pTransform);
			m_pSceneImpl->m_TransformManager.NotifyRecalculation();
		}
	}

	void Scene::SetSceneName(const char* pSceneName) noexcept
	{
		m_pSceneImpl->m_SceneName = pSceneName;
	}

	GameObject* const Scene::GetGameObject(const char* pGameObjectName) const noexcept
	{
		const auto cIt{ std::find_if(m_pSceneImpl->m_GameObjects.cbegin(), m_pSceneImpl->m_GameObjects.cend(), [pGameObjectName](const GameObjectInformation& pG)->bool
			{
				return pG.pName == pGameObjectName;
			}) };

		if (cIt != m_pSceneImpl->m_GameObjects.cend())
			return cIt->pGameObject;
		else
		{
			Logger::LogWarning(std::string{ "Scene::GetGameObject() > GameObject with name: " } + pGameObjectName + " is not present! Returning nullptr!");
			return nullptr;
		}
	}

	const std::vector<GameObjectInformation>& Scene::GetGameObjects() const noexcept
	{
		return m_pSceneImpl->m_GameObjects;
	}

	const char* Scene::GetSceneName() const noexcept
	{
		return m_pSceneImpl->m_SceneName.c_str();
	}

	bool Scene::IsSceneActive() const noexcept
	{
		return m_pSceneImpl->m_IsActive.load();
	}

	void Scene::SetIsSceneActive(const bool isActive) noexcept
	{
		m_pSceneImpl->m_IsActive.store(isActive);
	}
}
