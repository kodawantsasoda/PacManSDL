#include "Timer.h"

namespace SDLCore{

	Timer::Timer() {

		ResetTimer();
	}

	Timer::~Timer() {


	}

	float Timer::DeltaTime() {

		return mDeltaTime;
	}

	void Timer::ResetTimer() {

		mStartTicks = SDL_GetTicks();
		mElapsedTicks = 0;
		mDeltaTime = 0.0f;
	}

	void Timer::Update() {

		mElapsedTicks = SDL_GetTicks() - mStartTicks;
		mDeltaTime = mElapsedTicks * 0.001f;
	}
}