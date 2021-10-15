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

	TextureComponent::TextureComponent(GameObject* pOwner, Texture* const pTexture, const float width, const float height)
		: Component{ pOwner }
		, m_pTexture{ pTexture }
		, m_SourceRect{}
		, m_Width{ width }
		, m_Height{ height }
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

			SetWidth(destRect, m_Width);
			SetHeight(destRect, m_Height);

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