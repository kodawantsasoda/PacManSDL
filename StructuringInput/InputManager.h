#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include <SDL.h>
#include <string.h>
#include <stdio.h>

namespace SDLCore {
	class InputManager {
	public:
		static InputManager* Instance();
		void Release();

		InputManager();
		~InputManager();

		//mouse functions/data
		void SetMouseAxis();
		int mMousePosX;
		int mMousePosY;

		//keyboard states
		bool IsKeyPressed(SDL_Scancode keyCode);
		bool IsKeyHeld(SDL_Scancode keyCode);
		bool IsKeyReleased(SDL_Scancode keyCode);

		void Update();
		void LateUpdate();


	private:
		static InputManager* sInstance;
		
		//keyboard capturing data structures
		const Uint8* mKeyState;
		Uint8* mOldKeyState;
		int mNumKeys;
	};
}

#endif

