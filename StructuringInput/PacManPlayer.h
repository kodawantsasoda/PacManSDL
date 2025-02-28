#ifndef PacManPlayer_H
#define PacManPlayer_H
#include "Texture.h"
#include "InputManager.h"
#include "GameMap.h"

using namespace SDLCore;

class PacManPlayer {

public:

	PacManPlayer(SDL_Rect moveSquare, GameMap* gameMap);
	~PacManPlayer();

	SDL_Rect mMoveSquare;
	GameMap* mGameMap;
	
	void Update();
	void Render();

	//bool CanMove(GameMap* map, int tileLocation);
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void Move(char input);
	bool mIsMoving;
	char mCurrentInput;
	int mTargetTileX;
	int mTargetTileY;
	Texture* mPacMan;

	int CurrentPositionOnGrid;
	std::vector<int> mScore;

private:

	//Graphics* mGraphics;
	InputManager* mInput;

	float mMoveSpeed;

	void ResetTimer();
	int startTicks;
	int elapsedTicks;
	float deltaTime;
};

#endif // !PacManPlayer
