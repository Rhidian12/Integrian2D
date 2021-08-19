#pragma once

#ifndef INTEGRIAN2D_GAMEOBJECT_H
#define INTEGRIAN2D_GAMEOBJECT_H

#include <vector>
#include <typeinfo>

#include "../Logger/Logger.h"

namespace Integrian2D
{
	class Component;

	class GameObject final
	{
	public:
		GameObject();
		~GameObject();

		void Update();
		void FixedUpdate();
		void LateUpdate();

		void Render() const;

		template<typename Type, typename = std::enable_if_t<std::is_base_of_v<Component, Type>>>
		Type* const GetComponentByType() const noexcept;

		void AddComponent(Component* pComponent) noexcept;
		void AddChild(GameObject* pChild) noexcept;

		void SetTag(std::string tag) noexcept;

		const std::string& GetTag() const noexcept;

		GameObject(const GameObject& other) noexcept;
		GameObject(GameObject&& other) noexcept;
		GameObject& operator=(const GameObject& other) noexcept;
		GameObject& operator=(GameObject&& other) noexcept;

	private:
		std::vector<Component*> m_pComponents;
		std::vector<GameObject*> m_pChildren;

		std::string m_Tag;
	};

	template<typename Type, typename>
	Type* const GameObject::GetComponentByType() const noexcept
	{
		const std::type_info& typeInfo{ typeid(Type) };

		for (Component* pC : m_pComponents)
			if (typeid(*pC) == typeInfo)
				return static_cast<Type*>(pC);

		Logger::LogWarning(std::string{ "GameObject::GetComponentByType() > Component of type: " } + typeInfo.name() + " was not present!");
		return nullptr;
	}
}

#endif // !INTEGRIAN2D_GAMEOBJECT_H