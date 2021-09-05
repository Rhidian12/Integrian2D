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
		static void CreateRenderer(SDL_Window* const pWindow) noexcept;

		static Renderer* GetInstance() noexcept;
		static void Cleanup() noexcept;

		void RenderTexture(Texture* const pTexture, const PRectf& destRect, const Rectf& sourceRect) noexcept;

		void Render() noexcept;

		void SetNewFrame() noexcept;

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;

	private:
		struct TextureInformation final
		{
			Texture* pTexture;
			PRectf destRect;
			Rectf sourceRect;
		};

		Renderer(SDL_Window* const pWindow);

		void StartRenderLoop() noexcept;
		void RenderAllTextures() noexcept;
		void EndRenderLoop() noexcept;

		inline static Renderer* m_pInstance{};

		bool m_IsNewFrame;

		RGBColour m_ClearColour;
		std::vector<TextureInformation> m_TexturesToRender;

		SDL_Window* const m_pWindow;
	};
}

