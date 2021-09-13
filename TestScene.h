#pragma once
#include "Scene/Scene.h"
#include "Texture/Texture.h"
#include "GameObject/GameObject.h"
#include "Components/TextureComponent/TextureComponent.h"
#include "TextureManager/TextureManager.h"
#include "Components/TransformComponent/TransformComponent.h"
#include "Input/InputManager/InputManager.h"
#include "Components/RectColliderComponent/RectColliderComponent.h"
#include "Components/PhysicsComponent/PhysicsComponent.h"

#include <string>
class TestScene final : public Integrian2D::Scene
{
public:
	TestScene(std::string name)
		: Scene{ name }
		, m_pGameObject{ new Integrian2D::GameObject{} }
	{
		Integrian2D::TextureManager::GetInstance()->AddTexture("DinoHappy", new Integrian2D::Texture{ "dinoHappy.png" });
	}

	virtual void Start() override
	{
		using namespace Integrian2D;

		m_pGameObject->AddComponent(new TextureComponent{ m_pGameObject, TextureManager::GetInstance()->GetTexture("DinoHappy") });
	}

	virtual void Update() override
	{
	}

	Integrian2D::GameObject* m_pGameObject;
};
#pragma once
