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
		, m_DestRect{}
	{
	}

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* const pTexture)
		: Component{ pOwner }
		, m_pTexture{ pTexture }
		, m_SourceRect{}
		, m_DestRect{}
	{
		if (pTexture)
		{
			m_SourceRect.width = pTexture->GetWidth();
			m_SourceRect.height = pTexture->GetHeight();

			m_DestRect = Rectf{ m_pOwner->pTransform->GetWorldPosition(), pTexture->GetWidth(), pTexture->GetHeight() };
		}
	}

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* const pTexture, const Rectf& destRect)
		: Component{ pOwner }
		, m_pTexture{ pTexture }
		, m_SourceRect{}
		, m_DestRect{ destRect }
	{
		if (pTexture)
		{
			m_SourceRect.width = pTexture->GetWidth();
			m_SourceRect.height = pTexture->GetHeight();
		}
	}

	void TextureComponent::Render() const
	{
		Renderer::GetInstance()->RenderTexture(m_pTexture,
			PRectf{ m_pOwner->pTransform->GetWorldPosition(), m_DestRect.width, m_DestRect.height,
			m_pOwner->pTransform->GetAngle(), m_pOwner->pTransform->GetScale() },
			m_SourceRect);
	}

	Component* TextureComponent::Clone(GameObject* pOwner) noexcept
	{
		TextureComponent* pTextureComponent{ new TextureComponent{pOwner} };

		pTextureComponent->m_DestRect = m_DestRect;
		pTextureComponent->m_SourceRect = m_SourceRect;
		pTextureComponent->m_pTexture = m_pTexture;

		return pTextureComponent;
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