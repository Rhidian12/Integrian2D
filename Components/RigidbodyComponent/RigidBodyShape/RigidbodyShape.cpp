#include "RigidbodyShape.h"

#include <string>

namespace Integrian2D
{
	RigidbodyShape::RigidbodyShape()
		: m_RigidbodyType{ RigidbodyType::None }
		, m_RigidbodyShape{ PossibleRigidbodyShapes::None }
		, m_BodyDefinition{}
		, m_RigidbodyFixtures{}
		, m_pShapeDefinition{}
		, m_FixtureDefinitions{}
		, m_RigidbodyDefinition{}
	{}

	const b2BodyDef& RigidbodyShape::GetBox2DBodyDefinition() const noexcept
	{
		return m_BodyDefinition;
	}

	const std::vector<b2FixtureDef>& RigidbodyShape::GetBox2DFixtureDefinitions() const noexcept
	{
		return m_FixtureDefinitions;
	}

	RigidbodyShape* const RigidbodyShape::CreateCircle(const RigidbodyDefinition& rigidbodyDefinition, const float circleRadius, const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		ASSERT(!Utils::AreEqual(rigidbodyFixture.density, 0.f), "RigidbodyShape::CreateCircle() > Density may not be 0!");

		RigidbodyShape* pRigidbodyShape{ new RigidbodyShape{} };
		pRigidbodyShape->m_RigidbodyDefinition = rigidbodyDefinition;
		pRigidbodyShape->m_RigidbodyDefinition.pShape = pRigidbodyShape;

		pRigidbodyShape->m_BodyDefinition.type = static_cast<b2BodyType>(rigidbodyDefinition.rigidbodyType);
		pRigidbodyShape->m_BodyDefinition.position = b2Vec2{ rigidbodyDefinition.position.x, rigidbodyDefinition.position.y };
		pRigidbodyShape->m_BodyDefinition.angle = rigidbodyDefinition.angle;
		pRigidbodyShape->m_BodyDefinition.linearVelocity = b2Vec2{ rigidbodyDefinition.linearVelocity.x, rigidbodyDefinition.linearVelocity.y };
		pRigidbodyShape->m_BodyDefinition.angularVelocity = rigidbodyDefinition.angularVelocity;
		pRigidbodyShape->m_BodyDefinition.linearDamping = rigidbodyDefinition.linearDamping;
		pRigidbodyShape->m_BodyDefinition.angularDamping = rigidbodyDefinition.angularDamping;
		pRigidbodyShape->m_BodyDefinition.allowSleep = rigidbodyDefinition.allowSleep;
		pRigidbodyShape->m_BodyDefinition.awake = rigidbodyDefinition.isAwake;
		pRigidbodyShape->m_BodyDefinition.fixedRotation = rigidbodyDefinition.fixedRotation;
		pRigidbodyShape->m_BodyDefinition.bullet = rigidbodyDefinition.isBullet;
		pRigidbodyShape->m_BodyDefinition.enabled = rigidbodyDefinition.isEnabled;
		pRigidbodyShape->m_BodyDefinition.gravityScale = rigidbodyDefinition.gravityScale;

		pRigidbodyShape->m_RigidbodyShape = PossibleRigidbodyShapes::Circle;

		pRigidbodyShape->m_pShapeDefinition = new b2CircleShape{};
		pRigidbodyShape->m_pShapeDefinition->m_radius = circleRadius;

		pRigidbodyShape->m_FixtureDefinitions.push_back(b2FixtureDef{});
		pRigidbodyShape->m_FixtureDefinitions.back().shape = pRigidbodyShape->m_pShapeDefinition;
		pRigidbodyShape->m_FixtureDefinitions.back().density = rigidbodyFixture.density;
		pRigidbodyShape->m_FixtureDefinitions.back().friction = rigidbodyFixture.friction;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.maskBits = rigidbodyFixture.filter.maskBits;
		pRigidbodyShape->m_FixtureDefinitions.back().isSensor = rigidbodyFixture.isTrigger;
		pRigidbodyShape->m_FixtureDefinitions.back().restitution = rigidbodyFixture.restitution;
		pRigidbodyShape->m_FixtureDefinitions.back().restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		pRigidbodyShape->m_RigidbodyFixtures.push_back(rigidbodyFixture);

		return pRigidbodyShape;
	}

	RigidbodyShape* const RigidbodyShape::CreateEdge(const RigidbodyDefinition& rigidbodyDefinition, const PLinef& edge, const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		ASSERT(!Utils::AreEqual(rigidbodyFixture.density, 0.f), "RigidbodyShape::CreateEdge() > Density may not be 0!");

		RigidbodyShape* pRigidbodyShape{ new RigidbodyShape{} };
		pRigidbodyShape->m_RigidbodyDefinition = rigidbodyDefinition;
		pRigidbodyShape->m_RigidbodyDefinition.pShape = pRigidbodyShape;

		pRigidbodyShape->m_BodyDefinition.type = static_cast<b2BodyType>(rigidbodyDefinition.rigidbodyType);
		pRigidbodyShape->m_BodyDefinition.position = b2Vec2{ rigidbodyDefinition.position.x, rigidbodyDefinition.position.y };
		pRigidbodyShape->m_BodyDefinition.angle = rigidbodyDefinition.angle;
		pRigidbodyShape->m_BodyDefinition.linearVelocity = b2Vec2{ rigidbodyDefinition.linearVelocity.x, rigidbodyDefinition.linearVelocity.y };
		pRigidbodyShape->m_BodyDefinition.angularVelocity = rigidbodyDefinition.angularVelocity;
		pRigidbodyShape->m_BodyDefinition.linearDamping = rigidbodyDefinition.linearDamping;
		pRigidbodyShape->m_BodyDefinition.angularDamping = rigidbodyDefinition.angularDamping;
		pRigidbodyShape->m_BodyDefinition.allowSleep = rigidbodyDefinition.allowSleep;
		pRigidbodyShape->m_BodyDefinition.awake = rigidbodyDefinition.isAwake;
		pRigidbodyShape->m_BodyDefinition.fixedRotation = rigidbodyDefinition.fixedRotation;
		pRigidbodyShape->m_BodyDefinition.bullet = rigidbodyDefinition.isBullet;
		pRigidbodyShape->m_BodyDefinition.enabled = rigidbodyDefinition.isEnabled;
		pRigidbodyShape->m_BodyDefinition.gravityScale = rigidbodyDefinition.gravityScale;

		pRigidbodyShape->m_RigidbodyShape = PossibleRigidbodyShapes::Edge;

		pRigidbodyShape->m_pShapeDefinition = new b2EdgeShape{};
		static_cast<b2EdgeShape*>(pRigidbodyShape->m_pShapeDefinition)->m_vertex1 = b2Vec2{ edge.begin.x, edge.begin.y };
		static_cast<b2EdgeShape*>(pRigidbodyShape->m_pShapeDefinition)->m_vertex1 = b2Vec2{ edge.end.x, edge.end.y };

		pRigidbodyShape->m_FixtureDefinitions.push_back(b2FixtureDef{});
		pRigidbodyShape->m_FixtureDefinitions.back().shape = pRigidbodyShape->m_pShapeDefinition;
		pRigidbodyShape->m_FixtureDefinitions.back().density = rigidbodyFixture.density;
		pRigidbodyShape->m_FixtureDefinitions.back().friction = rigidbodyFixture.friction;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.maskBits = rigidbodyFixture.filter.maskBits;
		pRigidbodyShape->m_FixtureDefinitions.back().isSensor = rigidbodyFixture.isTrigger;
		pRigidbodyShape->m_FixtureDefinitions.back().restitution = rigidbodyFixture.restitution;
		pRigidbodyShape->m_FixtureDefinitions.back().restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		pRigidbodyShape->m_RigidbodyFixtures.push_back(rigidbodyFixture);

		return pRigidbodyShape;
	}

	RigidbodyShape* const RigidbodyShape::CreatePolygon(const RigidbodyDefinition& rigidbodyDefinition, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		ASSERT(!Utils::AreEqual(rigidbodyFixture.density, 0.f), "RigidbodyShape::CreatePolygon() > Density may not be 0!");
		ASSERT(points.size() <= b2_maxPolygonVertices, std::string{ "RigidbodyShape::CreatePolygon() > There may only be " } + std::to_string(b2_maxPolygonVertices) + " vertices in a polygon");

		RigidbodyShape* pRigidbodyShape{ new RigidbodyShape{} };
		pRigidbodyShape->m_RigidbodyDefinition = rigidbodyDefinition;
		pRigidbodyShape->m_RigidbodyDefinition.pShape = pRigidbodyShape;

		pRigidbodyShape->m_BodyDefinition.type = static_cast<b2BodyType>(rigidbodyDefinition.rigidbodyType);
		pRigidbodyShape->m_BodyDefinition.position = b2Vec2{ rigidbodyDefinition.position.x, rigidbodyDefinition.position.y };
		pRigidbodyShape->m_BodyDefinition.angle = rigidbodyDefinition.angle;
		pRigidbodyShape->m_BodyDefinition.linearVelocity = b2Vec2{ rigidbodyDefinition.linearVelocity.x, rigidbodyDefinition.linearVelocity.y };
		pRigidbodyShape->m_BodyDefinition.angularVelocity = rigidbodyDefinition.angularVelocity;
		pRigidbodyShape->m_BodyDefinition.linearDamping = rigidbodyDefinition.linearDamping;
		pRigidbodyShape->m_BodyDefinition.angularDamping = rigidbodyDefinition.angularDamping;
		pRigidbodyShape->m_BodyDefinition.allowSleep = rigidbodyDefinition.allowSleep;
		pRigidbodyShape->m_BodyDefinition.awake = rigidbodyDefinition.isAwake;
		pRigidbodyShape->m_BodyDefinition.fixedRotation = rigidbodyDefinition.fixedRotation;
		pRigidbodyShape->m_BodyDefinition.bullet = rigidbodyDefinition.isBullet;
		pRigidbodyShape->m_BodyDefinition.enabled = rigidbodyDefinition.isEnabled;
		pRigidbodyShape->m_BodyDefinition.gravityScale = rigidbodyDefinition.gravityScale;

		pRigidbodyShape->m_RigidbodyShape = PossibleRigidbodyShapes::Polygon;

		b2Vec2 pPoints[b2_maxPolygonVertices]{};
		for (size_t i{}; i < points.size(); ++i)
			pPoints[i] = b2Vec2{ points[i].x, points[i].y };

		pRigidbodyShape->m_pShapeDefinition = new b2PolygonShape{};
		static_cast<b2PolygonShape*>(pRigidbodyShape->m_pShapeDefinition)->Set(pPoints, points.size());

		pRigidbodyShape->m_FixtureDefinitions.push_back(b2FixtureDef{});
		pRigidbodyShape->m_FixtureDefinitions.back().shape = pRigidbodyShape->m_pShapeDefinition;
		pRigidbodyShape->m_FixtureDefinitions.back().density = rigidbodyFixture.density;
		pRigidbodyShape->m_FixtureDefinitions.back().friction = rigidbodyFixture.friction;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.maskBits = rigidbodyFixture.filter.maskBits;
		pRigidbodyShape->m_FixtureDefinitions.back().isSensor = rigidbodyFixture.isTrigger;
		pRigidbodyShape->m_FixtureDefinitions.back().restitution = rigidbodyFixture.restitution;
		pRigidbodyShape->m_FixtureDefinitions.back().restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		pRigidbodyShape->m_RigidbodyFixtures.push_back(rigidbodyFixture);

		return pRigidbodyShape;
	}

	RigidbodyShape* const RigidbodyShape::CreateChain(const RigidbodyDefinition& rigidbodyDefinition, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		ASSERT(!Utils::AreEqual(rigidbodyFixture.density, 0.f), "RigidbodyShape::CreateChain() > Density may not be 0!");
		ASSERT(points.size() <= m_MaxVerticesInChain, std::string{ "RigidbodyShape::CreateChain() > There may only be " } + std::to_string(m_MaxVerticesInChain) + " vertices in a chain");

		RigidbodyShape* pRigidbodyShape{ new RigidbodyShape{} };
		pRigidbodyShape->m_RigidbodyDefinition = rigidbodyDefinition;
		pRigidbodyShape->m_RigidbodyDefinition.pShape = pRigidbodyShape;

		pRigidbodyShape->m_BodyDefinition.type = static_cast<b2BodyType>(rigidbodyDefinition.rigidbodyType);
		pRigidbodyShape->m_BodyDefinition.position = b2Vec2{ rigidbodyDefinition.position.x, rigidbodyDefinition.position.y };
		pRigidbodyShape->m_BodyDefinition.angle = rigidbodyDefinition.angle;
		pRigidbodyShape->m_BodyDefinition.linearVelocity = b2Vec2{ rigidbodyDefinition.linearVelocity.x, rigidbodyDefinition.linearVelocity.y };
		pRigidbodyShape->m_BodyDefinition.angularVelocity = rigidbodyDefinition.angularVelocity;
		pRigidbodyShape->m_BodyDefinition.linearDamping = rigidbodyDefinition.linearDamping;
		pRigidbodyShape->m_BodyDefinition.angularDamping = rigidbodyDefinition.angularDamping;
		pRigidbodyShape->m_BodyDefinition.allowSleep = rigidbodyDefinition.allowSleep;
		pRigidbodyShape->m_BodyDefinition.awake = rigidbodyDefinition.isAwake;
		pRigidbodyShape->m_BodyDefinition.fixedRotation = rigidbodyDefinition.fixedRotation;
		pRigidbodyShape->m_BodyDefinition.bullet = rigidbodyDefinition.isBullet;
		pRigidbodyShape->m_BodyDefinition.enabled = rigidbodyDefinition.isEnabled;
		pRigidbodyShape->m_BodyDefinition.gravityScale = rigidbodyDefinition.gravityScale;

		pRigidbodyShape->m_RigidbodyShape = PossibleRigidbodyShapes::Chain;

		b2Vec2 pPoints[b2_maxPolygonVertices]{};
		for (size_t i{}; i < points.size(); ++i)
			pPoints[i] = b2Vec2{ points[i].x, points[i].y };

		pRigidbodyShape->m_pShapeDefinition = new b2ChainShape{};
		static_cast<b2ChainShape*>(pRigidbodyShape->m_pShapeDefinition)->CreateLoop(pPoints, points.size());

		pRigidbodyShape->m_FixtureDefinitions.push_back(b2FixtureDef{});
		pRigidbodyShape->m_FixtureDefinitions.back().shape = pRigidbodyShape->m_pShapeDefinition;
		pRigidbodyShape->m_FixtureDefinitions.back().density = rigidbodyFixture.density;
		pRigidbodyShape->m_FixtureDefinitions.back().friction = rigidbodyFixture.friction;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		pRigidbodyShape->m_FixtureDefinitions.back().filter.maskBits = rigidbodyFixture.filter.maskBits;
		pRigidbodyShape->m_FixtureDefinitions.back().isSensor = rigidbodyFixture.isTrigger;
		pRigidbodyShape->m_FixtureDefinitions.back().restitution = rigidbodyFixture.restitution;
		pRigidbodyShape->m_FixtureDefinitions.back().restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		pRigidbodyShape->m_RigidbodyFixtures.push_back(rigidbodyFixture);

		return pRigidbodyShape;
	}

	void RigidbodyShape::AddFixture(const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		m_FixtureDefinitions.push_back(b2FixtureDef{});
		b2FixtureDef& fixtureDef{ m_FixtureDefinitions.back() };

		fixtureDef.shape = m_pShapeDefinition;
		fixtureDef.density = rigidbodyFixture.density;
		fixtureDef.friction = rigidbodyFixture.friction;
		fixtureDef.filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		fixtureDef.filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		fixtureDef.filter.maskBits = rigidbodyFixture.filter.maskBits;
		fixtureDef.isSensor = rigidbodyFixture.isTrigger;
		fixtureDef.restitution = rigidbodyFixture.restitution;
		fixtureDef.restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		m_RigidbodyFixtures.push_back(rigidbodyFixture);
	}

	RigidbodyType RigidbodyShape::GetRigidbodyType() const noexcept
	{
		return m_RigidbodyType;
	}

	PossibleRigidbodyShapes RigidbodyShape::GetRigidbodyShape() const noexcept
	{
		return m_RigidbodyShape;
	}

	const RigidbodyDefinition& RigidbodyShape::GetRigidbodyDefinition() const noexcept
	{
		return m_RigidbodyDefinition;
	}

	const std::vector<RigidbodyFixture>& RigidbodyShape::GetRigidbodyFixtures() const noexcept
	{
		return m_RigidbodyFixtures;
	}
}