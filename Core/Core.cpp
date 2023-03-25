#include "Core.h"
#include "../Logger/Logger.h"
#include "../SceneManager/SceneManager.h"
#include "../Scene/Scene.h"
#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../TextureManager/TextureManager.h"
#include "../Timer/Timer.h"
#include "../ThreadManager/ThreadManager.h"
#include "../AudioLocator/AudioLocator.h"
#include "../Input/InputManager/InputManager.h"
#include "../EventQueue/EventQueue.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_video.h>
#include <GL\GLU.h>

// extern inline bool volatile g_IsLooping;

namespace Integrian2D
{
	Core::Core(const int windowWidth, const int windowHeight, const std::string& windowTitle)
		: m_IsEngineRunning{}
		, m_pWindow{}
		, m_WindowWidth{ windowWidth }
		, m_WindowHeight{ windowHeight }
	{
		InitializeLibraries(windowWidth, windowHeight, windowTitle);
	}

	Core& Core::GetInstance()
	{
		__ASSERT(m_pInstance);

		return *m_pInstance;
	}

	Core& Core::CreateEngine(const int windowWidth, const int windowHeight, const std::string& windowTitle)
	{
		__ASSERT(!m_pInstance && "Core::CreateEngine() > The Engine has already been created! Do not call this function twice!");
		return *(m_pInstance = new Core{ windowWidth, windowHeight, windowTitle });
	}

	void Core::Cleanup()
	{
		Utils::SafeDelete(m_pInstance);
	}

	Core::~Core()
	{
		ThreadManager::Cleanup();
		Renderer::Cleanup();
		TextureManager::Cleanup();
		EventQueue::Cleanup();
		InputManager::Cleanup();
		AudioLocator::Cleanup();

		ShutdownLibraries(); // m_pWindow is deleted in ShutDownLibraries() because of SDL reasons
	}

	void Core::Run()
	{
		using namespace Time;

		SceneManager& sceneManager{ SceneManager::GetInstance() };
		Renderer* pRenderer{ Renderer::GetInstance() };
		Timer& timer{ Timer::GetInstance() };
		AudioLocator* pAudioLocator{ AudioLocator::GetInstance() };
		EventQueue* const pEventQueue{ EventQueue::GetInstance() };

		for (Scene* pScene : sceneManager.GetScenes())
			pScene->Awake();

		for (Scene* pScene : sceneManager.GetScenes())
			pScene->Start();

		__ASSERT(sceneManager.GetActiveScene() != nullptr && "Core::Run() > No Scene has been added!");

		m_IsEngineRunning = true;

		double lag{};
		const double timePerFrame{ timer.GetFixedElapsedTime<TimeLength::MilliSeconds>() };

		while (g_IsLooping)
		{
			lag += timer.GetElapsedTime<TimeLength::MilliSeconds>();

			timer.Update();

			pRenderer->SetNewFrame();

			Scene* const pActiveScene{ sceneManager.GetActiveScene() };

			InputManager::GetInstance()->HandleInput();

			pActiveScene->Update();

			while (lag >= timePerFrame)
			{
				pActiveScene->FixedUpdate();

				lag -= timePerFrame;
			}

			pActiveScene->LateUpdate();

			pEventQueue->Update();

			pAudioLocator->GetAudio()->Update();

			pActiveScene->Render();

			pRenderer->Render();
		}

		m_IsEngineRunning = false;
	}

	bool Core::IsEngineRunning() const
	{
		return m_IsEngineRunning;
	}

	int Core::GetWindowWidth() const
	{
		return m_WindowWidth;
	}

	int Core::GetWindowHeight() const
	{
		return m_WindowHeight;
	}

	void Core::InitializeLibraries(const int windowWidth, const int windowHeight, const std::string& windowTitle)
	{
	#pragma region SDL Stuff
		//Create window + surfaces
		__ASSERT(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) == 0);

		m_pWindow = new Window{ windowWidth, windowHeight, windowTitle };

		__ASSERT(SDL_GL_SetSwapInterval(1) == 0);

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
		__ASSERT((IMG_Init(pngFlags) & pngFlags) || !(IMG_Init(jpgFlags) & jpgFlags));

		__ASSERT(TTF_Init() == 0);
	#pragma endregion

	#pragma region SDL_Mixer
		// this final parameter is the chunk size of the audio, this might have to be made larger if too much hooks are getting used
		__ASSERT(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 8, 2048) == 0);

		// == Initialize SDL_Mixer == 
		const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
		__ASSERT((Mix_Init(mixerFlags) & mixerFlags) == mixerFlags);
	#pragma endregion

	#pragma region SDL_Controllers
		__ASSERT(SDL_JoystickEventState(SDL_ENABLE) == 1);
	#pragma endregion
	}

	void Core::ShutdownLibraries()
	{
		Mix_CloseAudio();
		Mix_Quit();

		TTF_Quit();
		IMG_Quit();

		__DELETE(m_pWindow);
		SDL_Quit();
	}
}