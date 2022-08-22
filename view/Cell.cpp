#include "Cell.hpp"
#include <mutex>

Cell::Cell (Point center, int w, int h, Fl_Color color) :
    center{center}, w{w}, h{h}, color{color}
{
  initialize ();
}

void Cell::initialize ()
{
  square = new Square (FL_UP_BOX, center.x, center.y, w, h, "", color);
  square->color (color);
}

Fl_Color Cell::get_color () const
{
  return color;
}

void Cell::set_color (Fl_Color new_color)
{
  color = new_color;
}

void Cell::mouseMove (Point mouseLoc)
{
  if (square->contains (mouseLoc))
    {
      square->color (FL_WHITE);
    }
  else
    {
      square->color (color);
    }
}

bool Cell::is_selected () const
{
  return selected;
}
void Cell::unselect ()
{
  selected = false;
}

Point Cell::get_center () const
{
  return center;
}

void Cell::change (Fl_Color color_)
{
  set_color (color_);
  square->color (color_);
}

void Cell::draw ()
{
  square->redraw ();
}

void Cell::mouseClick (Point mouseLoc)
{
  if ((square->contains (mouseLoc)))
    {
      selected = true;
    }
}