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

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* pTexture)
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
		Renderer::GetInstance()->RenderTexture(m_pTexture, Rectf{ m_pOwner->pTransform->position.x, m_pOwner->pTransform->position.y, m_Width, m_Height }, m_SourceRect);
	}

	Component* TextureComponent::Clone(GameObject* pOwner) noexcept
	{
		return new TextureComponent{ pOwner, m_pTexture };
	}

	void TextureComponent::SetTexture(Texture* const pTexture) noexcept
	{
		m_pTexture = pTexture;
	}

	void TextureComponent::SetSourceRect(Rectf sourceRect) noexcept
	{
		m_SourceRect = sourceRect;
	}

	Texture* const TextureComponent::GetTexture() const noexcept
	{
		return m_pTexture;
	}

	const Rectf& TextureComponent::GetSourceRect() const noexcept
	{
		return m_SourceRect;
	}
}