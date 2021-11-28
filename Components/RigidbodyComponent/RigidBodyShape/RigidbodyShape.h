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
		Rectangle = 4,
		None
	};

	class RigidbodyShape final
	{
	public:
		~RigidbodyShape();

		static RigidbodyShape* const CreateCircle(const RigidbodyDefinition& rigidbodyDefinition, const float circleRadius, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreateEdge(const RigidbodyDefinition& rigidbodyDefinition, const PLinef& edge, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreatePolygon(const RigidbodyDefinition& rigidbodyDefinition, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreateChain(const RigidbodyDefinition& rigidbodyDefinition, const std::vector<Point2f>& points, const RigidbodyFixture& rigidbodyFixture) noexcept;
		static RigidbodyShape* const CreateRectangle(const RigidbodyDefinition& rigidbodyDefinition, const PRectf& rect, const RigidbodyFixture& rigidbodyFixture) noexcept;

		void AddFixture(const RigidbodyFixture& rigidbodyFixture) noexcept;

		RigidbodyType GetRigidbodyType() const noexcept;
		PossibleRigidbodyShapes GetRigidbodyShape() const noexcept;
		const RigidbodyDefinition& GetRigidbodyDefinition() const noexcept;
		const std::vector<RigidbodyFixture>& GetRigidbodyFixtures() const noexcept;

		template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Circle, bool> = true>
		float GetShapeSpecificData() const noexcept;

		template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Edge, bool> = true>
		PLinef GetShapeSpecificData() const noexcept;

		template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Polygon, bool> = true>
		std::vector<Point2f> GetShapeSpecificData() const noexcept;

		template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Chain, bool> = true>
		std::vector<Point2f> GetShapeSpecificData() const noexcept;

		template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Rectangle, bool> = true>
		PRectf GetShapeSpecificData() const noexcept;

	private:
		friend class PhysicsEngine;

		RigidbodyShape();
		const b2BodyDef& GetBox2DBodyDefinition() const noexcept;
		const std::vector<b2FixtureDef>& GetBox2DFixtureDefinitions() const noexcept;

		RigidbodyType m_RigidbodyType;
		PossibleRigidbodyShapes m_RigidbodyShape;
		RigidbodyDefinition m_RigidbodyDefinition;

		std::vector<RigidbodyFixture> m_RigidbodyFixtures;
		std::vector<b2FixtureDef> m_FixtureDefinitions;

		b2BodyDef m_BodyDefinition;
		b2Shape* m_pShapeDefinition;

		constexpr inline static int m_MaxVerticesInChain{ 16 };
	};

	template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Circle, bool>>
	float RigidbodyShape::GetShapeSpecificData() const noexcept
	{
		return static_cast<b2CircleShape*>(m_pShapeDefinition)->m_radius;
	}

	template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Edge, bool>>
	PLinef RigidbodyShape::GetShapeSpecificData() const noexcept
	{
		const b2Vec2 begin{ static_cast<b2EdgeShape*>(m_pShapeDefinition)->m_vertex1 };
		const b2Vec2 end{ static_cast<b2EdgeShape*>(m_pShapeDefinition)->m_vertex2 };

		return PLinef{ Point2f{ begin.x, begin.y }, Point2f{ end.x, end.y }, Point2f{ 1.f, 1.f }, m_BodyDefinition.angle };
	}

	template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Polygon, bool>>
	std::vector<Point2f> RigidbodyShape::GetShapeSpecificData() const noexcept
	{
		b2Vec2* pPoints{ static_cast<b2PolygonShape*>(m_pShapeDefinition)->m_vertices };
		std::vector<Point2f> convertedPoints{};

		for (int i{}; i < static_cast<b2PolygonShape*>(m_pShapeDefinition)->m_count; ++i)
			convertedPoints.push_back(Point2f{ pPoints[i].x, pPoints[i].y });

		return convertedPoints;
	}

	template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Chain, bool>>
	std::vector<Point2f> RigidbodyShape::GetShapeSpecificData() const noexcept
	{
		b2Vec2* pPoints{ static_cast<b2ChainShape*>(m_pShapeDefinition)->m_vertices };
		std::vector<Point2f> convertedPoints{};

		for (int i{}; i < static_cast<b2ChainShape*>(m_pShapeDefinition)->m_count; ++i)
			convertedPoints.push_back(Point2f{ pPoints[i].x, pPoints[i].y });

		return convertedPoints;
	}

	template<PossibleRigidbodyShapes BodyType, std::enable_if_t<BodyType == PossibleRigidbodyShapes::Rectangle, bool>>
	PRectf RigidbodyShape::GetShapeSpecificData() const noexcept
	{
		const float width{ static_cast<b2PolygonShape*>(m_pShapeDefinition)->m_vertices[1].x - static_cast<b2PolygonShape*>(m_pShapeDefinition)->m_vertices[0].x };
		const float height{ static_cast<b2PolygonShape*>(m_pShapeDefinition)->m_vertices[2].y - static_cast<b2PolygonShape*>(m_pShapeDefinition)->m_vertices[1].y };
		return PRectf{ Point2f{ m_BodyDefinition.position.x, m_BodyDefinition.position.y }, width, height, m_BodyDefinition.angle };
	}
}