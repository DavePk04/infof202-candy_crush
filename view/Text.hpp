#include "../model/Point.hpp"
#include <string>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

using namespace std;

class Text {
  Point center;
  string s;
  string s1;
  string s2;
  int fontSize;
  Fl_Color color;
 public:
  Text (string s1, string s2, Point center, Fl_Color color = FL_BLACK, int fontSize = 20);
  void draw ();
  string getString ();
  void setFirstString (const string &newString);
  void setSecondString (const string &newString);
  int getFontSize ();
  void setFontSize (int newFontSize);
  Point getCenter ();
  void setCenter (Point newCenter);
};