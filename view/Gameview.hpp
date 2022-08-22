#include "Gamesessionview.hpp"
#include <FL/Fl_Button.H>
#include <FL/Fl_Wizard.H>
#include <FL/Fl_Window.H>
#include <fstream>
#include <ctime>

class Gameview : public Fl_Window {
  Text name1, name2, selectlvl, highScore, candycrush;
 public:
  Gameview ();
  static void back_cb (Fl_Widget *, void *);
  static void next_cb (Fl_Widget *, void *);
  static void play_cb (Fl_Widget *, void *);
  static void erase_cb (Fl_Widget *, void *);
  static void lvl1_cb (Fl_Widget *, void *);
  static void lvl2_cb (Fl_Widget *, void *);
  static void lvl3_cb (Fl_Widget *, void *);
  void draw () override;
  static void Timer_CB (void *userdata);
};