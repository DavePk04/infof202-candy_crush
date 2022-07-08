#include "cell.hpp"

class Canvas {
  vector<vector<Cell>> cells;
  int** board = new int*[COL];
 public:
  Canvas();
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
};