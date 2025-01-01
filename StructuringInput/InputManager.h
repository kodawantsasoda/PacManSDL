#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include <SDL.h>

namespace SDLCore {
	class InputManager {
	public:
		static InputManager* Instance();
		void Release();

		InputManager();
		~InputManager();

		void SetMouseAxis();

		int mMousePosX;
		int mMousePosY;

	private:
		static InputManager* sInstance;

	};
}

#endif

