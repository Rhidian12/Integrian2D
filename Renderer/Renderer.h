#pragma once

#include <vector>
#include "../Math/RGBColour.h"

namespace Integrian2D
{
	class Texture;

	class Renderer final
	{
	public:
		void Render(Texture* const pTexture) noexcept;


	private:
		friend class Scene; // Make sure only Scene can access the Render loop

		Renderer();

		void StartRenderLoop() noexcept;
		void EndRenderLoop() noexcept;

		RGBColour m_ClearColour;
		std::vector<unsigned int> m_TexturesToRender;
	};
}

