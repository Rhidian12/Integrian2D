#include "TextureComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Texture/Texture.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../Renderer/Renderer.h"

namespace Integrian2D
{
	TextureComponent::TextureComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_pTexture{}
		, m_SourceRect{}
		, m_Width{}
		, m_Height{}
	{
	}

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* const pTexture)
		: Component{ pOwner }
		, m_pTexture{ pTexture }
		, m_SourceRect{}
		, m_Width{}
		, m_Height{}
	{
		if (pTexture)
		{
			m_SourceRect.width = pTexture->GetWidth();
			m_SourceRect.height = pTexture->GetHeight();
			m_Width = pTexture->GetWidth();
			m_Height = pTexture->GetHeight();
		}
	}

	void TextureComponent::Render() const
	{
		//m_pTexture->Draw(m_pOwner->pTransform->position, m_SourceRect);
		Renderer::GetInstance()->RenderTexture(m_pTexture, Rectf{ GetPosition(m_pOwner->pTransform->GetDestRect()).x, GetPosition(m_pOwner->pTransform->GetDestRect()).y, m_Width, m_Height }, m_SourceRect);
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