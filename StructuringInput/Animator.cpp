#include "Animator.h"

namespace SDLCore {

	Animator::Animator(bool isSpriteSheet, Texture* referenceTexture, int numberOfSprites, int startFrame, float speed) {

		Init(isSpriteSheet, referenceTexture, numberOfSprites, startFrame, speed);

		startTicks = SDL_GetTicks();
		elapsedTicks = 0;
		deltaTime = 0.0f;
	}

	Animator::~Animator() {

		mText = NULL;
	}

	void Animator::Init(bool isSpriteSheet, Texture* referenceTexture, int numberOfSprites, int startFrame, float speed) {

		mText = referenceTexture;
		this->numberOfSprites = numberOfSprites;
		this->isSpriteSheet = isSpriteSheet;
		mStartFrame = startFrame;
		startFrame = mCurrentFrame;
		mAnimationSpeed = speed;

		x = mText->mImageClip.x;
		y = mText->mImageClip.y;

		mAnimationCycleComplete = false;
	}

	void Animator::ResetTimer() {

		startTicks = SDL_GetTicks();
		elapsedTicks = 0;
		deltaTime = 0.0f;
	}

	void Animator::Animate() {

		elapsedTicks = SDL_GetTicks() - startTicks;
		deltaTime = elapsedTicks * 0.001f;

		if (isSpriteSheet) {

			if (deltaTime > mAnimationSpeed) {

				ResetTimer();

				mCurrentFrame++;

				if (mCurrentFrame > numberOfSprites) {

					mCurrentFrame = 0;
					mText->mImageClip.x = x;
				}
				
				else
					mText->mImageClip.x = x + (mText->mImageClip.w * mCurrentFrame);

				if (mCurrentFrame == mStartFrame) {

					mAnimationCycleComplete = true;
					//printf("CYCLED\n");
				}
			}
		}
	}

}