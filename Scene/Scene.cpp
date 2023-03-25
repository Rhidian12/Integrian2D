#include "Scene.h"
#include "../Utils/Utils.h"
#include "../Logger/Logger.h"
#include "../GameObject/GameObject.h"
#include "../TransformManager/TransformManager.h"
#include "../ThreadManager/ThreadManager.h"
#include "../Input/InputManager/InputManager.h"
#include "../IListener/IListener.h"
#include "../Component/Component.h"

namespace Integrian2D
{
	Scene::Scene(const std::string& name)
		: m_SceneName{ name }
		, m_GameObjects{}
		, m_IsActive{}
		, m_TransformManager{}
	{
	}

	Scene::~Scene()
	{
		m_IsActive = false;

		for (GameObject* pG : m_GameObjects)
			__DELETE(pG);

		m_GameObjects.Clear();
	}

#pragma region Internal_Functionality

	void Scene::Awake()
	{
		for (GameObject* const pG : m_GameObjects)
			pG->Awake();
	}

	void Scene::Start()
	{
		for (GameObject* const pG : m_GameObjects)
			pG->Start();
	}

	void Scene::Update()
	{
		for (GameObject* const pG : m_GameObjects)
			pG->Update();
	}

	void Scene::FixedUpdate()
	{
		for (GameObject* const pG : m_GameObjects)
			pG->FixedUpdate();
	}

	void Scene::LateUpdate()
	{
		for (GameObject* const pG : m_GameObjects)
			pG->LateUpdate();
	}

	void Scene::Render() const
	{
		for (GameObject* const pG : m_GameObjects)
			pG->Render();
	}

	void Scene::__OnSceneEnter()
	{
		m_IsActive = true;

		/* [TODO]: What the fuck am I doing here??? */
		InputManager::GetInstance()->Activate(this);

		ThreadManager::GetInstance()->AssignThreadTask([this]()
			{
				using namespace std::chrono_literals;

				ThreadManager* const pInstance{ ThreadManager::GetInstance() };

				while (m_IsActive.load())
				{
					pInstance->SleepThreadWhile<float, std::micro>([this]()->bool
						{
							return !m_IsActive.load() || m_TransformManager.ShouldRecalculate();
						}, 10us);

					m_TransformManager.UpdateTransforms();
				}
			}, 0);

		/* [TODO]: What the fuck am I doing here??? */
		for (GameObject* const pGameObject : m_GameObjects)
			for (Component* pC : pGameObject->GetComponents())
				if (IListener* pL{ dynamic_cast<IListener*>(pC) }; pL != nullptr)
					pL->m_IsActive = true;
	}

	void Scene::__OnSceneExit()
	{
		m_IsActive = false;

		/* [TODO]: What the fuck am I doing here??? */
		InputManager::GetInstance()->Deactivate(this);

		/* [TODO]: What the fuck am I doing here??? */
		for (GameObject* const pGameObject : m_GameObjects)
			for (Component* pC : pGameObject->GetComponents())
				if (IListener* pL{ dynamic_cast<IListener*>(pC) }; pL != nullptr)
					pL->m_IsActive = false;
	}

#pragma endregion


#pragma region GameObject_Functionality

	void Scene::AddGameObject(GameObject* const pGameObject)
	{
		const auto cIt{ m_GameObjects.Find(pGameObject) };

		if (cIt == m_GameObjects.cend())
		{
			m_GameObjects.Add(pGameObject);
			m_TransformManager.AddTransformComponent(pGameObject->pTransform);
			m_TransformManager.NotifyRecalculation();
		}
	}

	GameObject* const Scene::GetGameObject(const std::string_view name) const
	{
		const auto cIt{ m_GameObjects.Find([name](const GameObject* const pG)->bool
			{
				return pG->GetName() == name;
			}) };

		if (cIt != m_GameObjects.cend())
			return *cIt;

		Logger::GetInstance().LogWarning
		(
			std::string{ "Scene::GetGameObject() > GameObject with name: " } + std::string{ name } + " is not present! Returning nullptr!",
			__LINE__,
			__FILE__
		);

		return nullptr;
	}

	const Array<GameObject*>& Scene::GetGameObjects() const
	{
		return m_GameObjects;
	}

#pragma endregion

#pragma region Scene_Functionality

	void Scene::SetSceneName(const std::string& name)
	{
		m_SceneName = name;
	}

	std::string_view Scene::GetSceneName() const
	{
		return m_SceneName;
	}

	bool Scene::IsSceneActive() const
	{
		return m_IsActive.load();
	}

	void Scene::SetIsSceneActive(const bool isActive)
	{
		m_IsActive.store(isActive);
	}

#pragma endregion
}
