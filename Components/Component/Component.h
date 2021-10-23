#pragma once

#include "../../Math/TypeDefines.h"

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

		// This function must return a Component* and must be overriden in any derived class
		virtual Component* Clone(GameObject* pOwner) noexcept = 0;
		/* 
			Example from the TextureComponent:
	
			Component* TextureComponent::Clone(GameObject* pOwner) noexcept
			{
				return new TextureComponent{ pOwner, m_pTexture };
			}
		*/

		void SetOwner(GameObject* const pOwner) noexcept;
		GameObject* const GetOwner() const noexcept;

		// All of the functions below should be overriden if necessary
		virtual void Update() {}
		virtual void FixedUpdate() {}
		virtual void LateUpdate() {}

		virtual void Render() const {}

	protected:
		GameObject* m_pOwner;
	};
}
