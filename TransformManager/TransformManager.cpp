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

	void TransformManager::UpdateTransforms() noexcept
	{
		/* Check if any of the transform components have moved */
		/* Check a parent, then check its children */
		for (const auto& [Parent, Children] : m_pTransformComponents)
		{
			if (Parent->GetHasMoved()) /* The Parent has moved, so inform all of its children */
				InformChildren(Parent);
			else /* The Parent has not moved, so check each of its children */
				for (TransformComponent* const pChild : Children)
					if (pChild->GetHasMoved()) /* The Child has moved so inform all of its children */
						InformChildren(pChild);
		}

		for (const auto& [Parent, Children] : m_pTransformComponents)
		{
			if (Parent->GetHasMoved()) /* The Parent has moved, so move all of its children */
				MoveChildren(Parent);
			else
				for (TransformComponent* const pChild : Children)
					if (pChild->GetHasMoved()) /* The Child has moved so move all of its children */
						MoveChildren(pChild);
		}
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


	void TransformManager::InformChildren(TransformComponent* const pParent) noexcept
	{
		const std::unordered_map<TransformComponent*, std::vector<TransformComponent*>>::const_iterator cIt{ m_pTransformComponents.find(pParent) };
		if (cIt == m_pTransformComponents.cend())
			return;

		/* Recursively call this function to inform all of the children */
		for (TransformComponent* const pChild : cIt->second)
		{
			/* First check if the child hasn't been informed already */
			if (!pChild->GetHasMoved())
			{
				pChild->SetHasMoved(true);
				InformChildren(pChild);
			}
		}
	}

	void TransformManager::MoveChildren(TransformComponent* const pParent) noexcept
	{
		const std::unordered_map<TransformComponent*, std::vector<TransformComponent*>>::const_iterator cIt{ m_pTransformComponents.find(pParent) };
		if (cIt == m_pTransformComponents.cend())
			return;

		/* Recursively call this function to move all of the children */
		for (TransformComponent* const pChild : cIt->second)
		{
			/* First check if the child has been informed to move */
			if (pChild->GetHasMoved())
			{
				pChild->CalculateNewWorldPosition();
				MoveChildren(pChild);
			}
		}
	}
}