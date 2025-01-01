#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <SDL.h>
#include <stdio.h>

namespace SDLCore {

	class Graphics {

	public:
		//static instance functions
		static Graphics* Instance();
		static void Release();
		static bool Initialized();

		//functions
		void DrawGrid(SDL_Rect rect);
		void FillRectInGrid(SDL_Rect rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
		void ClearPreviousFrame();
		void Render();

		//constants
		const int SCREEN_WIDTH = 1080;
		const int SCREEN_HEIGHT = 800;
		const char* WINDOW_TITLE = "PAC-MAN";

		SDL_Window* mWindow;
		SDL_Renderer* mRenderer;

	private:
		//singleton data
		static Graphics* sInstance;
		static bool sInitialized;

		//Constructor/destuctor
		Graphics();
		~Graphics();

		//overall initializations
		bool Init();
	};
}

#endif
