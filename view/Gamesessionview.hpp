//
// Created by bdmr on 21/08/22.
//

#ifndef _GAMESESSIONVIEW_HPP_
#define _GAMESESSIONVIEW_HPP_

#include "../controller/Gamesessioncontroller.hpp"
#include "Text.hpp"

class GameSessionViewWindow : public Fl_Window{
  GameSessionController &game_session_controller = GameSessionController::getInstance ();
  Text score, remaining_moves;

  int levelidx;
 public:
  explicit GameSessionViewWindow (int idx = -1);
  void draw () override;
  int handle (int event) override;
  static void Timer_CB (void *userdata);
};

#endif //_GAMESESSIONVIEW_HPP_
