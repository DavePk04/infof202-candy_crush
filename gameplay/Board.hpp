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
	public:
		Board();
		int** getBoard();
		void swap(Point cell_1, Point cell_2);
		bool is_inBoard(Point pos);
		bool is_validSwap(Point ori, Point target);
        bool is_aligned(Point target);
        void delete_candies(vector<Point> targets);
        void swim(Point p);
		void control_generation (int x, int y);
		void gen_color_grid ();
        int GetColorAt (int colomn, int row);
  bool CheckMatches ();
  vector<Point> FindColumnMatchForCell (int col, int row, int color);
  vector<Point> FindRowMatchForCell (int row, int col, int color);
  void FillGrid ();
};

#endif // __BOARD_H__