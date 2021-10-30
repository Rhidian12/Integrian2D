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

			m_DestRect = PRectf{ m_pOwner->pTransform->GetLocalPosition(), pTexture->GetWidth(), pTexture->GetHeight() };
		}
	}

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* const pTexture, const PRectf& destRect)
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
		Renderer::GetInstance()->RenderTexture(m_pTexture, PRectf{ m_pOwner->pTransform->GetWorldPosition(), m_DestRect.width, m_DestRect.height }, m_SourceRect);
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