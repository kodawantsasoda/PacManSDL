#ifndef _TILES_H
#define _TILES_H
#include <SDL.h>

namespace SDLCore {

	struct Tiles {

		SDL_Rect mTile;
		bool mIsWall;
		bool mHasVisited;

		Tiles(SDL_Rect tile, bool isWall, bool hasVisited) {

			mTile = tile;
			mIsWall = isWall;
			mHasVisited = hasVisited;
		}
	};
}

#endif