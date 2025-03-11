#include "Animator.h"

namespace SDLCore {

	Animator::Animator(bool isSpriteSheet, Texture* referenceTexture, int numberOfSprites, int startFrame, float speed) {

		Init(isSpriteSheet, referenceTexture, numberOfSprites, startFrame, speed);

		mTimer = Timer();
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

		mX = mText->mImageClip.x;
		mY = mText->mImageClip.y;

		mAnimationCycleComplete = false;
	}

	void Animator::Animate() {

		mTimer.Update();

		if (isSpriteSheet) {

			if (mTimer.DeltaTime() > mAnimationSpeed) {

				mTimer.ResetTimer();

				mCurrentFrame++;

				if (mCurrentFrame > numberOfSprites) {

					mCurrentFrame = 0;
					mText->mImageClip.x = mX;
				}
				
				else
					mText->mImageClip.x = mX + (mText->mImageClip.w * mCurrentFrame);

				if (mCurrentFrame == mStartFrame) {

					mAnimationCycleComplete = true;
					//printf("CYCLED\n");
				}
			}
		}
	}
}