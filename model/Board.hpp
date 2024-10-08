#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <utility>
#include "Point.hpp"
#include "../model/levels/Levels.hpp"

using namespace std;

class Board {
 private:
  Levels level;
  int **_board = new int *[GRID_DIMENSION];
  vector<vector<int>> _colors_grid;
  vector<Point> _aligned_candies_H, _aligned_candies_V, explosion, copy_matchedCells;
  GameState game_state = PENDING;
  int _score = 0;
  int _nummoves;
  bool win = true;
  vector<pair<Point, Point>> _possibleswap;

 public:
  explicit Board (int idx = -1);
  int **getBoard ();
  bool swaps (Point cell_1, Point cell_2);
  static bool is_inBoard (Point pos);
  void gen_color_grid ();
  int getColorAt (int colomn, int row, int **bd);
  bool CheckMatches (bool counted);
  vector<Point> FindColumnMatchForCell (int col, int row, int color);
  vector<Point> FindRowMatchForCell (int row, int col, int color);
  void fillGrid ();
  void bomb (Point bombpos);
  int getScore () const;
  int getNumMoves () const;
  void addSwap (Point Source, Point Destination);
  void identifypossibleswap ();
  void loopFillGrid ();
  vector<pair<Point, Point>> get_possibleswap ();
  vector<Point> getMatchedCells ();
  GameState getState () const;
  bool isWinner () const;
  void clearMatchedCells ();
  void regen_color_grid ();
  vector<atomic_int> *getObjectives ();

};

#endif // __BOARD_HPP__