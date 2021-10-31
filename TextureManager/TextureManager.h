#pragma once

#include <string>
#include <unordered_map>

namespace Integrian2D
{
	class Texture;

	class TextureManager final
	{
	public:
		/* Get a TextureManager instance */
		static TextureManager* GetInstance() noexcept;

		/* Internal Usage
		   Do NOT call this function manually */
		static void Cleanup() noexcept;

		~TextureManager();

		/* Add a Texture to the Texture Manager
		   Textures with duplicate names do not get added */
		void AddTexture(std::string textureID, Texture* const pTexture) noexcept;

		/* Get a previously added Texture to the TextureManager */
		Texture* const GetTexture(const std::string& textureID) const noexcept;

		/* Get all previously added Textures 
		   If no Textures have been added, this function returns an empty map */
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