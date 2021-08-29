#pragma once

#include <string>
#include <unordered_map>

namespace Integrian2D
{
	class Texture;

	class TextureManager final
	{
	public:
		static TextureManager* GetInstance() noexcept;
		static void Cleanup() noexcept;

		~TextureManager();

		void AddTexture(std::string textureID, Texture* const pTexture) noexcept;

		const Texture* const GetTexture(const std::string& textureID) const noexcept;
		const std::unordered_map<std::string, Texture*>& GetTextures() const noexcept;

	private:
		TextureManager() = default;

		std::unordered_map<std::string, Texture*> m_pTextures;

		inline static TextureManager* m_pInstance{};
	};
}