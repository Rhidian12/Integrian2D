#include "NavigationGraphComponent.h"
#include "../../GameObject/GameObject.h"
#include "../TransformComponent/TransformComponent.h"

#include <algorithm>

namespace Integrian2D
{
	NavigationGraphComponent::NavigationGraphComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_Polygons{}
		, m_IsPolygonAdded{}
	{}

	NavigationGraphComponent::NavigationGraphComponent(GameObject* pOwner, const Array<NavGraphPolygon>& polygons, const bool triangulate)
		: Component{ pOwner }
		, m_Polygons{ polygons }
		, m_IsPolygonAdded{}
	{
		if (triangulate)
			for (NavGraphPolygon& polygon : m_Polygons)
				polygon.Triangulate();
	}

	void NavigationGraphComponent::Render() const
	{
		/* TODO: Make this rendering optional */
		for (const NavGraphPolygon& polygon : m_Polygons)
			polygon.Render(m_pOwner->pTransform->GetWorldPosition());
	}

	void NavigationGraphComponent::AddPolygon(NavGraphPolygon& polygon, const bool triangulatePolygon)
	{
		const auto cIt{ m_Polygons.Find(polygon) };

		if (cIt == m_Polygons.cend())
		{
			if (triangulatePolygon)
				if (!polygon.IsTriangulated())
					polygon.Triangulate();

			m_Polygons.Add(polygon);
			m_IsPolygonAdded = true;
		}
	}

	void NavigationGraphComponent::RemovePolygon(const NavGraphPolygon& polygonToRemove)
	{
		const auto cIt{ m_Polygons.Find(polygonToRemove) };

		if (cIt != m_Polygons.cend())
			m_Polygons.Erase(cIt);
	}

	void NavigationGraphComponent::Triangulate()
	{
		for (NavGraphPolygon& polygon : m_Polygons)
			polygon.Triangulate();
	}

	const Array<NavGraphPolygon>& NavigationGraphComponent::GetPolygons() const
	{
		return m_Polygons;
	}
}