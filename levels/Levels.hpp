//
// Created by bdmr on 19/08/22.
//

#ifndef _LEVELS_HPP_
#define _LEVELS_HPP_
#include <string>
#include <vector>
#include "../const.hpp"

using namespace std;

class Levels {
  int _idx;
  string _level_filename = " ";
  float _maxMoves = 0;
  vector<int> _objectives;
  int **_board = new int *[GRID_DIMENSION];
  bool _level = false;
 public:
  explicit Levels(int idx = -1);
  int **getBoard ();
  bool islevel() const;
  int get_levelnumber() const;
  float get_maxMoves() const;
};

#endif //_LEVELS_HPP_
