#pragma once

#include <vector>
#include "../Math/TypeDefines.h"

struct SDL_Window;
namespace Integrian2D
{
	class Texture;

	class Renderer final
	{
	public:
		static Renderer* GetInstance() noexcept;
		static void Cleanup() noexcept;

		void RenderTexture(Texture* const pTexture, const Rectf& destRect, const Rectf& sourceRect) noexcept;

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;

	private:
		friend class Core; // Let only the Core do the render loop
		friend class Window; // Let only the Window make a Renderer

		struct TextureInformation final
		{
			Texture* pTexture;
			Rectf destRect;
			Rectf sourceRect;
		};

		static void CreateRenderer(SDL_Window* const pWindow) noexcept;

		Renderer(SDL_Window* const pWindow);

		void StartRenderLoop() noexcept;
		void Render() noexcept;
		void RenderAllTextures() noexcept;
		void EndRenderLoop() noexcept;

		inline static Renderer* m_pInstance{};

		RGBColour m_ClearColour;
		std::vector<TextureInformation> m_TexturesToRender;

		SDL_Window* const m_pWindow;
	};
}

