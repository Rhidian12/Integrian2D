#include "PhysicsComponent.h"
#include "../../Locator/Locator.h"
#include "../../PhysicsEngine/PhysicsEngine.h"

namespace Integrian2D
{
	PhysicsComponent::PhysicsComponent(GameObject* pOwner)
		: PhysicsComponent{ pOwner, 1.f, Vector2f{}, nullptr }
	{}

	PhysicsComponent::PhysicsComponent(GameObject* pOwner, const float mass)
		: PhysicsComponent{ pOwner, mass, Vector2f{}, nullptr }
	{}

	PhysicsComponent::PhysicsComponent(GameObject* pOwner, const float mass, const Vector2f velocity)
		: PhysicsComponent{ pOwner, mass, velocity, nullptr }
	{}

	PhysicsComponent::PhysicsComponent(GameObject* pOwner, const float mass, const Vector2f velocity, ColliderComponent* const pCollider)
		: Component{ pOwner }
		, m_PhysicsInfo{ mass, velocity, pCollider }
	{
		Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this);
	}

	PhysicsComponent::~PhysicsComponent()
	{
		Locator::GetInstance()->GetPhysicsEngine()->RemovePhysicsComponent(this);
	}

	Component* PhysicsComponent::Clone(GameObject* const pOwner) noexcept
	{
		return new PhysicsComponent{ pOwner, m_PhysicsInfo.mass, m_PhysicsInfo.velocity, m_PhysicsInfo.pHitbox };
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

	void PhysicsComponent::SetVelocity(const Vector2f velocity) noexcept
	{
		m_PhysicsInfo.velocity = velocity;
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