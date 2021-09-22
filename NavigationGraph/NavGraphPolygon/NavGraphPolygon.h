#pragma once

#include "../../Math/TypeDefines.h"
#include <vector>

namespace Integrian2D
{
	class NavGraphPolygon final
	{
	public:
		NavGraphPolygon(const std::vector<Point2f> vertices);
		NavGraphPolygon(const std::vector<Point2f> outerVertices, const std::vector<std::vector<Point2f>> innerVertices);

		NavGraphPolygon* AddChild(const std::vector<Point2f> vertices) noexcept;
		void AddChild(const NavGraphPolygon child) noexcept;
		void RemoveChild(const NavGraphPolygon& childToRemove) noexcept;

		const Point2f GetCenter() const noexcept;
		const std::vector<Point2f>& GetVertices() const noexcept;
		const std::vector<NavGraphPolygon>& GetChildren() const noexcept;

	private:
		std::vector<Point2f> m_Vertices; // outer vertices of the polygon
		std::vector<NavGraphPolygon> m_ChildPolygons; // inner vertices of the polygon
		// TODO: Make a std::vector of Trianglef (Polygon<3, float>)
	};

	inline bool operator==(const NavGraphPolygon& a, const NavGraphPolygon& b) noexcept
	{
		return a.GetVertices() == b.GetVertices() && a.GetChildren() == b.GetChildren();
	}

	inline bool operator!=(const NavGraphPolygon& a, const NavGraphPolygon& b) noexcept
	{
		return !(a == b);
	}
}