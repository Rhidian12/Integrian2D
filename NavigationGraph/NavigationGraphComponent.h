#pragma once

#include "../Components/Component/Component.h"
#include "NavGraphPolygon/NavGraphPolygon.h"

#include <vector>

namespace Integrian2D
{
	/* This Component can represent a 2D Polygon as a NavigationGraph 
	   Note that a Polygon must not be a triangle */
	class NavigationGraphComponent final : public Component
	{
	public:
		NavigationGraphComponent(GameObject* pOwner);
		NavigationGraphComponent(GameObject* pOwner, const std::vector<NavGraphPolygon>& polygons);

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		/* This function should NOT get called manually. If this component is added to a GameObject,
		   the GameObject in question will call this function internally */
		virtual void Update() override;

		/* This function should NOT get called manually. If this component is added to a GameObject,
		   the GameObject in question will call this function internally */
		virtual void Render() const override;

		/* Add a NavGraph Polygon to the Navigation Graph 
		   Duplicate polygons do not get added */
		void AddPolygon(const NavGraphPolygon& polygon) noexcept;

		/* Remove a previously added NavGraph Polygon from the Navigation Graph */
		void RemovePolygon(const NavGraphPolygon& polygonToRemove) noexcept;

		/* Return all added NavGraph Polygon to the Navigation Graph */
		const std::vector<NavGraphPolygon>& GetPolygons() const noexcept;

	private:
		std::vector<NavGraphPolygon> m_Polygons;
		bool m_IsPolygonAdded;
	};
}