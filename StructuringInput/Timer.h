#ifndef TIMER_H
#define TIMER_H

#include "SDL.h"

namespace SDLCore {

	class Timer {

	public:
		Timer();
		~Timer();

		void ResetTimer();

		void Update();

	public:
		float DeltaTime();

	private: 
		int mStartTicks;
		int mElapsedTicks;
		float mDeltaTime;
	};
}

#endif
