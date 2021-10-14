#pragma once

#include "../../Math/TypeDefines.h"
#include <vector>

namespace Integrian2D
{
	class NavGraphPolygon final
	{
	public:
		NavGraphPolygon(const std::vector<Point2f>& vertices);
		NavGraphPolygon(const std::vector<Point2f>& outerVertices, const std::vector<std::vector<Point2f>>& innerVertices);

		void Render(const Point2f& offset) const noexcept;

		void Triangulate() noexcept;

		NavGraphPolygon* AddChild(const std::vector<Point2f> vertices) noexcept;
		void AddChild(const NavGraphPolygon child) noexcept;
		void RemoveChild(const NavGraphPolygon& childToRemove) noexcept;

		Point2f GetCenterOfPolygon() const noexcept;
		bool IsTriangulated() const noexcept;
		float GetMaxXVertex() const noexcept;
		float GetMaxYVertex() const noexcept;
		float GetMinXVertex() const noexcept;
		float GetMinYVertex() const noexcept;
		bool IsOverlapping(const NavGraphPolygon& polygon) const noexcept;
		const std::vector<Point2f>& GetVertices() const noexcept;
		const std::vector<NavGraphPolygon>& GetChildren() const noexcept;

	private:
		std::vector<Point2f> m_Vertices; // outer vertices of the polygon
		std::vector<NavGraphPolygon> m_ChildPolygons; // inner polygons of this polygon
		std::vector<PTrianglef> m_Triangles; // Used for rendering

		bool m_IsTriangulated;
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