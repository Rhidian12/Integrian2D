#include "NavGraphPolygon.h"
#include <algorithm>

namespace Integrian2D
{
	NavGraphPolygon::NavGraphPolygon(const std::vector<Point2f> vertices)
		: m_Vertices{ vertices }
		, m_ChildPolygons{}
	{}

	NavGraphPolygon::NavGraphPolygon(const std::vector<Point2f> outerVertices, const std::vector<std::vector<Point2f>> innerVertices)
		: m_Vertices{ outerVertices }
		, m_ChildPolygons{}
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

	const Point2f NavGraphPolygon::GetCenter() const noexcept
	{
		Point2f average{};

		for (const Point2f& p : m_Vertices)
			average += p;

		return average / static_cast<float>(m_Vertices.size());
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