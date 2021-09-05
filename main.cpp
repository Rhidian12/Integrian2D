bool volatile g_IsLooping{ true }; // Maybe move this somewhere else

//#define UNIT_TESTS

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

	Integrian2D::GameObject* pMoveOperator{ new Integrian2D::GameObject{} };
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

#include "Math/TypeDefines.h"
TEST_CASE("Testing the Point...")
{
	using namespace Integrian2D;

	Point2f point{ 1.f, 1.f };
	REQUIRE(point.x == 1.f);
	REQUIRE(point.y == 1.f);

	point += Vector2f{ 5.f, 8.f };

	REQUIRE(point.x == 6.f);
	REQUIRE(point.y == 9.f);

	Point2f copiedPoint{ point };
	REQUIRE(copiedPoint == point);
	REQUIRE_FALSE(copiedPoint != point);

	Point2f movedPoint{ std::move(point) };
	REQUIRE(copiedPoint == movedPoint);
	REQUIRE_FALSE(copiedPoint != movedPoint);
}

TEST_CASE("Testing the Vector...")
{
	using namespace Integrian2D;

	Vector2f vector{ 1.f, 0.f };
	REQUIRE(Magnitude(vector) == 1.f);

}

#include "Parsing/BinaryWriter/BinaryWriter.h"
TEST_CASE("Testing the Writer...")
{
	using namespace Integrian2D;

	BinaryWriter writer{ "Test.bin" };

	writer.Write(50);
	writer.Write(100.f);
	writer.Write(150.0);
	writer.Write(std::string{ "200" });
	writer.Write(uint8_t(12));
	writer.Write(int8_t(-12));
}

#include "Parsing/BinaryReader/BinaryReader.h"
TEST_CASE("Testing the Reader...")
{
	using namespace Integrian2D;

	BinaryReader reader{ "Test.bin" };

	REQUIRE(reader.Read<int>() == 50);
	REQUIRE(reader.Read<float>() == 100.f);
	REQUIRE(reader.Read<double>() == 150.0);
	REQUIRE(reader.Read<std::string>() == "200");
	REQUIRE(reader.Read<uint8_t>() == 12);
	REQUIRE(reader.Read<int8_t>() == -12);
}

TEST_CASE("Testing the Matrix...")
{
	using namespace Integrian2D;

	{
		Matrix2x2 matrix{};

		for (int r{}; r < 2; ++r)
			for (int c{}; c < 2; ++c)
				REQUIRE(Utils::AreEqual(matrix(r, c), 0.f));

		matrix(0, 0) = 69.f;
		matrix(1, 1) = 42.f;

		REQUIRE(Utils::AreEqual(matrix(0, 0), 69.f));
		REQUIRE(Utils::AreEqual(matrix(1, 1), 42.f));

		REQUIRE(Utils::AreEqual(GetDeterminantOfMatrix(matrix, 2), 2898.f));

		matrix = GetIdentityMatrix<2, 2, float>();

		REQUIRE(Utils::AreEqual(matrix(0, 0), 1.f));
		REQUIRE(Utils::AreEqual(matrix(1, 1), 1.f));

		matrix = Matrix2x2{};

		float counter{ 1.f };
		for (int r{}; r < 2; ++r)
			for (int c{}; c < 2; ++c)
				matrix(r, c) = counter++;

		auto transposedMatrix{ TransposeMatrix(matrix) };

		REQUIRE(Utils::AreEqual(transposedMatrix(0, 0), 1.f));
		REQUIRE(Utils::AreEqual(transposedMatrix(0, 1), 3.f));
		REQUIRE(Utils::AreEqual(transposedMatrix(1, 0), 2.f));
		REQUIRE(Utils::AreEqual(transposedMatrix(1, 1), 4.f));

		{
			Matrix2x2 otherMatrix{};

			for (int r{}; r < 2; ++r)
				for (int c{}; c < 2; ++c)
					otherMatrix(r, c) = counter++;

			auto result = matrix * otherMatrix;

			REQUIRE(Utils::AreEqual(result(0, 0), 19.f));
			REQUIRE(Utils::AreEqual(result(0, 1), 22.f));
			REQUIRE(Utils::AreEqual(result(1, 0), 43.f));
			REQUIRE(Utils::AreEqual(result(1, 1), 50.f));

			otherMatrix(0, 1) = -otherMatrix(0, 1);
			otherMatrix(1, 1) = -otherMatrix(1, 1);

			result = matrix * otherMatrix;

			REQUIRE(Utils::AreEqual(result(0, 0), 19.f));
			REQUIRE(Utils::AreEqual(result(0, 1), -22.f));
			REQUIRE(Utils::AreEqual(result(1, 0), 43.f));
			REQUIRE(Utils::AreEqual(result(1, 1), -50.f));
		}
	}

	{
		Matrix3x3 matrix{};

		for (int r{}; r < 3; ++r)
			for (int c{}; c < 3; ++c)
				REQUIRE(Utils::AreEqual(matrix(r, c), 0.f));

		matrix(0, 0) = 69.f;
		matrix(1, 1) = 42.f;
		matrix(2, 2) = 21.f;

		REQUIRE(Utils::AreEqual(matrix(0, 0), 69.f));
		REQUIRE(Utils::AreEqual(matrix(1, 1), 42.f));
		REQUIRE(Utils::AreEqual(matrix(2, 2), 21.f));

		REQUIRE(Utils::AreEqual(GetDeterminantOfMatrix(matrix, 3), 60858.f));

		matrix = GetIdentityMatrix<3, 3, float>();

		REQUIRE(Utils::AreEqual(matrix(0, 0), 1.f));
		REQUIRE(Utils::AreEqual(matrix(1, 1), 1.f));
		REQUIRE(Utils::AreEqual(matrix(2, 2), 1.f));

		Matrix3x3 testMatrix{};

		for (int r{}; r < 3; ++r)
			for (int c{}; c < 3; ++c)
				matrix(r, c) = float(rand() % 101 - 50);

		for (int r{}; r < 3; ++r)
			for (int c{}; c < 3; ++c)
				testMatrix(r, c) = float(rand() % 101 - 50);

	}
}

#include "Components/TransformComponent/TransformComponent.h"

TEST_CASE("Testing the TransformComponent...")
{
	using namespace Integrian2D;

	GameObject gameObject{};

	//REQUIRE(Utils::AreEqual(gameObject.pTransform->GetAngle(), 0.f));
	//REQUIRE(Utils::AreEqual(gameObject.pTransform->GetScale().x, 1.f));
	//REQUIRE(Utils::AreEqual(gameObject.pTransform->GetScale().y, 1.f));
	//REQUIRE(Utils::AreEqual(gameObject.pTransform->GetPosition().x, 0.f));
	//REQUIRE(Utils::AreEqual(gameObject.pTransform->GetPosition().y, 0.f));
}

#else
#include "Core/Core.h"
#include "SceneManager/SceneManager.h"
#include "Scene/Scene.h"
#include "GameObject/GameObject.h"
#include "Texture/Texture.h"
#include "Components/TextureComponent/TextureComponent.h"

#include <vld.h>

#include "TestScene.h"

#undef main
int main(int, char*[])
{
	using namespace Integrian2D;

	Core engine{ 640,480, "TestWindow" };

	Scene* pScene{ new TestScene{"TestScene"} };

	SceneManager::GetInstance()->AddScene(pScene);

	engine.Run();

	return 0;
	}
#endif