#include "square.hpp"

/*--------------------------------------------------

Cell class.

The Canvas class below will have cells as instance
vraiables and call the methods of Cell
--------------------------------------------------*/


class Cell {
  Rectangle r;
 public:
  // Constructor
  Cell(Point center, int w, int h, Fl_Color frameColor, Fl_Color fillColor);

  // Methods that draw and handle events
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);

};
