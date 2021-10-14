#include "NavGraphPolygon.h"
#include "../../Renderer/Renderer.h"
#include "delaunator.hpp"

#include <algorithm>
#include <limits>
#include <set>

#undef min // THESE MACROS ARE THE WORST
#undef max // THESE MACROS ARE THE WORST

namespace Integrian2D
{
	NavGraphPolygon::NavGraphPolygon(const std::vector<Point2f>& vertices)
		: m_Vertices{ vertices }
		, m_ChildPolygons{}
		, m_IsTriangulated{}
	{}

	NavGraphPolygon::NavGraphPolygon(const std::vector<Point2f>& outerVertices, const std::vector<std::vector<Point2f>>& innerVertices)
		: m_Vertices{ outerVertices }
		, m_ChildPolygons{}
		, m_IsTriangulated{}
	{
		for (const std::vector<Point2f>& vector : innerVertices)
			AddChild(vector);
	}

	void NavGraphPolygon::Render(const Point2f& offset) const noexcept
	{
		for (size_t i{}; i < m_Vertices.size(); ++i)
		{
			if (i != m_Vertices.size() - 1)
				Renderer::GetInstance()->RenderLine(Point2f{ m_Vertices[i].x + offset.x, m_Vertices[i].y + offset.y },
					Point2f{ m_Vertices[i + 1].x + offset.x, m_Vertices[i + 1].y + offset.y }, 3.f);
			else
				Renderer::GetInstance()->RenderLine(Point2f{ m_Vertices[i].x + offset.x, m_Vertices[i].y + offset.y },
					Point2f{ m_Vertices[0].x + offset.x, m_Vertices[0].y + offset.y }, 3.f);
		}

		if (m_IsTriangulated)
			for (const Trianglef& triangle : m_Triangles)
				Renderer::GetInstance()->RenderTriangle(Trianglef{ triangle.leftPoint + offset,
					triangle.topPoint + offset, triangle.rightPoint + offset }, RGBColour{ 0, 255, 0 });
	}

	void NavGraphPolygon::Triangulate() noexcept
	{
		m_IsTriangulated = true;
		m_Triangles.clear();

		std::vector<double> coordinates{};

		for (const Point2f& p : m_Vertices)
		{
			coordinates.push_back(static_cast<double>(p.x));
			coordinates.push_back(static_cast<double>(p.y));
		}

		delaunator::Delaunator triangulator{ coordinates };

		for (size_t i{}; i < triangulator.triangles.size(); i += 3)
		{
			m_Triangles.push_back(Trianglef{
				Point2f{static_cast<float>(triangulator.coords[2 * triangulator.triangles[i]]), static_cast<float>(triangulator.coords[2 * triangulator.triangles[i] + 1])},
				Point2f{static_cast<float>(triangulator.coords[2 * triangulator.triangles[i + 1]]), static_cast<float>(triangulator.coords[2 * triangulator.triangles[i + 1] + 1])},
				Point2f{static_cast<float>(triangulator.coords[2 * triangulator.triangles[i + 2]]), static_cast<float>(triangulator.coords[2 * triangulator.triangles[i + 2] + 1])}
				});
		}
	}

	NavGraphPolygon* NavGraphPolygon::AddChild(const std::vector<Point2f> vertices) noexcept
	{
		m_ChildPolygons.push_back(NavGraphPolygon{ vertices });
		return &m_ChildPolygons.back();
	}

	void NavGraphPolygon::AddChild(const NavGraphPolygon child) noexcept
	{
		m_ChildPolygons.push_back(child);
	}

	void NavGraphPolygon::RemoveChild(const NavGraphPolygon& childToRemove) noexcept
	{
		m_ChildPolygons.erase(std::remove(m_ChildPolygons.begin(), m_ChildPolygons.end(), childToRemove), m_ChildPolygons.end());
	}

	Point2f NavGraphPolygon::GetCenterOfPolygon() const noexcept
	{
		Point2f average{};

		for (const Point2f& p : m_Vertices)
			average += p;

		return average / static_cast<float>(m_Vertices.size());
	}

	bool NavGraphPolygon::IsTriangulated() const noexcept
	{
		return m_IsTriangulated;
	}

	float NavGraphPolygon::GetMaxXVertex() const noexcept
	{
		float maxXPosition{ std::numeric_limits<float>::min() };

		for (const Point2f& position : m_Vertices)
			if (position.x > maxXPosition)
				maxXPosition = position.x;

		return maxXPosition;
	}

	float NavGraphPolygon::GetMaxYVertex() const noexcept
	{
		float maxYPosition{ std::numeric_limits<float>::min() };

		for (const Point2f& position : m_Vertices)
			if (position.y > maxYPosition)
				maxYPosition = position.y;

		return maxYPosition;
	}

	float NavGraphPolygon::GetMinXVertex() const noexcept
	{
		float minXPosition{ std::numeric_limits<float>::max() };

		for (const Point2f& position : m_Vertices)
			if (position.x < minXPosition)
				minXPosition = position.x;

		return minXPosition;
	}

	float NavGraphPolygon::GetMinYVertex() const noexcept
	{
		float minYPosition{ std::numeric_limits<float>::max() };

		for (const Point2f& position : m_Vertices)
			if (position.y < minYPosition)
				minYPosition = position.y;

		return minYPosition;
	}

	bool NavGraphPolygon::IsOverlapping(const NavGraphPolygon& p) const noexcept
	{
		// == Check if they CERTAINLY cannot overlap ==
		if (GetMinXVertex() > p.GetMaxXVertex() || GetMaxXVertex() < p.GetMinXVertex())
			return false;

		// == Check if they CERTAINLY cannot overlap ==
		if (GetMinYVertex() > p.GetMaxYVertex() || GetMaxYVertex() < p.GetMinYVertex())
			return false;

		// == The Expensive way to check if they overlap ==
		for (size_t i{}; i < m_Vertices.size(); ++i)
		{
			const Point2f& startVertex{ m_Vertices[i] };
			Point2f endVertex{ m_Vertices[i + 1] };

			if (i == m_Vertices.size() - 1)
				endVertex = m_Vertices[0];

			for (size_t j{}; j < p.m_Vertices.size(); ++j)
			{
				if (j == p.m_Vertices.size() - 1)
				{
					if (DoVectorsIntersect(startVertex, Vector2f{ startVertex,  endVertex }, p.m_Vertices[j], Vector2f{ p.m_Vertices[j], p.m_Vertices[0] }, nullptr))
						return true;
				}
				else
				{
					if (DoVectorsIntersect(startVertex, Vector2f{ startVertex,  endVertex }, p.m_Vertices[j], Vector2f{ p.m_Vertices[j], p.m_Vertices[j + 1] }, nullptr))
						return true;
				}
			}
		}

		return false;
	}

	const std::vector<Point2f>& NavGraphPolygon::GetVertices() const noexcept
	{
		return m_Vertices;
	}

	const std::vector<NavGraphPolygon>& NavGraphPolygon::GetChildren() const noexcept
	{
		return m_ChildPolygons;
	}
}