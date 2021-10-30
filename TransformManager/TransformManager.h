#pragma once

#include <vector>
#include <unordered_map>

namespace Integrian2D
{
	class TransformComponent;

	class TransformManager final
	{
	public:
		void UpdateTransforms() noexcept;

		void AddTransformComponent(TransformComponent* const pTransformComponent) noexcept;
		void RemoveTransformComponent(TransformComponent* const pTransformComponent) noexcept;

	private:
		friend class Scene;

		TransformManager();
		void InformChildren(TransformComponent* const pParent) noexcept;
		void MoveChildren(TransformComponent* const pParent) noexcept;

		std::unordered_map<TransformComponent*, std::vector<TransformComponent*>> m_pTransformComponents;
	};
}