
#include "../controller/gamesessioncontroller.hpp"

const int windowWidth = 500;
const int windowHeight = 500;
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

class MainWindow : public Fl_Window {
  GameSessionController &game_session_controller = GameSessionController::getInstance();

 public:
  MainWindow() : Fl_Window(500, 500, windowWidth, windowHeight, "Candy Crush") {
    Fl::add_timeout(1.0/refreshPerSecond, Timer_CB, this);
    resizable(this);
    game_session_controller.initiate();
  }
  void draw() override {
    Fl_Window::draw();
    game_session_controller.draw();
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
  srand(time(nullptr));
  MainWindow window;
  window.show(argc, argv);
  return Fl::run();
}