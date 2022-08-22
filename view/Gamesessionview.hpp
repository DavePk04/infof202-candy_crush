//
// Created by bdmr on 21/08/22.
//

#ifndef _GAMESESSIONVIEW_HPP_
#define _GAMESESSIONVIEW_HPP_

#include "../controller/Gamesessioncontroller.hpp"
#include "Text.hpp"

class GameSessionView : public Fl_Window {
  GameSessionController &game_session_controller = GameSessionController::getInstance ();
  Text score, remaining_moves;
  Text blue = Text ("b : ", "0", Point{40, 505}, FL_BLUE);
  Text red = Text ("r : ", "0", Point{105, 505}, FL_RED);
  Text green = Text ("g : ", "0", Point{165, 492}, FL_GREEN);
  Text orange = Text ("o : ", "0", Point{225, 492}, 0xffb34700);
  Text yellow = Text ("y : ", "0", Point{285, 492}, FL_YELLOW);
  Text magenta = Text ("m : ", "0", Point{345, 480}, FL_MAGENTA);
  Text ice = Text ("i : ", "0", Point{420, 491});
  Fl_Window *parent = nullptr;
  int levelidx;
 public:
  explicit GameSessionView (int idx = -1);
  void draw () override;
  int handle (int event) override;
  static void Timer_CB (void *userdata);
};

#endif //_GAMESESSIONVIEW_HPP_
