#pragma once

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
		const std::unordered_map<std::string, Scene*>& GetScenes() const noexcept;

	private:
		SceneManager();

		inline static SceneManager* m_pInstance{};

		Scene* m_pActiveScene;
		std::unordered_map<std::string, Scene*> m_pScenes;
	};
}
