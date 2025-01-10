#include "ScreenManager.h"

namespace SDLCore {

	ScreenManager* ScreenManager::sInstance = NULL;

	ScreenManager* ScreenManager::Instance() {

		if (sInstance == NULL)
			sInstance = new ScreenManager;

		return sInstance;
	}

	void ScreenManager::Release() {
		
		delete sInstance;
		sInstance = NULL;
	}

	ScreenManager::ScreenManager() {

		mGameScreen = new GameScreen;
	}

	ScreenManager::~ScreenManager() {

		delete mGameScreen;
		mGameScreen = NULL;
	}

	void ScreenManager::Update() {

		mGameScreen->Update();
	}

	void ScreenManager::Render() {

		mGameScreen->Render();
	}
}