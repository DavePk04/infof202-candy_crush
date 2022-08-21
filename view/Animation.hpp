//
// Created by bdmr on 20/08/22.
//

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include "../model/Point.hpp"
#include <math.h>

struct Translation {
  Translation(Point p) {
    fl_push_matrix();
    fl_translate(p.x, p.y);
  }
  ~Translation() {
    fl_pop_matrix();
  }
};

/*--------------------------------------------------

Rotation Class
--------------------------------------------------*/

struct Rotation {
  Rotation(Point center, double angle) {
    fl_push_matrix();
    fl_translate(center.x, center.y);
    fl_rotate(angle);
    fl_translate(-1*center.x, -1*center.y);
  }
  ~Rotation() {
    fl_pop_matrix();
  }
};

#endif //_ANIMATION_HPP_
