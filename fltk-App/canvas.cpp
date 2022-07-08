#include "canvas.hpp"

Canvas::Canvas() {
    for (int i = 0; i < ROW; i++)
    {   
        board[i] = new int[ROW];
        for (int j = 0; j <= COL; j++)
        {
            board[i][j] = rand()%TOTALCOLOR + 1;  //Generate number between 1 to 6
        } 
    }  

    for (int x = 0; x<ROW; x++) {
        cells.push_back({});
        for (int y = 0; y<COL; y++){
            switch (board[x][y])
            {
            case COLOR1:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_RED, FL_BLACK});
                break;
            case COLOR2:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_YELLOW, FL_BLACK});
                break;
            case COLOR3:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_GREEN, FL_BLACK});
                break;
            case COLOR4:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_BLUE, FL_BLACK});
                break;
            case COLOR5:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_CYAN, FL_BLACK});
                break;
            case COLOR6:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_MAGENTA, FL_BLACK});
                break;
            }
        }
    }

}


void Canvas::draw() {
  for (auto &v: cells)
    for (auto &c: v)
      c.draw();
}

void Canvas::mouseMove(Point mouseLoc) {
  for (auto &v: cells)
    for (auto &c: v)
      c.mouseMove(mouseLoc);
}

void Canvas::mouseClick(Point mouseLoc) {
  for (auto &v: cells)
    for (auto &c: v)
      for (auto &c: v) c.mouseClick(mouseLoc);
}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'q':
      exit(0);
  }
}