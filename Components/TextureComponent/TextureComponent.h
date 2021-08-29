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

		virtual void Render() const override;

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		void SetTexture(Texture* const pTexture) noexcept;
		void SetSourceRect(Rectf sourceRect) noexcept;

		Texture* const GetTexture() const noexcept;
		const Rectf& GetSourceRect() const noexcept;

	private:
		Texture* m_pTexture;
		Rectf m_SourceRect;
		float m_Width;
		float m_Height;
	};
}