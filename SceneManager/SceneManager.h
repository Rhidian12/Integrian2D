#pragma once

#include "../Integrian2D_API.h"
#include "../Scene/Scene.h"
#include "../Array/TArray.h"

#include <memory> /* std::unique_ptr */
#include <string_view> /* std::string_view */

namespace Integrian2D
{
	class SceneManager final
	{
	public:
		INTEGRIAN2D_API ~SceneManager();

		INTEGRIAN2D_API static SceneManager& GetInstance();

		INTEGRIAN2D_API void AddScene(Scene* scene);

		INTEGRIAN2D_API void ChangeScene(const std::string_view sceneName);

		INTEGRIAN2D_API __NODISCARD Scene* const GetActiveScene() { return m_pActiveScene; }
		INTEGRIAN2D_API __NODISCARD const Scene* const GetActiveScene() const { return m_pActiveScene; }

		INTEGRIAN2D_API __NODISCARD Scene* const GetScene(const std::string_view sceneName);
		INTEGRIAN2D_API __NODISCARD const Scene* const GetScene(const std::string_view sceneName) const;

		INTEGRIAN2D_API __NODISCARD const Array<Scene*>& GetScenes() const;

	private:
		INTEGRIAN2D_API SceneManager();

		friend std::unique_ptr<SceneManager> std::make_unique();
		inline static std::unique_ptr<SceneManager> m_pInstance{};

		Array<Scene*> m_Scenes;
		Scene* m_pActiveScene;
	};
}