#pragma once
#include "Scene/Scene.h"
#include "Texture/Texture.h"
#include "GameObject/GameObject.h"
#include "Components/TextureComponent/TextureComponent.h"

#include <string>
class TestScene final : public Integrian2D::Scene
{
public:
	TestScene(std::string name)
		: Scene{ name }
		, m_pTexture{ new Integrian2D::Texture{"dinoHappy.png"} }
		, m_pGameObject{ new Integrian2D::GameObject{} }
	{}
	~TestScene() override
	{
		delete m_pTexture;
	}

	virtual void Start() override
	{
		m_pGameObject->AddComponent(new Integrian2D::TextureComponent{ m_pGameObject, m_pTexture });

		AddGameObject("Test", m_pGameObject);
	}

	Integrian2D::Texture* m_pTexture;
	Integrian2D::GameObject* m_pGameObject;
};
#pragma once
