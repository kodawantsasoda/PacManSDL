#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include <SDL.h>
#include <stdio.h>
#include "InputManager.h"
#include "Graphics.h"
#include "AssetManager.h"
#include "ScreenManager.h"

namespace SDLCore {

	class GameManager {

	public:
		//static instance functions
		static GameManager* Instance();
		static void Release();
		void Run();

	private:
		//singleton data
		static GameManager* sInstance;

		//Constructor/destuctor
		GameManager();
		~GameManager();

		//functions
		void Update();
		void LateUpdate();
		void Render();

	private:
		//managing other managers
		InputManager* mInput;
		Graphics* mGraphics;
		AssetManager* mAssets;
		ScreenManager* mScreen;
		Timer mTimer;
	};
}

#endif
#pragma once
