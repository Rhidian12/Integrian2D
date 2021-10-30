#pragma once

#include "../../Math/TypeDefines.h"
#include <vector>

namespace Integrian2D
{
	/* This class represents a 2D Polygon that can be added to the NavigationGraphComponent */
	class NavGraphPolygon final
	{
	public:
		/* Create the Polygon from a list of vertices */
		NavGraphPolygon(const std::vector<Point2f>& vertices);

		/* Create the Polygon from a list of vertices with inner polygons defined by the second list of vertices */
		NavGraphPolygon(const std::vector<Point2f>& outerVertices, const std::vector<std::vector<Point2f>>& innerVertices);

		/* This function should NOT get called manually. If this component is added to a NavigationGraphComponent,
		   the Component in question will call this function internally */
		void Render(const Point2f& offset) const noexcept;

		/* This function triangulates the polygon using the Delaunay triangulation algorithm
		   Note that this function could be expensive depending on the polygon */
		void Triangulate() noexcept;

		/* Add another polygon to this polygon */
		NavGraphPolygon* AddChild(const std::vector<Point2f> vertices) noexcept;
		
		/* Add another polygon to this polygon */
		void AddChild(const NavGraphPolygon child) noexcept;

		/* Remove a previously added polygon from this polygon */
		void RemoveChild(const NavGraphPolygon& childToRemove) noexcept;

		/* This function calculates the center of this polygon and then returns it */
		Point2f GetCenterOfPolygon() const noexcept;

		/* Checks whether this Polygon has been triangulated */
		bool IsTriangulated() const noexcept;

		/* Get the vertex with the largest X value in this Polygon */
		float GetMaxXVertex() const noexcept;

		/* Get the vertex with the largest Y value in this Polygon */
		float GetMaxYVertex() const noexcept;

		/* Get the vertex with the smallest X value in this Polygon */
		float GetMinXVertex() const noexcept;

		/* Get the vertex with the smallest Y value in this Polygon */
		float GetMinYVertex() const noexcept;

		/* Checks whether this Polygon is overlapping with another Polygon 
		   Note that this function can be VERY expensive depending on the Polygons */
		bool IsOverlapping(const NavGraphPolygon& polygon) const noexcept;

		/* Get the vertices making up this Polygon */
		const std::vector<Point2f>& GetVertices() const noexcept;

		/* Get this Polygon's Children
		   If there are no Children, this returns an empty list */
		const std::vector<NavGraphPolygon>& GetChildren() const noexcept;

	private:
		std::vector<Point2f> m_Vertices; // outer vertices of the polygon
		std::vector<NavGraphPolygon> m_ChildPolygons; // inner polygons of this polygon
		std::vector<Trianglef> m_Triangles; // Used for rendering

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