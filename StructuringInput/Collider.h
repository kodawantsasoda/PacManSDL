#ifndef COLLIDER_H
#define COLLIDER_H
#include "SDL.h"

namespace SDLCore {

	struct Collider {

		SDL_Rect* mEntityMain;
		SDL_Rect* mParent;

		int mXParentDifference;
		int mYParentDifference;

		Collider() {

			mXParentDifference = 0;
			mYParentDifference = 0;

			mEntityMain = NULL;
			mParent = NULL;
		}

		void SetParent(SDL_Rect* entityMain, SDL_Rect* parent) {

			this->mEntityMain = entityMain;
			this->mParent = parent;

			mXParentDifference = entityMain->x - parent->x;
			mYParentDifference = entityMain->y - parent->y;
		}

		void FollowParent() {

			if (mParent == NULL) {

				printf("Collider Error... Assign parent to entity using 'SetParet' first!\n");
				return;
			}

			mEntityMain->x = mParent->x + mXParentDifference;
			mEntityMain->y = mParent->y + mYParentDifference;
		}
	};

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