#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "Texture.h"
#include "Timer.h"

namespace SDLCore {

	class Animator {
	public:
		Animator(bool isSpriteSheet, Texture* referenceTexture, int numberOfSprites, int startFrame, float speed);
		~Animator();

		void Animate();

		void Init(bool isSpriteSheet, Texture* referenceTexture, int numberOfSprites, int startFrame, float speed);

	public:
		bool mAnimationCycleComplete;


	private:
		Texture* mText;
		Timer mTimer;

		bool isSpriteSheet;
		int numberOfSprites;
		int mCurrentFrame;
		int mStartFrame;
		float mAnimationSpeed;
		int mX, mY;

	};
}



#endif