#include "canvas.hpp"
#include <unistd.h>
#include <algorithm>

Canvas::Canvas() {
    board = bd.getBoard();
    for (int x = 0; x<GRID_DIMENSION; x++) {
        cells.push_back({});
        for (int y = 0; y<GRID_DIMENSION; y++){
            switch (board[x][y])
            {
            case BLUE:
                cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_BLUE});
                break;
            case RED:
                cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_RED});
                break;
            case GREEN:
                cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_GREEN});
                break;
            case YELLOW:
                cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_YELLOW});
                break;
            case CYAN:
                cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_CYAN});
                break;
            case MAGENTA:
                cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_MAGENTA});
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
        gamesession(&c);

    }
}

void Canvas::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'q':
      exit(0);
  }
}

void Canvas::normalise(){
    for (int x = 0; x < GRID_DIMENSION; x++)
    {
      for (int y = 0; y < GRID_DIMENSION; y++)
        {
            Cell c = cells[x][y];
            switch (board[x][y])
            {
            case BLUE:
                cells[x][y].change(FL_BLUE);
                c.reposition(c.get_center());
                break;
            case RED:
                cells[x][y].change(FL_RED);
                c.reposition(c.get_center());
                break;
            case GREEN:
                cells[x][y].change(FL_GREEN);
                c.reposition(c.get_center());
                break;
            case YELLOW:
                cells[x][y].change(FL_YELLOW);
                c.reposition(c.get_center());
                break;
            case CYAN:
                cells[x][y].change(FL_CYAN);
                c.reposition(c.get_center());
                break;
            case MAGENTA:
                cells[x][y].change(FL_MAGENTA);
                c.reposition(c.get_center());
                break;
            }
        }
    }
}

void Canvas::gamesession(Cell *c){
    if (c->is_selected()){
      if (find (selected.begin (), selected.end (), c) == selected.end ())
        selected.push_back (c);
      c->unselect ();
    }

    if (selected.size() == 2)
    {
        Point p1 = Point{(selected[0]->get_center().x-25)/50, (selected[0]->get_center().y-25)/50};
        Point p2 = Point{(selected[1]->get_center().x-25)/50, (selected[1]->get_center().y-25)/50};
        p1 = p1.reverse();
        p2 = p2.reverse();
        cout << board[p1.x][p2.y] << endl;
        if (bd.swaps(p1, p2))
        {
            normalise();
        }
        selected.clear();
    }
}

/*
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

    if (selected.size() >= 1)
    {
        int x = (selected[0]->get_center().x-25)/50;
        int y = 0;
        Fl_Color color = generateColor();
        c->change(color);
        swim(c);
        selected.clear();
    }
}
*/