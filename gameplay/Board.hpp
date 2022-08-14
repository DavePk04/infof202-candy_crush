#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <utility>
#include "const.hpp"
#include "Point.hpp"


using namespace std;


class Board
{
	private:
		int** _board = new int*[GRID_DIMENSION];
		vector<vector<int>> _colors_grid;
        vector<Point> _aligned_candies_H, _aligned_candies_V;
        int _score = 0;
        int _nummoves;
        vector<pair<Point, Point>> _possibleswap;
	public:
		Board();
		int** getBoard();
		bool swaps(Point cell_1, Point cell_2);
		bool is_inBoard(Point pos);
		void gen_color_grid ();
        int GetColorAt (int colomn, int row);
        bool CheckMatches (bool counted);
        vector<Point> FindColumnMatchForCell (int col, int row, int color);
        vector<Point> FindRowMatchForCell (int row, int col, int color);
        void FillGrid ();
        void bomb(Point bombpos);
        int GetScore();
        void SetScore(int newscore);
        int GetNumMoves();
        void SetNumMoves(int numMoves);
        void addSwap(Point Source, Point Destination);
        void identifypossibleswap();
        vector<pair<Point, Point>> get_possibleswap();
};

#endif // __BOARD_H__