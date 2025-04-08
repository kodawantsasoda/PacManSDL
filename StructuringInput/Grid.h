#ifndef _GRID
#define _GRID
#include "Graphics.h"
#include "Tiles.h"
#include <vector>
#include <unordered_map>

namespace SDLCore {

	class Grid {
	public:

		Grid(SDL_Rect referenceRect, int numColumns, int numRows);
		~Grid();

		std::vector<Tiles>mTiles;

		int GetColumns();
		int GetRows();

		int GetScaleFactor();
		void FitTextureOnGrid(SDL_Rect referenceRect, int scaleFactor, SDL_Rect* textRect);

		void SetNonOrbs();
		void ResetOrbState(Tiles Tile);

	private:

		bool IsWallPos(int i);

		int mColumns;
		int mRows;
		int mScaleFactor;
	};
}

#endif