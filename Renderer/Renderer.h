#pragma once

#include <vector>
#include "../Math/TypeDefines.h"

struct SDL_Window;
namespace Integrian2D
{
	class Texture;

	/* This class renders Textures to the Window and can draw polygons to the Window */
	class Renderer final
	{
	public:
		/* Interal Usage
		   Do NOT call this function manually */
		static void CreateRenderer(SDL_Window* const pWindow) noexcept;

		/* Return an instance of the Renderer */
		static Renderer* GetInstance() noexcept;

		/* Internal Usage
		   Do NOT call this function manually */
		static void Cleanup() noexcept;

		/* Queue a Texture to be Rendered */
		void RenderTexture(Texture* const pTexture, const PRectf& destRect, const Rectf& sourceRect) noexcept;

		/* Render all queued Textures
		   Do NOT call this function manually, this gets called internally */
		void Render() noexcept;

		/* Internal Usage
		   Do NOT call this function manually, this gets called internally */
		void SetNewFrame() noexcept;

		/* Render an empty rectangle to the screen */
		void RenderRectangle(const Rectf& rect, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

		/* Render an empty to the screen */
		void RenderRectangle(const PRectf& rect, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

		/* Render a filled rectangle to the screen */
		void RenderFilledRectangle(const Rectf& rect, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

		/* Render a filled rectangle to the screen */
		void RenderFilledRectangle(const PRectf& rect, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

		/* Render an empty triangle to the screen */
		void RenderTriangle(const PTrianglef& triangle, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

		/* Render an empty triangle to the screen */
		void RenderTriangle(const Trianglef& triangle, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

		/* Render a filled triangle to the screen */
		void RenderFilledTriangle(const PTrianglef& triangle, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

		/* Render a filled triangle to the screen */
		void RenderFilledTriangle(const Trianglef& triangle, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;
		
		/* Render a line to the screen */
		void RenderLine(const Point2f& start, const Point2f& end, const float lineWidth, const RGBColour& colour = RGBColour{ 255,0,0 }) noexcept;

		// TODO: Add Circle

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

