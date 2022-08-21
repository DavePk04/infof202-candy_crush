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

void Cell::draw ()
{
//  if (animation && animation->isComplete()) {
//      delete animation;
//      animation = nullptr;
//    }
//  if (animation)
//    animation->draw();
//  else
//    drawWithoutAnimate();

}

Fl_Color Cell::get_color () const
{
  return color;
}

void Cell::set_color (Fl_Color new_color)
{
  color = new_color;
}

void Cell::set_center (Point new_center)
{
  center.x = new_center.x;
  center.y = new_center.y;
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

void Cell::mouseClick (Point mouseLoc)
{
  if ((square->contains (mouseLoc)))
    {
      selected = true;
      //cout << '(' << square->get_position().x << ',' << square->get_position().y << ')' << endl;
    }
}

void Cell::reposition (Point p)
{
  int x = p.x;
  int y = p.y;
  //cout << "(" << x << "," << y << endl;
  square->position (x, y);
  square->redraw ();
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
  //mutex lock;
  //lock.lock();
  set_color (color_);
  square->color (color_);
  //lock.unlock();
}
void Cell::drawWithoutAnimate ()
{
  square->redraw();
}
