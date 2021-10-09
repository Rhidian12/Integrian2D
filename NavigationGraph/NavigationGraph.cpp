#include "NavigationGraph.h"

namespace Integrian2D
{
	NavigationGraph::NavigationGraph(GameObject* pOwner)
		: Component{ pOwner }
		, m_Polygons{}
	{}
	
	NavigationGraph::NavigationGraph(GameObject* pOwner, const std::vector<NavGraphPolygon>& polygons)
		: Component{ pOwner }
		, m_Polygons{ polygons }
	{}

	Component* NavigationGraph::Clone(GameObject* pOwner) noexcept
	{
		return new NavigationGraph{ pOwner, m_Polygons };
	}

	void NavigationGraph::Render() const
	{
		for (const NavGraphPolygon& polygon : m_Polygons)
			polygon.Render();
	}
}