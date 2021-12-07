#include "TransformManager.h"
#include "../Utils/Utils.h"
#include "../Components/TransformComponent/TransformComponent.h"
#include "../GameObject/GameObject.h"

#include <algorithm>

namespace Integrian2D
{
	TransformManager::TransformManager()
		: m_pTransformComponents{}
		, m_pHead{}
		, m_HasATransformBeenChanged{}
	{}

	TransformManager::~TransformManager() noexcept
	{
		for (TransformComponentNode* pNode : m_pTransformComponents)
			Utils::SafeDelete(pNode);
	}

	void TransformManager::UpdateTransforms() noexcept
	{
		if (m_HasATransformBeenChanged)
		{
			std::unique_lock<std::mutex> lock{ m_Mutex }; /* Acquire the lock */

			/* safety check */
			if (m_pTransformComponents.empty())
				return;

			/* Check if any of the transform components have moved */
			/* Check a parent, then check its children */
			for (auto it{ m_pTransformComponents.begin() }; it != m_pTransformComponents.end(); ++it)
				if ((*it)->pTransform->GetHasMoved()) /* The Parent has moved, so inform all of its children */
					InformChildren((*it)->pTransform);

			for (auto it{ m_pTransformComponents.begin() }; it != m_pTransformComponents.end(); ++it)
				if ((*it)->pTransform->GetHasMoved()) /* The Parent has moved, so move all of its children */
					MoveTree((*it)->pTransform);

			m_HasATransformBeenChanged = false;
		}
	}

	void TransformManager::AddTransformComponent(TransformComponent* const pTransformComponent) noexcept
	{
		std::unique_lock<std::mutex> lock{ m_Mutex }; /* Acquire the lock */

		if (std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pTransformComponent](TransformComponentNode* pNode)->bool
			{
				return pNode->pTransform == pTransformComponent;
			}) != m_pTransformComponents.cend())
		{
			return;
		}

			/* If the Transform Component has no parent, it is the root parent */
			if (pTransformComponent->GetOwner()->GetParent() == nullptr)
			{
				/* If there are no roots yet, we can just add our first root */
				if (m_pTransformComponents.empty())
				{
					TransformComponentNode* pNode{ new TransformComponentNode{ nullptr, pTransformComponent, nullptr, nullptr } };
					pNode->pPreviousNode = pNode;
					pNode->pNextNode = pNode;
					m_pTransformComponents.push_back(pNode);

					m_pHead = pNode;

					pTransformComponent->m_pTransformManager = this;
				}
				else
				{
					/* Make the new root node */
					TransformComponentNode* pNode{ new TransformComponentNode{ m_pHead->pPreviousNode, pTransformComponent, m_pHead, nullptr } };

					m_pHead->pPreviousNode->pNextNode = pNode;
					m_pHead->pPreviousNode = pNode;

					m_pTransformComponents.push_back(pNode);

					pTransformComponent->m_pTransformManager = this;
				}
			}
			else /* The Transform Component has a parent, so it is a child */
			{
				/* Is the Transform Component's parent in the vector? */
				TransformComponent* pParent{ pTransformComponent->GetOwner()->GetParent()->pTransform };
				const auto cIt{ std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pParent](const TransformComponentNode* node)->bool
					{
						return node->pPreviousNode->pTransform == pParent;
					}) };

				/* The Transform Component its parent is NOT present in the vector, so a new root must be made */
				if (cIt == m_pTransformComponents.cend())
				{
					/* We'll do this by recursively calling this function with the Transform Component's parent */
					AddTransformComponent(pParent);
				}

				/* The original Transform Component all of it's parents should have been added to the vector */
				auto wantedParent = std::find_if(m_pTransformComponents.begin(), m_pTransformComponents.end(), [pParent](const TransformComponentNode* const pNode)->bool
					{
						return pNode->pTransform == pParent;
					});

				/* Find the next parent, if it exists */
				auto nextParent = m_pTransformComponents.end();
				for (auto it{ wantedParent + 1 }; it != m_pTransformComponents.end(); ++it)
					if ((*it)->pParent != (*wantedParent)->pParent)
						nextParent = it;

				/* There is no next parent */
				if (nextParent == m_pTransformComponents.end())
				{
					TransformComponentNode* pNode{ new TransformComponentNode{ m_pHead->pPreviousNode, pTransformComponent, m_pHead, *wantedParent} };

					m_pHead->pPreviousNode->pNextNode = pNode;
					m_pHead->pPreviousNode = pNode;

					m_pTransformComponents.push_back(pNode);
					pTransformComponent->m_pTransformManager = this;
				}
				else
				{
					TransformComponentNode* pNode{ new TransformComponentNode{ *nextParent, pTransformComponent, (*nextParent)->pNextNode, *wantedParent } };

					(*nextParent)->pNextNode->pPreviousNode = pNode;
					(*nextParent)->pNextNode = pNode;

					m_pTransformComponents.insert(nextParent, pNode);
					pTransformComponent->m_pTransformManager = this;
				}

				ASSERT(std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pParent](const TransformComponentNode* node)->bool
					{
						return node->pPreviousNode->pTransform == pParent;
					}) != m_pTransformComponents.cend(), "TransformManager::AddTransformComponent() > The parent has not been added to the map!");
			}
	}

	void TransformManager::RemoveTransformComponent(TransformComponent* const pTransformComponent) noexcept
	{
		std::unique_lock<std::mutex> lock{ m_Mutex }; /* Acquire the lock */

		m_pTransformComponents.erase(std::remove_if(m_pTransformComponents.begin(), m_pTransformComponents.end(), [pTransformComponent](const TransformComponentNode* element)->bool
			{
				return element->pTransform == pTransformComponent;
			}), m_pTransformComponents.end());
	}

	void TransformManager::ForceImmediateRecalculation(TransformComponent* const pTransformComponent) noexcept
	{
		std::unique_lock<std::mutex> lock{ m_Mutex }; /* Acquire the lock */

		InformChildren(pTransformComponent);
		MoveTree(pTransformComponent);
	}

	void TransformManager::NotifyRecalculation() noexcept
	{
		m_HasATransformBeenChanged = true;
	}

	void TransformManager::InformChildren(TransformComponent* const pRoot) noexcept
	{
		/* Make sure the root node is informed as well */
		pRoot->SetHasMoved(true);

		/* Check if this root node has children */

		/* First find this root node in the list */
		const auto rootNodeCIt{ std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pRoot](const TransformComponentNode* node)->bool
			{
				return node->pTransform == pRoot;
			}) };

		/* Safety check */
		if (rootNodeCIt == m_pTransformComponents.cend())
			return;

		/* The node after the root node should be this root node's child, if it exists
			if the next node does not have a pParent, it is another root node */
		if ((rootNodeCIt + 1) == m_pTransformComponents.cend() || (*(rootNodeCIt + 1))->pParent == nullptr)
			return;

		/* Inform all of this root node's children */

		/* We start the for-loop at the root node's first child
			and we keep going until we encounter a node that doesn't have a pParent */
		for (auto it{ rootNodeCIt + 1 }; it != m_pTransformComponents.cend() && (*it)->pParent != nullptr; ++it)
		{
			/* if the child hasnt moved already */
			if (!(*it)->pTransform->GetHasMoved())
				(*it)->pTransform->SetHasMoved(true);
		}
	}

	void TransformManager::MoveTree(TransformComponent* const pRoot) noexcept
	{
		/* Move the root node */
		pRoot->RecalculateWorldData();

		/* Check if this root node has children */

		/* First find this root node in the list */
		const auto rootNodeCIt{ std::find_if(m_pTransformComponents.cbegin(), m_pTransformComponents.cend(), [pRoot](const TransformComponentNode* node)->bool
			{
				return node->pTransform == pRoot;
			}) };

		/* Safety check */
		if (rootNodeCIt == m_pTransformComponents.cend())
			return;

		/* The node after the root node should be this root node's child, if it exists
			if the next node does not have a pParent, it is another root node */
		if ((rootNodeCIt + 1) == m_pTransformComponents.cend() || (*(rootNodeCIt + 1))->pParent == nullptr)
			return;

		/* Move all of this root node's children */

		/* We start the for-loop at the root node's first child
			and we keep going until we encounter a node that doesn't have a pParent */
		for (auto it{ rootNodeCIt + 1 }; it != m_pTransformComponents.cend() && (*it)->pParent != nullptr; ++it)
		{
			/* if the child hasnt moved already */
			if ((*it)->pTransform->GetHasMoved())
				(*it)->pTransform->RecalculateWorldData();
		}
	}

	bool TransformManager::ShouldRecalculate() const noexcept
	{
		return m_HasATransformBeenChanged;
	}
}