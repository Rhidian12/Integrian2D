bool volatile g_IsLooping{ true }; // Maybe move this somewhere else

//#define UNIT_TESTS

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

	Core* pEngine{ Core::CreateEngine(640,480, "TestWindow") };

	Scene* pScene{ new TestScene{"TestScene"} };

	SceneManager::GetInstance()->AddScene(pScene);

	pEngine->Run();

	pEngine->Cleanup();

	return 0;
}