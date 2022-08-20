
#include "../controller/gamesessioncontroller.hpp"
#include "text.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Shared_Image.H>
#include <Fl/Fl_JPEG_Image.H>

const int windowWidth = 500;
const int windowHeight = 520;
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

class ModalWindow : public Fl_Window {
  Text text, name1, name2;
  Fl_JPEG_Image* img;
  public:
    ModalWindow() : 
    Fl_Window(500, 500, windowWidth, windowHeight, "Candy Crush"),
    name1("Ben-David Malyane ", Point{255, 200}), name2("Dave Pikop Pokam ", Point{252, 230}), text("Candy Crush", Point{250, 100}){
      G_wiz = new Fl_Wizard(0,0,500,520);
      // Wizard: page 1
    {
        Fl_Group *g = new Fl_Group(0,0,500,520);
        Fl_Button *next = new Fl_Button(290,480,100,25,"Next @->"); next->callback(next_cb);
        g->end();
    }
    // Wizard: page 2
    {
        Fl_Group *g = new Fl_Group(0,0,500,520);
        Fl_Button *next = new Fl_Button(290,480,100,25,"Next @->"); next->callback(next_cb);
        Fl_Button *back = new Fl_Button(180,480,100,25,"@<- Back"); back->callback(back_cb);
        Fl_Button *level_1 = new Fl_Button(200, 100,100,25,"level1"); level_1->callback(next_cb);
        Fl_Button *level_2 = new Fl_Button(200, 150,100,25,"level2"); level_2->callback(next_cb);
        Fl_Button *level_3 = new Fl_Button(200, 200,100,25,"level3"); level_3->callback(next_cb);
        g->end();
    }
    // Wizard: page 3
    {
        Fl_Group *g = new Fl_Group(0,0,500,520);
        Fl_Button *done = new Fl_Button(290,480,100,25,"Finish"); done->callback((Fl_Callback*)done_cb);   // ((Fl_Callback*)back_cb);
        Fl_Button *back = new Fl_Button(180,480,100,25,"@<- Back"); back->callback((Fl_Callback*)back_cb);
        g->end();
    }
    }

    static void back_cb(Fl_Widget*,void*) { G_wiz->prev(); }
    static void next_cb(Fl_Widget*,void*) { 
    G_wiz->next(); 
    next_compt++;
    if (next_compt == 2)
      res = true;
    next_compt;
    }
    static void done_cb(Fl_Widget*,void*) { exit(0); }
};


class MainWindow : public Fl_Window {
  GameSessionController &game_session_controller = GameSessionController::getInstance();
  Text score, scoreNbr, remaining_moves, remainingMovesNbr;
 public:
  MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Candy Crush"),
  score("score : ", Point{75, 490}), scoreNbr("0", Point{130, 503}), remaining_moves("remaining moves :", Point{250, 480}),
  remainingMovesNbr("0", Point{400, 505})
 {
    Fl::add_timeout(1.0/refreshPerSecond, Timer_CB, this);
    resizable(this);
    game_session_controller.initiate();
  }
  void draw() override {
    Fl_Window::draw();
    game_session_controller.draw();
    score.draw();
    remaining_moves.draw();
    scoreNbr.setString(to_string(game_session_controller.getScore()));
    scoreNbr.draw();
    remainingMovesNbr.setString(to_string(game_session_controller.getNumMoves()));
    remainingMovesNbr.draw();
  }

  int handle(int event) override
  {
    switch (event)
      {
        case FL_MOVE: game_session_controller.mouseMove (Point{Fl::event_x (), Fl::event_y ()});
        return 1;
        case FL_PUSH: game_session_controller.mouseClick (Point{Fl::event_x (), Fl::event_y ()});
        return 1;
        case FL_KEYDOWN: game_session_controller.keyPressed (Fl::event_key ());
        return 1;

        default: return 0;

      }
  }


  static void Timer_CB(void *userdata) {
    auto *o = (MainWindow*) userdata;
    o->redraw();
    Fl::repeat_timeout(1.0/refreshPerSecond, Timer_CB, userdata);
  }
};


/*--------------------------------------------------

main

Do not edit!!!!

--------------------------------------------------*/


int main(int argc, char *argv[]) {
  MainWindow window;
  window.show(argc, argv);
  window.end();
  ModalWindow win;
  win.show(argc, argv);
  win.end();
  return Fl::run();
}