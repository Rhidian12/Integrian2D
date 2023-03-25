#include "GameObject.h"
#include "../Utils/Utils.h"
#include "../Component/Component.h"
#include "../Logger/Logger.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../SceneManager/SceneManager.h"

namespace Integrian2D
{
#pragma region Ctor_And_Dtor

	GameObject::GameObject()
		: GameObject{ "" }
	{}

	GameObject::GameObject(const std::string& name)
		: Object{ name }
		, pTransform{}
		, m_Components{}
		, m_Tags{}
	{
		pTransform = AddComponent(new TransformComponent{ this });
	}

	GameObject::~GameObject()
	{
		for (ComponentInfo& info : m_Components)
		{
			info.ID = 0;
			__DELETE(info.pComponent);
		}

		m_Components.Clear();
	}

#pragma endregion

#pragma region Internal_Functionality

	void GameObject::Awake()
	{
		for (const ComponentInfo& info : m_Components)
			if (info.pComponent->IsActive())
				info.pComponent->Awake();
	}

	void GameObject::Start()
	{
		for (const ComponentInfo& info : m_Components)
			if (info.pComponent->IsActive())
				info.pComponent->Start();
	}

	void GameObject::Update()
	{
		if (!m_IsActive)
			return;

		for (const ComponentInfo& info : m_Components)
			if (info.pComponent->IsActive())
				info.pComponent->Update();

		for (GameObject* const pChild : m_Children)
			pChild->Update();
	}

	void GameObject::FixedUpdate()
	{
		if (!m_IsActive)
			return;

		for (const ComponentInfo& info : m_Components)
			if (info.pComponent->IsActive())
				info.pComponent->FixedUpdate();

		for (GameObject* const pChild : m_Children)
			pChild->FixedUpdate();
	}

	void GameObject::LateUpdate()
	{
		if (!m_IsActive)
			return;

		for (const ComponentInfo& info : m_Components)
			if (info.pComponent->IsActive())
				info.pComponent->LateUpdate();

		for (GameObject* const pChild : m_Children)
			pChild->LateUpdate();
	}

	void GameObject::Render() const
	{
		if (!m_IsActive)
			return;

		for (const ComponentInfo& info : m_Components)
			if (info.pComponent->IsActive())
				info.pComponent->Render();

		for (GameObject* const pChild : m_Children)
			pChild->Render();
	}

#pragma endregion

#pragma region Tag_Functionality

	const std::string& GameObject::AddTag(const std::string& tag)
	{
		m_Tags.Add(tag);

		return tag;
	}

	const std::string& GameObject::SetTag(const std::string& tag, const uint64_t index)
	{
		__ASSERT(index < m_Tags.Size() && "GameObject::SetTag() > Index is out of bounds");

		m_Tags[index] = tag;

		return tag;
	}

	void GameObject::RemoveTag(const std::string& tag)
	{
		m_Tags.Erase(tag);
	}

	void GameObject::RemoveTag(const uint64_t index)
	{
		__ASSERT(index < m_Tags.Size() && "GameObject::RemoveTag() > Index is out of bounds");

		m_Tags.EraseByIndex(index);
	}

	const std::string& GameObject::GetTag(const uint64_t index) const
	{
		__ASSERT(index < m_Tags.Size() && "GameObject::GetTag() > Index is out of bounds");

		return m_Tags[index];
	}

	const Array<std::string>& GameObject::GetTags() const
	{
		return m_Tags;
	}

	bool GameObject::HasTag(const std::string& tag) const
	{
		return m_Tags.Find(tag) != m_Tags.cend();
	}

#pragma endregion

#pragma region Parent_Child_Functionality

	void GameObject::AddChild(GameObject* const pChild)
	{
		const auto cIt{ m_Children.Find(pChild) };

		if (cIt == m_Children.cend())
		{
			if (pChild->m_pParent)
			{
				pChild->m_pParent->RemoveChild(pChild);
			}

			pChild->m_pParent = this;
			
			m_Children.Add(pChild);
		}
	}

	void GameObject::RemoveChild(GameObject* const pChild)
	{
		m_Children.Erase(pChild);

		/* Make sure child no longer has this as parent */
		pChild->m_pParent = nullptr;
	}

	void GameObject::RemoveChildByIndex(const size_t index)
	{
		__ASSERT(index < m_Children.Size() && "GameObject::RemoveChildByIndex() > Index was out of bounds");

		GameObject* const pChild{ m_Children[index] };
		m_Children.EraseByIndex(index);

		/* Make sure child no longer has this as parent */
		pChild->m_pParent = nullptr;
	}

	void GameObject::SetParent(GameObject* const pParent)
	{
		__ASSERT(pParent != nullptr && "GameObject::SetParent() > Parent is nullptr");

		/* If we have a parent, make sure we unchild ourselves from it */
		if (m_pParent)
		{
			m_pParent->RemoveChild(this);
			m_pParent = nullptr; // should be redundant, but better safe than sorry
		}

		pParent->AddChild(this);
	}

	GameObject* const GameObject::GetParent() const
	{
		return m_pParent;
	}

	const Array<GameObject*>& GameObject::GetChildren() const
	{
		return m_Children;
	}

#pragma endregion

#pragma region Helper_Functions

	GameObject* Instantiate(const std::string& name)
	{
		Scene* const pActiveScene{ SceneManager::GetInstance().GetActiveScene() };

		__ASSERT(pActiveScene != nullptr && "Instantiate(std::string) > No scene has been added, add a scene first");


		GameObject* pG{ new GameObject{ name } };

		pActiveScene->AddGameObject(pG);

		return pG;
	}

	GameObject* Instantiate(const std::string& name, Scene* pScene)
	{
		__ASSERT(pScene != nullptr && "Instantiate(std::string, Scene*) > Given scene is a nullptr");

		GameObject* pG{ new GameObject{ name } };

		pScene->AddGameObject(pG);

		return pG;
	}

	GameObject* FindGameObjectWithTag(const std::string& tag)
	{
		Scene* const pActiveScene{ SceneManager::GetInstance().GetActiveScene() };

		__ASSERT(pActiveScene != nullptr && "FindGameObjectWithTag(std::string) > No scene has been added, add a scene first");

		const auto& gameObjects{ pActiveScene->GetGameObjects() };

		for (GameObject* const pG : gameObjects)
			if (pG->HasTag(tag))
				return pG;

		return nullptr;
	}

	Array<GameObject*> FindGameObjectsWithTag(const std::string& tag)
	{
		Scene* const pActiveScene{ SceneManager::GetInstance().GetActiveScene() };

		__ASSERT(pActiveScene != nullptr && "FindGameObjectsWithTag(std::string) > No scene has been added, add a scene first");

		const auto& gameObjects{ pActiveScene->GetGameObjects() };
		Array<GameObject*> foundGameObjects{};

		for (GameObject* const pG : gameObjects)
			if (pG->HasTag(tag))
				foundGameObjects.Add(pG);

		return foundGameObjects;
	}

#pragma endregion
}