#pragma once
#include <vector>
#include <unordered_map>

namespace Integrian2D
{
	class TransformComponent;

	class TransformManager final
	{
	public:
		static TransformManager* const GetInstance() noexcept;
		static void Cleanup() noexcept;

		void UpdateTransforms() noexcept;

		void AddTransformComponent(TransformComponent* const pTransformComponent) noexcept;
		void RemoveTransformComponent(TransformComponent* const pTransformComponent) noexcept;

	private:
		TransformManager();

		inline static TransformManager* m_pInstance{};
		std::unordered_map<TransformComponent*, std::vector<TransformComponent*>> m_pTransformComponents;
	};
}