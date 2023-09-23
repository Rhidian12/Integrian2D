#include "GameObject.h"
#include "../Utils/Utils.h"
#include "../Components/Component/Component.h"
#include "../Logger/Logger.h"
#include "../Components/TransformComponent/TransformComponent.h"

#include <algorithm>

namespace Integrian2D
{
	GameObject::GameObject()
		: m_pComponents{}
		, m_pChildren{}
		, m_Tag{}
		, m_pParent{}
		, pTransform{ new TransformComponent{ this } }
	{
	}

	GameObject::~GameObject()
	{
		for (Component*& pC : m_pComponents)
			Utils::SafeDelete(pC);

		Utils::SafeDelete(pTransform);
	}

	void GameObject::Start()
	{
		for (Component* const pC : m_pComponents)
		{
			pC->RootStart();
			pC->Start();
		}
	}

	void GameObject::Update()
	{
		for (Component* pC : m_pComponents)
			pC->Update();

		for (GameObject* pG : m_pChildren)
			pG->Update();
	}

	void GameObject::FixedUpdate()
	{
		pTransform->FixedUpdate();

		for (Component* pC : m_pComponents)
			pC->FixedUpdate();

		for (GameObject* pG : m_pChildren)
			pG->FixedUpdate();
	}

	void GameObject::LateUpdate()
	{
		for (Component* pC : m_pComponents)
			pC->LateUpdate();

		for (GameObject* pG : m_pChildren)
			pG->LateUpdate();
	}

	void GameObject::Render() const
	{
		for (Component* pC : m_pComponents)
			pC->Render();

		for (GameObject* pG : m_pChildren)
			pG->Render();
	}

	void GameObject::AddComponent(Component* const pComponent) noexcept
	{
		std::vector<Component*>::const_iterator cIt{ std::find(m_pComponents.cbegin(), m_pComponents.cend(), pComponent) };

		if (cIt == m_pComponents.cend())
			m_pComponents.push_back(pComponent);
	}

	void GameObject::RemoveComponentByValue(Component* const pComponent) noexcept
	{
		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), pComponent), m_pComponents.end());
	}

	void GameObject::DeleteComponentByValue(Component* const pComponent) noexcept
	{
		for (Component*& pC : m_pComponents)
			if (pC == pComponent)
				Utils::SafeDelete(pC);

		m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), nullptr), m_pComponents.end());
	}

	void GameObject::AddChild(GameObject* const pChild) noexcept
	{
		std::vector<GameObject*>::const_iterator cIt{ std::find(m_pChildren.cbegin(), m_pChildren.cend(), pChild) };

		if (cIt == m_pChildren.cend())
		{
			m_pChildren.push_back(pChild);
			pChild->m_pParent = this;
		}
	}

	void GameObject::SetParent(GameObject* const pParent) noexcept
	{
		m_pParent = pParent;
		pParent->AddChild(this);
	}

	void GameObject::SetTag(const std::string& tag) noexcept
	{
		m_Tag = tag;
	}

	GameObject* const GameObject::GetParent() const noexcept
	{
		return m_pParent;
	}

	const std::vector<GameObject*>& GameObject::GetChildren() const noexcept
	{
		return m_pChildren;
	}

	const std::string& GameObject::GetTag() const noexcept
	{
		return m_Tag;
	}

	INTEGRIAN2D_API const std::vector<Component*>& GameObject::GetComponents() const noexcept
	{
		return m_pComponents;
	}


	// ================================
	// ================================
	// == Rule Of Five ==
	// ================================
	// ================================


	GameObject::GameObject(const GameObject& other) noexcept
		: m_pComponents{}
		, m_pChildren{}
		, m_Tag{ other.m_Tag }
		, m_pParent{ other.m_pParent }
		, pTransform{ static_cast<TransformComponent*>(other.pTransform->Clone(this)) }
	{
		for (Component* pC : other.m_pComponents)
			m_pComponents.push_back(pC->Clone(this));

		for (GameObject* pG : other.m_pChildren)
			m_pChildren.push_back(new GameObject{ *pG });
	}
	GameObject::GameObject(GameObject&& other) noexcept
		: m_pComponents{ std::forward<std::vector<Component*>>(other.m_pComponents) }
		, m_pChildren{ std::forward<std::vector<GameObject*>>(other.m_pChildren) }
		, m_Tag{ std::forward<std::string>(other.m_Tag) }
		, m_pParent{ std::forward<GameObject*>(other.m_pParent) }
		, pTransform{ std::forward<TransformComponent*>(other.pTransform) }
	{
		pTransform->SetOwner(this);

		for (Component* pC : m_pComponents)
			pC->SetOwner(this);

		other.m_pComponents.clear();
		other.m_pChildren.clear();
		other.pTransform = nullptr;
	}
	GameObject& GameObject::operator=(const GameObject& other) noexcept
	{
		pTransform = static_cast<TransformComponent*>(other.pTransform->Clone(this));

		for (Component* pC : other.m_pComponents)
			m_pComponents.push_back(pC->Clone(this));

		for (GameObject* pG : other.m_pChildren)
			m_pChildren.push_back(new GameObject{ *pG });

		m_pParent = other.m_pParent;
		m_Tag = other.m_Tag;

		return *this;
	}
	GameObject& GameObject::operator=(GameObject&& other) noexcept
	{
		pTransform = std::forward<TransformComponent*>(other.pTransform);
		pTransform->SetOwner(this);

		m_pComponents = std::forward<std::vector<Component*>>(other.m_pComponents);
		m_pChildren = std::forward<std::vector<GameObject*>>(other.m_pChildren);
		m_pParent = std::forward<GameObject*>(m_pParent);
		m_Tag = std::forward<std::string>(other.m_Tag);

		for (Component* pC : m_pComponents)
			pC->SetOwner(this);

		other.m_pComponents.clear();
		other.m_pChildren.clear();
		other.pTransform = nullptr;

		return *this;
	}
}