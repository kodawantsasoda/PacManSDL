#include "Graphics.h"

namespace SDLCore {
	//instance
	Graphics* Graphics::sInstance = NULL;
	bool Graphics::sInitialized = false;

	//initializing instance
	Graphics* Graphics::Instance() {
		
		if (sInstance == NULL) 
			sInstance = new Graphics;

		return sInstance;
	}

	//resetting instance and flag
	void Graphics::Release() {

		if (sInstance != NULL)
			delete sInstance;

		sInstance = NULL;
		sInitialized = false;
	}

	bool Graphics::Initialized() {
		return sInitialized;
	}

	Graphics::Graphics() {

		sInitialized = Init();
	}

	Graphics::~Graphics() {

		SDL_DestroyWindow(mWindow);
		mWindow = NULL;

		SDL_DestroyRenderer(mRenderer);
		mRenderer = NULL;
		
		SDL_Quit();
	}

	//all initializations in order to get our window. this includes creating a renderer as well.
	bool Graphics::Init() {

		//initializing SDL video/audio
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
			printf("SDL has failed to initialize: %s\n", SDL_GetError());
			return false;
		}

		//creating the window
		mWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (mWindow == NULL) {
			printf("SDL has failed to create window: %s\n", SDL_GetError());
			return false;
		}

		//creating the renderer
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		if (mRenderer == NULL) {
			printf("SDL has failed to create renderer: %s\n", SDL_GetError());
		}

		SDL_SetRenderDrawColor(mRenderer, 0x00, 0x00, 0x00, 0xFF);
	}

	//drawing grid for gameboard. This will need to be adjusted as the game grows to include positioning, scaling, etc...
	void Graphics::DrawGrid(SDL_Rect rect) {

		SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_TRANSPARENT);
		SDL_RenderDrawRect(mRenderer, &rect);
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	}

	void Graphics::FillRectInGrid(SDL_Rect rect, Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha) {

		SDL_SetRenderDrawColor(mRenderer, red, green, blue, alpha);
		SDL_RenderFillRect(mRenderer, &rect);
		SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
	}

	void Graphics::ClearPreviousFrame() {

		SDL_RenderClear(mRenderer);
	}

	void Graphics::Render() {

		SDL_RenderPresent(mRenderer);
	}
}