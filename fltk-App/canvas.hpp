#include "cell.hpp"

class Canvas {
  vector<vector<Cell>> cells;
  //vector<Cell*> selected_cells;
  vector<Cell*> selected;
  Board bd;
  int** board;
 public:
  Canvas();
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  void gamesession(Cell *c);
  void normalise();
  // Fl_Color generateColor();
  // void check(Cell *c);
  // void swim(Cell *c);
  // void swap(Cell *c1, Cell *c2);
  // void swap_(Cell &c1, Cell &c2);
  // void delete_(Cell *c);
};