#pragma once

namespace Integrian2D
{
	class Scene;

	class Command
	{
	public:
		Command(Scene* const pScene);

		virtual ~Command() = default;

		/* When the input related to this command gets triggered, Execute() gets called */
		virtual void Execute() = 0;

		/* Optionally overrideable function for ease-of-use, 
			meaning that this function will never get called internally */
		virtual void Undo() {}

		/* Optionally overrideable function for ease-of-use,
			meaning that this function will never get called internally */
		virtual void Redo() {}

		/* Get the Scene this Command is attached to */
		Scene* const GetScene() const noexcept;

	protected:
		Scene* m_pScene;
	};
}