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
		for (auto it{ m_pTransformComponents.begin() }; it != m_pTransformComponents.end(); ++it)
			if (it->pTransform->GetHasMoved()) /* The Parent has moved, so inform all of its children */
				InformChildren(it->pTransform);

		for (auto it{ m_pTransformComponents.begin() }; it != m_pTransformComponents.end(); ++it)
			if (it->pTransform->GetHasMoved()) /* The Parent has moved, so move all of its children */
				MoveTree(it->pTransform);
	}

	void TransformManager::AddTransformComponent(TransformComponent* const pTransformComponent) noexcept
	{
		/* If the Transform Component has no parent, it is the root parent */
		if (pTransformComponent->GetOwner()->GetParent() == nullptr)
		{
			/* If there are no roots yet, we can just add our first root */
			if (m_pTransformComponents.empty())
			{
				TransformComponentNode node{ nullptr, pTransformComponent, nullptr };
				node.pRoot = &node;
				m_pTransformComponents.push_back(node);
			}
			else
			{
				/* Check whether the pTransformComponent its parent is in any of the roots */
				const auto cIt{ std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pTransformComponent](const TransformComponentNode& node)->bool
					{
						return pTransformComponent->GetOwner()->GetParent()->pTransform == node.pRoot->pTransform;
					}) };

				/* If it's not present in the vector, we should make a new root node */
				if (cIt == m_pTransformComponents.cend())
				{
					/* Make the new root node */
					TransformComponentNode node{ nullptr, pTransformComponent, nullptr };
					node.pRoot = &node;

					/* Find the last root node */
					for (size_t i{ m_pTransformComponents.size() - 1 }; i > 0; --i)
					{
						/* If the next root isn't set, we've found the end of our roots */
						if (!m_pTransformComponents[i].pNextRoot)
						{
							m_pTransformComponents[i].pNextRoot = &node;

							m_pTransformComponents.push_back(node);

							break; /* we did what we had to do, so stop the loop*/
						}
					}
				}
			}
		}
		else /* The Transform Component has a parent, so it is a child */
		{
			/* Is the Transform Component's parent in the vector? */
			TransformComponent* pParent{ pTransformComponent->GetOwner()->GetParent()->pTransform };
			const auto cIt{ std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pParent](const TransformComponentNode& node)->bool
				{
					return node.pRoot->pTransform == pParent;
				}) };

			/* The Transform Component its parent is NOT present in the vector, so a new root must be made */
			if (cIt == m_pTransformComponents.cend())
			{
				/* We'll do this by recursively calling this function with the Transform Component's parent */
				AddTransformComponent(pParent);
			}

			/* The original Transform Component all of it's parents should have been added to the vector */
#ifdef _DEBUG
			auto it{ std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pParent](const TransformComponentNode& node)->bool
				{
					return node.pRoot->pTransform == pParent;
				}) };

			std::advance(it, it->pNextRoot - it->pRoot);

			m_pTransformComponents.insert(it, TransformComponentNode{ it->pRoot, pTransformComponent, it->pNextRoot });

			ASSERT(std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pParent](const TransformComponentNode& node)->bool
				{
					return node.pRoot->pTransform == pParent;
		}) != m_pTransformComponents.cend(), "TransformManager::AddTransformComponent() > The parent has not been added to the map!");
#else
			m_pTransformComponents[pTransformComponent->GetOwner()->GetParent()->pTransform].push_back(pTransformComponent);
#endif
	}
}

	void TransformManager::RemoveTransformComponent(TransformComponent* const pTransformComponent) noexcept
	{
		m_pTransformComponents.erase(std::remove_if(m_pTransformComponents.begin(), m_pTransformComponents.end(), [pTransformComponent](const TransformComponentNode& element)->bool
			{
				return element.pTransform == pTransformComponent;
			}), m_pTransformComponents.end());
	}

	void TransformManager::InformChildren(TransformComponent* const pParent) noexcept
	{
		/* Make sure the Parent is informed as well */
		pParent->SetHasMoved(true);

		/* Check if this Parent has children */
		const auto cIt{ std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pParent](const TransformComponentNode& node)->bool
			{
				return node.pRoot->pTransform == pParent;
			}) };

		if (cIt == m_pTransformComponents.cend())
			return;

		/* Recursively call this function to inform all of the children */
		for (auto it{ cIt }; it != m_pTransformComponents.end(); ++it)
		{
			if (it->pRoot != cIt->pRoot)
				break;
			else
			{
				if (!it->pTransform->GetHasMoved())
				{
					it->pTransform->SetHasMoved(true);
					InformChildren(it->pTransform);
				}
			}
		}
	}

	void TransformManager::MoveTree(TransformComponent* const pParent) noexcept
	{
		/* Move the Parent */
		pParent->CalculateNewWorldPosition();

		/* Check if this Parent has children */
		const auto cIt{ std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pParent](const TransformComponentNode& node)->bool
			{
				return node.pRoot->pTransform == pParent;
			}) };

		if (cIt == m_pTransformComponents.cend())
			return;

		/* Recursively call this function to move all of the children */
		for (auto it{ cIt }; it != m_pTransformComponents.end(); ++it)
		{
			if (it->pRoot != cIt->pRoot)
				break;
			else
			{
				if (it->pTransform->GetHasMoved())
				{
					it->pTransform->CalculateNewWorldPosition();
					MoveTree(it->pTransform);
				}
			}
		}
	}
}