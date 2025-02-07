#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "Texture.h"

namespace SDLCore {

	class Animator {
	public:
		Animator(bool isSpriteSheet, Texture* mReferenceTexture, int numberOfSprites, int startFrame, float speed);
		~Animator();

		void Animate();


	private:
		Texture* mText;
		bool isSpriteSheet;
		int numberOfSprites;
		int x, y;
		void ResetTimer();
		int startTicks;
		int elapsedTicks;
		float deltaTime;
		int mCurrentFrame;
		int mStartFrame;
		float mAnimationSpeed;

	};
}



#endif