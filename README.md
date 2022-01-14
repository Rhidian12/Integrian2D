# Integrian2D

### Features
- Fully functional math library
- Fully supported Navmesh generation, Behaviour trees and finite state machines
- Texture rendering using OpenGL and SDL2
- Keyboard, Mouse and GameController input supported
- Particle Systems using Textures or Colours
- (Binary) file reader and writer fully supported
- Automatic resource management
- Multi-threaded transforms
- Easy-to-use thread manager
- Fully supported Audio system using SDL2
- Fully supported Event Queue

### Requirements
- C++17

### Documentation
#### Engine Flowchart
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
