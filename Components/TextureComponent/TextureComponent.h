#pragma once

#include "../Component/Component.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	class Texture;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* pOwner);
		TextureComponent(GameObject* pOwner, Texture* const pTexture);
		TextureComponent(GameObject* pOwner, Texture* const pTexture, const float width, const float height);

		virtual void Render(const Point2f& offset) const override;

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		void SetTexture(Texture* const pTexture) noexcept;

		Texture* const GetTexture() const noexcept;
		
		Rectf m_SourceRect;
		float m_Width;
		float m_Height;

	private:
		Texture* m_pTexture;
	};
}