#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "GameScreen.h"

/*this class is the most prone to change of the namespace SDLCore, in that it largely revolves around the functionailty of the game...
* Respnsible for managing everything you see on the screen. Notably, switching between game states like start screen, pause, play, etc...*/

namespace SDLCore {
	class ScreenManager {
	public:
		//singleton
		static ScreenManager* Instance();
		void Release();

		ScreenManager();
		~ScreenManager();

		void Update();
		void Render();


	private:

		static ScreenManager* sInstance;

		GameScreen* mGameScreen;
		//GameMap* mMap;
		//PacManPlayer* mPacMan;
	};
}

#endif // SCREEN_MANAGER_
