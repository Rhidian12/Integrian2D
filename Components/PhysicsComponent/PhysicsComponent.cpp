#include "PhysicsComponent.h"
#include "../../Locator/Locator.h"
#include "../../PhysicsEngine/PhysicsEngine.h"

namespace Integrian2D
{
	PhysicsComponent::PhysicsComponent(GameObject* pOwner)
		: PhysicsComponent{ pOwner, 1.f, 1.f, nullptr }
	{}

	PhysicsComponent::PhysicsComponent(GameObject* pOwner, const float mass, const float drag)
		: PhysicsComponent{ pOwner, mass, drag, nullptr }
	{}

	PhysicsComponent::PhysicsComponent(GameObject* pOwner, const float mass, const float drag, ColliderComponent* const pCollider)
		: Component{ pOwner }
		, m_PhysicsInfo{ mass, drag, Vector2f{}, pCollider }
	{
		Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this);
	}

	PhysicsComponent::~PhysicsComponent()
	{
		Locator::GetInstance()->GetPhysicsEngine()->RemovePhysicsComponent(this);
	}

	Component* PhysicsComponent::Clone(GameObject* const pOwner) noexcept
	{
		PhysicsComponent* pPhysicsComponent{ new PhysicsComponent{ pOwner } };

		pPhysicsComponent->m_PhysicsInfo = m_PhysicsInfo;

		return pPhysicsComponent;
	}

	bool PhysicsComponent::CheckCollision(PhysicsComponent* const pOtherCollider) noexcept
	{
		return m_PhysicsInfo.pHitbox->CheckCollision(pOtherCollider->GetPhysicsInfo().pHitbox);
	}

	void PhysicsComponent::AddForce(const Vector2f& force) noexcept
	{
		m_PhysicsInfo.velocity += (force * m_PhysicsInfo.mass);
	}

	void PhysicsComponent::SetMass(const float mass) noexcept
	{
		m_PhysicsInfo.mass = mass;
	}

	void PhysicsComponent::SetVelocity(const Vector2f& velocity) noexcept
	{
		m_PhysicsInfo.velocity = velocity;
	}

	void PhysicsComponent::SetIsAffectedByGravity(const bool isAffectedByGravity) noexcept
	{
		m_PhysicsInfo.gravity = isAffectedByGravity;
	}

	void PhysicsComponent::SetColliderComponent(ColliderComponent* const pCollider, ColliderShape shape) noexcept
	{
		m_PhysicsInfo.pHitbox = pCollider;
		m_PhysicsInfo.pHitbox->SetColliderShape(shape);
	}

	const PhysicsInfo& PhysicsComponent::GetPhysicsInfo() const noexcept
	{
		return m_PhysicsInfo;
	}
}