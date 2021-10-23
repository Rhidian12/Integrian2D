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
		, m_DestRectWidth{}
		, m_DestRectHeight{}
	{
	}

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* const pTexture)
		: Component{ pOwner }
		, m_pTexture{ pTexture }
		, m_SourceRect{}
		, m_DestRectWidth{}
		, m_DestRectHeight{}
	{
		if (pTexture)
		{
			m_SourceRect.width = pTexture->GetWidth();
			m_SourceRect.height = pTexture->GetHeight();
			m_DestRectWidth = pTexture->GetWidth();
			m_DestRectHeight = pTexture->GetHeight();
		}
	}

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* const pTexture, const float destRectWidth, const float destRectHeight)
		: Component{ pOwner }
		, m_pTexture{ pTexture }
		, m_SourceRect{}
		, m_DestRectWidth{ destRectWidth }
		, m_DestRectHeight{ destRectHeight }
	{
		if (pTexture)
		{
			m_SourceRect.width = pTexture->GetWidth();
			m_SourceRect.height = pTexture->GetHeight();
		}
	}

	void TextureComponent::Render() const
	{
		PRectf destRect{ m_pOwner->pTransform->GetDestRect() };

		if (Utils::AreEqual(destRect.width, 0.f) && Utils::AreEqual(destRect.height, 0.f))
		{
			const float angle{ destRect.angle };
			SetRotation(destRect, 0.f);

			SetWidth(destRect, m_DestRectWidth);
			SetHeight(destRect, m_DestRectHeight);

			SetRotation(destRect, angle);
		}

		const Point2f& leftBottom{ GetLeftBottom(destRect) };
		const Point2f worldPosition{ m_pOwner->pTransform->GetWorldPosition() };

		Renderer::GetInstance()->RenderTexture(m_pTexture, PRectf{ leftBottom.x + worldPosition.x, leftBottom.y + worldPosition.y, destRect.width, destRect.height }, m_SourceRect);
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