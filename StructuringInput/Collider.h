#ifndef COLLIDER_H
#define COLLIDER_H
#include "SDL.h"

namespace SDLCore {

	inline bool HasCollided(const SDL_Rect* entityMain, const SDL_Rect* opposingEntity) {

		if (opposingEntity->x >= entityMain->x && 
			opposingEntity->x <= entityMain->x + entityMain->w &&
			opposingEntity->y >= entityMain->y &&
			opposingEntity->y <= entityMain->y + entityMain->w) {

			return true;
		}

		return false;
	}
}



#endif