#include "RigidbodyComponent.h"
#include "../TransformComponent/TransformComponent.h"
#include "../../GameObject/GameObject.h"
#include "../../Locator/Locator.h"
#include "../../PhysicsEngine/PhysicsEngine.h"
#include "RigidBodyShape/RigidbodyShape.h"
#include "../../Renderer/Renderer.h"

namespace Integrian2D
{
	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, RigidbodyShape* const pRigidBody)
		: Component{ pOwner }
		, m_pRigidbody{ pRigidBody }
		, m_pBox2DBody{}
		, m_ShouldDebugRender{}
	{
		m_pBox2DBody = Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this);
	}

	RigidbodyComponent::RigidbodyComponent(GameObject* const pOwner, RigidbodyShape* const pRigidBody, const bool shouldDebugRender)
		: Component{ pOwner }
		, m_pRigidbody{ pRigidBody }
		, m_pBox2DBody{}
		, m_ShouldDebugRender{ shouldDebugRender }
	{
		m_pBox2DBody = Locator::GetInstance()->GetPhysicsEngine()->AddPhysicsComponent(this);
	}

	RigidbodyComponent::~RigidbodyComponent()
	{
		Utils::SafeDelete(m_pRigidbody);
	}

	Component* RigidbodyComponent::Clone(GameObject* const pOwner) noexcept
	{
		return new RigidbodyComponent{ pOwner, m_pRigidbody, m_ShouldDebugRender };
	}

	void RigidbodyComponent::FixedUpdate()
	{
		const TransformComponent* const pTransform{ m_pOwner->pTransform };
		m_pBox2DBody->SetTransform(b2Vec2{ pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y }, pTransform->GetAngle());

		/* TODO: Let RigidbodyShape change the definitions */
		// m_pRigidbody->GetRigidbodyDefinition().position = pTransform->GetWorldPosition();
	}

	void RigidbodyComponent::Render() const
	{
		if (!m_ShouldDebugRender)
			return;

		Renderer* const pRenderer{ Renderer::GetInstance() };

		switch (m_pRigidbody->GetRigidbodyShape())
		{
		case PossibleRigidbodyShapes::None:
			break;
		case PossibleRigidbodyShapes::Circle:
			pRenderer->RenderCircle(Circlef{ m_pOwner->pTransform->GetWorldPosition(), m_pRigidbody->GetShapeSpecificData<PossibleRigidbodyShapes::Circle>() });
			break;
		case PossibleRigidbodyShapes::Edge:
			pRenderer->RenderLine(m_pRigidbody->GetShapeSpecificData<PossibleRigidbodyShapes::Edge>(), 3.f);
			break;
		case PossibleRigidbodyShapes::Polygon:
			pRenderer->RenderPolygon(m_pRigidbody->GetShapeSpecificData<PossibleRigidbodyShapes::Polygon>());
			break;
		case PossibleRigidbodyShapes::Chain:
			pRenderer->RenderPolygon(m_pRigidbody->GetShapeSpecificData<PossibleRigidbodyShapes::Chain>());
			break;
		case PossibleRigidbodyShapes::Rectangle:
			pRenderer->RenderRectangle(m_pRigidbody->GetShapeSpecificData<PossibleRigidbodyShapes::Rectangle>());
			break;
		}
	}

	void RigidbodyComponent::SetDebugRendering(const bool shouldDebugRender) noexcept
	{
		m_ShouldDebugRender = shouldDebugRender;
	}

	RigidbodyShape* const RigidbodyComponent::GetRigidbodyShape() const noexcept
	{
		return m_pRigidbody;
	}

	bool RigidbodyComponent::IsDebugRendering() const noexcept
	{
		return m_ShouldDebugRender;
	}

	void RigidbodyComponent::RootStart() noexcept
	{
		const TransformComponent* const pTransform{ m_pOwner->pTransform };
		m_pBox2DBody->SetTransform(b2Vec2{ pTransform->GetWorldPosition().x, pTransform->GetWorldPosition().y }, pTransform->GetAngle());
	}
}
