#include "GameManager.h"

namespace SDLCore {
	//instance
	GameManager* GameManager::sInstance = NULL;

	//initializing instance
	GameManager* GameManager::Instance() {

		if (sInstance == NULL)
			sInstance = new GameManager;

		return sInstance;
	}

	//resetting instance and flag
	void GameManager::Release() {

		if (sInstance != NULL)
			delete sInstance;

		sInstance = NULL;
	}

	//creating instances for our singletons/managers
	GameManager::GameManager() {

		mInput = InputManager::Instance();
		mGraphics = Graphics::Instance();
		mAssets = AssetManager::Instance();
		mScreen = ScreenManager::Instance();
	}

	GameManager::~GameManager() {

		mInput->Release();
		mGraphics->Release();
		mAssets->Release();
		mScreen->Release();

		mInput = NULL;
		mGraphics = NULL;
		mAssets = NULL;
		mScreen = NULL;
	}

	//meant to be used to check for input in other managers
	void GameManager::Update() {

		mInput->SetMouseAxis();
		mScreen->Update();
	}

	//rendering each manager
	void GameManager::Render() {

		mGraphics->ClearPreviousFrame();
		mScreen->Render();
		mGraphics->Render();
	}

	void GameManager::Run() {

		SDL_Event e;
		bool quit = false;

		while (quit == false) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT)
					quit = true;
			}
			//call early update (input manager)
			Update();
			//call updates
			//Render last
			Render();
		}
	}
}