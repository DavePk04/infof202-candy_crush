#include <vector>
#include "model/Point.hpp"

using namespace std;


// constants

//Windows settings
const int WINDOWWIDTH = 500;
const int WINDOWHEIGHT = 600;
const double REFRESHPERSECOND = 60;

// _board related
const int GRID_DIMENSION = 9;
const int TOTALCOLOR = 6;
const int MIN_CANDIES_ALIGNED = 3;
const int OBJECTIVES = 8;
enum COLORS {
  BLUE = 1,
  RED = 2,
  GREEN = 3,
  ORANGE = 4,
  YELLOW = 5,
  MAGENTA = 6,
  BRICK = 7,
  BOMB = 8,
  SIMPLEICE = 9,
  DOUBLEICE = 10
};
const vector<int> COLORS_VECT{1, 2, 3, 4, 5, 6, 7};
const vector<Point> DIR{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
const vector<Point> BOMBDIR{{0, -1}, {0, 1}, {-1, 0}, {1, 0}, {1, 1}, {1, -1},
                            {-1, 1}, {-1, -1}, {0, -2}, {0, 2}, {-2, 0}, {2, 0}};

enum ACTION { MOVE = 1, PUSH = 2, KEYDOWN = 3 };
enum GameState { PENDING, RUNNING, GAME_OVER };
const string SV_HIGHSCORE_FILE = "../highscorefile.txt";
const vector<string> LEVELS{"../model/levels/level1", "../model/levels/level2", "../model/levels/level3"};