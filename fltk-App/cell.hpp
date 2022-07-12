#include <vector>
#include <iostream>
#include <map>
#include <memory>
#include "square.hpp"


using namespace std;

class Cell {
  Point center;
  int w, h;
  bool selected = false;

  Square *square = nullptr;

  Fl_Color color;

  // Private methods
 public:
  // Constructor
  Cell (Point center, int w, int h, Fl_Color color);
  ~Cell(){};
  void initialize();
  Fl_Color get_color();
  void set_color(Fl_Color new_color);

  // Methods that draw and handle events
  void draw ();
  void mouseMove (Point mouseLoc);
  void mouseClick(Point mouseLoc);
  bool is_selected() const;
  void unselect();
//  void mouseClick (Point mouseLoc);
//  void deleting();
  void reposition(Point p);
  Point get_center() const;
  void set_center(Point new_center);

};