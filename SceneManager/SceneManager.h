#pragma once

#include <unordered_map>

namespace Integrian2D
{
	class Scene;

	class SceneManager final
	{
	public:
		/* Get a SceneManager instance */
		static SceneManager* const GetInstance() noexcept;

		/* Interal Usage
		   Do NOT call this manually */
		static void Cleanup() noexcept;

		~SceneManager();

		/* Adds a Scene to the SceneManager 
		   Duplicate Scenes do not get added */
		void AddScene(Scene* const pScene) noexcept;
		
		/* Get the currently active scene 
		   If no scene is marked as the active scene, this will return a nullptr */
		Scene* const GetActiveScene() const noexcept;

		/* Get the Scene with the corresponding Scene Name */
		Scene* const GetScene(std::string sceneName) const noexcept;

		/* Get all added Scenes 
		   If no Scenes have been added, this will return an empty map */
		const std::unordered_map<std::string, Scene*>& GetScenes() const noexcept;

	private:
		SceneManager();

		inline static SceneManager* m_pInstance{};

		Scene* m_pActiveScene;
		std::unordered_map<std::string, Scene*> m_pScenes;
	};
}
