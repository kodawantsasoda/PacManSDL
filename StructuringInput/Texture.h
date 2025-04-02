#ifndef _TEXTURE_H
#define _TEXTURE_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Graphics.h"
#include "AssetManager.h"
#include <stdio.h>
#include <string>


namespace SDLCore {

	class Texture {
	public:
		//use the contructor in combination of file name you want to pull to create texture
		Texture(std::string file);
		Texture(std::string file, std::string text, int fontSize, SDL_Color color, int x, int y);
		~Texture();

		//if file doesnt exist in asset map, create texture
		void CreateTexture(std::string file);

		void CreateFont(std::string file, std::string text, int fontSize, SDL_Color color);
		void UpdateTextFont(std::string text, SDL_Color color);

		//After texture has been created/loaded, we can scale it
		void ClipLocalTexture(int x, int y, int w, int h);

		void PositionTextureArea(int x, int y);
		void LerpTextureArea(float xStart, float yStart, float xEnd, float yEnd, float time, float speed);
		void ScaleTextureArea(int scaleFactor, int offSetW, int offSetH);

		void Render();

		SDL_Rect mTextureArea;
		SDL_Rect mImageClip;

		//local texture that is rendered
		SDL_Texture* GetLocalTexture();


	private:
		//local texture that is rendered
		SDL_Texture* mLocalTexture;
		//for rendering
		Graphics* mGraphics;
		//for adding to mInGameTextures map
		AssetManager* mAsset;

		//bool used to signal if texture is being clipped as in a spritesheet
		bool mIsClipped;

		std::string mFileExtension;

		TTF_Font* mFont;
	};
}


#endif
