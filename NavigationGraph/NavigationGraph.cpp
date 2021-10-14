#include "NavigationGraph.h"

#include <algorithm>

namespace Integrian2D
{
	NavigationGraph::NavigationGraph(GameObject* pOwner)
		: Component{ pOwner }
		, m_Polygons{}
		, m_IsPolygonAdded{}
	{}
	
	NavigationGraph::NavigationGraph(GameObject* pOwner, const std::vector<NavGraphPolygon>& polygons)
		: Component{ pOwner }
		, m_Polygons{ polygons }
		, m_IsPolygonAdded{}
	{}

	Component* NavigationGraph::Clone(GameObject* pOwner) noexcept
	{
		return new NavigationGraph{ pOwner, m_Polygons };
	}

	void NavigationGraph::Update()
	{
		if (m_IsPolygonAdded)
		{
			m_IsPolygonAdded = false;

			for (NavGraphPolygon& polygon : m_Polygons)
				if (!polygon.IsTriangulated())
					polygon.Triangulate();
		}
	}

	void NavigationGraph::Render() const
	{
		for (const NavGraphPolygon& polygon : m_Polygons)
			polygon.Render();
	}

	void NavigationGraph::AddPolygon(const NavGraphPolygon& polygon, const bool allowDuplicatePolygons) noexcept
	{
		if (allowDuplicatePolygons)
		{
			m_Polygons.push_back(polygon);
			m_IsPolygonAdded = true;
		}
		else
		{
			const std::vector<NavGraphPolygon>::const_iterator cIt{ std::find(m_Polygons.cbegin(), m_Polygons.cend(), polygon) };
			if (cIt == m_Polygons.cend())
			{
				m_Polygons.push_back(polygon);
				m_IsPolygonAdded = true;
			}
		}
	}

	void NavigationGraph::RemovePolygon(const NavGraphPolygon& polygonToRemove) noexcept
	{
		const std::vector<NavGraphPolygon>::const_iterator cIt{ std::find(m_Polygons.cbegin(), m_Polygons.cend(), polygonToRemove) };
		if (cIt != m_Polygons.cend())
			m_Polygons.erase(cIt);
	}

	const std::vector<NavGraphPolygon>& NavigationGraph::GetPolygons() const noexcept
	{
		return m_Polygons;
	}
}