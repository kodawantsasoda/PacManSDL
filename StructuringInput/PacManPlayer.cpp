#include "PacManPlayer.h"

PacManPlayer::PacManPlayer() {

	mPacMan = new Texture("PMSpriteSheet.png");
	mPacMan->ClipLocalTexture(471, 0, 16, 16);//
}

PacManPlayer::~PacManPlayer() {

	delete mPacMan;
	mPacMan = NULL;
}

void PacManPlayer::Move() {


}

void PacManPlayer::Update() {


}

void PacManPlayer::Render() {

	mPacMan->Render();
}