#pragma once

#include <string>
#include <unordered_map>

#include "../Input/InputManager/InputManager.h"
#include "../PhysicsEngine/PhysicsEngine.h"

namespace Integrian2D
{
	class GameObject;

	class Scene
	{
	public:
		Scene(std::string sceneName);
		virtual ~Scene();

		virtual void Start() = 0;

		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}

		virtual void Render() const {}

		void AddGameObject(std::string gameObjectName, GameObject* const pGameObject) noexcept;
		void SetSceneName(std::string sceneName) noexcept;

		GameObject* const GetGameObject(std::string gameObjectName) const noexcept;
		const std::string& GetSceneName() const noexcept;

	protected:
#pragma warning ( push )
#pragma warning ( disable : 4201 ) // Disable nameless struct warning
		struct
		{
			InputManager inputManager{}; // TODO: Make this not a struct if not necessary
			PhysicsEngine physicsEngine{};
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
	};
}

