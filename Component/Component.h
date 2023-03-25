#pragma once

#include "../Integrian2D_API.h"
#include "../Object/Object.h"
#include "../GameObject/GameObject.h"

namespace Integrian2D
{
	class INTEGRIAN2D_API Component : public Object
	{
	public:
		explicit Component(GameObject* pOwner);
		virtual ~Component() = default;

		Component(const Component&) noexcept = delete;
		Component(Component&&) noexcept = delete;
		Component& operator=(const Component&) noexcept = delete;
		Component& operator=(Component&&) noexcept = delete;

		void SetOwner(GameObject* const pOwner);

		GameObject* const GetOwner() const;

		virtual void Awake() {}
		virtual void Start() {}
		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}
		virtual void Render() const {}

	protected:
		GameObject* m_pOwner;
	};
}
