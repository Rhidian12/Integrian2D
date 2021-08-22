#pragma once

#include "../Component/Component.h"

namespace Integrian2D
{
	class Texture;

	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* pOwner);
		TextureComponent(GameObject* pOwner, Texture* pTexture);

		virtual void Render() const override;

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		void SetTexture(Texture* const pTexture) noexcept;

		Texture* const GetTexture() const noexcept;

	private:
		Texture* m_pTexture;
	};
}