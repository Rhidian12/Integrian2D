#pragma once
#include "Scene/Scene.h"
#include "Texture/Texture.h"
#include "GameObject/GameObject.h"
#include "Components/TextureComponent/TextureComponent.h"
#include "TextureManager/TextureManager.h"
#include "Components/TransformComponent/TransformComponent.h"
#include "Input/InputManager/InputManager.h"

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
		m_pGameObject->AddComponent(new Integrian2D::TextureComponent{ m_pGameObject, Integrian2D::TextureManager::GetInstance()->GetTexture("DinoHappy") });

		AddGameObject("Test", m_pGameObject);

		m_pGameObject->pTransform->Translate(Integrian2D::Vector2f{ 100.f,100.f });
		m_pGameObject->pTransform->Rotate(Integrian2D::Utils::ToRadians(-45.f));

		inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::Space }, [this]()->void
			{
				m_pGameObject->pTransform->Rotate(Integrian2D::Utils::ToRadians(45.f));
			}, Integrian2D::State::OnRelease);

		inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::ArrowUp }, [this]()->void
			{
				m_pGameObject->pTransform->Translate(Integrian2D::Vector2f{ 0.f, 5.f });
			}, Integrian2D::State::OnHeld);

		inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::ArrowDown }, [this]()->void
			{
				m_pGameObject->pTransform->Translate(Integrian2D::Vector2f{ 0.f, -5.f });
			}, Integrian2D::State::OnHeld);

		inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::ArrowLeft }, [this]()->void
			{
				m_pGameObject->pTransform->Translate(Integrian2D::Vector2f{ -5.f, 0.f });
			}, Integrian2D::State::OnHeld);

		inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::ArrowRight }, [this]()->void
			{
				m_pGameObject->pTransform->Translate(Integrian2D::Vector2f{ 5.f, 0.f });
			}, Integrian2D::State::OnHeld);

		inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::Q }, [this]()->void
			{
				m_pGameObject->pTransform->Scale(Integrian2D::Point2f{ 1.f, 1.f });
			}, Integrian2D::State::OnRelease);

		inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::A }, [this]()->void
			{
				m_pGameObject->pTransform->Scale(Integrian2D::Point2f{ -1.f, -1.f });
			}, Integrian2D::State::OnRelease);
	}

	virtual void Update() override
	{
		std::cout << "Angle: " << Integrian2D::Utils::ToDegrees(m_pGameObject->pTransform->GetAngle()) << std::endl;
	}

	Integrian2D::GameObject* m_pGameObject;
};
#pragma once
