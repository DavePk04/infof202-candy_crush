#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <iostream>
#include "const.hpp"
#include "Point.hpp"

using namespace std;


class Board
{
	private:
		int** board = new int*[COL];
		vector<vector<int>> colors_grid;
        vector<Point> aligned_candies_H, aligned_candies_V;
	public:
		Board();
		int** getBoard();
		void swap(Point ori, Point target);
		bool is_inBoard(Point pos);
		bool is_validSwap(Point ori, Point target);
        bool is_aligned(Point target);
        void delete_candies(vector<Point> targets);
        void swim(Point p);
		void control_generation (int x, int y);
		void gen_color_grid ();
};

#endif // __BOARD_H__