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
		
		/* 
		The destination rect (the area where the Texture gets rendered) is set to its default,
		which is the GameObject's position, Texture's width and Texture's height
		*/
		TextureComponent(GameObject* pOwner, Texture* const pTexture);

		/*
		The destination rect is set to the GameObject's position and the width and height defined by their respective parameters.
		*/
		TextureComponent(GameObject* pOwner, Texture* const pTexture, const float destRectWidth, const float destRectHeight);

		virtual void Render() const override;

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		void SetTexture(Texture* const pTexture) noexcept;

		Texture* const GetTexture() const noexcept;
		
		Rectf m_SourceRect;
		float m_DestRectWidth;
		float m_DestRectHeight;

	private:
		Texture* m_pTexture;
	};
}