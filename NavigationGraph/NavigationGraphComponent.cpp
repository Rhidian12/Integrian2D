#include "NavigationGraphComponent.h"
#include "../GameObject/GameObject.h"
#include "../Components/TransformComponent/TransformComponent.h"

#include <algorithm>

namespace Integrian2D
{
	NavigationGraphComponent::NavigationGraphComponent(GameObject* pOwner)
		: Component{ pOwner }
		, m_Polygons{}
		, m_IsPolygonAdded{}
	{}
	
	NavigationGraphComponent::NavigationGraphComponent(GameObject* pOwner, const std::vector<NavGraphPolygon>& polygons)
		: Component{ pOwner }
		, m_Polygons{ polygons }
		, m_IsPolygonAdded{}
	{}

	Component* NavigationGraphComponent::Clone(GameObject* pOwner) noexcept
	{
		return new NavigationGraphComponent{ pOwner, m_Polygons };
	}

	void NavigationGraphComponent::Update()
	{
		if (m_IsPolygonAdded)
		{
			m_IsPolygonAdded = false;

			for (NavGraphPolygon& polygon : m_Polygons)
				if (!polygon.IsTriangulated())
					polygon.Triangulate();
		}
	}

	void NavigationGraphComponent::Render() const
	{
		for (const NavGraphPolygon& polygon : m_Polygons)
			polygon.Render(m_pOwner->pTransform->GetWorldPosition());
	}

	void NavigationGraphComponent::AddPolygon(const NavGraphPolygon& polygon) noexcept
	{
			const std::vector<NavGraphPolygon>::const_iterator cIt{ std::find(m_Polygons.cbegin(), m_Polygons.cend(), polygon) };
			if (cIt == m_Polygons.cend())
			{
				m_Polygons.push_back(polygon);
				m_IsPolygonAdded = true;
			}
	}

	void NavigationGraphComponent::RemovePolygon(const NavGraphPolygon& polygonToRemove) noexcept
	{
		const std::vector<NavGraphPolygon>::const_iterator cIt{ std::find(m_Polygons.cbegin(), m_Polygons.cend(), polygonToRemove) };
		if (cIt != m_Polygons.cend())
			m_Polygons.erase(cIt);
	}

	const std::vector<NavGraphPolygon>& NavigationGraphComponent::GetPolygons() const noexcept
	{
		return m_Polygons;
	}
}