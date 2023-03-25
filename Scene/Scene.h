#pragma once

#include "../Integrian2D_API.h"

#include "../EventQueue/EventQueue.h"
#include "../GameObject/GameObject.h"
#include "../Array/TArray.h"
#include "../TransformManager/TransformManager.h"

#include <string>

namespace Integrian2D
{
	/* This class is supposed to be inherited from */
	class INTEGRIAN2D_API Scene
	{
	public:
		explicit Scene(const std::string& name);
		virtual ~Scene();

	#pragma region Inheritable_Functionality

		virtual void Initialize() = 0;

		virtual void OnSceneEnter() {}

		virtual void OnSceneExit() {}

	#pragma endregion

	#pragma region Internal_Functionality

		void Awake();

		void Start();

		void Update();

		void FixedUpdate();

		void LateUpdate();

		void Render() const;

		void __OnSceneEnter();

		void __OnSceneExit();

	#pragma endregion

	#pragma region GameObject_Functionality

		void AddGameObject(GameObject* const pGameObject);

		GameObject* const GetGameObject(const std::string_view name) const;

		const Array<GameObject*>& GetGameObjects() const;

	#pragma endregion

	#pragma region Scene_Functionality

		/* Set the Scene's Name */
		void SetSceneName(const std::string& name);

		/* Get the Scene's name */
		std::string_view GetSceneName() const;

		/* Is the Scene active? */
		bool IsSceneActive() const;

		/* Set whether the scene is active */
		void SetIsSceneActive(const bool isActive);

	#pragma endregion

	private:
		std::string m_SceneName;
		Array<GameObject*> m_GameObjects;
		std::atomic_bool m_IsActive;

		TransformManager m_TransformManager;
	};
}

