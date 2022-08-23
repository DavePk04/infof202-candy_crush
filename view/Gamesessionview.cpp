#include "Gamesessionview.hpp"

#include <FL/Fl_Window.H>
#include <Fl/fl_ask.H>

GameSessionView::GameSessionView (int idx) : Fl_Window (500, 500, WINDOWWIDTH, WINDOWHEIGHT, "Candy Crush"),
                                             score ("score : ", "0", Point{100, 560}),
                                             remaining_moves ("remaining moves : ", "0", Point{100,
                                                                                               520}), levelidx (idx),
                                             parent (parent)
{
  Fl::add_timeout (1.0 / REFRESHPERSECOND, Timer_CB, this);
  resizable (this);
  game_session_controller.initiate (levelidx);
}

/**
 * method called 60 times per second to display and update cells, score, remainning moves and aims
 * and handle the end of game
 */
void GameSessionView::draw ()
{
  Fl_Window::draw ();
  game_session_controller.draw ();
  score.setSecondString (to_string (game_session_controller.getScore ()));
  remaining_moves.setSecondString (to_string (game_session_controller.getNumMoves ()));
  score.draw ();
  remaining_moves.draw ();

  blue.setSecondString (to_string (game_session_controller.objectives ()->at (0)));
  red.setSecondString (to_string (game_session_controller.objectives ()->at (1)));
  green.setSecondString (to_string (game_session_controller.objectives ()->at (2)));
  orange.setSecondString (to_string (game_session_controller.objectives ()->at (3)));
  yellow.setSecondString (to_string (game_session_controller.objectives ()->at (4)));
  magenta.setSecondString (to_string (game_session_controller.objectives ()->at (5)));
  magenta.setSecondString (to_string (game_session_controller.objectives ()->at (6)));
  ice.setSecondString (to_string (game_session_controller.objectives ()->at (7)));

  blue.draw ();
  red.draw ();
  green.draw ();
  orange.draw ();
  yellow.draw ();
  magenta.draw ();
  magenta.draw ();
  ice.draw ();

  if (game_session_controller.endgame () and game_session_controller.win ())
    {
      if (levelidx > -1 and levelidx < 2)
        {
          game_session_controller.reset ();
          Fl::wait (10);
          game_session_controller.newLevelinit (++levelidx);

          auto res = fl_choice ("Next : Level %i, Continuer ?", "Yes, let go !", "No, exit", 0, levelidx + 1);
          if (res == 1) exit (0);
        }
      else if (levelidx == -1)
        {

          if (game_session_controller.saveScore ())
            {
              switch (fl_choice ("New HighScore %i", "", "OK", 0, game_session_controller.getScore ()))
                {
                  case 1: exit (0);
                }
            }
          else exit (0);

        }
      else exit (0);
    }
  else if (game_session_controller.endgame () and !game_session_controller.win ())
    {
      auto res = fl_choice ("Level %i : Perdu ! Vous n'avez pas atteint les objectifs, Recommenecr ?", "Oui", "No", 0, levelidx);
      if (res == 1) exit (0);
      else
        {
          game_session_controller.reset ();
          Fl::wait (10);
          game_session_controller.newLevelinit (levelidx);
        }
    }
}

/**
 * method called 60 times per second to control events on gamesessionview
 */
int GameSessionView::handle (int event)
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

      default: game_session_controller.saveScore ();
      return 0;

    }
}

/**
 * this method is called to fixe a time to refresh this window
*/
void GameSessionView::Timer_CB (void *userdata)
{
  auto *o = (GameSessionView *) userdata;
  o->redraw ();
  Fl::repeat_timeout (1.0 / REFRESHPERSECOND, Timer_CB, userdata);
}
