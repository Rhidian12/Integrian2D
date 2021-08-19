#include "Integrian2D.h"
#include "../Logger/Logger.h"
#include "../SceneManager/SceneManager.h"
#include "../Scene/Scene.h"

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_video.h>
#include <GL\GLU.h>

namespace Integrian2D
{
	Integrian2D::Integrian2D(const int windowWidth, const int windowHeight, std::string windowTitle)
		: m_pWindow{}
		, m_WindowWidth{ windowWidth }
		, m_WindowHeight{ windowHeight }
	{
		if (!InitializeLibraries(windowTitle))
			std::abort(); // TODO: Throw an exception
	}

	Integrian2D::~Integrian2D()
	{
		ShutdownLibraries();
	}

	void Integrian2D::Run()
	{
		SceneManager* pSceneManager{ SceneManager::GetInstance() };
		
		while (true)
		{
			Scene* pActiveScene{ pSceneManager->GetActiveScene() };
			
			pActiveScene->RootUpdate();
			pActiveScene->Update();
			
			pActiveScene->RootFixedUpdate();
			pActiveScene->FixedUpdate();

			pActiveScene->RootLateUpdate();
			pActiveScene->LateUpdate();

			pActiveScene->RootRender();
			pActiveScene->Render();
		}
	}

	bool Integrian2D::InitializeLibraries(std::string windowTitle) noexcept
	{
#pragma region SDL Stuff
		//Create window + surfaces
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) == -1)
			Logger::LogSevereError(std::string{ "SDL_Init failed:" } + SDL_GetError() + "\n");

		m_pWindow = SDL_CreateWindow(
			windowTitle.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_WindowWidth, m_WindowHeight,
			SDL_WINDOW_OPENGL);

		if (!m_pWindow)
		{
			Logger::LogSevereError("Error: m_pWindow failed in App::Initialize()\n");
			return false;
		}

		SDL_GLContext context = SDL_GL_CreateContext(m_pWindow);
		if (context == nullptr)
			Logger::LogSevereError("App::Initialize() CreateContext() failed\n");

		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			Logger::LogSevereError(std::string{ "App::Initialize() error when calling SDL_GL_SetSwapInterval " } + SDL_GetError() + "\n");
			return false;
		}

		// Set the Projection matrix to the identity matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// Set up a two-dimensional orthographic viewing region.
		gluOrtho2D(0, m_WindowWidth, 0, m_WindowHeight); // y from bottom to top

		// Set the viewport to the client window area
		// The viewport is the rectangu	lar region of the window where the image is drawn.
		glViewport(0, 0, m_WindowWidth, m_WindowHeight);

		// Set the Modelview matrix to the identity matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// Enable color blending and use alpha blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Initialize PNG loading
		const int pngFlags{ IMG_INIT_PNG };
		const int jpgFlags{ IMG_INIT_JPG };
		if (!(IMG_Init(pngFlags) & pngFlags) || !(IMG_Init(jpgFlags) & jpgFlags))
			Logger::LogSevereError(std::string{ "SDL_image could not initialize! SDL_image Error: " } + SDL_GetError() + "\n");

		if (TTF_Init() != 0)
			Logger::LogSevereError(SDL_GetError());
#pragma endregion

#pragma region SDL_Mixer
		// this final parameter is the chunk size of the audio, this might have to be made larger if too much hooks are getting used
		// TODO: Load in all filesizes of music in our folder, and take the average of that
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 8, 2048) == -1)
			Logger::LogSevereError(std::string{ "SDL_Mixer failed to open! " } + Mix_GetError() + "\n");

		// == Initialize SDL_Mixer == 
		const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
		if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags)
			Logger::LogSevereError(std::string{ "SDL_Mixer failed to initialize!" } + Mix_GetError() + "\n");
#pragma endregion

#pragma region SDL_Controllers
		if (SDL_JoystickEventState(SDL_ENABLE) == -1)
			Logger::LogSevereError(std::string{ "SDL_JoystickEventState() failed! " } + SDL_GetError() + "\n");
#pragma endregion

		return true;
	}
	void Integrian2D::ShutdownLibraries() noexcept
	{
		Mix_CloseAudio();
		Mix_Quit();

		SDL_DestroyWindow(m_pWindow);
		SDL_Quit();
	}
}