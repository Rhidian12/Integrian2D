#pragma once

#include "../Component/Component.h"
#include "../../Utils/Utils.h"
#include "../../Locator/Locator.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"

#include <type_traits>
#include <box2d.h>

namespace Integrian2D
{
	enum class RigidbodyType
	{
		Static = 0,
		Dynamic = 1,
		Kinematic = 2
	};

	enum class RigidbodyShape
	{
		Circle = 0,
		Edge = 1,
		Polygon = 2,
		Chain = 3,
		TypeCount = 4
	};

	class RigidbodyComponent final : public Component
	{
	public:
		RigidbodyComponent(GameObject* const pOwner);

#pragma region Templated Constructors
		template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Circle, bool> = true>
		RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const float circleRadius, const float density = 1.f, const float friction = 0.1f);
		template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Edge, bool> = true>
		RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const PLinef& edge, const float density = 1.f, const float friction = 0.1f);
#pragma endregion

		Component* Clone(GameObject* const pOwner) noexcept override;

	private:
		virtual void RootStart() noexcept override;

		RigidbodyType m_RigidbodyType;
		RigidbodyShape m_RigidbodyShape;
	};

	template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Circle, bool>>
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const float circleRadius, const float density, const float friction)
		: Component{ pOwner }
		, m_RigidbodyType{ rigidBodyType }
		, m_RigidbodyShape{ _RigidBodyShape }
	{
		ASSERT(!Utils::AreEqual(density, 0.f), "RigidbodyComponent(RigidbodyShape::Circle) > Density may not be 0!");

		b2BodyDef bodyDef{};

		bodyDef.type = static_cast<b2BodyType>(rigidBodyType);
		bodyDef.position.Set(pOwner->pTransform->GetWorldPosition().x, pOwner->pTransform->GetWorldPosition().y);

		b2CircleShape shape{};
		shape.m_radius = circleRadius;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;

		Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this, bodyDef, fixtureDef);
	}

	template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Edge, bool>>
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const PLinef& edge, const float density, const float friction)
		: Component{ pOwner }
		, m_RigidbodyType{ rigidBodyType }
		, m_RigidbodyShape{ _RigidBodyShape }
	{
		ASSERT(!Utils::AreEqual(density, 0.f), "RigidbodyComponent(RigidbodyShape::Edge) > Density may not be 0!");

		b2BodyDef bodyDef{};

		bodyDef.type = static_cast<b2BodyType>(rigidBodyType);
		bodyDef.position.Set(pOwner->pTransform->GetWorldPosition().x, pOwner->pTransform->GetWorldPosition().y);

		b2EdgeShape shape{};
		shape.m_vertex1 = edge.begin;
		shape.m_vertex2 = edge.end;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;

		Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this, bodyDef, fixtureDef);
	}
}