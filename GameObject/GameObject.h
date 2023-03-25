#pragma once

#include "../Integrian2D_API.h"
#include "../Object/Object.h"
#include "../Array/TArray.h"
#include "GameObjectUtils.h"

namespace Integrian2D
{
	class Component;
	class TransformComponent;

	class INTEGRIAN2D_API GameObject : public Object
	{
	public:
		/* The GameObject's Transform Component */
		TransformComponent* pTransform;

		~GameObject();

		GameObject(const GameObject&) noexcept = delete;
		GameObject(GameObject&&) noexcept = delete;
		GameObject& operator=(const GameObject&) noexcept = delete;
		GameObject& operator=(GameObject&&) noexcept = delete;

	#pragma region Internal_Functionality

		void Awake();

		void Start();

		void Update();

		void FixedUpdate();

		void LateUpdate();

		void Render() const;

	#pragma endregion

	#pragma region Component_Functionality

		template<typename T>
		T* const GetComponentByType() const;

		template<typename T>
		void DeleteComponentByType();

		template<typename T>
		T* const AddComponent(T* const pComponent);

		Array<Component*> GetComponents() const;

	#pragma endregion

	#pragma region Tag_Functionality

		const std::string& AddTag(const std::string& tag);

		const std::string& SetTag(const std::string& tag, const uint64_t index);

		void RemoveTag(const std::string& tag);

		void RemoveTag(const uint64_t index);

		__NODISCARD const std::string& GetTag(const uint64_t index) const;

		__NODISCARD const Array<std::string>& GetTags() const;

		__NODISCARD bool HasTag(const std::string& tag) const;

	#pragma endregion

	#pragma region Parent_Child_Functionality

		void AddChild(GameObject* const pChild);

		void RemoveChild(GameObject* const pChild);

		void RemoveChildByIndex(const size_t index);

		void SetParent(GameObject* const pParent);

		GameObject* const GetParent() const;

		const Array<GameObject*>& GetChildren() const;

	#pragma endregion

	protected:
		GameObject();
		explicit GameObject(const std::string& name);
		friend GameObject* Instantiate(const std::string&);
		friend GameObject* Instantiate(const std::string&, class Scene*);

		struct ComponentInfo final
		{
			uint32_t ID;
			class Component* pComponent;
		};

		Array<ComponentInfo> m_Components;
		Array<GameObject*> m_Children;
		Array<std::string> m_Tags;

		GameObject* m_pParent;
	};

#pragma region Templated_Functions

	template<typename T>
	T* const GameObject::GetComponentByType() const
	{
		constexpr uint32_t id{ GOUtils::GenerateComponentID<T>() };
		const auto cIt{ m_Components.Find([id](const ComponentInfo& info)->bool
			{
				return info.ID == id;
			}) };

		if (cIt != m_Components.cend())
			return static_cast<T*>(cIt->pComponent);

		return nullptr;
	}

	template<typename T>
	T* const GameObject::AddComponent(T* const pComponent)
	{
		constexpr uint32_t id{ GOUtils::GenerateComponentID<T>() };

		if (m_Components.Find([id](const ComponentInfo& info)->bool
			{
				return info.ID == id;
			}) == m_Components.cend())
		{
			m_Components.Add(ComponentInfo{ id, pComponent });

			return pComponent;
		}

			return nullptr;
	}

	template<typename T>
	void GameObject::DeleteComponentByType()
	{
		constexpr uint32_t id{ GOUtils::GenerateComponentID<T>() };
		const auto it{ m_Components.Find([id](const ComponentInfo& info)->bool
			{
				return info.ID == id;
			}) };

		if (it != m_Components.end())
		{
			it->pComponent->MarkForDestruction();
		}
	}

#pragma endregion


#pragma region Helper_Functions

	__NODISCARD GameObject* Instantiate(const std::string& name = "");
	__NODISCARD GameObject* Instantiate(const std::string& name, class Scene* pScene);

	__NODISCARD GameObject* FindGameObjectWithTag(const std::string& tag);
	__NODISCARD Array<GameObject*> FindGameObjectsWithTag(const std::string& tag);

#pragma endregion
}

