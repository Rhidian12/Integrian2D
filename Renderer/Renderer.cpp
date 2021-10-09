#include "Renderer.h"
#include "../Texture/Texture.h"
#include "../Utils/Utils.h"

namespace Integrian2D
{
	inline uint8_t operator"" _u(unsigned long long x) // adding _8 behind any integer (IN THIS FILE) will make it a uint8_t
	{
		ASSERT((x <= 255) && (x >= 0), "_u suffix was used for a value outside the uint8_t range [0, 255]");
		return static_cast<uint8_t>(x);
	}
}

namespace Integrian2D
{
	Renderer* Renderer::GetInstance() noexcept
	{
		ASSERT(m_pInstance != nullptr, "Renderer::GetInstance() > m_pInstance was never created! Was the Window created properly?");
		return m_pInstance;
	}

	void Renderer::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	Renderer::Renderer(SDL_Window* const pWindow)
		: m_IsNewFrame{}
		, m_ClearColour{ 192_u,192_u,192_u }
		, m_TexturesToRender{}
		, m_pWindow{ pWindow }
	{}

	void Renderer::CreateRenderer(SDL_Window* const pWindow) noexcept
	{
		ASSERT(!m_pInstance, "Renderer::CreateRenderer() > This function is called by the Core, do not manually call this function!");

		m_pInstance = new Renderer{ pWindow };
	}

	void Renderer::StartRenderLoop() noexcept
	{
		glClearColor(static_cast<float>(m_ClearColour.r / 255_u), static_cast<float>(m_ClearColour.g / 255_u), static_cast<float>(m_ClearColour.b / 255_u),
			static_cast<float>(m_ClearColour.a));
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix(); // This is for when a camera gets added
	}

	void Renderer::Render() noexcept
	{
		ASSERT(m_IsNewFrame, "Renderer::Render() > This function was called twice this frame, don't call this function manually!");

		RenderAllTextures();

		EndRenderLoop();

		m_IsNewFrame = false;
	}

	void Renderer::SetNewFrame() noexcept
	{
		m_IsNewFrame = true;

		StartRenderLoop();
	}

	void Renderer::RenderRectangle(const Rectf& rect, const RGBColour& colour) noexcept
	{
		glColor3i(colour.r.v, colour.g.v, colour.b.v);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(rect.x, rect.y);
			glVertex2f(rect.x, rect.y + rect.height);
			glVertex2f(rect.x + rect.width, rect.y + rect.height);
			glVertex2f(rect.x + rect.width, rect.y);
		}
		glEnd();
	}

	void Renderer::RenderRectangle(const PRectf& rect, const RGBColour& colour) noexcept
	{
		glColor3i(colour.r.v, colour.g.v, colour.b.v);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(GetLeftBottom(rect).x, GetLeftBottom(rect).y);
			glVertex2f(GetLeftTop(rect).x, GetLeftTop(rect).y);
			glVertex2f(GetRightTop(rect).x, GetRightTop(rect).y);
			glVertex2f(GetRightBottom(rect).x, GetRightBottom(rect).y);
		}
		glEnd();
	}

	void Renderer::RenderFilledRectangle(const Rectf& rect, const RGBColour& colour) noexcept
	{
		glColor3i(colour.r.v, colour.g.v, colour.b.v);
		glBegin(GL_POLYGON);
		{
			glVertex2f(rect.x, rect.y);
			glVertex2f(rect.x, rect.y + rect.height);
			glVertex2f(rect.x + rect.width, rect.y + rect.height);
			glVertex2f(rect.x + rect.width, rect.y);
		}
		glEnd();
	}

	void Renderer::RenderFilledRectangle(const PRectf& rect, const RGBColour& colour) noexcept
	{
		glColor3i(colour.r.v, colour.g.v, colour.b.v);
		glBegin(GL_POLYGON);
		{
			glVertex2f(GetLeftBottom(rect).x, GetLeftBottom(rect).y);
			glVertex2f(GetLeftTop(rect).x, GetLeftTop(rect).y);
			glVertex2f(GetRightTop(rect).x, GetRightTop(rect).y);
			glVertex2f(GetRightBottom(rect).x, GetRightBottom(rect).y);
		}
		glEnd();
	}

	void Renderer::RenderTriangle(const PTrianglef& triangle, const RGBColour& colour) noexcept
	{
		glColor3i(colour.r.v, colour.g.v, colour.b.v);
		glBegin(GL_LINES);
		{
			for (const Point2f& p : triangle)
				glVertex2f(p.x, p.y);
		}
		glEnd();
	}

	void Renderer::RenderFilledTriangle(const PTrianglef& triangle, const RGBColour& colour) noexcept
	{
		glColor3i(colour.r.v, colour.g.v, colour.b.v);
		glBegin(GL_POLYGON);
		{
			for (const Point2f& p : triangle)
				glVertex2f(p.x, p.y);
		}
		glEnd();
	}

	void Renderer::RenderLine(const Point2f& start, const Point2f& end, const float lineWidth, const RGBColour& colour) noexcept
	{
		glColor3i(colour.r.v, colour.g.v, colour.b.v);
		glLineWidth(lineWidth);
		glBegin(GL_LINES);
		{
			glVertex2f(start.x, start.y);
			glVertex2f(end.x, end.y);
		}
		glEnd();
	}

	void Renderer::RenderAllTextures() noexcept
	{
		for (const TextureInformation& textureInformation : m_TexturesToRender)
		{
			// Determine texture coordinates using srcRect and default destination width and height
			float textLeft{};
			float textRight{ 1.f };
			float textTop{};
			float textBottom{ 1.f };

			float defaultDestWidth{ textureInformation.pTexture->GetHeight() };
			float defaultDestHeight{ textureInformation.pTexture->GetWidth() };

			if (!Utils::AreEqual(textureInformation.sourceRect.width, 0.f) && !Utils::AreEqual(textureInformation.sourceRect.height, 0.f)) // srcRect specified
			{
				// Convert to the range [0.0, 1.0]
				textLeft = textureInformation.sourceRect.x / textureInformation.sourceRect.width;
				textRight = (textureInformation.sourceRect.x + textureInformation.sourceRect.width) / textureInformation.sourceRect.width;
				textTop = (textureInformation.sourceRect.y - textureInformation.sourceRect.height) / textureInformation.sourceRect.height;
				textBottom = textureInformation.sourceRect.y / textureInformation.sourceRect.height;

				defaultDestHeight = textureInformation.sourceRect.height;
				defaultDestWidth = textureInformation.sourceRect.width;
			}

			// Determine vertex coordinates
			const Point2f& leftBottom{ GetLeftBottom(textureInformation.destRect) };
			const Point2f& leftTop{ GetLeftTop(textureInformation.destRect) };
			const Point2f& rightTop{ GetRightTop(textureInformation.destRect) };
			const Point2f& rightBottom{ GetRightBottom(textureInformation.destRect) };

			// Tell opengl which texture we will use
			glBindTexture(GL_TEXTURE_2D, textureInformation.pTexture->GetTextureID());
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			// Draw
			glEnable(GL_TEXTURE_2D);
			{
				glBegin(GL_QUADS);
				{
					glTexCoord2f(textLeft, textBottom);
					glVertex2f(leftBottom.x, leftBottom.y);

					glTexCoord2f(textLeft, textTop);
					glVertex2f(leftTop.x, leftTop.y);

					glTexCoord2f(textRight, textTop);
					glVertex2f(rightTop.x, rightTop.y);

					glTexCoord2f(textRight, textBottom);
					glVertex2f(rightBottom.x, rightBottom.y);
				}
				glEnd();
			}
			glDisable(GL_TEXTURE_2D);
		}
	}

	void Renderer::EndRenderLoop() noexcept
	{
		glPopMatrix(); // This is for when a camera gets added

		// == Swap back- and frontbuffer ==
		SDL_GL_SwapWindow(m_pWindow);

		m_TexturesToRender.clear();
	}

	void Renderer::RenderTexture(Texture* const pTexture, const PRectf& destRect, const Rectf& sourceRect) noexcept
	{
		m_TexturesToRender.push_back(TextureInformation{ pTexture, destRect, sourceRect });
	}
}