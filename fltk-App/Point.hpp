#ifndef __POINT_H__
#define __POINT_H__

/* Point Structure
*
* Represents an exact point on a Board
* 
*/

struct Point {
	int x, y;

    Point formatForWall() { return Point{(x*2)-1,(y*2)-1}; }
    Point formatForBoard() { return Point{(x*2)-2,(y*2)-2}; }
    Point formatForReality() { return Point{(x+2)/2,(y+2)/2}; }
    Point reverse() { return Point{y,x}; }

    Point operator+(const Point &p) const { return Point{x+p.x, y+p.y}; }
    Point operator*(const int &i)   const { return Point{x*i, y*i}; }
    Point operator*(const Point &p) const { return Point{x*p.x, y*p.y}; }
    bool operator==(const Point &p) const { return (x==p.x and y==p.y); }
    int operator[](int index) {
        if (index == 0)  return x;
        if (index == 1) return y;
        //TODO: error
        return -1;
    }
};

#endif // __POINT_H__