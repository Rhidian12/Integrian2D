#include "TransformManager.h"
#include "../Utils/Utils.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../GameObject/GameObject.h"

#include <algorithm>

namespace Integrian2D
{
	TransformManager::TransformManager()
		: m_pTransformComponents{}
	{}

	TransformManager* const TransformManager::GetInstance() noexcept
	{
		if (!m_pInstance)
			m_pInstance = new TransformManager{};

		return m_pInstance;
	}

	void TransformManager::Cleanup() noexcept
	{
		Utils::SafeDelete(m_pInstance);
	}

	void TransformManager::UpdateTransforms() noexcept
	{
	}

	void TransformManager::AddTransformComponent(TransformComponent* const pTransformComponent) noexcept
	{
		/* If the Transform Component has no parent, it is the root parent */
		if (pTransformComponent->GetOwner()->GetParent() == nullptr)
		{
			m_pTransformComponents.insert(std::make_pair(pTransformComponent, std::vector<TransformComponent*>{}));
		}
		else /* The Transform Component has a parent, it is a child */
		{
			/* Is the Transform Component's parent in the map? */
			if (m_pTransformComponents.find(pTransformComponent->GetOwner()->GetParent()->pTransform) == m_pTransformComponents.cend())
			{
				/* The Transform Component's parent is not in the map,
				so add all of the possible parents in the map by calling this function recursively */
				AddTransformComponent(pTransformComponent->GetOwner()->GetParent()->pTransform);
			}

			/* The original Transform Component all of it's parents should have been added to the map */
#ifdef _DEBUG
			ASSERT(m_pTransformComponents.find(pTransformComponent->GetOwner()->GetParent()->pTransform) != m_pTransformComponents.cend(),
				"TransformManager::AddTransformComponent() > The parent has not been added to the map!");

			m_pTransformComponents[pTransformComponent->GetOwner()->GetParent()->pTransform].push_back(pTransformComponent);
#else
			m_pTransformComponents[pTransformComponent->GetOwner()->GetParent()->pTransform].push_back(pTransformComponent);
#endif
		}
	}

	void TransformManager::RemoveTransformComponent(TransformComponent* const pTransformComponent) noexcept
	{
		Utils::Erase_If(m_pTransformComponents, [pTransformComponent](const std::pair<TransformComponent*, std::vector<TransformComponent*>> element)->bool
			{
				return element.first == pTransformComponent;
			});
	}
}