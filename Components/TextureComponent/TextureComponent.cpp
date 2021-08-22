#include "TextureComponent.h"

namespace Integrian2D
{
	TextureComponent::TextureComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_pTexture{}
	{
	}

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* pTexture)
		: Component{ pOwner }
		, m_pTexture{ pTexture }
	{
	}

	void TextureComponent::Render() const
	{
	}

	Component* TextureComponent::Clone(GameObject* pOwner) noexcept
	{
		return new TextureComponent{ pOwner, m_pTexture };
	}

	void TextureComponent::SetTexture(Texture* const pTexture) noexcept
	{
		m_pTexture = pTexture;
	}

	Texture* const TextureComponent::GetTexture() const noexcept
	{
		return m_pTexture;
	}
}