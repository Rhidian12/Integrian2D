#include "TextureManager.h"
#include "../Utils/Utils.h"
#include "../Texture/Texture.h"
#include "../Logger/Logger.h"

namespace Integrian2D
{
	TextureManager::TextureManager()
		: m_pTextures{}
	{}

	TextureManager* TextureManager::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new TextureManager{};

		return m_pInstance;
	}

	void TextureManager::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	TextureManager::~TextureManager()
	{
		for (std::pair<const std::string, Texture*>& pair : m_pTextures)
			Utils::SafeDelete(pair.second);
	}

	void TextureManager::AddTexture(const std::string& textureID, Texture* const pTexture) noexcept
	{
		const std::unordered_map<std::string, Texture*>::const_iterator cIt{ m_pTextures.find(textureID) };

		if (cIt == m_pTextures.cend())
			m_pTextures.insert(std::make_pair(textureID, pTexture));
	}

	Texture* const TextureManager::GetTexture(const std::string& textureID) const noexcept
	{
		const std::unordered_map<std::string, Texture*>::const_iterator cIt{ m_pTextures.find(textureID) };

		if (cIt != m_pTextures.cend())
			return cIt->second;
		else
			return nullptr;
	}

	const std::unordered_map<std::string, Texture*>& TextureManager::GetTextures() const noexcept
	{
		return m_pTextures;
	}
}