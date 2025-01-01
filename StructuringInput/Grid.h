#ifndef _GRID
#define _GRID
#include "Graphics.h"
#include <vector>

namespace SDLCore {

	class Grid {
	public:
		Grid(SDL_Rect referenceRect, int numColumns, int numRows);
		~Grid();
		std::vector<SDL_Rect>tiles;
		int GetColumns();
		int GetRows();
		int GetScaleFactor();
		void FitTextureOnGrid(SDL_Rect referenceRect, int scaleFactor, SDL_Rect* textRect);

	private:
		int mColumns;
		int mRows;
		int mScaleFactor;
	};
}

#endif