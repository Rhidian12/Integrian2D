#include "Command.h"

namespace Integrian2D
{
	Scene* const Command::GetScene() const noexcept
	{
		return m_pScene;
	}
}