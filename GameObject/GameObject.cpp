#include "GameObject.h"
#include "../Utils/Utils.h"
#include "../Components/Component/Component.h"
#include "../Logger/Logger.h"

#include <algorithm>

namespace Integrian2D
{
	GameObject::GameObject()
		: m_pComponents{}
		, m_pChildren{}
		, m_Tag{}
	{
	}

	GameObject::~GameObject()
	{
		for (Component*& pC : m_pComponents)
			Utils::SafeDelete(pC);

		for (GameObject*& pG : m_pChildren)
			Utils::SafeDelete(pG);
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

	void GameObject::AddComponent(Component* pComponent) noexcept
	{
		std::vector<Component*>::const_iterator cIt{ std::find(m_pComponents.cbegin(), m_pComponents.cend(), pComponent) };

		if (cIt == m_pComponents.cend())
			m_pComponents.push_back(pComponent);
		else
			Logger::LogWarning("GameObject::AddComponent() > Component is already present and is not added twice!");
	}

	void GameObject::AddChild(GameObject* pChild) noexcept
	{
		std::vector<GameObject*>::const_iterator cIt{ std::find(m_pChildren.cbegin(), m_pChildren.cend(), pChild) };

		if (cIt == m_pChildren.cend())
			m_pChildren.push_back(pChild);
		else
			Logger::LogWarning("GameObject::AddChild() > Child is already present and is not added twice!");
	}

	void GameObject::SetTag(std::string tag) noexcept
	{
		m_Tag = tag;
	}

	const std::string& GameObject::GetTag() const noexcept
	{
		return m_Tag;
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
	{
		for (Component* pC : m_pComponents)
			pC->SetOwner(this);

		other.m_pComponents.clear();
		other.m_pChildren.clear();
	}
	GameObject& GameObject::operator=(const GameObject& other) noexcept
	{
		for (Component* pC : other.m_pComponents)
			m_pComponents.push_back(pC->Clone(this));

		for (GameObject* pG : other.m_pChildren)
			m_pChildren.push_back(new GameObject{ *pG });

		m_Tag = other.m_Tag;

		return *this;
	}
	GameObject& GameObject::operator=(GameObject&& other) noexcept
	{
		m_pComponents = std::forward<std::vector<Component*>>(other.m_pComponents);
		m_pChildren = std::forward<std::vector<GameObject*>>(other.m_pChildren);
		m_Tag = std::forward<std::string>(other.m_Tag);

		for (Component* pC : m_pComponents)
			pC->SetOwner(this);

		other.m_pComponents.clear();
		other.m_pChildren.clear();

		return *this;
	}
}