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

#include <string>
class TestScene final : public Integrian2D::Scene
{
public:
	TestScene(std::string name)
		: Scene{ name }
		, m_pGameObject{ new Integrian2D::GameObject{} }
		, m_pGameObject2{ new Integrian2D::GameObject{} }
	{}

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

		m_pGameObject->AddChild(m_pGameObject2);

		AddGameObject("Test1", m_pGameObject);
		AddGameObject("Test2", m_pGameObject2);

		m_pGameObject->SetTag("Parent");
		m_pGameObject2->SetTag("Child");

		inputManager.AddCommand(GameInput{ KeyboardInput::W }, [this]()
			{
				m_pGameObject->pTransform->Translate(Vector2f{ 0.f, 5.f });
			}, State::OnHeld);

		inputManager.AddCommand(GameInput{ KeyboardInput::A }, [this]()
			{
				m_pGameObject->pTransform->Translate(Vector2f{ -5.f, 0.f });
			}, State::OnHeld);

		inputManager.AddCommand(GameInput{ KeyboardInput::S }, [this]()
			{
				m_pGameObject->pTransform->Translate(Vector2f{ 0.f, -5.f });
			}, State::OnHeld);

		inputManager.AddCommand(GameInput{ KeyboardInput::D }, [this]()
			{
				m_pGameObject->pTransform->Translate(Vector2f{ 5.f, 0.f });
			}, State::OnHeld);

		inputManager.AddCommand(GameInput{ KeyboardInput::ArrowUp }, [this]()
			{
				m_pGameObject2->pTransform->Translate(Vector2f{ 0.f, 5.f });
			}, State::OnHeld);

		inputManager.AddCommand(GameInput{ KeyboardInput::ArrowLeft }, [this]()
			{
				m_pGameObject2->pTransform->Translate(Vector2f{ -5.f, 0.f });
			}, State::OnHeld);

		inputManager.AddCommand(GameInput{ KeyboardInput::ArrowDown }, [this]()
			{
				m_pGameObject2->pTransform->Translate(Vector2f{ 0.f, -5.f });
			}, State::OnHeld);

		inputManager.AddCommand(GameInput{ KeyboardInput::ArrowRight }, [this]()
			{
				m_pGameObject2->pTransform->Translate(Vector2f{ 5.f, 0.f });
			}, State::OnHeld);
	}

	virtual void Render() const override
	{
		using namespace Integrian2D;

		//Renderer::GetInstance()->RenderRectangle(Rectf{ Point2f{}, 640.f, 20.f });

		Renderer::GetInstance()->RenderRectangle(Rectf{ m_pGameObject->pTransform->GetWorldPosition(), 10.f, 10.f }, RGBColour{ 255, 0, 0 });
		Renderer::GetInstance()->RenderRectangle(Rectf{ m_pGameObject2->pTransform->GetWorldPosition(), 10.f, 10.f }, RGBColour{ 0, 255, 0 });
	}

	Integrian2D::GameObject* m_pGameObject;
	Integrian2D::GameObject* m_pGameObject2;
};
#pragma once
