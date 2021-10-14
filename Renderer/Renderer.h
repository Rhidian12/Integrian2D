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

		void RenderRectangle(const Rectf& rect, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		void RenderRectangle(const PRectf& rect, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		void RenderFilledRectangle(const Rectf& rect, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		void RenderFilledRectangle(const PRectf& rect, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		void RenderTriangle(const PTrianglef& triangle, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		void RenderTriangle(const Trianglef& triangle, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		void RenderFilledTriangle(const PTrianglef& triangle, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		void RenderFilledTriangle(const Trianglef& triangle, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		// TODO: Add Circle and Triangle
		void RenderLine(const Point2f& start, const Point2f& end, const float lineWidth, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

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

