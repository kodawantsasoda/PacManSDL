#include "InputManager.h"

namespace SDLCore {
	//singleton
	InputManager* InputManager::sInstance = NULL;

	InputManager* InputManager::Instance() {

		if (sInstance == NULL)
			sInstance = new InputManager();

		return sInstance;
	}

	void InputManager::Release() {

		delete sInstance;
		sInstance = NULL;
	}

	InputManager::InputManager() {

		
	}

	InputManager::~InputManager() {


	}

	void InputManager::SetMouseAxis() {

		SDL_GetMouseState(&mMousePosX, &mMousePosY);
	}


}