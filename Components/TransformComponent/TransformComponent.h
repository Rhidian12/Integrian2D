#pragma once

#include "../Component/Component.h"
#include "../../Math/TypeDefines.h"

namespace Integrian2D
{
	class TransformComponent final : public Component
	{
	public:
		TransformComponent(GameObject* pOwner);

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		Point2f position;
	};
}

