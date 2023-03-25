#pragma once

#include "../Integrian2D_API.h"

#include <string> /* std::string */

namespace Integrian2D
{
	class INTEGRIAN2D_API Object
	{
	public:
		virtual ~Object() = default;

		void SetActive(const bool isActive);

		__NODISCARD bool IsActive() const { return m_IsActive; }

		void MarkForDestruction() { m_IsMarkedForDestruction = true; }
		__NODISCARD bool IsMarkedForDestruction() const { return m_IsMarkedForDestruction; }

		__NODISCARD const std::string_view GetName() const { return m_ObjectName; }
		void SetName(const std::string& name);

	protected:
		Object();
		explicit Object(const std::string& name);

		START_DISABLE_EXPORT_WARNING;
		std::string m_ObjectName;
		END_DISABLE_EXPORT_WARNING;
		bool m_IsActive;
		bool m_IsMarkedForDestruction;
	};
}