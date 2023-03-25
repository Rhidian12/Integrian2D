#pragma once

#include "../../Integrian2D_API.h"

#include "../../Component/Component.h"
#include "../../NavGraphPolygon/NavGraphPolygon.h"

namespace Integrian2D
{
	/* This Component can represent a 2D Polygon as a NavigationGraph 
	   Note that a Polygon must not be a triangle */
	class NavigationGraphComponent final : public Component
	{
	public:
		INTEGRIAN2D_API NavigationGraphComponent(GameObject* pOwner);
		INTEGRIAN2D_API NavigationGraphComponent(GameObject* pOwner, const Array<NavGraphPolygon>& polygons, const bool triangulate = true);

		/* This function should NOT get called manually. If this component is added to a GameObject,
		   the GameObject in question will call this function internally */
		INTEGRIAN2D_API virtual void Render() const override;

		/* Add a NavGraph Polygon to the Navigation Graph 
		   Duplicate polygons do not get added */
		INTEGRIAN2D_API void AddPolygon(NavGraphPolygon& polygon, const bool triangulatePolygon = true);

		/* Remove a previously added NavGraph Polygon from the Navigation Graph */
		INTEGRIAN2D_API void RemovePolygon(const NavGraphPolygon& polygonToRemove);

		/* This triangulates all NavGraphPolygons added to this Navigation Graph 
		   Note that this function can be very expensive depending on the NavGraphPolygons and the amount of Polygons
		   This function should not be called every frame */
		INTEGRIAN2D_API void Triangulate();

		/* Return all added NavGraph Polygon to the Navigation Graph */
		INTEGRIAN2D_API const Array<NavGraphPolygon>& GetPolygons() const;

	private:
		Array<NavGraphPolygon> m_Polygons;
		bool m_IsPolygonAdded;
	};
}