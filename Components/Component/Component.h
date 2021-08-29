#pragma once

namespace Integrian2D
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pOwner);
		virtual ~Component() = default;

		Component(const Component& other) noexcept;
		Component(Component&& other) noexcept;
		Component& operator=(const Component& other) noexcept;
		Component& operator=(Component&& other) noexcept;

		virtual Component* Clone(GameObject* pOwner) noexcept = 0;

		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}

		virtual void Render() const {}

		void SetOwner(GameObject* const pOwner) noexcept;
		GameObject* const GetOwner() const noexcept;

	protected:
		GameObject* m_pOwner;
	};
}
