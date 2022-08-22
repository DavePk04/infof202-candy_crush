#include "Gameview.hpp"

//Setting the page wizard widget
Fl_Wizard *G_wiz = (Fl_Wizard *) 0;
int next_compt = 0;
bool quit = false;
bool res = true;

Gameview::Gameview () :
    Fl_Window (500, 500, WINDOWWIDTH, WINDOWHEIGHT, "Candy Crush"),
    name1 ("Ben-David Malyane", "", Point{255, 200}), name2 ("Dave Pikop Pokam ", "", Point{252, 230}),
    candycrush ("CandyCrush", "", Point{250, 100}, FL_DARK_RED), selectlvl ("Select Level", "", Point{250,
                                                                                                      100}, FL_DARK_GREEN),
    highScore ("High Score : ", "0", Point{185, 465})
{
  Fl::add_timeout (1.0 / REFRESHPERSECOND, Timer_CB, this);
  G_wiz = new Fl_Wizard (0, 0, WINDOWWIDTH, WINDOWHEIGHT);
  time_t start = time (0);

  // Wizard: page 1
  {
    Fl_Group *g = new Fl_Group (0, 0, WINDOWWIDTH, WINDOWHEIGHT);
    Fl_Button *startbtn = new Fl_Button (290, 480, 100, 25, "start @>");
    startbtn->color (FL_GREEN);
    startbtn->callback (next_cb);
    g->end ();
  }

  // Wizard: page 2
  {
    Fl_Group *g = new Fl_Group (0, 0, WINDOWWIDTH, WINDOWHEIGHT);
    Fl_Button *play = new Fl_Button (170, 200, 150, 25, "partie rapide @>");
    play->color (FL_GREEN);
    play->callback (play_cb);
    Fl_Button *resethightscore = new Fl_Button (170, 400, 150, 25, "reset highscore");
    resethightscore->color (FL_RED);
    resethightscore->callback (erase_cb);
    Fl_Button *levels = new Fl_Button (170, 300, 150, 25, "levels");
    levels->color (0xfdbcb400);
    levels->callback (next_cb);
    g->end ();
  }

  // Wizard: page 3
  {
    Fl_Group *g = new Fl_Group (0, 0, WINDOWWIDTH, WINDOWHEIGHT);
    Fl_Button *level_1 = new Fl_Button (200, 200, 100, 25, "level1");
    level_1->callback (lvl1_cb);
    level_1->color (FL_WHITE);
    Fl_Button *level_2 = new Fl_Button (200, 250, 100, 25, "level2");
    level_2->callback (lvl2_cb);
    level_2->color (FL_GREEN);
    Fl_Button *level_3 = new Fl_Button (200, 300, 100, 25, "level3");
    level_3->callback (lvl3_cb);
    level_3->color (FL_CYAN);
    Fl_Button *back = new Fl_Button (200, 450, 100, 25, "@<- back");
    back->color (FL_RED);
    back->callback (back_cb);
    g->end ();
  }

}
/*------------------Callback Functions----------------------*/
void Gameview::back_cb (Fl_Widget *, void *)
{ G_wiz->prev (); }

void Gameview::next_cb (Fl_Widget *, void *)
{
  G_wiz->next ();
  next_compt++;
  if (next_compt == 2)
    res = true;
}

void Gameview::play_cb (Fl_Widget *, void *)
{
  quit = true;
  auto *game_session_window = new GameSessionView ();
  game_session_window->size_range (WINDOWWIDTH, WINDOWHEIGHT, WINDOWWIDTH, WINDOWHEIGHT);
  game_session_window->position (750, 250);
  game_session_window->show ();
  game_session_window->end ();
}

void Gameview::erase_cb (Fl_Widget *, void *)
{
  ofstream sv_newscore;
  sv_newscore.open (SV_HIGHSCORE_FILE);
  sv_newscore << 0;
  sv_newscore.close ();
}

void Gameview::lvl1_cb (Fl_Widget *, void *)
{
  quit = true;
  auto *game_session_window = new GameSessionView (0);
  game_session_window->size_range (WINDOWWIDTH, WINDOWHEIGHT, WINDOWWIDTH, WINDOWHEIGHT);
  game_session_window->position (750, 250);
  game_session_window->show ();
  game_session_window->end ();
}

void Gameview::lvl2_cb (Fl_Widget *, void *)
{
  quit = true;
  auto *game_session_window = new GameSessionView (1);
  game_session_window->size_range (WINDOWWIDTH, WINDOWHEIGHT, WINDOWWIDTH, WINDOWHEIGHT);
  game_session_window->position (750, 250);
  game_session_window->show ();
  game_session_window->end ();
}

void Gameview::lvl3_cb (Fl_Widget *, void *)
{
  quit = true;
  auto *game_session_window = new GameSessionView (2);
  game_session_window->size_range (WINDOWWIDTH, WINDOWHEIGHT, WINDOWWIDTH, WINDOWHEIGHT);
  game_session_window->position (750, 250);
  game_session_window->show ();
  game_session_window->end ();
}
/*----------------------------------Fin Callback functions----------------------------------------------------------*/


void Gameview::draw ()
{
  Fl_Window::draw ();
  if (quit) Fl_Window::hide (); //if a configuration choice is done Hide the gameview window

  if (next_compt == 0) //page 0
    {
      candycrush.setFontSize (50);
      candycrush.draw ();
      name1.draw ();
      name2.draw ();
    }

  else if (next_compt == 1) //page 1
    {
      candycrush.setFontSize (50);
      candycrush.draw ();

      ifstream sv_score;
      int highsc;
      sv_score.open (SV_HIGHSCORE_FILE);
      sv_score >> highsc;
      sv_score.close ();
      highScore.setSecondString (to_string (highsc));
      if (highsc == 0) highScore.setCenter ({240, 500});
      highScore.draw ();
    }

  else if (next_compt == 2) //page 2
    {
      selectlvl.setFontSize (50);
      selectlvl.draw ();
    }

}

void Gameview::Timer_CB (void *userdata)
{
  auto *o = (GameSessionView *) userdata;
  o->redraw ();
  Fl::repeat_timeout (1.0 / REFRESHPERSECOND, Timer_CB, userdata);
}

int main (int argc, char *argv[])
{
  Gameview win;
  win.size (WINDOWWIDTH, WINDOWHEIGHT);
  win.position (750, 250);
  win.show (argc, argv);
  win.end ();

  return Fl::run ();
}

