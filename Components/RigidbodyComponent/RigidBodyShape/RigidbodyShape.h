#pragma once

#include "../../../Math/TypeDefines.h"
#include "../RigidbodyFixture/RigidbodyFixture.h"
#include "../RigidbodyDefinition/RigidbodyDefinition.h"

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

	class RigidbodyShape final
	{
	public:
		static RigidbodyShape* const CreateCircle(const RigidbodyDefinition& rigidbodyDefinition, const float circleRadius, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreateEdge(const RigidbodyDefinition& rigidbodyDefinition, const PLinef& edge, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreatePolygon(const RigidbodyDefinition& rigidbodyDefinition, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreateChain(const RigidbodyDefinition& rigidbodyDefinition, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept;
		
		RigidbodyType GetRigidbodyType() const noexcept;
		PossibleRigidbodyShapes GetRigidbodyShape() const noexcept;
		const RigidbodyDefinition& GetRigidbodyDefinition() const noexcept;
		const std::vector<RigidbodyFixture>& GetRigidbodyFixtures() const noexcept;

	private:
		RigidbodyShape();

		RigidbodyType m_RigidbodyType;
		PossibleRigidbodyShapes m_RigidbodyShape;
		RigidbodyDefinition m_RigidbodyDefinition;

		std::vector<RigidbodyFixture> m_RigidbodyFixtures;
		std::vector<b2FixtureDef> m_FixtureDefinitions;

		b2BodyDef m_BodyDefinition;
		b2Shape* m_pShapeDefinition;

		constexpr inline static int m_MaxVerticesInChain{ 16 };
	};
}