#ifndef _LEVELS_HPP_
#define _LEVELS_HPP_
#include <string>
#include <vector>
#include "../../const.hpp"
#include <atomic>

using namespace std;

class Levels {
  int _idx;
  string _level_filename = " ";
  float _maxMoves = 0;
  vector<atomic_int> *_objectives = new vector<atomic_int> (8);
  int **_board = new int *[GRID_DIMENSION];
  bool _level = false;
 public:
  explicit Levels (int idx = -1);
  int **getBoard ();
  bool islevel () const;
  float get_maxMoves () const;
  bool goalAchieved ();
  vector<atomic_int> *getObjectives ();
};

#endif //_LEVELS_HPP_
