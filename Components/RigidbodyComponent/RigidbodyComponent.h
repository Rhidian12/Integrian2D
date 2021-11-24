#pragma once

#include "../Component/Component.h"
#include "../../Utils/Utils.h"
#include "../../Locator/Locator.h"

#include <type_traits>
#include <vector>
#include <box2d.h>

namespace Integrian2D
{
	enum class RigidbodyType
	{
		Static = 0,
		Dynamic = 1,
		Kinematic = 2,
		None = 3
	};

	enum class RigidbodyShape
	{
		Circle = 0,
		Edge = 1,
		Polygon = 2,
		Chain = 3,
		None = 4
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

		template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Chain, bool> = true>
		RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const std::vector<Point2f>& points, const float density = 1.f, const float friction = 0.1f);

		template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Polygon, bool> = true>
		RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const std::vector<Point2f>& points, const float density = 1.f, const float friction = 0.1f);
#pragma endregion

		Component* Clone(GameObject* const pOwner) noexcept override;

	private:
		virtual void RootStart() noexcept override;

		RigidbodyType m_RigidbodyType;
		RigidbodyShape m_RigidbodyShape;
		b2Body* m_pBox2DBody;

		constexpr inline static int m_MaxVerticesInChain{ 16 };
	};

	template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Circle, bool>>
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const float circleRadius, const float density, const float friction)
		: Component{ pOwner }
		, m_RigidbodyType{ rigidBodyType }
		, m_RigidbodyShape{ _RigidBodyShape }
		, m_pBox2DBody{}
	{
		ASSERT(!Utils::AreEqual(density, 0.f), "RigidbodyComponent(RigidbodyShape::Circle) > Density may not be 0!");

		b2BodyDef bodyDef{};
		bodyDef.type = static_cast<b2BodyType>(rigidBodyType);

		b2CircleShape shape{};
		shape.m_radius = circleRadius;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;

		m_pBox2DBody = Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this, bodyDef, fixtureDef);
	}

	template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Edge, bool>>
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const PLinef& edge, const float density, const float friction)
		: Component{ pOwner }
		, m_RigidbodyType{ rigidBodyType }
		, m_RigidbodyShape{ _RigidBodyShape }
		, m_pBox2DBody{}
	{
		ASSERT(!Utils::AreEqual(density, 0.f), "RigidbodyComponent(RigidbodyShape::Edge) > Density may not be 0!");

		b2BodyDef bodyDef{};
		bodyDef.type = static_cast<b2BodyType>(rigidBodyType);

		b2EdgeShape shape{};
		shape.m_vertex1 = edge.begin;
		shape.m_vertex2 = edge.end;

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;

		m_pBox2DBody = Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this, bodyDef, fixtureDef);
	}

	template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Polygon, bool>>
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const std::vector<Point2f>& points, const float density, const float friction)
		: Component{ pOwner }
		, m_RigidbodyType{ rigidBodyType }
		, m_RigidbodyShape{ _RigidBodyShape }
		, m_pBox2DBody{}
	{
		ASSERT(!Utils::AreEqual(density, 0.f), "RigidbodyComponent(RigidbodyShape::Polygon) > Density may not be 0!");
		ASSERT(points.size() <= b2_maxPolygonVertices, std::string{ "RigidbodyComponent(RigidbodyShape::Polygon) > There may only be " } + std::to_string(b2_maxPolygonVertices) + " vertices in a polygon");

		b2BodyDef bodyDef{};
		bodyDef.type = static_cast<b2BodyType>(rigidBodyType);

		b2PolygonShape shape{};
		b2Vec2* pPoints[b2_maxPolygonVertices]{};

		for (size_t i{}; i < points.size(); ++i)
			pPoints[i] = b2Vec2{ points[i].x, points[i].y };

		shape.Set(pPoints, points.size());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;

		m_pBox2DBody = Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this, bodyDef, fixtureDef);
	}

	template<RigidbodyShape _RigidBodyShape, std::enable_if_t<_RigidBodyShape == RigidbodyShape::Chain, bool>>
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, const RigidbodyType rigidBodyType, const std::vector<Point2f>& points, const float density, const float friction)
		: Component{ pOwner }
		, m_RigidbodyType{ rigidBodyType }
		, m_RigidbodyShape{ _RigidBodyShape }
		, m_pBox2DBody{}
	{
		ASSERT(!Utils::AreEqual(density, 0.f), "RigidbodyComponent(RigidbodyShape::Chain) > Density may not be 0!");
		ASSERT(points.size() <= m_MaxVerticesInChain, std::string{ "RigidbodyComponent(RigidbodyShape::Chain) > There may only be " } + std::to_string(m_MaxVerticesInChain) + " vertices in a chain");

		b2BodyDef bodyDef{};
		bodyDef.type = static_cast<b2BodyType>(rigidBodyType);

		b2ChainShape shape{};
		b2Vec2* pPoints[m_MaxVerticesInChain]{};

		for (size_t i{}; i < points.size(); ++i)
			pPoints[i] = b2Vec2{ points[i].x, points[i].y };

		shape.CreateLoop(pPoints, points.size());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = density;
		fixtureDef.friction = friction;

		m_pBox2DBody = Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this, bodyDef, fixtureDef);
	}
}