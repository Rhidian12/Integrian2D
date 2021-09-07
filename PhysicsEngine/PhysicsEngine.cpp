#include "PhysicsEngine.h"

void Integrian2D::PhysicsEngine::AddGameObject(GameObject* const pGameObject) noexcept
{
	const std::unordered_map<GameObject*, PhysicsInfo>::const_iterator cIt{ m_pGameObjects.find(pGameObject) };

	if (cIt == m_pGameObjects.cend())
	{
		m_pGameObjects.insert()
	}
}
