#include "Object.h"

namespace Integrian2D
{
	Object::Object()
		: Object{ "" }
	{}

	Object::Object(const std::string& name)
		: m_ObjectName{ name }
		, m_IsActive{ true }
		, m_IsMarkedForDestruction{}
	{}

	void Object::SetActive(const bool isActive)
	{
		m_IsActive = isActive;
	}

	void Object::SetName(const std::string& name)
	{
		m_ObjectName = name;
	}
}