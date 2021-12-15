#pragma once

#include "../Component/Component.h"

namespace Integrian2D
{
	class TextComponent;

	/* A Component that renders the current FPS to the screen */
	class FPSComponent final : public Component
	{
	public:
		/* The FPSComponent does NOT take ownership of the passed TextComponent
			Both components should be added to the same GameObject */
		FPSComponent(GameObject* const pOwner, TextComponent* const pTextComponent);

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		virtual void Update() override;

		/* Get the provided text component */
		TextComponent* const GetTextComponent() const noexcept;

	private:
		TextComponent* m_pTextComponent;
	};
}