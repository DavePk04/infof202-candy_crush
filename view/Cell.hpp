#include <vector>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include "Square.hpp"
#include "Animation.hpp"

using namespace std;

class Animation;

class Cell {
  Point center;
  int w, h;
  bool selected = false;

  Square *square = nullptr;
  Animation *animation = nullptr;

  Fl_Color color;

  // Private methods
 public:
  // Constructor
  Cell (Point center, int w, int h, Fl_Color color);
  ~Cell () = default;;
  void initialize ();
  Fl_Color get_color () const;
  void set_color (Fl_Color new_color);

  // Methods that draw and handle events
  void draw ();
  void mouseMove (Point mouseLoc);
  void mouseClick (Point mouseLoc);
  bool is_selected () const;
  void unselect ();
  Point get_center () const;
  void set_center (Point new_center);
  void change (Fl_Color color_);

  void drawWithoutAnimate ();
};