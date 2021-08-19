#pragma once

#ifndef INTEGRIAN2D_SCENE_H
#define INTEGRIAN2D_SCENE_H

#include <string>
#include <vector>
#include <unordered_map>

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

	private:
		friend class Integrian2D; // Make sure that only Integrian2D can access the Root[] functions
		void RootUpdate();
		void RootFixedUpdate();
		void RootLateUpdate();

		void RootRender() const;

		std::string m_SceneName;

		std::unordered_map<std::string, GameObject*> m_pGameObjects;
	};
}

#endif // !INTEGRIAN2D_SCENE_H