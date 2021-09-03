#include "Renderer.h"
#include "../Texture/Texture.h"
#include "../Utils/Utils.h"

inline uint8_t operator"" _u(unsigned long long x) // adding _8 behind any integer (IN THIS FILE) will make it a uint8_t
{
	Integrian2D::Utils::Assert((x <= 255) && (x >= 0), "_u suffix was used for a value outside the uint8_t range [0, 255]");
	return static_cast<uint8_t>(x);
}

namespace Integrian2D
{
	Renderer* Renderer::GetInstance() noexcept
	{
		Utils::Assert(m_pInstance != nullptr, "Renderer::GetInstance() > m_pInstance was never created! Was the Window created properly?");
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
		Utils::Assert(!m_pInstance, "Renderer::CreateRenderer() > This function is called by the Core, do not manually call this function!");

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
		Utils::Assert(m_IsNewFrame, "Renderer::Render() > This function was called twice this frame, don't call this function manually!");

		StartRenderLoop();

		RenderAllTextures();

		EndRenderLoop();

		m_IsNewFrame = false;
	}

	void Renderer::SetNewFrame() noexcept
	{
		m_IsNewFrame = true;
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
			const float vertexLeft{ textureInformation.destRect.x };
			const float vertexBottom{ textureInformation.destRect.y };
			float vertexRight{ vertexLeft + defaultDestWidth };
			float vertexTop{ vertexBottom + defaultDestHeight };

			if (!Utils::AreEqual(textureInformation.destRect.width, 0.f) || !Utils::AreEqual(textureInformation.destRect.height, 0.f)) // size specified
			{
				vertexRight = vertexLeft + textureInformation.destRect.width;
				vertexTop = vertexBottom + textureInformation.destRect.height;
			}

			// Tell opengl which texture we will use
			glBindTexture(GL_TEXTURE_2D, textureInformation.pTexture->GetTextureID());
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

			// Draw
			glEnable(GL_TEXTURE_2D);
			{
				glBegin(GL_QUADS);
				{
					glTexCoord2f(textLeft, textBottom);
					glVertex2f(vertexLeft, vertexBottom);

					glTexCoord2f(textLeft, textTop);
					glVertex2f(vertexLeft, vertexTop);

					glTexCoord2f(textRight, textTop);
					glVertex2f(vertexRight, vertexTop);

					glTexCoord2f(textRight, textBottom);
					glVertex2f(vertexRight, vertexBottom);
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

	void Renderer::RenderTexture(Texture* const pTexture, const Rectf& destRect, const Rectf& sourceRect) noexcept
	{
		m_TexturesToRender.push_back(TextureInformation{ pTexture, destRect, sourceRect });
	}
}