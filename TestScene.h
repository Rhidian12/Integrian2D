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
#include "AI/AIComponent/AIComponent.h"
#include "AI/Blackboard/Blackboard.h"
#include "AI/DecisionMaking/BehaviourTree/BehaviourTree.h"
#include "Command/Command.h"
#include "Components/TextComponent/TextComponent.h"

#include <string>

class ScaleUpCommand final : public Integrian2D::Command
{
public:
	ScaleUpCommand(Integrian2D::Scene* const pScene, Integrian2D::TransformComponent* const pTransform)
		: Command{ pScene }
		, m_pTransform{ pTransform }
	{}

	virtual void Execute() override
	{
		m_pTransform->Scale(Integrian2D::Point2f{ 1.f, 1.f });
	}

private:
	Integrian2D::TransformComponent* m_pTransform;
};

class ScaleDownCommand final : public Integrian2D::Command
{
public:
	ScaleDownCommand(Integrian2D::Scene* const pScene, Integrian2D::TransformComponent* const pTransform)
		: Command{ pScene }
		, m_pTransform{ pTransform }
	{}

	virtual void Execute() override
	{
		m_pTransform->Scale(Integrian2D::Point2f{ -1.f, -1.f });
	}

private:
	Integrian2D::TransformComponent* m_pTransform;
};

class TestScene final : public Integrian2D::Scene
{
public:
	TestScene(std::string name)
		: Scene{ name }
		, m_pGameObject{ new Integrian2D::GameObject{} }
		, m_pGameObject2{ new Integrian2D::GameObject{} }
	{
		Integrian2D::TextureManager::GetInstance()->AddTexture("Dino", new Integrian2D::Texture{ "dinoHappy.png" });
		Integrian2D::TextureManager::GetInstance()->AddTexture("Kat", new Integrian2D::Texture{ "katHappy.png" });
	}

	virtual void Start() override
	{
		using namespace Integrian2D;

		/*Blackboard* const pBlackboard{ new Blackboard{} };

		pBlackboard->AddData("FirstTime", true);
		pBlackboard->AddData("FirstTimeRunning", true);

		m_pGameObject->AddComponent(new AIComponent{ m_pGameObject, pBlackboard, new BehaviourTree{std::vector<BehaviourTreeNode*>
				{
					new ActionNode{ [](Blackboard* const)->BehaviourState
						{
							std::cout << "First Action!" << std::endl;
							return BehaviourState::Success;
						} },
					new SequenceNode{std::vector<BehaviourTreeNode*>
						{
							new ActionNode{ [](Blackboard* const)->BehaviourState
							{
								std::cout << "First Action in Sequence!" << std::endl;
								return BehaviourState::Success;
							} },
							new ActionNode{ [](Blackboard* const)->BehaviourState
							{
								std::cout << "Second Action in Sequence!" << std::endl;
								return BehaviourState::Success;
							} }
						} },
					new ConditionalNode{ [](Blackboard* const pBlackboard)->bool
						{
							if (pBlackboard->GetData<bool>("FirstTime"))
							{
								pBlackboard->ChangeData("FirstTime", false);
								return false;
							}
							else
								return true;
						}},
					new ActionNode{ [](Blackboard* const)->BehaviourState
						{
							std::cout << "Second Action after Sequence and after sucessfully changing bool in blackboard previous time!" << std::endl;
							return BehaviourState::Success;
						} },
					new ActionNode{ [](Blackboard* const pBlackboard)->BehaviourState
						{
							if (pBlackboard->GetData<bool>("FirstTimeRunning"))
							{
								std::cout << "Third Action Before Running!" << std::endl;
								pBlackboard->ChangeData("FirstTimeRunning", false);
								return BehaviourState::Running;
							}
							else
							{
								std::cout << "Third Action After Running!" << std::endl;
								return BehaviourState::Success;
							}
						} },
				}
			} });*/

		//m_pGameObject->AddComponent(new TextureComponent{ m_pGameObject, TextureManager::GetInstance()->GetTexture("Dino") });
		//m_pGameObject2->AddComponent(new TextureComponent{ m_pGameObject2, TextureManager::GetInstance()->GetTexture("Kat") });
		m_pGameObject->AddComponent(new TextComponent{ m_pGameObject, "WOOOOOOOOOOOH" });

		m_pGameObject->AddChild(m_pGameObject2);

		AddGameObject("Test1", m_pGameObject);
		AddGameObject("Test2", m_pGameObject2);

		m_pGameObject->SetTag("Parent");
		m_pGameObject2->SetTag("Child");

		InputManager* const pInputManager{ InputManager::GetInstance() };

		pInputManager->AddAxis(InputAxis{ "ParentVerticalMovement", GameInput{ KeyboardInput::W }, GameInput{ KeyboardInput::S } });
		pInputManager->AddAxis(InputAxis{ "ParentHorizontalMovement", GameInput{ KeyboardInput::D }, GameInput{ KeyboardInput::A } });

		pInputManager->AddAxis(InputAxis{ "ChildVerticalMovement", GameInput{ KeyboardInput::ArrowUp }, GameInput{ KeyboardInput::ArrowDown } });
		pInputManager->AddAxis(InputAxis{ "ChildHorizontalMovement", GameInput{ KeyboardInput::ArrowRight }, GameInput{ KeyboardInput::ArrowLeft } });

		pInputManager->AddAxis(InputAxis{ "ParentRotation", GameInput{ KeyboardInput::I }, GameInput{ KeyboardInput::U } });
		pInputManager->AddAxis(InputAxis{ "ChildRotation", GameInput{ KeyboardInput::L }, GameInput{ KeyboardInput::K } });

		pInputManager->AddCommand(GameInput{ KeyboardInput::T }, new ScaleDownCommand{ this,m_pGameObject->pTransform }, State::OnRelease);
		pInputManager->AddCommand(GameInput{ KeyboardInput::Y }, new ScaleUpCommand{ this,m_pGameObject->pTransform }, State::OnRelease);

		pInputManager->AddCommand(GameInput{ KeyboardInput::G }, new ScaleDownCommand{ this,m_pGameObject2->pTransform }, State::OnRelease);
		pInputManager->AddCommand(GameInput{ KeyboardInput::H }, new ScaleUpCommand{ this,m_pGameObject2->pTransform }, State::OnRelease);
	}

	virtual void Update() override
	{
		using namespace Integrian2D;

		InputManager* const pInputManager{ InputManager::GetInstance() };

		if (int8_t value = pInputManager->GetAxis("ParentVerticalMovement"); value != 0)
			m_pGameObject->pTransform->Translate(Vector2f{ 0.f, 5.f * value });

		if (int8_t value = pInputManager->GetAxis("ParentHorizontalMovement"); value != 0)
			m_pGameObject->pTransform->Translate(Vector2f{ 5.f * value, 0.f });

		if (int8_t value = pInputManager->GetAxis("ChildVerticalMovement"); value != 0)
			m_pGameObject2->pTransform->Translate(Vector2f{ 0.f, 5.f * value });

		if (int8_t value = pInputManager->GetAxis("ChildHorizontalMovement"); value != 0)
			m_pGameObject2->pTransform->Translate(Vector2f{ 5.f * value, 0.f });

		if (int8_t value = pInputManager->GetAxis("ParentRotation"); value != 0)
			m_pGameObject->pTransform->Rotate(Utils::ToRadians(5.f) * value);

		if (int8_t value = pInputManager->GetAxis("ChildRotation"); value != 0)
			m_pGameObject2->pTransform->Rotate(Utils::ToRadians(5.f) * value);
	}

	Integrian2D::GameObject* m_pGameObject;
	Integrian2D::GameObject* m_pGameObject2;
};