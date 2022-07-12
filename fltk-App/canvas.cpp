#include "canvas.hpp"
#include <unistd.h>
#include <algorithm>

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
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_RED});
                break;
            case COLOR2:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_YELLOW});
                break;
            case COLOR3:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_GREEN});
                break;
            case COLOR4:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_BLUE});
                break;
            case COLOR5:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_CYAN});
                break;
            case COLOR6:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_MAGENTA});
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
    {
        c.mouseClick(mouseLoc);
        check(&c);
    }
}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'q':
      exit(0);
  }
}


void Canvas::update ()
{
    Point save_center{selected_cells[0]->get_center().x, selected_cells[0]->get_center().y};
    selected_cells[0]->reposition(selected_cells[1]->get_center());
    selected_cells[0]->set_center(selected_cells[1]->get_center());
    selected_cells[1]->reposition(save_center);
    selected_cells[1]->set_center(save_center);
}

void Canvas::check (Cell * c)
{ 
    if (c->is_selected()){
      if (find (selected_cells.begin (), selected_cells.end (), c) == selected_cells.end ())
        selected_cells.push_back (c);
      c->unselect ();
    }
    if (selected_cells.size()==2)
    {
        Cell *c1 = selected_cells.at(0);
        Cell *c2 = selected_cells.at(1);
        Point p1 = selected_cells[0]->get_center();
        Point p2 = selected_cells[1]->get_center();
        int i1 = (p1.x-25)/50;
        int j1 = (p1.y-25)/50;
        int i2 = (p2.x-25)/50;
        int j2 = (p2.y-25)/50;
        
        update();
        std::swap(cells[i1][j1], cells[i2][j2]);
        selected_cells.clear();

    }
}