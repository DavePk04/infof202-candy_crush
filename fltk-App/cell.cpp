#include "cell.hpp"


Cell::Cell(Point center, int w, int h, Fl_Color frameColor, Fl_Color fillColor):
  r(center, w, h, frameColor, fillColor) {}

void Cell::draw() {
  r.draw();
}

void Cell::mouseMove(Point mouseLoc) {
  if (r.contains(mouseLoc)) {
    r.setFrameColor(FL_RED);
  } else {
    r.setFrameColor(FL_BLACK);
  }
}


void Cell::mouseClick(Point mouseLoc) {
  if (r.contains(mouseLoc))
    cout << '(' << r.getCenter().x << ',' << r.getCenter().y << ')' << endl;
}