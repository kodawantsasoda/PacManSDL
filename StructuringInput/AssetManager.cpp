#include "AssetManager.h"

namespace SDLCore {
	//instance
	AssetManager* AssetManager::sInstance = NULL;

	//initializing instance
	AssetManager* AssetManager::Instance() {
		
		if (sInstance == NULL)
			sInstance = new AssetManager;
		return sInstance;
	}

	void AssetManager::Release() {

		delete sInstance;
		sInstance = NULL;
	}

	AssetManager::AssetManager() {

	}
	
	//delete assets
	AssetManager::~AssetManager() {
		//have to manually destroy each texture in memory in map
		for (auto texture : mInGameTextures) {
			if (texture.second != NULL)
				SDL_DestroyTexture(texture.second);
		}

		for (auto texture : mInGameShapes) {
			if (texture.second != NULL)
				SDL_DestroyTexture(texture.second);
		}

		for (auto font : mFonts) {
			if (font.second != NULL)
				TTF_CloseFont(font.second);
		}

		mInGameTextures.clear();
		mInGameShapes.clear();
		mFonts.clear();
	}
}