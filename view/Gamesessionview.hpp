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
  Text blue = Text("b : ", "0", Point{40, 505});
  Text red = Text("r : ", "0", Point{105, 505});
  Text green = Text("g : ", "0", Point{165, 492});
  Text yellow = Text("y : ", "0", Point{225, 492});
  Text cyan = Text("c : ", "0", Point{285, 492});
  Text magenta = Text("m : ", "0", Point{345, 480});
  Text ice = Text("i : ", "0", Point{420, 491});
  Fl_Window * parent = nullptr;
  int levelidx;
  bool firstinit = true;
 public:
  explicit GameSessionViewWindow (int idx = -1);
  void draw () override;
  int handle (int event) override;
  static void Timer_CB (void *userdata);
};

#endif //_GAMESESSIONVIEW_HPP_
