#include "canvas.hpp"
#include <unistd.h>
#include <algorithm>

Canvas::Canvas() {
    for (int i = 0; i < GRID_DIMENSION; i++)
    {   
        board[i] = new int[GRID_DIMENSION];
        for (int j = 0; j <= GRID_DIMENSION; j++)
        {
            board[i][j] = rand()%TOTALCOLOR + 1;  //Generate number between 1 to 6
        } 
    }  

    for (int x = 0; x<GRID_DIMENSION; x++) {
        cells.push_back({});
        for (int y = 0; y<GRID_DIMENSION; y++){
            switch (board[x][y])
            {
            case BLUE:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_BLUE});
                break;
            case RED:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_RED});
                break;
            case GREEN:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_GREEN});
                break;
            case YELLOW:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_YELLOW});
                break;
            case CYAN:
                cells[x].push_back({{50*x+25, 50*y+25}, 40, 40, FL_CYAN});
                break;
            case MAGENTA:
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
        delete_(&c);
    }
}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'q':
      exit(0);
  }
}

Fl_Color Canvas::generateColor(){
    Fl_Color colors[6] = {FL_RED, FL_YELLOW, FL_GREEN, FL_BLUE, FL_CYAN, FL_MAGENTA};
    int randomColor = rand() % 6;
    cout << randomColor << endl;
    return colors[randomColor];
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
        // cout << "i1,j1 = (" << i1 << "," << j1 << ")" << endl;
        // cout << "i2,j2 = (" << i2 << "," << j2 << ")" << endl;
        // swap_(cells[i1][j1], cells[i2][j2]);
        swap(c1, c2);
        std::swap(cells[i1][j1], cells[i2][j2]);
        selected_cells.clear();

    }
}


void Canvas::swap(Cell *c1, Cell *c2){
    Point save_center{c1->get_center().x, c1->get_center().y};
    c1->reposition(c2->get_center());
    c1->set_center(c2->get_center());
    c2->reposition(save_center);
    c2->set_center(save_center);
}

void Canvas::swap_(Cell &c1, Cell &c2){
    Point save_center{c1.get_center().x, c1.get_center().y};
    c1.reposition(c2.get_center());
    c1.set_center(c2.get_center());
    c2.reposition(save_center);
    c2.set_center(save_center);
}

void Canvas::swim(Cell *c){
    int x = (selected[0]->get_center().x-25)/50;
    int y = (selected[0]->get_center().y-25)/50;
    int i = y-1;
    int j = 0;
    while (i >= 0 && y >= 0)
    {
        swap_(cells[x][y], cells[x][i]);
        std::swap(cells[x][y], cells[x][i]);
        i--;
        y--;
        j++;
    }
}

void Canvas::delete_(Cell *c){
    if (c->is_selected()){
      if (find (selected.begin (), selected.end (), c) == selected.end ())
        selected.push_back (c);
      c->unselect ();
    }

    if (selected.size() == 1)
    {
        int x = (selected[0]->get_center().x-25)/50;
        int y = 0;
        Fl_Color color = generateColor();
        c->destroy(color);
        swim(c);
        selected.clear();
    }
}