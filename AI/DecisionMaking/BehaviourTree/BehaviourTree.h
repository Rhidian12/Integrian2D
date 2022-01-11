#pragma once

#include "../../../Integrian2D_API.h"
#include "../BaseDecisionMaking/BaseDecisionMaking.h"

#include <functional>
#include <vector>

namespace Integrian2D
{
	class INTEGRIAN2D_API BehaviourTreeNode
	{
	public:
		 virtual ~BehaviourTreeNode() = default;

		virtual BehaviourTreeNode* Clone() noexcept = 0;

		virtual BehaviourState Execute(Blackboard* const) const = 0;
	};

	class INTEGRIAN2D_API ActionNode final : public BehaviourTreeNode
	{
	public:
		using Action = std::function<BehaviourState(Blackboard* const)>;

		ActionNode(const Action& action);

		virtual BehaviourTreeNode* Clone() noexcept override;

		virtual BehaviourState Execute(Blackboard* const pBlackboard) const override;

	private:
		Action m_Action;
	};

	class INTEGRIAN2D_API ConditionalNode final : public BehaviourTreeNode
	{
	public:
		using Predicate = std::function<bool(Blackboard* const)>;

		ConditionalNode(const Predicate& predicate);

		virtual BehaviourTreeNode* Clone() noexcept override;

		virtual BehaviourState Execute(Blackboard* const pBlackboard) const override;

	private:
		Predicate m_Predicate;
	};

	class INTEGRIAN2D_API InvertedConditionalNode final : public BehaviourTreeNode
	{
	public:
		using Predicate = std::function<bool(Blackboard* const)>;

		InvertedConditionalNode(const Predicate& predicate);

		virtual BehaviourTreeNode* Clone() noexcept override;

		virtual BehaviourState Execute(Blackboard* const pBlackboard) const override;

	private:
		Predicate m_Predicate;
	};

	class INTEGRIAN2D_API SequenceNode final : public BehaviourTreeNode
	{
	public:
		SequenceNode(const std::vector<BehaviourTreeNode*>& nodes);
		~SequenceNode();

		SequenceNode(const SequenceNode& other) noexcept;
		SequenceNode(SequenceNode&& other) noexcept;
		SequenceNode& operator=(const SequenceNode& other) noexcept;
		SequenceNode& operator=(SequenceNode&& other) noexcept;

		virtual BehaviourTreeNode* Clone() noexcept override;

		virtual BehaviourState Execute(Blackboard* const pBlackboard) const override;

	private:
		std::vector<BehaviourTreeNode*> m_Nodes;
	};

	class BehaviourTree final : public BaseDecisionMaking
	{
	public:
		INTEGRIAN2D_API BehaviourTree(const std::vector<BehaviourTreeNode*>& nodes);
		INTEGRIAN2D_API ~BehaviourTree();

		INTEGRIAN2D_API BehaviourTree(const BehaviourTree& other) noexcept;
		INTEGRIAN2D_API BehaviourTree(BehaviourTree&& other) noexcept;
		INTEGRIAN2D_API BehaviourTree& operator=(const BehaviourTree& other) noexcept;
		INTEGRIAN2D_API BehaviourTree& operator=(BehaviourTree&& other) noexcept;

		INTEGRIAN2D_API virtual BaseDecisionMaking* Clone() noexcept override;

		INTEGRIAN2D_API virtual BehaviourState Update(Blackboard* const pBlackboard) override;

	private:
		std::vector<BehaviourTreeNode*> m_Nodes;
		const BehaviourTreeNode* m_pCurrentNode;
	};
}