#ifndef COLLIDER_H
#define COLLIDER_H
#include "SDL.h"

namespace SDLCore {

	class Collider {
	public:
		Collider(SDL_Rect collider);
		~Collider();

		SDL_Rect mBoxCollider;


	private:
		bool HasCollided(SDL_Rect obj1, SDL_Rect obj2);

	};
}



#endif