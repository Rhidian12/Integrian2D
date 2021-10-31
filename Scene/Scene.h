#pragma once

#include <string>
#include <unordered_map>
#include <mutex>

#include "../Input/InputManager/InputManager.h"
#include "../PhysicsEngine/PhysicsEngine.h"
#include "../EventQueue/EventQueue.h"
#include "../TransformManager/TransformManager.h"

namespace Integrian2D
{
	class GameObject;

	/* This class is supposed to be inherited from */
	class Scene
	{
	public:
		Scene(const std::string& sceneName);
		virtual ~Scene();

		/* This function has to be overridden 
		   This is where all of the Scene initisialition should start! */
		virtual void Start() = 0;

		/* An optionally overridable Scene-specific Update
		   This function should not try to update the GameObject's Update
		   This happens internally */
		virtual void Update() {}

		/* An optionally overridable Scene-specific FixedUpdate
		   This function should not try to update the GameObject's FixedUpdate
		   This happens internally */
		virtual void FixedUpdate() {}

		/* An optionally overridable Scene-specific LateUpdate
		   This function should not try to update the GameObject's LateUpdate
		   This happens internally */
		virtual void LateUpdate() {}

		/* An optionally overridable Scene-specific Render
		   This function should not try to update the GameObject's Render
		   This happens internally */
		virtual void Render() const {}

		/* Use this function to add GameObjects to the Scene! 
		   GameObjects with duplicate GameObject names are not allowed, except if the shouldAlwaysAdd parameter is set to true
		   If this boolean is set to true and there is a duplicate GameObject name, the name will be the same, with (N) added to it
		   where N is the amount of times this name has been added - 1 */
		void AddGameObject(const std::string& gameObjectName, GameObject* const pGameObject, const bool shouldAlwaysAdd = true) noexcept;

		/* Set the Scene's Name */
		void SetSceneName(const std::string& sceneName) noexcept;

		/* Get a previously added GameObject by its name 
		   This function will return a nullptr if the GameObject is not present */
		GameObject* const GetGameObject(const std::string& gameObjectName) const noexcept;

		/* Get all previously added GameObjects to the Scene 
		   This function will return an empty map if there have been no added GameObjects */
		const std::unordered_map<std::string, GameObject*> GetGameObjects() const noexcept;

		/* Get the Scene's name */
		const std::string& GetSceneName() const noexcept;

	protected:
#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
		struct
		{
			InputManager inputManager{};
			PhysicsEngine physicsEngine{};
			EventQueue eventQueue{};
		};
#pragma warning ( pop )

	private:
		friend class Core; // Make sure that only Core can access the Root functions
		friend class Locator; // Make sure that only the Locator can access the InputManager

		void RootUpdate();
		void RootFixedUpdate();
		void RootLateUpdate();
		void RootRender() const;

		std::string m_SceneName;
		std::unordered_map<std::string, GameObject*> m_pGameObjects;

		std::mutex m_Mutex;
		TransformManager m_TransformManager;
	};
}

