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

		mMap = new GameMap;
		mPacMan = new PacManPlayer;
		
		int pacXOffset = 0, pacYOffset = 3;
		mPacMan->mPacMan->PositionTextureArea(mMap->mGrid->tiles[657].x, mMap->mGrid->tiles[657].y - pacYOffset);
		mPacMan->mPacMan->ScaleTextureArea(2);
	}

	ScreenManager::~ScreenManager() {

		delete mMap;
		mMap = NULL;

		delete mPacMan;
		mPacMan = NULL;
	}

	void ScreenManager::Update() {

		mMap->Update();
		mPacMan->Update();
	}

	void ScreenManager::Render() {

		mMap->Render();
		mPacMan->Render();
	}
}