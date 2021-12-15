#include "FPSComponent.h"
#include "../TextComponent/TextComponent.h"
#include "../../Timer/Timer.h"

namespace Integrian2D
{
	FPSComponent::FPSComponent(GameObject* const pOwner, TextComponent* const pTextComponent)
		: Component{ pOwner }
		, m_pTextComponent{ pTextComponent }
	{}

	Component* FPSComponent::Clone(GameObject* pOwner) noexcept
	{
		return new FPSComponent{ pOwner, m_pTextComponent };
	}

	void FPSComponent::Update()
	{
		m_pTextComponent->SetTextToRender("FPS: " + std::to_string(Timer::GetInstance()->GetFPS()));
	}

	TextComponent* const FPSComponent::GetTextComponent() const noexcept
	{
		return m_pTextComponent;
	}
}