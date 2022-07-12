#include "cell.hpp"

class Canvas {
  vector<vector<Cell>> cells;
  int** board = new int*[COL];
  vector<Cell*> selected_cells;
 public:
  Canvas();
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  void check(Cell *c);
  void update ();
};