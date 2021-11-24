#include "RigidbodyShape.h"

#include <string>

namespace Integrian2D
{
	RigidbodyShape::RigidbodyShape()
		: m_RigidbodyType{ RigidbodyType::None }
		, m_RigidbodyShape{ PossibleRigidbodyShapes::None }
		, m_BodyDefinition{}
		, m_RigidbodyFixture{}
		, m_pShapeDefinition{}
		, m_FixtureDefinition{}
	{}

	RigidbodyShape* const RigidbodyShape::CreateCircle(const RigidbodyType rigidBodyType, const float circleRadius, const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		ASSERT(!Utils::AreEqual(rigidbodyFixture.density, 0.f), "RigidbodyShape::CreateCircle() > Density may not be 0!");

		RigidbodyShape* pRigidbodyShape{ new RigidbodyShape{} };
		pRigidbodyShape->m_BodyDefinition.type = static_cast<b2BodyType>(rigidBodyType);

		pRigidbodyShape->m_RigidbodyShape = PossibleRigidbodyShapes::Circle;

		pRigidbodyShape->m_pShapeDefinition = new b2CircleShape{};
		pRigidbodyShape->m_pShapeDefinition->m_radius = circleRadius;

		pRigidbodyShape->m_FixtureDefinition.shape = pRigidbodyShape->m_pShapeDefinition;
		pRigidbodyShape->m_FixtureDefinition.density = rigidbodyFixture.density;
		pRigidbodyShape->m_FixtureDefinition.friction = rigidbodyFixture.friction;
		pRigidbodyShape->m_FixtureDefinition.filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		pRigidbodyShape->m_FixtureDefinition.filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		pRigidbodyShape->m_FixtureDefinition.filter.maskBits = rigidbodyFixture.filter.maskBits;
		pRigidbodyShape->m_FixtureDefinition.isSensor = rigidbodyFixture.isTrigger;
		pRigidbodyShape->m_FixtureDefinition.restitution = rigidbodyFixture.restitution;
		pRigidbodyShape->m_FixtureDefinition.restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		pRigidbodyShape->m_RigidbodyFixture = rigidbodyFixture;

		return pRigidbodyShape;
	}

	RigidbodyShape* const RigidbodyShape::CreateEdge(const RigidbodyType rigidBodyType, const PLinef& edge, const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		ASSERT(!Utils::AreEqual(rigidbodyFixture.density, 0.f), "RigidbodyShape::CreateEdge() > Density may not be 0!");

		RigidbodyShape* pRigidbodyShape{ new RigidbodyShape{} };
		pRigidbodyShape->m_BodyDefinition.type = static_cast<b2BodyType>(rigidBodyType);

		pRigidbodyShape->m_RigidbodyShape = PossibleRigidbodyShapes::Edge;

		pRigidbodyShape->m_pShapeDefinition = new b2EdgeShape{};
		static_cast<b2EdgeShape*>(pRigidbodyShape->m_pShapeDefinition)->m_vertex1 = b2Vec2{ edge.begin.x, edge.begin.y };
		static_cast<b2EdgeShape*>(pRigidbodyShape->m_pShapeDefinition)->m_vertex1 = b2Vec2{ edge.end.x, edge.end.y };

		pRigidbodyShape->m_FixtureDefinition.shape = pRigidbodyShape->m_pShapeDefinition;
		pRigidbodyShape->m_FixtureDefinition.density = rigidbodyFixture.density;
		pRigidbodyShape->m_FixtureDefinition.friction = rigidbodyFixture.friction;
		pRigidbodyShape->m_FixtureDefinition.filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		pRigidbodyShape->m_FixtureDefinition.filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		pRigidbodyShape->m_FixtureDefinition.filter.maskBits = rigidbodyFixture.filter.maskBits;
		pRigidbodyShape->m_FixtureDefinition.isSensor = rigidbodyFixture.isTrigger;
		pRigidbodyShape->m_FixtureDefinition.restitution = rigidbodyFixture.restitution;
		pRigidbodyShape->m_FixtureDefinition.restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		pRigidbodyShape->m_RigidbodyFixture = rigidbodyFixture;

		return pRigidbodyShape;
	}

	RigidbodyShape* const RigidbodyShape::CreatePolygon(const RigidbodyType rigidBodyType, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		ASSERT(!Utils::AreEqual(rigidbodyFixture.density, 0.f), "RigidbodyShape::CreatePolygon() > Density may not be 0!");
		ASSERT(points.size() <= b2_maxPolygonVertices, std::string{ "RigidbodyShape::CreatePolygon() > There may only be " } + std::to_string(b2_maxPolygonVertices) + " vertices in a polygon");

		RigidbodyShape* pRigidbodyShape{ new RigidbodyShape{} };
		pRigidbodyShape->m_BodyDefinition.type = static_cast<b2BodyType>(rigidBodyType);

		pRigidbodyShape->m_RigidbodyShape = PossibleRigidbodyShapes::Polygon;

		b2Vec2 pPoints[b2_maxPolygonVertices]{};
		for (size_t i{}; i < points.size(); ++i)
			pPoints[i] = b2Vec2{ points[i].x, points[i].y };

		pRigidbodyShape->m_pShapeDefinition = new b2PolygonShape{};
		static_cast<b2PolygonShape*>(pRigidbodyShape->m_pShapeDefinition)->Set(pPoints, points.size());

		pRigidbodyShape->m_FixtureDefinition.shape = pRigidbodyShape->m_pShapeDefinition;
		pRigidbodyShape->m_FixtureDefinition.density = rigidbodyFixture.density;
		pRigidbodyShape->m_FixtureDefinition.friction = rigidbodyFixture.friction;
		pRigidbodyShape->m_FixtureDefinition.filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		pRigidbodyShape->m_FixtureDefinition.filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		pRigidbodyShape->m_FixtureDefinition.filter.maskBits = rigidbodyFixture.filter.maskBits;
		pRigidbodyShape->m_FixtureDefinition.isSensor = rigidbodyFixture.isTrigger;
		pRigidbodyShape->m_FixtureDefinition.restitution = rigidbodyFixture.restitution;
		pRigidbodyShape->m_FixtureDefinition.restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		pRigidbodyShape->m_RigidbodyFixture = rigidbodyFixture;

		return pRigidbodyShape;
	}

	RigidbodyShape* const RigidbodyShape::CreateChain(const RigidbodyType rigidBodyType, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept
	{
		ASSERT(!Utils::AreEqual(rigidbodyFixture.density, 0.f), "RigidbodyShape::CreateChain() > Density may not be 0!");
		ASSERT(points.size() <= m_MaxVerticesInChain, std::string{ "RigidbodyShape::CreateChain() > There may only be " } + std::to_string(m_MaxVerticesInChain) + " vertices in a chain");

		RigidbodyShape* pRigidbodyShape{ new RigidbodyShape{} };
		pRigidbodyShape->m_BodyDefinition.type = static_cast<b2BodyType>(rigidBodyType);

		pRigidbodyShape->m_RigidbodyShape = PossibleRigidbodyShapes::Chain;

		b2Vec2 pPoints[b2_maxPolygonVertices]{};
		for (size_t i{}; i < points.size(); ++i)
			pPoints[i] = b2Vec2{ points[i].x, points[i].y };

		pRigidbodyShape->m_pShapeDefinition = new b2ChainShape{};
		static_cast<b2ChainShape*>(pRigidbodyShape->m_pShapeDefinition)->CreateLoop(pPoints, points.size());

		pRigidbodyShape->m_FixtureDefinition.shape = pRigidbodyShape->m_pShapeDefinition;
		pRigidbodyShape->m_FixtureDefinition.density = rigidbodyFixture.density;
		pRigidbodyShape->m_FixtureDefinition.friction = rigidbodyFixture.friction;
		pRigidbodyShape->m_FixtureDefinition.filter.categoryBits = rigidbodyFixture.filter.categoryBits;
		pRigidbodyShape->m_FixtureDefinition.filter.groupIndex = rigidbodyFixture.filter.groupIndex;
		pRigidbodyShape->m_FixtureDefinition.filter.maskBits = rigidbodyFixture.filter.maskBits;
		pRigidbodyShape->m_FixtureDefinition.isSensor = rigidbodyFixture.isTrigger;
		pRigidbodyShape->m_FixtureDefinition.restitution = rigidbodyFixture.restitution;
		pRigidbodyShape->m_FixtureDefinition.restitutionThreshold = rigidbodyFixture.restitutionThreshold;

		pRigidbodyShape->m_RigidbodyFixture = rigidbodyFixture;

		return pRigidbodyShape;
	}

	RigidbodyType RigidbodyShape::GetRigidbodyType() const noexcept
	{
		return m_RigidbodyType;
	}

	PossibleRigidbodyShapes RigidbodyShape::GetRigidbodyShape() const noexcept
	{
		return m_RigidbodyShape;
	}
}