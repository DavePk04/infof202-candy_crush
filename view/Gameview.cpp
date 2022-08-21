#include "Gamesessionview.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Window.H>
#include <fstream>
#include <ctime>


/*--------------------------------------------------

GameSessionController class.

One instance of the canvas class is made by the
GameSessionViewWindow class.

The fltk system via GameSessionViewWindow calls:

draw 60 times a second
mouseMove whenever the mouse is moved
mouseClick whenever the mouse is clicked
keyPressed whenever a key is pressed

Any drawing code should be called ONLY in draw
or methods called by draw. If you try to draw
elsewhere it will probably crash.
--------------------------------------------------*/


/*--------------------------------------------------

GameSessionViewWindow class.

Do not edit!!!!

--------------------------------------------------*/
Fl_Wizard *G_wiz = (Fl_Wizard *) 0;
int next_compt = 0;
bool quit = false;
bool res = true;

class GameviewWindow : public Fl_Window {
  Text name1, name2, selectlvl, highScore, candycrush;

 public:
  GameviewWindow () :
      Fl_Window (500, 500, WINDOWWIDTH, WINDOWHEIGHT, "Candy Crush"),
      name1("Ben-David Malyane", "", Point{255, 200}), name2("Dave Pikop Pokam ", "", Point{252, 230}),
      candycrush("CandyCrush", "", Point{250, 100}), selectlvl("Select Level", "", Point{250, 100}),
      highScore("High Score : ", "0", Point{255, 400})
      {
      G_wiz = new Fl_Wizard(0,0,WINDOWWIDTH,WINDOWHEIGHT);
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
    auto *window = new GameSessionViewWindow ();
    window->show ();
    window->end ();
  }

  static void lvl1_cb (Fl_Widget *, void *)
  {
    quit = true;
    auto *window = new GameSessionViewWindow (0);
    window->show ();
    window->end ();
  }

  static void lvl2_cb (Fl_Widget *, void *)
  {
    quit = true;
    auto *window = new GameSessionViewWindow (1);
    window->show ();
    window->end ();
  }

  static void lvl3_cb (Fl_Widget *, void *)
  {
    quit = true;
    auto *window = new GameSessionViewWindow (2);
    window->show ();
    window->end ();
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
        int hightscore;
        sv_score.open (SV_HIGHSCORE_FILE);
        sv_score >> hightscore;
        sv_score.close ();
        highScore.setSecondString(to_string(hightscore));
        highScore.draw();
      }

    else if (next_compt == 2)
      {
        selectlvl.setFontSize(50);
        selectlvl.draw();
      }

  }

};

int main (int argc, char *argv[])
{
  GameviewWindow win;
  win.size (WINDOWWIDTH, WINDOWHEIGHT);
  win.position (750,250);
  win.show (argc, argv);
  win.end ();

  return Fl::run ();
}