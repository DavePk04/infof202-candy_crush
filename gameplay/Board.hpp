#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include "const.hpp"
#include "Point.hpp"


using namespace std;


class Board
{
	private:
		int** board = new int*[GRID_DIMENSION];
		vector<vector<int>> colors_grid;
        vector<Point> aligned_candies_H, aligned_candies_V;
        int mscore = 0;
        int mnummoves;
	public:
		Board();
		int** getBoard();
		bool swaps(Point cell_1, Point cell_2);
		bool is_inBoard(Point pos);
		void gen_color_grid ();
        int GetColorAt (int colomn, int row);
        bool CheckMatches ();
        vector<Point> FindColumnMatchForCell (int col, int row, int color);
        vector<Point> FindRowMatchForCell (int row, int col, int color);
        void FillGrid ();
        void bomb(Point bombpos);
        int GetScore();
        void SetScore(int newscore);
        int GetNumMoves();
        void SetNumMoves(int numMoves);
};

#endif // __BOARD_H__