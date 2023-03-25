#include "Component.h"

namespace Integrian2D
{
	Component::Component(GameObject* pOwner)
		: Object{ "Component" }
		, m_pOwner{ pOwner }
	{}

	void Component::SetOwner(GameObject* const pOwner)
	{
		m_pOwner = pOwner;
	}

	GameObject* const Component::GetOwner() const
	{
		return m_pOwner;
	}
}