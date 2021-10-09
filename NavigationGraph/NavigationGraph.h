#pragma once

#include "../Components/Component/Component.h"
#include "NavGraphPolygon/NavGraphPolygon.h"

#include <vector>

namespace Integrian2D
{
	class NavigationGraph final : public Component
	{
	public:
		NavigationGraph(GameObject* pOwner);
		NavigationGraph(GameObject* pOwner, const std::vector<NavGraphPolygon>& polygons);

		virtual Component* Clone(GameObject* pOwner) noexcept override;

		virtual void Render() const override;

	private:
		std::vector<NavGraphPolygon> m_Polygons;
	};
}