#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <iostream>
//#include "Board.hpp"
#include "../model/Board.hpp"
using namespace std;



class Square: public Fl_Box {
//  Point center;
//  int w, h;

 public:
  Square (Fl_Boxtype b, int x, int y, int w, int h, const char *l, Fl_Color color = FL_BLACK);
  Point get_position() const;

  bool contains (Point p) const;
};