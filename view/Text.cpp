#include "Text.hpp"
#include <string>
#include <FL/fl_draw.H>

using namespace std;

Text::Text (string s1, string s2, Point center, Fl_Color color, int fontSize) :
    s1{s1}, s2{s2}, center{center}, color{color}, fontSize{fontSize}
{
  s = s1 + s2;
}

string Text::getString ()
{
  return s1 + s2;
}

void Text::setFirstString (const string &newString)
{
  s1 = newString;
  s = s1 + s2;
}

void Text::setSecondString (const string &newString)
{
  s2 = newString;
  s = s1 + s2;
}

int Text::getFontSize ()
{
  return fontSize;
}

void Text::setFontSize (int newFontSize)
{
  fontSize = newFontSize;
}

Point Text::getCenter ()
{
  return center;
}

void Text::setCenter (Point newCenter)
{
  center = newCenter;
}

void Text::draw ()
{
  fl_color (color);
  fl_font (FL_HELVETICA, fontSize);
  int width, height;
  fl_measure (s.c_str (), width, height, false);
  fl_draw (s.c_str (), center.x - width / 2, center.y - fl_descent () + height / 2);
}
