#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <unordered_map>

namespace SDLCore {

	class AssetManager {
	public:
		//instance
		static AssetManager* Instance();
		static void Release();

		AssetManager();
		~AssetManager();

		//map for all in game textures to prevent creating multiple textures
		std::unordered_map<std::string, SDL_Texture*> mInGameTextures;

		//all shapes created in the game to prevent frequent drawing
		std::unordered_map<std::string, SDL_Texture*> mInGameShapes;

	private:
		static AssetManager* sInstance;
	};
}

#endif
