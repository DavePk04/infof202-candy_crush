#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <utility>
#include "../const.hpp"
#include "Point.hpp"


using namespace std;


class Board
{
	private:
		int** _board = new int*[GRID_DIMENSION];
		vector<vector<int>> _colors_grid;
        vector<Point> _aligned_candies_H, _aligned_candies_V, matchedCells;;
        int _score = 0;
        int _nummoves;
        vector<pair<Point, Point>> _possibleswap;
	public:
		Board();
		int** getBoard();
		bool swaps(Point cell_1, Point cell_2);
		static bool is_inBoard(Point pos);
		void gen_color_grid ();
        int GetColorAt (int colomn, int row);
        bool CheckMatches (bool counted);
        vector<Point> FindColumnMatchForCell (int col, int row, int color);
        vector<Point> FindRowMatchForCell (int row, int col, int color);
        void FillGrid ();
        void bomb(Point bombpos);
        int GetScore() const;
        void SetScore(int newscore);
        int GetNumMoves() const;
        void SetNumMoves(int numMoves);
        void addSwap(Point Source, Point Destination);
        void identifypossibleswap();
        void loopFillGrid();
        vector<pair<Point, Point>> get_possibleswap ();
  vector<Point> getMatchedCells ();
};

#endif // __BOARD_HPP__