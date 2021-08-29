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

		Texture* const GetTexture(const std::string& textureID) const noexcept;
		const std::unordered_map<std::string, Texture*>& GetTextures() const noexcept;

		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(TextureManager&&) = delete;

	private:
		TextureManager() = default;

		std::unordered_map<std::string, Texture*> m_pTextures;

		inline static TextureManager* m_pInstance{};
	};
}