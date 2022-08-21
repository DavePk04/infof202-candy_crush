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
  //Constructor
  Text (string s1, string s2, Point center, int fontSize = 20, Fl_Color color = FL_BLACK) :
      s1{s1}, s2{s2}, center{center}, fontSize{fontSize}, color{color}{
    s = s1+s2;
  }

  //Draw
  void draw ();

  //Setters and getters
  string getString ()
  {
    return s1+s2;
  }
  void setFirstString (const string &newString)
  {
    s1 = newString;
    s = s1+s2;
  }
  void setSecondString (const string &newString)
  {
    s2 = newString;
    s = s1+s2;
  }

  int getFontSize ()
  {
    return fontSize;
  }
  void setFontSize (int newFontSize)
  {
    fontSize = newFontSize;
  }
  Point getCenter ()
  {
    return center;
  }
  void setCenter (Point newCenter)
  {
    center = newCenter;
  }
};