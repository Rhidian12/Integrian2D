#include "NavGraphPolygon.h"
#include <algorithm>
#include <limits>

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

	Point2f NavGraphPolygon::GetCenter() const noexcept
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

	bool NavGraphPolygon::IsOverlapping(const NavGraphPolygon& polygon) const noexcept
	{
		// == Check if they CERTAINLY cannot overlap ==
		if (GetMinXVertex() > polygon.GetMaxXVertex() || GetMaxXVertex() < polygon.GetMinXVertex())
			return false;

		// == Check if they CERTAINLY cannot overlap ==
		if (GetMinYVertex() > polygon.GetMaxYVertex() || GetMaxYVertex() < polygon.GetMinYVertex())
			return false;


		return true;
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