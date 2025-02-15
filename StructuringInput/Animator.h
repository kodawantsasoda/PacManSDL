#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "Texture.h"

namespace SDLCore {

	class Animator {
	public:
		Animator(bool isSpriteSheet, Texture* referenceTexture, int numberOfSprites, int startFrame, float speed);
		~Animator();

		void Animate();

		void Init(bool isSpriteSheet, Texture* referenceTexture, int numberOfSprites, int startFrame, float speed);

		bool mAnimationCycleComplete;


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