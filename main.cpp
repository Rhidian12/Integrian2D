#include "Integrian2D/Integrian2D.h"

#include <vld.h>

#define UNIT_TESTS

#ifdef UNIT_TESTS
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "GameObject/GameObject.h"
#include "Components/Component/Component.h"

TEST_CASE("Testing the GameObject...")
{
	class ComponentWithNumbers final : public Integrian2D::Component
	{
	public:
		ComponentWithNumbers(Integrian2D::GameObject* pOwner, int a, float b, char c, double d)
			: Component{ pOwner }
			, m_A{ a }
			, m_B{ b }
			, m_C{ c }
			, m_D{ d }
		{}

		virtual Component* Clone(Integrian2D::GameObject* pOwner) noexcept override
		{
			return new ComponentWithNumbers{ pOwner, m_A, m_B, m_C, m_D };
		}

		int m_A;
		float m_B;
		char m_C;
		double m_D;
	};

	Integrian2D::GameObject* pGameObject{ new Integrian2D::GameObject{} };

	pGameObject->AddComponent(new ComponentWithNumbers{ pGameObject, 0, 1.f, '2', 3.0 });
	REQUIRE(pGameObject->GetComponentByType<ComponentWithNumbers>()->GetOwner() == pGameObject);
	REQUIRE(pGameObject->GetComponentByType<ComponentWithNumbers>()->m_A == 0);
	REQUIRE(pGameObject->GetComponentByType<ComponentWithNumbers>()->m_B == 1.f);
	REQUIRE(pGameObject->GetComponentByType<ComponentWithNumbers>()->m_C == '2');
	REQUIRE(pGameObject->GetComponentByType<ComponentWithNumbers>()->m_D == 3.0);

	Integrian2D::GameObject* pCopyConstructor{ new Integrian2D::GameObject{*pGameObject} };
	REQUIRE(pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->GetOwner() == pCopyConstructor);
	REQUIRE(pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_A == pGameObject->GetComponentByType<ComponentWithNumbers>()->m_A);
	REQUIRE(pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_B == pGameObject->GetComponentByType<ComponentWithNumbers>()->m_B);
	REQUIRE(pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_C == pGameObject->GetComponentByType<ComponentWithNumbers>()->m_C);
	REQUIRE(pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_D == pGameObject->GetComponentByType<ComponentWithNumbers>()->m_D);

	Integrian2D::GameObject* pMoveConstructor{ new Integrian2D::GameObject{std::move(*pGameObject)} };
	REQUIRE(pMoveConstructor->GetComponentByType<ComponentWithNumbers>()->GetOwner() == pMoveConstructor);
	REQUIRE(pMoveConstructor->GetComponentByType<ComponentWithNumbers>()->m_A == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_A);
	REQUIRE(pMoveConstructor->GetComponentByType<ComponentWithNumbers>()->m_B == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_B);
	REQUIRE(pMoveConstructor->GetComponentByType<ComponentWithNumbers>()->m_C == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_C);
	REQUIRE(pMoveConstructor->GetComponentByType<ComponentWithNumbers>()->m_D == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_D);

	Integrian2D::GameObject* pCopyOperator{ new Integrian2D::GameObject{} };
	*pCopyOperator = *pCopyConstructor;
	REQUIRE(pCopyOperator->GetComponentByType<ComponentWithNumbers>()->GetOwner() == pCopyOperator);
	REQUIRE(pCopyOperator->GetComponentByType<ComponentWithNumbers>()->m_A == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_A);
	REQUIRE(pCopyOperator->GetComponentByType<ComponentWithNumbers>()->m_B == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_B);
	REQUIRE(pCopyOperator->GetComponentByType<ComponentWithNumbers>()->m_C == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_C);
	REQUIRE(pCopyOperator->GetComponentByType<ComponentWithNumbers>()->m_D == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_D);

	Integrian2D::GameObject* pMoveOperator{new Integrian2D::GameObject{}};
	*pMoveOperator = std::move(*pCopyOperator);
	REQUIRE(pMoveOperator->GetComponentByType<ComponentWithNumbers>()->GetOwner() == pMoveOperator);
	REQUIRE(pMoveOperator->GetComponentByType<ComponentWithNumbers>()->m_A == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_A);
	REQUIRE(pMoveOperator->GetComponentByType<ComponentWithNumbers>()->m_B == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_B);
	REQUIRE(pMoveOperator->GetComponentByType<ComponentWithNumbers>()->m_C == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_C);
	REQUIRE(pMoveOperator->GetComponentByType<ComponentWithNumbers>()->m_D == pCopyConstructor->GetComponentByType<ComponentWithNumbers>()->m_D);

	delete pGameObject;
	delete pCopyConstructor;
	delete pMoveConstructor;
	delete pCopyOperator;
	delete pMoveOperator;
}

TEST_CASE("Testing the Point...")
{
#include "Math/TypeDefines.h"

	using namespace Integrian2D;

	Point2f 
}

#else

bool volatile g_IsLooping{ true }; // Maybe move this somewhere else

int main()
{
	Integrian2D::Integrian2D engine{ 640,480, "TestWindow" };
}
#endif