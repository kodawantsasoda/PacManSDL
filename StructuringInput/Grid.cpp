#include "Grid.h"

namespace SDLCore {

	Grid::Grid(SDL_Rect referenceRect, int numColumns, int numRows) {

		SDL_Rect tile = referenceRect;
		mColumns = numColumns;
		mRows = numRows;
		mScaleFactor = 1;

		for (int i = 0; i < numRows; i++) {
			for (int j = 0; j < numColumns; j++) {
				tiles.push_back(tile);
				tile.x += tile.w;
			}
			tile.x = referenceRect.x;
			tile.y += tile.h;
		}
	}

	Grid::~Grid() {

	}

	int Grid::GetColumns() {

		return mColumns;
	}

	int Grid::GetRows() {

		return mRows;
	}
	int Grid::GetScaleFactor() {

		return mScaleFactor;
	}


	//this molds the texture rect to fit within the grid
	void Grid::FitTextureOnGrid(SDL_Rect referenceRect, int scaleFactor, SDL_Rect* textRect) {

		mScaleFactor = scaleFactor;

		int columns = GetColumns(), rows = GetRows();

		textRect->w = (scaleFactor * referenceRect.w);
		textRect->h = (scaleFactor * referenceRect.h);

		if (columns < rows)
			textRect->h += (referenceRect.h * (rows - columns));
		else if (rows < columns)
			textRect->w += (referenceRect.w * (columns - rows));
	}
}                                                                                                                                                                                                                                                                                                  