#include "Core.h"
#include "../Logger/Logger.h"
#include "../SceneManager/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../TextureManager/TextureManager.h"
#include "../Locator/Locator.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_video.h>
#include <GL\GLU.h>

extern bool volatile g_IsLooping;

namespace Integrian2D
{
	Core::Core(const int windowWidth, const int windowHeight, const std::string windowTitle)
		: m_pWindow{}
		, m_WindowWidth{windowWidth}
		, m_WindowHeight{windowHeight}
	{
		InitializeLibraries(windowWidth, windowHeight, windowTitle);
	}

	Core::~Core()
	{
		SceneManager::Cleanup();
		Renderer::Cleanup();
		TextureManager::Cleanup();
		Locator::Cleanup();

		ShutdownLibraries(); // m_pWindow is deleted in ShutDownLibraries() because of SDL reasons
	}

	void Core::Run()
	{
		SceneManager* pSceneManager{ SceneManager::GetInstance() };
		Renderer* pRenderer{ Renderer::GetInstance() };

		for (const std::pair<const std::string, Scene*>& scenePair : pSceneManager->GetScenes())
			scenePair.second->Start();

		ASSERT(pSceneManager->GetActiveScene() != nullptr, "Core::Run() > No Active Scene has been added!");

		while (g_IsLooping)
		{
			pRenderer->SetNewFrame();

			Scene* pActiveScene{ pSceneManager->GetActiveScene() };

			pActiveScene->inputManager.HandleInput();

			pActiveScene->RootUpdate();
			pActiveScene->Update();

			pActiveScene->physicsEngine.FixedUpdate();
			pActiveScene->RootFixedUpdate();
			pActiveScene->FixedUpdate();

			pActiveScene->RootLateUpdate();
			pActiveScene->LateUpdate();

			pActiveScene->RootRender();
			pActiveScene->Render();

			pRenderer->Render();
		}
	}

	void Core::InitializeLibraries(const int windowWidth, const int windowHeight, const std::string windowTitle) noexcept
	{
#pragma region SDL Stuff
		//Create window + surfaces
		ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) == 0, "Core::InitializeLibraries() > SDL initialisation failed : "_s + SDL_GetError());

		m_pWindow = new Window{ windowWidth, windowHeight, windowTitle };

		ASSERT(SDL_GL_SetSwapInterval(1) == 0, "Core::InitializeLibraries() > Setting the screen refresh rate failed: "_s + SDL_GetError());

		// Set the Projection matrix to the identity matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set up a two-dimensional orthographic viewing region.
		gluOrtho2D(0, windowWidth, 0, windowHeight); // y from bottom to top

		// Set the viewport to the client window area
		// The viewport is the rectangu	lar region of the window where the image is drawn.
		glViewport(0, 0, windowWidth, windowHeight);

		// Set the Modelview matrix to the identity matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Enable color blending and use alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Initialize PNG loading
		const int pngFlags{ IMG_INIT_PNG };
		const int jpgFlags{ IMG_INIT_JPG };
		ASSERT((IMG_Init(pngFlags) & pngFlags) || !(IMG_Init(jpgFlags) & jpgFlags), "Core::InitializeLibraries() > SDL_image could not initialize! "_s + SDL_GetError());
		
		ASSERT(TTF_Init() == 0, "Core::InitializeLibraries() > SDL_ttf could not initialize!"_s + SDL_GetError());
#pragma endregion

#pragma region SDL_Mixer
		// this final parameter is the chunk size of the audio, this might have to be made larger if too much hooks are getting used
		// TODO: Load in all filesizes of music in our folder, and take the average of that
		ASSERT(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 8, 2048) == 0, "Core::InitializeLibraries() > SDL_Mixer could not be opened! "_s + Mix_GetError());

		// == Initialize SDL_Mixer == 
		const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
		ASSERT((Mix_Init(mixerFlags) & mixerFlags) == mixerFlags, "Core::InitializeLibraries() > SDL_Mixer failed to initialize!"_s + Mix_GetError());
#pragma endregion

#pragma region SDL_Controllers
		ASSERT(SDL_JoystickEventState(SDL_ENABLE) == 1, "Core::InitializeLibraries() > The SDL_Joystick failed to initialize!"_s + SDL_GetError());
#pragma endregion
	}

	void Core::ShutdownLibraries() noexcept
	{
		Mix_CloseAudio();
		Mix_Quit();

		Utils::SafeDelete(m_pWindow);
		SDL_Quit();
	}
}