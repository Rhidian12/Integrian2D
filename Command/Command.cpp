#include "Command.h"

namespace Integrian2D
{
	Command::Command(Scene* const pScene)
		: m_pScene{ pScene }
	{}

	Scene* const Command::GetScene() const noexcept
	{
		return m_pScene;
	}
}