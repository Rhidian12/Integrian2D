#pragma once

#include "../Math/TypeDefines.h"

#include <vector>
#include <string>
#include <typeinfo>

namespace Integrian2D
{
	class Component;
	class TransformComponent;

	/* The GameObject is the class that holds a list of Components, and calls their overridable functions, such as Render() 
	   The GameObjects get added to the Scene via Scene::AddGameObject */
	class GameObject final
	{
	public:
		/* Every GameObject has a TransformComponent by default! */
		GameObject();
		~GameObject();

		/* This function calls the GameObject's Components' Update(). Do NOT call this manually */
		void Update();

		/* This function calls the GameObject's Components' FixedUpdate(). Do NOT call this manually */
		void FixedUpdate();

		/* This function calls the GameObject's Components' LateUpdate(). Do NOT call this manually */
		void LateUpdate();

		/* This function calls the GameObject's Components' Render(). Do NOT call this manually */
		void Render() const;

		/* This function returns the Component requested by the User. This function will cause a compilation error
		   if the requested Type is class not derived from Component 
		   If the requested Type is present, it will return a pointer to the requested component
		   Otherwise this function returns a nullptr */
		template<typename Type, typename = std::enable_if_t<std::is_base_of_v<Component, Type>>>
		Type* const GetComponentByType() const noexcept;

		/* Adds a Component to the GameObject, if it not already present
		   Duplicate Component Types are allowed, but not the same Component twice */
		void AddComponent(Component* pComponent) noexcept;

		/* Sets another GameObject as this GameObject's Child
		   The GameObject set as Child its parent is set as this GameObject */
		void AddChild(GameObject* pChild) noexcept;

		/* Set a GameObject's parent
		   It is unnecessary to call this in conjunction with AddChild()
		   Since AddChild() sets the parent automatically */
		void SetParent(GameObject* const pParent) noexcept;

		/* Set the GameObject's tag */
		void SetTag(std::string tag) noexcept;

		/* Get this GameObject's parent 
		   If the GameObject has no parent, this function returns a nullptr */
		GameObject* GetParent() const noexcept;

		/* Get the GameObject's Children 
		   If the GameObject has no Children, this functions returns an empty std::vector */
		const std::vector<GameObject*>& GetChildren() const noexcept;

		/* Get the GameObject's tag */
		const std::string& GetTag() const noexcept;

		/* The GameObject's Transform Component */
		TransformComponent* pTransform;

		GameObject(const GameObject& other) noexcept;
		GameObject(GameObject&& other) noexcept;
		GameObject& operator=(const GameObject& other) noexcept;
		GameObject& operator=(GameObject&& other) noexcept;

	private:
		std::vector<Component*> m_pComponents;
		std::vector<GameObject*> m_pChildren;
		GameObject* m_pParent;

		std::string m_Tag;
	};

	template<typename Type, typename>
	Type* const GameObject::GetComponentByType() const noexcept
	{
		const std::type_info& typeInfo{ typeid(Type) };

		for (Component* pC : m_pComponents)
			if (typeid(*pC) == typeInfo)
				return static_cast<Type*>(pC);

		return nullptr;
	}
}

