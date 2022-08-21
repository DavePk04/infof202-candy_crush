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
void Cell::drawWithoutAnimate ()
{
  square->redraw ();
}

class Animation {
 public:
  enum AnimationType { spin, bounce, spinAndBounce };
 private:
  const int animationTime = 60;
  const int bounceHeight = 200;
  Cell *c;
  AnimationType animationType;
  int anim_time = 0;
  Point currentTranslation ();
 public:
  Animation (Cell *cellToAnimate, AnimationType animationType)
      : c{cellToAnimate}, animationType{animationType}
  {}
  void draw ();
  bool isComplete ();
};

void Animation::draw ()
{
  ++anim_time;
  Translation t3{currentTranslation ()};
  c->drawWithoutAnimate ();
}

Point Animation::currentTranslation ()
{
  if (animationType == bounce || animationType == spinAndBounce)
    return {0, static_cast<int>(-1 * bounceHeight * sin (3.1415 * anim_time / animationTime))};
  else
    return {0, 0};
}

bool Animation::isComplete ()
{
  return anim_time > 60;
}

void Cell::draw ()
{
  if (animation && animation->isComplete ())
    {
      delete animation;
      animation = nullptr;
    }
  if (animation)
    animation->draw ();
  else
    drawWithoutAnimate ();

}

void Cell::mouseClick (Point mouseLoc)
{
  if ((square->contains (mouseLoc)))
    {
      selected = true;
      if (!animation) animation = new Animation (this, Animation::bounce);
    }
}