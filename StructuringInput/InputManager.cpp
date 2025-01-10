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

		mKeyState = SDL_GetKeyboardState(&mNumKeys);
		mOldKeyState = new Uint8[mNumKeys];
		memcpy(mOldKeyState, mKeyState, mNumKeys);
	}

	InputManager::~InputManager() {

		delete[] mOldKeyState;
		mOldKeyState = NULL;
	}

	void InputManager::SetMouseAxis() {

		SDL_GetMouseState(&mMousePosX, &mMousePosY);
	}

	bool InputManager::IsKeyPressed(SDL_Scancode keyCode) {

		if (mKeyState[keyCode] != 0 && mOldKeyState[keyCode] == 0)
			return true;
		else
			return false;
	}

	bool InputManager::IsKeyHeld(SDL_Scancode keyCode) {

		if (mKeyState[keyCode] != 0 && mOldKeyState[keyCode] != 0)
			return true;
		else
			return false;
	}
	bool InputManager::IsKeyReleased(SDL_Scancode keyCode) {

		if (mKeyState[keyCode] == 0 && mOldKeyState[keyCode] != 0)
			return true;
		else
			return false;
	}

	void InputManager::Update() {

		SetMouseAxis();
		//mKeyState = SDL_GetKeyboardState(NULL);
	}

	void InputManager::LateUpdate() {

		memcpy(mOldKeyState, mKeyState, mNumKeys);
	}
}