//
// Created by bdmr on 21/08/22.
//

#include "Gamesessionview.hpp"

#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>



GameSessionViewWindow::GameSessionViewWindow (int idx) : Fl_Window (500, 500, WINDOWWIDTH, WINDOWHEIGHT, "Candy Crush"),
                                                         score ("score : ", "0", Point{100, 500}),
                                                         remaining_moves ("remaining moves : ", "0", Point{260, 500}), levelidx (idx)
  {
    Fl::add_timeout (1.0 / REFRESHPERSECOND, Timer_CB, this);
    resizable (this);
    game_session_controller.initiate (levelidx);
  }
  void GameSessionViewWindow::draw ()
  {
    Fl_Window::draw ();
    game_session_controller.draw ();
    score.draw ();
    remaining_moves.draw ();
    score.setSecondString (to_string (game_session_controller.getScore ()));
    remaining_moves.setSecondString (to_string (game_session_controller.getNumMoves ()));
    score.draw ();
    remaining_moves.draw ();
  }

  int GameSessionViewWindow::handle (int event)
  {
    switch (event)
      {
        case FL_MOVE: game_session_controller.mouseMove (Point{Fl::event_x (), Fl::event_y ()});
        return 1;
        case FL_PUSH: game_session_controller.mouseClick (Point{Fl::event_x (), Fl::event_y ()});
        return 1;
        case FL_KEYDOWN: game_session_controller.keyPressed (Fl::event_key ());
        return 1;
        case FL_DRAG: game_session_controller.mouseDrag (Point{Fl::event_x (), Fl::event_y ()});
        return 1;

        default: return 0;

      }
  }

  void GameSessionViewWindow::Timer_CB (void *userdata)
  {
    auto *o = (GameSessionViewWindow *) userdata;
    o->redraw ();
    Fl::repeat_timeout (1.0 / REFRESHPERSECOND, Timer_CB, userdata);
  }
