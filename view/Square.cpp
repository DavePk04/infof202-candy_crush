#include "Square.hpp"

Square::Square (Fl_Boxtype b, int x, int y, int w, int h, const char *l, Fl_Color color) :
    Fl_Box (b, x, y, w, h, l)
{} //center{x, y}, w{w}, h{h}{}


/**
 * check if a point is contained in a square
 */
bool Square::contains (Point p) const
{
  return p.x >= x () &&
         p.x < x () + w () &&
         p.y >= y () &&
         p.y < y () + h ();
}