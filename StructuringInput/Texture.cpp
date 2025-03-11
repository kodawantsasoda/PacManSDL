#include "Texture.h"

namespace SDLCore{
	//creating texture based on file; unless already created then just load
	Texture::Texture(std::string file) {
		
		mGraphics = Graphics::Instance();
		mAsset = AssetManager::Instance();
		
		mFileExtension = file.substr(file.size() - 3, file.size() - 1);

		//loading texture if created
		mLocalTexture = mAsset->mInGameTextures[file];
		if (mLocalTexture == NULL && mFileExtension != "ttf")
			CreateTexture(file);

		mIsClipped = false;
	}

	Texture::Texture(std::string file, std::string text, int fontSize, SDL_Color color, int x, int y) : Texture(file){

		CreateFont(file, text, fontSize, color);
		PositionTextureArea(x, y);
		mIsClipped = false;
	}

	Texture::~Texture() {

		mLocalTexture = NULL;
		mGraphics = NULL;
		mAsset = NULL;
	}

	void Texture::CreateTexture(std::string file) {
		//couldnt find texture so we make one
		//preparing surface for texture creation
		SDL_Surface* surface;

		surface = IMG_Load(file.c_str());

		if (surface == NULL) {
			printf("Image failed to load with surface @ path %s Error %s\n", file.c_str(), IMG_GetError());
			return;
		}

		mLocalTexture = SDL_CreateTextureFromSurface(mGraphics->mRenderer, surface);
		if (mLocalTexture == NULL) {
			printf("SDL failed to create texture: %s", SDL_GetError());
			return;
		}

		if (mFileExtension == "ttf") {

			SDL_QueryTexture(mLocalTexture, NULL, NULL, &mTextureArea.w, &mTextureArea.h);

		}

		//adding the created texture to asset manager
		mAsset->mInGameTextures[file] = mLocalTexture;

		//throw away the surface
		SDL_FreeSurface(surface);
	}

	void Texture::CreateFont(std::string file, std::string text, int fontSize, SDL_Color color) {
		//couldnt find font so we make one
		//preparing surface for font-texture creation
		SDL_Surface* surface;

		if (mAsset->mFonts[file]) {

			mFont = mAsset->mFonts[file];
		}

		mAsset->mFonts[file] = TTF_OpenFont(file.c_str(), fontSize);

		mFont = mAsset->mFonts[file];

		surface = TTF_RenderText_Solid(mFont, text.c_str(), color);

		if (surface == NULL) {
			printf("Image failed to load with surface FONT @ path %s Error %s\n", file.c_str(), IMG_GetError());
			return;
		}

		mLocalTexture = SDL_CreateTextureFromSurface(mGraphics->mRenderer, surface);
		if (mLocalTexture == NULL) {
			printf("SDL failed to create texture FONT: %s", SDL_GetError());
			return;
		}

		SDL_QueryTexture(mLocalTexture, NULL, NULL, &mTextureArea.w, &mTextureArea.h);

		//throw away the surface
		SDL_FreeSurface(surface);
	}

	void Texture::ClipLocalTexture(int x, int y, int w, int h) {
		//making sure a texture is actually loaded up on the local texture
		if (mLocalTexture == NULL) {
			printf("Error: Local texture has not been loaded on the texture class! Check the constructor/image path and resolve those errors first...\n");
			return;
		}

		//flag to signal to the renderer that we are doing a special render from this texture
		mIsClipped = true;

		//the area of the actual texture
		mTextureArea.x = 0;
		mTextureArea.y = 0;
		mTextureArea.w = w;
		mTextureArea.h = h;

		//clipping the image of the texture. If NULL, the entire image will be rendered
		mImageClip.x = x;
		mImageClip.y = y;
		mImageClip.w = w;
		mImageClip.h = h;
	}

	void Texture::PositionTextureArea(int x, int y) {

		mTextureArea.x = x;
		mTextureArea.y = y;
	}

	void Texture::LerpTextureArea(float xStart, float yStart, float xEnd, float yEnd, float time, float speed) {

		time *= speed;

		if (time <= 0.0f) {

			mTextureArea.x = xStart;
			mTextureArea.y = yStart;
		}
		else if (time >= 1.0f) {

			mTextureArea.x = xEnd;
			mTextureArea.y = yEnd;
		}
		else {
			mTextureArea.x = std::round(xStart + (xEnd - xStart) * time);
			mTextureArea.y = std::round(yStart + (yEnd - yStart) * time);
		}
	}

	void Texture::ScaleTextureArea(int scaleFactor, int offSetW, int offSetH) {

		mTextureArea.w = mTextureArea.w * scaleFactor - offSetW;
		mTextureArea.h = mTextureArea.h * scaleFactor - offSetH;
	}

	SDL_Texture* Texture::GetLocalTexture() {

		return mLocalTexture;
	}

	void Texture::Render() {
		//drawing...
		if (mIsClipped) {
			SDL_RenderCopy(mGraphics->mRenderer, mLocalTexture, &mImageClip, &mTextureArea);
		}
		else {
			SDL_RenderCopy(mGraphics->mRenderer, mLocalTexture, NULL, &mTextureArea);
		}
		//mGraphics->Render();
	}
}
