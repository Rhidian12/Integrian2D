#include "AIComponent.h"
#include "../../AI/Blackboard/Blackboard.h"
#include "../../AI/DecisionMaking/BaseDecisionMaking/BaseDecisionMaking.h"
#include "../../Utils/Utils.h"

namespace Integrian2D
{
	AIComponent::AIComponent(GameObject* const pOwner, Blackboard* const pBlackboard, BaseDecisionMaking* const pAI)
		: Component{ pOwner }
		, m_pBlackboard{ pBlackboard }
		, m_pDecisionMaking{ pAI }
	{}

	AIComponent::~AIComponent()
	{
		Utils::SafeDelete(m_pBlackboard);
		Utils::SafeDelete(m_pDecisionMaking);
	}

#pragma region Rule Of 5
	AIComponent::AIComponent(const AIComponent& other) noexcept
		: Component{ m_pOwner }
		, m_pBlackboard{ new Blackboard{ *other.m_pBlackboard } }
		, m_pDecisionMaking{ other.m_pDecisionMaking->Clone() }
	{

	}

	AIComponent::AIComponent(AIComponent&& other) noexcept
		: Component{ m_pOwner }
		, m_pBlackboard{ std::move(other.m_pBlackboard) }
		, m_pDecisionMaking{ std::move(other.m_pDecisionMaking) }
	{
		other.m_pBlackboard = nullptr;
		other.m_pDecisionMaking = nullptr;
	}

	AIComponent& AIComponent::operator=(const AIComponent& other) noexcept
	{
		m_pBlackboard = new Blackboard{ *other.m_pBlackboard };
		m_pDecisionMaking = other.m_pDecisionMaking->Clone();

		return *this;
	}

	AIComponent& AIComponent::operator=(AIComponent&& other) noexcept
	{
		m_pBlackboard = std::move(other.m_pBlackboard);
		m_pDecisionMaking = std::move(other.m_pDecisionMaking);

		other.m_pBlackboard = nullptr;
		other.m_pDecisionMaking = nullptr;

		return *this;
	}
#pragma endregion

	Component* AIComponent::Clone(GameObject* pOwner) noexcept
	{
		return new AIComponent{ pOwner, m_pBlackboard, m_pDecisionMaking };
	}

	void AIComponent::Update()
	{
		m_pDecisionMaking->Update(m_pBlackboard);
	}

	Blackboard* const AIComponent::GetBlackboard() const noexcept
	{
		return m_pBlackboard;
	}

	BaseDecisionMaking* const AIComponent::GetDecisionMaking() const noexcept
	{
		return m_pDecisionMaking;
	}

	BehaviourState AIComponent::GetCurrentState() const noexcept
	{
		return m_pDecisionMaking->GetCurrentState();
	}
}