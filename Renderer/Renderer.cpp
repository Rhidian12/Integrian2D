#include "Renderer.h"
#include "../Texture/Texture.h"
#include "../Utils/Utils.h"

uint8_t operator"" _u(unsigned long long x) // adding _8 behind any integer (IN THIS FILE) will make it a uint8_t
{
	Integrian2D::Utils::Assert((x <= 255) && (x >= 0), "_u suffix was used for a value outside the uint8_t range [0, 255]");
	return static_cast<uint8_t>(x);
}

namespace Integrian2D
{
	Renderer::Renderer()
		: m_ClearColour{ 192_u,192_u,192_u }
		, m_TexturesToRender{}
	{}

	void Renderer::StartRenderLoop() noexcept
	{
		glClearColor(static_cast<float>(m_ClearColour.r / 255_u), static_cast<float>(m_ClearColour.g / 255_u), static_cast<float>(m_ClearColour.b / 255_u),
			static_cast<float>(m_ClearColour.a));
		glClear(GL_COLOR_BUFFER_BIT);

		glPushMatrix(); // This is for when a camera gets added
	}

	void Renderer::EndRenderLoop() noexcept
	{
		glPopMatrix(); // This is for when a camera gets added

		// == Swap back- and frontbuffer ==
		SDL_GL_SwapWindow(pWindow);

		m_TexturesToRender.clear();
	}

	void Renderer::Render(Texture* const pTexture) noexcept
	{
		m_TexturesToRender.push_back(pTexture->GetTextureID());
	}
}