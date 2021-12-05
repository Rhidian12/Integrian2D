#pragma once

#include "../../Components/Component/Component.h"

namespace Integrian2D
{
	class AIComponent final : public Component
	{
	public:
		AIComponent(GameObject* const pOwner);

		virtual Component* Clone(GameObject* pOwner) noexcept override;
	};
}