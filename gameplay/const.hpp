#ifndef __CONST_H__
#define __CONST_H__

#include <vector>
#include "Point.hpp"
using namespace std;


// constants

// board related
const int GRID_DIMENSION = 9;
const int TOTALCOLOR = 6;
const int MIN_CANDIES_ALIGNED = 3;
const int CANDY_DELETED = 0;
enum COLORS {BLUE=1, RED=2, GREEN=3, YELLOW=4, CYAN=5, MAGENTA=6};
vector<int> COLORS_VECT{1,2,3,4,5,6};
const vector<Point> DIR{{0,-1},{0,1},{-1,0},{1,0}};


// wall related
const vector<int> STANDART_WALLSET{1,1,1,1,1,1,1,1,1,1};
const vector<Point> ROT{{1,1},{-1,1},{-1,-1},{1,-1}};

// errors
const int INVALID =-1;

#endif // __CONST_H__