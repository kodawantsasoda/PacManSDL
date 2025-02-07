#ifndef PacManPlayer_H
#define PacManPlayer_H
#include "Texture.h"
#include "InputManager.h"
#include "GameMap.h"
#include "Animator.h"
#include "Collider.h"

using namespace SDLCore;

class PacManPlayer {

public:

	PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap);
	~PacManPlayer();

	SDL_Rect mMoveSquare;
	GameMap* mGameMap;
	
	void Update();
	void Render();

	void Move(char input);
	int GetTileInFrontOfMouth();
	bool mIsMoving;
	char mCurrentInput;
	int mTargetTileX;
	int mTargetTileY;
	Texture* mPacMan;

	int CurrentPositionOnGrid;
	std::vector<int> mScore;

	SDL_Rect mCollider;

private:

	//Graphics* mGraphics;
	InputManager* mInput;
	Animator* mAnimator;

	float mMoveSpeed;

	void ResetTimer();
	int startTicks;
	int elapsedTicks;
	float deltaTime;
};

#endif // !PacManPlayer
