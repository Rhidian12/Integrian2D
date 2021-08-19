#include "Component.h"

#include <utility>

namespace Integrian2D
{
	Component::Component(GameObject* pOwner)
		: m_pOwner{ pOwner }
	{}
	Component::Component(const Component& other) noexcept
		: m_pOwner{ other.m_pOwner }
	{}
	Component::Component(Component&& other) noexcept
		: m_pOwner{ std::move(other.m_pOwner) }
	{
		other.m_pOwner = nullptr;
	}
	Component& Component::operator=(const Component& other) noexcept
	{
		m_pOwner = other.m_pOwner;
		return *this;
	}
	Component& Component::operator=(Component&& other) noexcept
	{
		m_pOwner = std::move(other.m_pOwner);
		other.m_pOwner = nullptr;
		return *this;
	}
	void Component::SetOwner(GameObject* const pOwner) noexcept
	{
		m_pOwner = pOwner;
	}
	GameObject* const Component::GetOwner() const noexcept
	{
		return m_pOwner;
	}
}