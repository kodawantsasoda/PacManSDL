#ifndef PacManPlayer_H
#define PacManPlayer_H
#include "Texture.h"
#include "InputManager.h"

using namespace SDLCore;

class PacManPlayer {
public:
	PacManPlayer();
	~PacManPlayer();
	
	void Update();
	void Render();

	void Move();
	Texture* mPacMan;


private:
	Graphics* mGraphics;
};

#endif // !PacManPlayer
