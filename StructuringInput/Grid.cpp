#include "Grid.h"

namespace SDLCore {

	Grid::Grid(SDL_Rect referenceRect, int numColumns, int numRows) {

		Tiles tiles(referenceRect, true, false); 
		SDL_Rect tile = referenceRect;

		mColumns = numColumns;
		mRows = numRows;
		mScaleFactor = 1;

		for (int i = 0; i < numRows; i++) {

			for (int j = 0; j < numColumns; j++) {

				mTiles.push_back(tiles);
				if (!IsWallPos(mTiles.size() - 1))
					mTiles[mTiles.size() - 1].mIsWall = false;

				tile.x += tile.w;
				tiles.mTile = tile;
			}
			tile.x = referenceRect.x;
			tile.y += tile.h;
			tiles.mTile = tile;
		}

        SetNonOrbs();
	}

	Grid::~Grid() {

	}

	bool Grid::IsWallPos(int i) {

        if (i == 29 || i == 30 || i == 31 || i == 32 || i == 33 || i == 34 ||
            i == 35 || i == 36 || i == 37 || i == 38 || i == 39 || i == 40 ||
            i == 43 || i == 44 || i == 45 || i == 46 || i == 47 || i == 48 ||
            i == 49 || i == 50 || i == 51 || i == 52 || i == 53 || i == 54 ||
            i == 57 || i == 62 || i == 68 || i == 71 || i == 77 || i == 82 ||
            i == 85 || i == 90 || i == 96 || i == 99 || i == 105 || i == 110 ||
            i == 113 || i == 118 || i == 124 || i == 127 || i == 133 || i == 138 ||
            i == 141 || i == 142 || i == 143 || i == 144 || i == 145 || i == 146 ||
            i == 147 || i == 148 || i == 149 || i == 150 || i == 151 || i == 152 ||
            i == 153 || i == 154 || i == 155 || i == 156 || i == 157 || i == 158 ||
            i == 159 || i == 160 || i == 161 || i == 162 || i == 163 || i == 164 ||
            i == 165 || i == 166 || i == 169 || i == 174 || i == 177 || i == 186 ||
            i == 189 || i == 194 || i == 197 || i == 202 || i == 205 || i == 214 ||
            i == 217 || i == 222 || i == 225 || i == 226 || i == 227 || i == 228 ||
            i == 229 || i == 230 || i == 233 || i == 234 || i == 235 || i == 236 ||
            i == 239 || i == 240 || i == 241 || i == 242 || i == 245 || i == 246 ||
            i == 247 || i == 248 || i == 249 || i == 250 || i == 258 || i == 264 ||
            i == 267 || i == 273 || i == 286 || i == 292 || i == 295 || i == 301 ||
            i == 314 || i == 317 || i == 318 || i == 319 || i == 320 || i == 321 ||
            i == 322 || i == 323 || i == 324 || i == 325 || i == 326 || i == 329 ||
            i == 342 || i == 345 || i == 350 || i == 349 || i == 354 || i == 357 || i == 370 || i == 373 || i == 375 || i == 376 || i == 377 || i == 378 || i == 379 ||
            i == 382 || i == 385 || i == 392 || i == 393 || i == 394 || i == 395 || i == 396 || i == 397 ||
            i == 398 || i == 399 || i == 400 || i == 401 || i == 403 || i == 404 || i == 405 || i == 406 || i == 407 || i == 410 || i == 411 ||
            i == 412 || i == 413 || i == 414 || i == 415 || i == 416 || i == 417 ||
            i == 418 || i == 419 || i == 426 || i == 429 || i == 438 || i == 441 ||
            i == 454 || i == 457 || i == 466 || i == 469 || i == 479 || i == 480 || i == 481 || i == 482 || i == 485 ||
            i == 486 || i == 487 || i == 488 || i == 489 || i == 490 || i == 491 ||
            i == 492 || i == 493 || i == 494 || i == 497 || i == 510 || i == 513 ||
            i == 522 || i == 525 || i == 538 || i == 541 || i == 550 || i == 553 ||
            i == 561 || i == 562 || i == 563 || i == 564 || i == 565 || i == 566 ||
            i == 567 || i == 568 || i == 569 || i == 570 || i == 571 || i == 572 ||
            i == 575 || i == 576 || i == 577 || i == 578 || i == 579 || i == 580 ||
            i == 581 || i == 582 || i == 583 || i == 584 || i == 585 || i == 586 ||
            i == 589 || i == 594 || i == 600 || i == 603 || i == 609 || i == 614 ||
            i == 617 || i == 622 || i == 628 || i == 631 || i == 637 || i == 642 ||
            i == 645 || i == 646 || i == 647 || i == 650 || i == 651 || i == 652 ||
            i == 653 || i == 654 || i == 655 || i == 656 || i == 657 || i == 658 || i == 659 ||
            i == 660 || i == 661 || i == 662 || i == 663 || i == 664 || i == 665 ||
            i == 668 || i == 669 || i == 670 || i == 675 || i == 678 || i == 681 || i == 687 || i == 690 ||
            i == 693 || i == 696 || i == 703 || i == 706 || i == 709 || i == 718 ||
            i == 721 || i == 724 || i == 729 || i == 730 || i == 731 || i == 732 ||
            i == 733 || i == 734 || i == 737 || i == 738 || i == 739 || i == 740 ||
            i == 743 || i == 744 || i == 745 || i == 746 || i == 749 || i == 750 ||
            i == 751 || i == 752 || i == 753 || i == 754 || i == 757 || i == 768 ||
            i == 771 || i == 782 || i == 785 || i == 796 || i == 799 || i == 810 ||
            i == 813 || i == 814 || i == 815 || i == 816 || i == 817 || i == 818 ||
            i == 819 || i == 820 || i == 821 || i == 822 || i == 823 || i == 824 ||
            i == 825 || i == 826 || i == 827 || i == 828 || i == 829 || i == 830 ||
            i == 831 || i == 832 || i == 833 || i == 834 || i == 835 || i == 836 ||
            i == 837 || i == 838) {
            return false;
        }

        return true;
	}

    //this is to set non orb tiles that are walkable, but do not offer any scoring
    void Grid::SetNonOrbs() {

        //56 tiles total that are non orbs
        //we set tile as visited so when the scoring logic checks if the space has been visited, it already has been visited so we don't add score
        mTiles[264].mHasVisited = true;
        mTiles[267].mHasVisited = true;
        mTiles[292].mHasVisited = true;
        mTiles[295].mHasVisited = true;
        mTiles[317].mHasVisited = true;
        mTiles[318].mHasVisited = true;
        mTiles[319].mHasVisited = true;
        mTiles[320].mHasVisited = true;
        mTiles[321].mHasVisited = true;
        mTiles[322].mHasVisited = true;
        mTiles[323].mHasVisited = true;
        mTiles[324].mHasVisited = true;
        mTiles[325].mHasVisited = true;
        mTiles[326].mHasVisited = true;
        mTiles[345].mHasVisited = true;
        mTiles[354].mHasVisited = true;
        mTiles[373].mHasVisited = true;
        mTiles[382].mHasVisited = true;
        mTiles[392].mHasVisited = true;
        mTiles[393].mHasVisited = true;
        mTiles[394].mHasVisited = true;
        mTiles[395].mHasVisited = true;
        mTiles[396].mHasVisited = true;
        mTiles[397].mHasVisited = true;
        mTiles[399].mHasVisited = true;
        mTiles[400].mHasVisited = true;
        mTiles[401].mHasVisited = true;
        mTiles[410].mHasVisited = true;
        mTiles[411].mHasVisited = true;
        mTiles[412].mHasVisited = true;
        mTiles[414].mHasVisited = true;
        mTiles[415].mHasVisited = true;
        mTiles[416].mHasVisited = true;
        mTiles[417].mHasVisited = true;
        mTiles[418].mHasVisited = true;
        mTiles[419].mHasVisited = true;
        mTiles[429].mHasVisited = true;
        mTiles[438].mHasVisited = true;
        mTiles[457].mHasVisited = true;
        mTiles[466].mHasVisited = true;
        mTiles[485].mHasVisited = true;
        mTiles[486].mHasVisited = true;
        mTiles[487].mHasVisited = true;
        mTiles[488].mHasVisited = true;
        mTiles[489].mHasVisited = true;
        mTiles[490].mHasVisited = true;
        mTiles[491].mHasVisited = true;
        mTiles[492].mHasVisited = true;
        mTiles[493].mHasVisited = true;
        mTiles[494].mHasVisited = true;
        mTiles[513].mHasVisited = true;
        mTiles[522].mHasVisited = true;
        mTiles[541].mHasVisited = true;
        mTiles[550].mHasVisited = true;
        mTiles[657].mHasVisited = true;
        mTiles[658].mHasVisited = true;
    }

    void Grid::ResetOrbState(Tiles Tile) {

        Tile.mHasVisited = false;
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