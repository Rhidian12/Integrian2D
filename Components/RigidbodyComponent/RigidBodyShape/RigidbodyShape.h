#pragma once

#include "../../../Math/TypeDefines.h"
#include "../RigidbodyFixture/RigidbodyFixture.h"

#include <box2d.h>
#include <vector>

namespace Integrian2D
{
	enum class PossibleRigidbodyShapes
	{
		Circle = 0,
		Edge = 1,
		Polygon = 2,
		Chain = 3,
		None = 4
	};

	enum class RigidbodyType
	{
		Static = 0,
		Dynamic = 1,
		Kinematic = 2,
		None = 3
	};

	class RigidbodyShape final
	{
	public:
		static RigidbodyShape* const CreateCircle(const RigidbodyType rigidBodyType, const float circleRadius, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreateEdge(const RigidbodyType rigidBodyType, const PLinef& edge, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreatePolygon(const RigidbodyType rigidBodyType, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreateChain(const RigidbodyType rigidBodyType, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept;
		
		RigidbodyType GetRigidbodyType() const noexcept;
		PossibleRigidbodyShapes GetRigidbodyShape() const noexcept;

	private:
		RigidbodyShape();

		RigidbodyType m_RigidbodyType;
		PossibleRigidbodyShapes m_RigidbodyShape;

		RigidbodyFixture m_RigidbodyFixture;

		b2BodyDef m_BodyDefinition;
		b2Shape* m_pShapeDefinition;
		b2FixtureDef m_FixtureDefinition;

		constexpr inline static int m_MaxVerticesInChain{ 16 };
	};
}