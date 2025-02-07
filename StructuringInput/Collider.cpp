#include "Collider.h"

namespace SDLCore {

	Collider::Collider(SDL_Rect collider) {

		mBoxCollider = collider;
	}

	Collider::~Collider() {


	}

	bool Collider::HasCollided(SDL_Rect obj1, SDL_Rect obj2) {

		int xBounds = obj1.x + obj1.w;
		int yBounds = obj1.y + obj1.h;

		if (obj2.x >= obj1.x && obj2.x <= xBounds) {

			return true;
		}

		return false;
	}

}