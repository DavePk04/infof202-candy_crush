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
	public:
		Board();
        explicit Board(string level);
		int** getBoard();
		bool swaps(Point cell_1, Point cell_2);
		static bool is_inBoard(Point pos);
		void gen_color_grid ();
        int getColorAt (int colomn, int row, int** bd);
        bool CheckMatches (bool counted);
        vector<Point> FindColumnMatchForCell (int col, int row, int color);
        vector<Point> FindRowMatchForCell (int row, int col, int color);
        void fillGrid ();
        void bomb(Point bombpos);
        int getScore() const;
        void setScore(int newscore);
        int getNumMoves() const;
        void SetNumMoves(int numMoves);
        void addSwap(Point Source, Point Destination);
        void identifypossibleswap();
        void loopFillGrid();
        vector<pair<Point, Point>> get_possibleswap ();
        vector<Point> getMatchedCells ();
        GameState getState() const;
        void clearMatchedCells ();
        void regen_color_grid ();

    private:
      int** _board = new int*[GRID_DIMENSION];
      vector<vector<int>> _colors_grid;
      vector<Point> _aligned_candies_H, _aligned_candies_V, explosion, copy_matchedCells;
    //        bool bombcause = false;
      GameState game_state = PENDING;
      int _score = 0;
      float _nummoves;
      int _score_goal;
      vector<int> _objectives_goal;
      vector<pair<Point, Point>> _possibleswap;

};

#endif // __BOARD_HPP__