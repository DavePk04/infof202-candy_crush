#include "cell.hpp"

class Canvas {
  vector<vector<Cell>> cells;
  int** board = new int*[COL];
  vector<Cell*> selected_cells;
  vector<Cell*> selected;
 public:
  Canvas();
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  void check(Cell *c);
  void swim(Cell *c);
  void swap(Cell *c1, Cell *c2);
  void swap_(Cell &c1, Cell &c2);
};