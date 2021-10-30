#pragma once

#include "../Components/Component/Component.h"
#include "NavGraphPolygon/NavGraphPolygon.h"

#include <vector>

namespace Integrian2D
{
	class NavigationGraphComponent final : public Component
	{
	public:
		NavigationGraphComponent(GameObject* pOwner);
		NavigationGraphComponent(GameObject* pOwner, const std::vector<NavGraphPolygon>& polygons);

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		virtual void Update() override;
		virtual void Render() const override;

		void AddPolygon(const NavGraphPolygon& polygon, const bool allowDuplicatePolygons = false) noexcept;
		void RemovePolygon(const NavGraphPolygon& polygonToRemove) noexcept;

		const std::vector<NavGraphPolygon>& GetPolygons() const noexcept;

	private:
		std::vector<NavGraphPolygon> m_Polygons;
		bool m_IsPolygonAdded;
	};
}