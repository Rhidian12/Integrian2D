# Integrian2D

## Features
- Fully functional math library, supporting Matrices, Points, Vectors, Lines, Triangles, Circles, Rectangles and more!
- Fully supported Navmesh generation, Behaviour trees and Finite State Machines, which can be used with each other.
- Fast Texture and basic shape rendering
- Keyboard, Mouse and GameController input supported through an InputManager which supports Axes and Commands.
- Particle Systems using Textures or plain colours.
- (Binary) file reader and writer fully supported
- Automatic Scene, Texture and GameObject management.
- Multi-threaded transforms to optimize recalculation of world information.
- Easy-to-use thread pool / manager.
- Fully supported Audio system using SDL2
- Fully supported Event Queue

## Requirements
- C++17 - A lot of the utilities use C++17 functionality
- C++ knowledge

## Future features
- Physics Engine
- UI System
- More pre-made Components

## Documentation
### Guide on how to create a basic scene and render a Texture
Start by creating a new Scene. The Scene must implement Start(), **ALL SCENE INITIALISATION SHOULD HAPPEN IN START()**</br>
In your `int main()`, create the Engine, add your Scenes to the SceneManager, and run the Engine!
```cpp
// TestScene.h
#pragma once

#include <Scene/Scene.h>

#include <string>

namespace Integrian2D
{
   class GameObject;
}

class TestScene final : public Integrian2D::Scene
{
public:
	TestScene(const std::string& name);

	virtual void Start() override;

private:
	Integrian2D::GameObject* m_pBall;
};
```

```cpp
// TestScene.cpp
#include "TestScene.h"

#include <GameObject/GameObject.h>
#include <Texture/Texture.h>
#include <TextureManager/TextureManager.h>
#include <Components/TextureComponent/TextureComponent.h> 
#include <Components/TransformComponent/TransformComponent.h>

TestScene::TestScene(const std::string& name)
	: Scene{ name.c_str() }
	, m_pBall{ new Integrian2D::GameObject{} }
{}

virtual void TestScene::Start()
{
	using namespace Integrian2D;

	TextureManager::GetInstance()->AddTexture("Ball", new Texture{ "Resources/Ball.png" });

	m_pGameObject->AddComponent(new TextureComponent{ m_pGameObject, TextureManager::GetInstance()->GetTexture("Ball") });
	m_pGameObject->pTransform->SetScale(Point2f{ 0.5f, 0.5f });

	/* Derived Function from Integrian2D::Scene to add GameObjects to the Scene */
	/* GameObjects MUST be added in this way */
	AddGameObject("Ball", m_pBall);
}
```
```cpp
// main.cpp
#include <Core/Core.h>
#include <SceneManager/SceneManager.h>

#include "TestScene.h"

int main()
{
    using namespace Integrian2D;

    Core* pEngine{ Core::CreateEngine(1080, 720, "Example") };

    SceneManager::GetInstance()->AddScene(new TestScene{ "ExampleScene" });

    pEngine->Run();

    pEngine->Cleanup();

    return 0;
}
```

### Engine Flowchart
1. The Core gets created
2. The Core initializes 3rd party libraries (such as SDL2)
3. The Core creates the Window and the Renderer
4. User-created scenes that were added to the SceneManager get initialized
    * 4a. User-Defined Scene::Start() gets called
    * 4b. GameObjects in User-Defined scene get initialized
5. The engine will now start running
6. The timer gets updated
7. The Renderer prepares a new frame to be rendered
8. The active scene gets requested from the Scene Manager
9. The Input Manager handles all input
10. The Active Scene's GameObjects call Update(), and by extension the Components attached to the GameObject
11. The User Defined Active Scene's Update() gets called
12. The Active Scene's GameObjects call FixedUpdate(), and by extension the Components attached to the GameObject
13. The User Defined Active Scene's FixedUpdate() gets called
14. The Active Scene's GameObjects call LateUpdate(), and by extension the Components attached to the GameObject
15. The User Defined Active Scene's LateUpdate() gets called
16. The EventQueue updates all events
17. The AudioLocator updates the AudioSystem
18. The Active Scene's GameObjects call Render(), and by extension the Components attached to the GameObject
19. The User Defined Active Scene's Render() gets called
20. The Renderer renders all Textures and OpenGL shapes
21. Steps 6-20 repeat until the engine is closed
