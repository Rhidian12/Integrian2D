#pragma once

#ifndef INTEGRIAN2D_SCENEMANAGER_H
#define INTEGRIAN2D_SCENEMANAGER_H

#include <unordered_map>

namespace Integrian2D
{
	class Scene;

	class SceneManager final
	{
	public:
		static SceneManager* const GetInstance() noexcept;
		static void Cleanup() noexcept;

		~SceneManager();

		void AddScene(Scene* const pScene) noexcept;
		
		Scene* const GetActiveScene() const noexcept;
		Scene* const GetScene(std::string sceneName) const noexcept;

	private:
		SceneManager();

		inline static SceneManager* m_pInstance{};

		Scene* m_pActiveScene;
		std::unordered_map<std::string, Scene*> m_pScenes;
	};
}

#endif // !INTEGRIAN2D_SCENEMANAGER_H