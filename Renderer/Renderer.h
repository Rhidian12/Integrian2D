#pragma once

#include <vector>
#include "../Math/RGBColour.h"

struct SDL_Window;
namespace Integrian2D
{
	class Texture;

	class Renderer final
	{
	public:
		static Renderer* GetInstance() noexcept;
		static void Cleanup() noexcept;

		void Render(Texture* const pTexture) noexcept;

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;

	private:
		friend class Scene; // Make sure only Scene can access the Render loop
		friend class Window; // Let only the Window make a Renderer

		static void CreateRenderer(SDL_Window* const pWindow) noexcept;

		Renderer(SDL_Window* const pWindow);

		void StartRenderLoop() noexcept;
		void EndRenderLoop() noexcept;

		inline static Renderer* m_pInstance{};

		RGBColour m_ClearColour;
		std::vector<unsigned int> m_TexturesToRender;

		SDL_Window* const m_pWindow;
	};
}

