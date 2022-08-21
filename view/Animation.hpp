//
// Created by bdmr on 20/08/22.
//

#ifndef _ANIMATION_HPP_
#define _ANIMATION_HPP_

#include "../model/Point.hpp"
#include <cmath>

struct Translation {
  Translation (Point p)
  {
    fl_push_matrix ();
    fl_translate (p.x, p.y);
  }
  ~Translation ()
  {
    fl_pop_matrix ();
  }
};

#endif //_ANIMATION_HPP_
