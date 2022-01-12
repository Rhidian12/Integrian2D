#pragma once
#include "Scene/Scene.h"
#include "Texture/Texture.h"
#include "GameObject/GameObject.h"
#include "Components/TextureComponent/TextureComponent.h"
#include "TextureManager/TextureManager.h"
#include "Components/TransformComponent/TransformComponent.h"
#include "Input/InputManager/InputManager.h"
#include "Timer/Timer.h"
#include "Components/NavigationGraphComponent/NavigationGraphComponent.h"
#include "NavGraphPolygon/NavGraphPolygon.h"
#include "Renderer/Renderer.h"
#include "Components/AIComponent/AIComponent.h"
#include "AI/Blackboard/Blackboard.h"
#include "AI/DecisionMaking/BehaviourTree/BehaviourTree.h"
#include "Command/Command.h"
#include "Components/TextComponent/TextComponent.h"
#include "Components/ParticleEmitterComponent/ParticleEmitterComponent.h"

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
		: Scene{ name.c_str() }
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

		TextureManager::GetInstance()->AddTexture("Michael", new Texture{ "Resources/Michael_SoyakPoint2.png" });
		TextureManager::GetInstance()->AddTexture("SmokeParticle", new Texture{ "Resources/Smoke_Particle.png" });

		Texture* const pSmokeParticle{ TextureManager::GetInstance()->GetTexture("SmokeParticle") };
		ParticleEmitterSettings settings{};
		settings.maximumTime = 3.f;
		settings.startingVelocity = Vector2f{ 0.f, 1.f };
		settings.minimumSpawnSize = pSmokeParticle->GetWidth();
		settings.maximumSpawnSize = pSmokeParticle->GetWidth();
		settings.maximumEmitterRange = 20.f;
		settings.spawnInterval = 0.1f;

		m_pGameObject->AddComponent(new ParticleEmitterComponent{ m_pGameObject,
			pSmokeParticle, settings });

		m_pGameObject->pTransform->SetPosition(Point2f{ 150.f, 50.f });

		AddGameObject("Test1", m_pGameObject);
		AddGameObject("Test2", m_pGameObject2);

		m_pGameObject->SetTag("Parent");
		m_pGameObject2->SetTag("Child");
	}

	virtual void Update() override
	{
		using namespace Integrian2D;
	}

	Integrian2D::GameObject* m_pGameObject;
	Integrian2D::GameObject* m_pGameObject2;
};