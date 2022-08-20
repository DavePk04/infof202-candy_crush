#include "gamesessioncontroller.hpp"
#include <algorithm>
#include <fstream>


void GameSessionController::initiate() {
    board = bd.getBoard();
    for (int x = 0; x<GRID_DIMENSION; x++) {
        cells.emplace_back();
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
            case DARK_YL:
              cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_DARK_YELLOW});
              break;
            case BLACK:
              cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_BLACK});
              break;
            case GRAY:
              cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_DARK2});
            break;
            case DGRAY:
              cells[x].push_back({{50*y+25, 50*x+25}, 40, 40, FL_DARK3});
            break;
            }
        }
    }
  chrono_possiblemove = 0;
}


void GameSessionController::draw() {
  for (auto &v: cells)
    for (auto &c: v)
      c.draw();

  chrono_possiblemove++;

  if (chrono_possiblemove == 900)
    {
      possible_move();
      chrono_possiblemove = 0;
    }
  else if (chrono_possiblemove > 900) chrono_possiblemove = 0;

}

void GameSessionController::mouseMove(Point mouseLoc) {
  for (auto &v: cells)
    for (auto &c: v)
      c.mouseMove(mouseLoc);
}

void GameSessionController::mouseClick(Point mouseLoc) {
  for (auto &v: cells)
    for (auto &c: v)
    {
        c.mouseClick(mouseLoc);
        selectCell (&c);

    }

  chrono_possiblemove = 0;
}

void GameSessionController::keyPressed(int keyCode) {
  switch (keyCode) {
    case 'q':
      exit(0);

    case 'm':
      possible_move_anim++;
      possible_move();
      break;

    case 'r':reinitialiseHightScore ();
      break;

    default: break;
  }
}

void GameSessionController::normalise(){
    drop_anim();
    for (int x = 0; x < GRID_DIMENSION; x++)
      {
        for (int y = 0; y < GRID_DIMENSION; y++)
          {
            Cell c = cells[x][y];
            switch (board[x][y])
              {
                case BLUE:
                  {
                    cells[x][y].change (FL_BLUE);
                    break;
                  }
                case RED:
                  {
                    cells[x][y].change (FL_RED);
                    break;
                  }
                case GREEN:
                  {
                    cells[x][y].change (FL_GREEN);
                    break;
                  }
                case YELLOW:
                  {
                    cells[x][y].change (FL_YELLOW);
                    break;
                  }
                case CYAN:
                  {
                    cells[x][y].change (FL_CYAN);
                    break;
                  }
                case MAGENTA:
                  {
                    cells[x][y].change (FL_MAGENTA);
                    break;
                  }
                case DARK_YL:
                  {
                    cells[x][y].change (FL_DARK_YELLOW);
                    break;
                  }
                case BLACK:
                  {
                    cells[x][y].change (FL_BLACK);
                    break;
                  }
                case GRAY :
                  {
                    cells[x][y].change (FL_DARK2);
                    break;
                  }
                case DGRAY :
                  {
                    cells[x][y].change (FL_DARK3);
                    break;
                  }
              }
          }
      }

  if (bd.getState() == GAME_OVER)
    {
      saveScore();
    }
  chrono_possiblemove = 0;

}

void GameSessionController::drop_anim() {
    vector<Point> tmp = bd.getMatchedCells();

    int anim = 0;
    //cout << "tmp > " << tmp.size() << endl;
     while (anim < 20)
     {
       for (auto& p : tmp)
           cells[p.x][p.y].change(FL_DARK_MAGENTA);
       anim++;
       Fl::wait();
     }

    bd.clearMatchedCells();
    
}

void GameSessionController::selectCell(Cell *c){
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

        if (bd.swaps(p1, p2))
        {
            normalise();
        }
        selected.clear();
    }
}
vector<Cell *> GameSessionController::getSelectedCell ()
{
  return selected;
}


std::unique_ptr<GameSessionController> GameSessionController::_instance = nullptr;

GameSessionController &GameSessionController::getInstance ()
{
  if (!_instance)
    _instance = std::make_unique<GameSessionController>();

  return *_instance;
}


void GameSessionController::possible_move(){
  chrono_possiblemove = 0;
  if (!bd.get_possibleswap().empty())
    {
      pair<Point, Point> possible_move;
      unsigned long s = bd.get_possibleswap().size();
      possible_move = bd.get_possibleswap()[random()%s];
      Point p1 = possible_move.first;
      Point p2 = possible_move.second;
      p1.x = p1.x-25/50;
      p1.y = p1.y-25/50;
      p2.x = p2.x-25/50;
      p2.y = p2.y-25/50;
      Fl_Color color1 =  cells[p1.x][p1.y].get_color();
      Fl_Color color2 =  cells[p2.x][p2.y].get_color();


      while (possible_move_anim < 45)
        {
          cells[p1.x][p1.y].change(FL_DARK_MAGENTA);
          cells[p2.x][p2.y].change(FL_DARK_MAGENTA);
          possible_move_anim++;
          Fl::wait();
        }
      cells[p1.x][p1.y].change(color1);
      cells[p2.x][p2.y].change(color2);

      possible_move_anim = 0;
    }
  else
    {
      bd.regen_color_grid();
      Fl::wait(15); //#TODO do an action here
      normalise();
    }
}


void GameSessionController::saveScore ()
{
  ifstream sv_score;
  ofstream sv_newscore;
  int hightscore;
  auto score = bd.getScore();
  sv_score.open (SV_HIGHSCORE_FILE);
  sv_score >> hightscore;
  sv_score.close();

  if (score > hightscore)
    {
      sv_newscore.open (SV_HIGHSCORE_FILE);
      sv_newscore << bd.getScore ();
      sv_newscore.close();
    }
}


void GameSessionController::reinitialiseHightScore ()
{
  ofstream sv_score;
  sv_score.open (SV_HIGHSCORE_FILE);
  sv_score.clear ();
  sv_score.close();
}

int GameSessionController::getScore(){
  return bd.getScore();
}

int GameSessionController::getNumMoves(){
  return bd.getNumMoves();
}