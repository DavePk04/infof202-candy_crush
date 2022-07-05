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
};

#endif // __BOARD_H__