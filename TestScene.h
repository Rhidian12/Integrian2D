#pragma once
#include "Scene/Scene.h"
#include "Texture/Texture.h"
#include "GameObject/GameObject.h"
#include "Components/TextureComponent/TextureComponent.h"
#include "TextureManager/TextureManager.h"
#include "Components/TransformComponent/TransformComponent.h"
#include "Input/InputManager/InputManager.h"
#include "Timer/Timer.h"
#include "NavigationGraph/NavigationGraphComponent.h"
#include "NavigationGraph/NavGraphPolygon/NavGraphPolygon.h"
#include "Renderer/Renderer.h"
#include "Components/RigidbodyComponent/RigidbodyComponent.h"

#include <string>
class TestScene final : public Integrian2D::Scene
{
public:
#pragma region PhysicsTestingCode
	//TestScene(std::string name)
	//	: Scene{ name }
	//	, m_pGameObject{ new Integrian2D::GameObject{} }
	//	, m_pGameObject2{ new Integrian2D::GameObject{} }
	//{
	//	Integrian2D::TextureManager::GetInstance()->AddTexture("DinoHappy", new Integrian2D::Texture{ "dinoHappy.png" });
	//}

	//virtual void Start() override
	//{
	//	using namespace Integrian2D;

	//	m_pGameObject->AddComponent(new RectColliderComponent{ m_pGameObject, PRectf{ 100.f,100.f, 152.f, 166.f } });
	//	m_pGameObject->AddComponent(new PhysicsComponent{ m_pGameObject, 1.f, Vector2f{}, m_pGameObject->GetComponentByType<RectColliderComponent>() });
	//	m_pGameObject->AddComponent(new TextureComponent{ m_pGameObject, TextureManager::GetInstance()->GetTexture("DinoHappy") });
	//	m_pGameObject->pTransform->Translate(Vector2f{ 100.f, 100.f });

	//	m_pGameObject2->AddComponent(new RectColliderComponent{ m_pGameObject2, PRectf{ 300.f,300.f, 152.f, 166.f } });
	//	m_pGameObject2->AddComponent(new PhysicsComponent{ m_pGameObject2, 1.f, Vector2f{}, m_pGameObject2->GetComponentByType<RectColliderComponent>() });
	//	m_pGameObject2->AddComponent(new TextureComponent{ m_pGameObject2, TextureManager::GetInstance()->GetTexture("DinoHappy") });
	//	m_pGameObject2->pTransform->Translate(Vector2f{ 300.f, 300.f });
	//	m_pGameObject2->GetComponentByType<PhysicsComponent>()->SetIsAffectedByGravity(false);


	//	inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::ArrowUp }, [this]()->void
	//		{
	//			m_pGameObject->GetComponentByType<PhysicsComponent>()->AddForce(Integrian2D::Vector2f{ 0.f, 5.f });
	//		}, Integrian2D::State::OnHeld);

	//	inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::ArrowDown }, [this]()->void
	//		{
	//			m_pGameObject->GetComponentByType<PhysicsComponent>()->AddForce(Integrian2D::Vector2f{ 0.f, -5.f });
	//		}, Integrian2D::State::OnHeld);

	//	inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::ArrowLeft }, [this]()->void
	//		{
	//			m_pGameObject->GetComponentByType<PhysicsComponent>()->AddForce(Integrian2D::Vector2f{ -5.f, 0.f });
	//		}, Integrian2D::State::OnHeld);

	//	inputManager.AddCommand(Integrian2D::GameInput{ Integrian2D::KeyboardInput::ArrowRight }, [this]()->void
	//		{
	//			m_pGameObject->GetComponentByType<PhysicsComponent>()->AddForce(Integrian2D::Vector2f{ 5.f, 0.f });
	//		}, Integrian2D::State::OnHeld);

	//	AddGameObject("Test1", m_pGameObject);
	//	AddGameObject("Test2", m_pGameObject2);
	//}
#pragma endregion

	TestScene(std::string name)
		: Scene{ name }
		, m_pGameObject{ new Integrian2D::GameObject{} }
		, m_pGameObject2{ new Integrian2D::GameObject{} }
	{}

	virtual void Start() override
	{
		using namespace Integrian2D;

		RigidbodyDefinition groundDefinition{};
		RigidbodyFixture groundFixture{};
		RigidbodyShape* pGround{ RigidbodyShape::CreateRectangle(groundDefinition,
			PRectf{ Point2f{}, 640.f, 20.f }, groundFixture) };
		m_pGameObject->AddComponent(new RigidbodyComponent{ m_pGameObject, pGround, true });

		RigidbodyShape* pBall{ RigidbodyShape::CreateCircle(RigidbodyDefinition{}, 3.f, RigidbodyFixture{}) };
		m_pGameObject2->AddComponent(new RigidbodyComponent{ m_pGameObject2, pBall, true });

		m_pGameObject2->pTransform->SetWorldPosition(Point2f{ 300.f, 70.f });

		AddGameObject("Test1", m_pGameObject);
		AddGameObject("Test2", m_pGameObject2);

		m_pGameObject->SetTag("Ground");
		m_pGameObject2->SetTag("Ball");
	}

	virtual void Render() const override
	{
		using namespace Integrian2D;

		//Renderer::GetInstance()->RenderRectangle(Rectf{ Point2f{}, 640.f, 20.f });

		//Renderer::GetInstance()->RenderRectangle(Rectf{ m_pGameObject->pTransform->GetWorldPosition(), 10.f, 10.f }, RGBColour{ 255, 0, 0 });
		//Renderer::GetInstance()->RenderRectangle(Rectf{ m_pGameObject2->pTransform->GetWorldPosition(), 10.f, 10.f }, RGBColour{ 0, 255, 0 });
	}

	Integrian2D::GameObject* m_pGameObject;
	Integrian2D::GameObject* m_pGameObject2;
};
#pragma once
