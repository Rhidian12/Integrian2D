#pragma once
#include "Scene/Scene.h"
#include "Texture/Texture.h"
#include "GameObject/GameObject.h"
#include "Components/TextureComponent/TextureComponent.h"
#include "TextureManager/TextureManager.h"

#include <string>
class TestScene final : public Integrian2D::Scene
{
public:
	TestScene(std::string name)
		: Scene{ name }
		, m_pGameObject{ new Integrian2D::GameObject{} }
	{
		Integrian2D::TextureManager::GetInstance()->AddTexture("DinoHappy", new Integrian2D::Texture{"dinoHappy.png"});
	}

	virtual void Start() override
	{
		m_pGameObject->AddComponent(new Integrian2D::TextureComponent{ m_pGameObject, Integrian2D::TextureManager::GetInstance()->GetTexture("DinoHappy") });

		AddGameObject("Test", m_pGameObject);
	}

	Integrian2D::GameObject* m_pGameObject;
};
#pragma once