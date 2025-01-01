#include "Texture.h"

namespace SDLCore{
	//creating texture based on file; unless already created then just load
	Texture::Texture(std::string file) {
		
		mGraphics = Graphics::Instance();
		mAsset = AssetManager::Instance();
		
		//loading texture if created
		mLocalTexture = mAsset->mInGameTextures[file];
		if(mLocalTexture == NULL)
			CreateTexture(file);

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
		SDL_Surface* surface = IMG_Load(file.c_str());
		if (surface == NULL) {
			printf("Image failed to load with surface @ path %s Error %s\n", file.c_str(), IMG_GetError());
			return;
		}

		mLocalTexture = SDL_CreateTextureFromSurface(mGraphics->mRenderer, surface);
		if (mLocalTexture == NULL) {
			printf("SDL failed to create texture: %s", SDL_GetError());
			return;
		}

		//throw away the surface
		SDL_FreeSurface(surface);

		return;
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

	void Texture::ScaleTextureArea(int scaleFactor) {

		mTextureArea.w *= scaleFactor;
		mTextureArea.h *= scaleFactor;
	}

	SDL_Texture* Texture::GetLocalTexture() {

		return mLocalTexture;
	}

	void Texture::Render() {
		
		if (mIsClipped) {
			SDL_RenderCopy(mGraphics->mRenderer, mLocalTexture, &mImageClip, &mTextureArea);
		}
		else {
			SDL_RenderCopy(mGraphics->mRenderer, mLocalTexture, NULL, &mTextureArea);
		}
		//mGraphics->Render();
	}
}
