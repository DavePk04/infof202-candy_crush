#include "Gamesessionview.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Window.H>
#include <fstream>
#include <ctime>


//Setting the page wizard widget
Fl_Wizard *G_wiz = (Fl_Wizard *) 0;
int next_compt = 0;
bool quit = false;
bool reset = false;
bool res = true;

class GameviewWindow : public Fl_Window {
  Text name1, name2, selectlvl, highScore, candycrush;

 public:
  GameviewWindow () :
      Fl_Window (500, 500, WINDOWWIDTH, WINDOWHEIGHT, "Candy Crush"),
      name1 ("Ben-David Malyane", "", Point{255, 200}), name2 ("Dave Pikop Pokam ", "", Point{252, 230}),
      candycrush ("CandyCrush", "", Point{250, 100}), selectlvl ("Select Level", "", Point{250, 100}),
      highScore ("High Score : ", "0", Point{255, 400})
  {
    Fl::add_timeout (1.0 / REFRESHPERSECOND, Timer_CB, this);
    G_wiz = new Fl_Wizard (0, 0, WINDOWWIDTH, WINDOWHEIGHT);
    time_t start = time (0);
    // Wizard: page 1
    {
      Fl_Group *g = new Fl_Group (0, 0, WINDOWWIDTH, WINDOWHEIGHT);
      Fl_Button *startbtn = new Fl_Button (290, 480, 100, 25, "start @->");
      startbtn->callback (next_cb);
      g->end ();
    }

    // Wizard: page 2
    {
      Fl_Group *g = new Fl_Group (0, 0, WINDOWWIDTH, WINDOWHEIGHT);
      Fl_Button *play = new Fl_Button (200, 200, 100, 25, "play @->");
      play->callback (play_cb);
      Fl_Button *resethightscore = new Fl_Button (200, 450, 100, 25, "reset");
      resethightscore->callback (erase_cb);
      Fl_Button *levels = new Fl_Button (200, 300, 100, 25, "levels");
      levels->callback (next_cb);
      g->end ();
    }

    // Wizard: page 3
    {
      Fl_Group *g = new Fl_Group (0, 0, WINDOWWIDTH, WINDOWHEIGHT);
      Fl_Button *level_1 = new Fl_Button (200, 150, 100, 25, "level1");
      level_1->callback (lvl1_cb);
      Fl_Button *level_2 = new Fl_Button (200, 200, 100, 25, "level2");
      level_2->callback (lvl2_cb);
      Fl_Button *level_3 = new Fl_Button (200, 250, 100, 25, "level3");
      level_3->callback (lvl3_cb);
      g->end ();
      //      if (anim_time(0) - start > 1 ) next_cb ();
    }

  }

//    static void back_cb(Fl_Widget*,void*) { G_wiz->prev(); }
  static void next_cb (Fl_Widget *, void *)
  {
    G_wiz->next ();
    next_compt++;
    if (next_compt == 2)
      res = true;
  }
  static void play_cb (Fl_Widget *, void *)
  {
    quit = true;
    auto *game_session_window = new GameSessionViewWindow ();
    game_session_window->size_range (WINDOWWIDTH, WINDOWHEIGHT, WINDOWWIDTH, WINDOWHEIGHT);
    game_session_window->position (750, 250);
    game_session_window->show ();
    game_session_window->end ();
  }

  static void erase_cb (Fl_Widget *, void *)
  {
    reset = true;
    ofstream sv_newscore;
    sv_newscore.open (SV_HIGHSCORE_FILE);
    sv_newscore << 0;
    sv_newscore.close ();
  }

  static void lvl1_cb (Fl_Widget *, void *)
  {
    quit = true;
    auto *game_session_window = new GameSessionViewWindow (0);
    game_session_window->size_range (WINDOWWIDTH, WINDOWHEIGHT, WINDOWWIDTH, WINDOWHEIGHT);
    game_session_window->position (750, 250);
    game_session_window->show ();
    game_session_window->end ();
  }

  static void lvl2_cb (Fl_Widget *, void *)
  {
    quit = true;
    auto *game_session_window = new GameSessionViewWindow (1);
    game_session_window->size_range (WINDOWWIDTH, WINDOWHEIGHT, WINDOWWIDTH, WINDOWHEIGHT);
    game_session_window->position (750, 250);
    game_session_window->show ();
    game_session_window->end ();
  }

  static void lvl3_cb (Fl_Widget *, void *)
  {
    quit = true;
    auto *game_session_window = new GameSessionViewWindow (2);
    game_session_window->size_range (WINDOWWIDTH, WINDOWHEIGHT, WINDOWWIDTH, WINDOWHEIGHT);
    game_session_window->position (750, 250);
    game_session_window->show ();
    game_session_window->end ();
  }

  void draw () override
  {
    Fl_Window::draw ();
    if (quit) Fl_Window::hide ();

    if (next_compt == 0)
      {
        candycrush.setFontSize (50);
        candycrush.draw ();
        name1.draw ();
        name2.draw ();
      }

    else if (next_compt == 1)
      {
        candycrush.setFontSize (50);
        candycrush.draw ();

        ifstream sv_score;
        int hightscore = 0;
        sv_score.open (SV_HIGHSCORE_FILE);
        sv_score >> hightscore;
        sv_score.close ();
        highScore.setSecondString (to_string (hightscore));
//        if (reset)  highScore.setSecondString(to_string(0));
        highScore.draw ();
      }

    else if (next_compt == 2)
      {
        selectlvl.setFontSize (50);
        selectlvl.draw ();
      }

  }

  static void Timer_CB (void *userdata);
};

int main (int argc, char *argv[])
{
  GameviewWindow win;
  win.size (WINDOWWIDTH, WINDOWHEIGHT);
  win.position (750, 250);
  win.show (argc, argv);
  win.end ();

  return Fl::run ();
}

void GameviewWindow::Timer_CB (void *userdata)
{
  auto *o = (GameSessionViewWindow *) userdata;
  o->redraw ();
  Fl::repeat_timeout (1.0 / REFRESHPERSECOND, Timer_CB, userdata);
}