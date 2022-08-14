#include "cell.hpp"

class Canvas {
  vector<vector<Cell>> cells;
  //vector<Cell*> selected_cells;
  vector<Cell*> selected;
  Board bd;
  int** board;
  int possible_move_anim = 0;
 public:
  Canvas();
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  void gamesession(Cell *c);
  void normalise();
  void possible_move();
  Point p1_;
  Point p2_;
  // Fl_Color generateColor();
  // void check(Cell *c);
  // void swim(Cell *c);
  // void swap(Cell *c1, Cell *c2);
  // void swap_(Cell &c1, Cell &c2);
  // void delete_(Cell *c);
};