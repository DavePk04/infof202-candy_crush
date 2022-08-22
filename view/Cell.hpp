#include <vector>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include "Square.hpp"

using namespace std;

class Cell {
  Point center;
  int w, h;
  bool selected = false;
  Square *square = nullptr;
  Fl_Color color;

 public:
  Cell (Point center, int w, int h, Fl_Color color);
  ~Cell () = default;;
  void initialize ();
  Fl_Color get_color () const;
  void set_color (Fl_Color new_color);

  void draw ();
  void mouseMove (Point mouseLoc);
  void mouseClick (Point mouseLoc);
  bool is_selected () const;
  void unselect ();
  Point get_center () const;
  void change (Fl_Color color_);
};