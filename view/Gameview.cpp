
#include "../controller/Gamesessioncontroller.hpp"
#include "Text.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <Fl/Fl_JPEG_Image.H>
#include <Fl/Fl_Image.H>
#include <fstream>
#include <ctime>

const int windowWidth = 500;
const int windowHeight = 550;
const double refreshPerSecond = 60;


/*--------------------------------------------------

GameSessionController class.

One instance of the canvas class is made by the
MainWindow class.

The fltk system via MainWindow calls:

draw 60 times a second
mouseMove whenever the mouse is moved
mouseClick whenever the mouse is clicked
keyPressed whenever a key is pressed

Any drawing code should be called ONLY in draw
or methods called by draw. If you try to draw
elsewhere it will probably crash.
--------------------------------------------------*/


/*--------------------------------------------------

MainWindow class.

Do not edit!!!!

--------------------------------------------------*/
extern Fl_Wizard *G_wiz=(Fl_Wizard *)0;
extern bool res = false;
extern int next_compt = 0;
extern bool quit = false;



class MainWindow : public Fl_Window {
  GameSessionController &game_session_controller = GameSessionController::getInstance ();
  Text score, remaining_moves;
  Fl_JPEG_Image* img;
 public:
  MainWindow () : Fl_Window (500, 500, windowWidth, windowHeight, "Candy Crush"),
                  score ("score : ", "0", Point{100, 500}), 
                  remaining_moves ("remaining moves : ", "0", Point{260, 500})
  {
    
    Fl::add_timeout (1.0 / refreshPerSecond, Timer_CB, this);
    resizable (this);
    game_session_controller.initiate ();
  }
  void draw () override
  {
    Fl_Window::draw ();
    game_session_controller.draw ();
    score.setSecondString (to_string (game_session_controller.getScore ()));
    remaining_moves.setSecondString (to_string (game_session_controller.getNumMoves ()));
    score.draw ();
    remaining_moves.draw ();
  }

  int handle (int event) override
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

  static void Timer_CB (void *userdata)
  {
    auto *o = (MainWindow *) userdata;
    o->redraw ();
    Fl::repeat_timeout (1.0 / refreshPerSecond, Timer_CB, userdata);
  }
};


class ModalWindow : public Fl_Window {
  Text name1, name2, mainWin, selectlvl, highScore;
  Fl_JPEG_Image* img;
  public:
    ModalWindow() : 
    Fl_Window(500, 500, windowWidth, windowHeight, "Candy Crush"),
    name1("Ben-David Malyane", "", Point{255, 200}), name2("Dave Pikop Pokam ", "", Point{252, 230}), 
    mainWin("Main Menu", "", Point{250, 100}), selectlvl("Select Level", "", Point{250, 100}), 
    highScore("High Score : ", "0", Point{255, 400}){
      G_wiz = new Fl_Wizard(0,0,windowWidth,windowHeight);
      time_t start = time(0);
      // Wizard: page 1
    {
        Fl_Group *g = new Fl_Group(0,0,windowWidth,windowHeight);
        G_wiz->color(FL_BLUE);
        Fl_Button *start = new Fl_Button(290,480,100,25,"start @->"); start->callback(next_cb);
        g->end();
    }
    // Wizard: page 2
    {
        Fl_Group *g = new Fl_Group(0,0,windowWidth,windowHeight);
        Fl_Button *play = new Fl_Button(290,480,100,25,"play @->"); play->callback(done_cb);
        Fl_Button *level_1 = new Fl_Button(200, 200,100,25,"level1"); level_1->callback(done_cb);
        Fl_Button *level_2 = new Fl_Button(200, 250,100,25,"level2"); level_2->callback(next_cb);
        Fl_Button *level_3 = new Fl_Button(200, 300,100,25,"level3"); level_3->callback(next_cb);
        
        g->end();
    }
    
    }

//    static void back_cb(Fl_Widget*,void*) { G_wiz->prev(); }
    static void next_cb(Fl_Widget*,void*)
    {
      G_wiz->next();
      G_wiz->color(FL_BLUE);
      next_compt++;
      if (next_compt == 2)
        res = true;
      next_compt;
    }
    static void done_cb(Fl_Widget*,void*)
    {
      quit = true;
      MainWindow *window = new MainWindow();
      window->show();
      window->end();
    }

    void draw() override
    {
      Fl_Window::draw(); 
      if (quit) Fl_Window::hide();

      if (next_compt == 0)
      {
        mainWin.setFontSize(50);
        mainWin.draw();
        name1.draw();
        name2.draw();
        ifstream sv_score;
        int hightscore;
        sv_score.open (SV_HIGHSCORE_FILE);
        sv_score >> hightscore;
        sv_score.close ();
        highScore.setSecondString(to_string(hightscore));
        highScore.draw();
        //highScoreNbr.draw();
      }
      if (next_compt == 1)
      {
        selectlvl.setFontSize(50);
        selectlvl.draw();
      }
    }

};


int main(int argc, char *argv[]) {

  ModalWindow win;
  win.show(argc, argv);
  win.end();
  return Fl::run();
}