#include "Board.hpp"
#include <algorithm>
#include <unordered_set>
#include<set>
#include <fstream>

using namespace std;


vector<int> delete_ele (vector<int> vec, int num)
{
  // initializing a reverse iterator
  vector<int>::reverse_iterator itr1;

  for (itr1 = vec.rbegin (); itr1 < vec.rend (); itr1++)
    {

      if (*itr1 == num)
        {

//          printf ("élément à supprimer = %i \n", num);
          vec.erase ((itr1 + 1).base ());
        }
    }

  return vec;
}


int Board::GetColorAt (int row, int col)
{
  if (col < 0 || col >= GRID_DIMENSION
      || row < 0 || row >= GRID_DIMENSION)
    return -1;

  auto color = _board[row][col];

  return color;
}

void Board::gen_color_grid ()
{
  for (int i = 0; i < GRID_DIMENSION; i++)
    {
      std::vector<int> copy_color_vect (COLORS_VECT);

      if (i==0 or i == 8) copy_color_vect = delete_ele (copy_color_vect, 7);
      else copy_color_vect.push_back (7);

      _board[i] = new int[GRID_DIMENSION];
      for (int j = 0; j <= GRID_DIMENSION; j++)
        {
          if (j==0 or j == 8) copy_color_vect = delete_ele (copy_color_vect, 7);
          else if (i != 0 and i != 8) copy_color_vect.push_back (7);

          int left1 = GetColorAt (i, j - 1); //2
          int left2 = GetColorAt (i, j - 2);
          if (left2 != -1 && left1 == left2) // 3
            {
              copy_color_vect = delete_ele (copy_color_vect, left1);
            }

          if (left1 == 7 or left2 == 7)
            copy_color_vect = delete_ele (copy_color_vect, 7);

          int down1 = GetColorAt (i - 1, j); // 5
          int down2 = GetColorAt (i - 2, j);
          if (down2 != -1 && down1 == down2)
            {
              copy_color_vect = delete_ele (copy_color_vect, down1);
            }

          if (down1 == 7 or down2 == 7)
            copy_color_vect = delete_ele (copy_color_vect, 7);

          int color = copy_color_vect[random() % copy_color_vect.size ()];
          _board[i][j] = color;
        }
    }
}

void print_board (int **data)
{
  for (int x = 0; x < GRID_DIMENSION; x++)
    {
      for (int y = 0; y < GRID_DIMENSION; y++)
        {
          printf (" %d", data[x][y]);
        }
      printf ("\n");
    }

}

Board::Board ()
{
  _nummoves = std::numeric_limits<float>::infinity();
  game_state = RUNNING;
  gen_color_grid ();
  identifypossibleswap();
}


Board::Board (string level)
{
  ifstream levelfile;
  levelfile.open (level);
  if (levelfile.is_open ())
    {
      levelfile >> _nummoves;
      for (int i = 0; i < GRID_DIMENSION; i++)
        {
          _board[i] = new int[GRID_DIMENSION];
          for (int j = 0; j < GRID_DIMENSION; j++)
            levelfile >> _board[i][j];
        }
    }

  levelfile.close();

  game_state = RUNNING;
  identifypossibleswap();
}


int **Board::getBoard ()
{
  return _board;
}

bool Board::is_inBoard (Point pos)
{
  return (0 <= pos.x and pos.x < GRID_DIMENSION && 0 <= pos.y && pos.y < GRID_DIMENSION);
}

/**
 * This function select Matched cells by Colomn
 * @param row
 * @param col
 * @param color
 * @return
 */
vector<Point> Board::FindColumnMatchForCell (int row, int col, int color)
{
  vector<Point> result;
  for (int i = col + 1; i < GRID_DIMENSION; i++)
    {
      int nextColumnColor = GetColorAt (row, i);
      if (nextColumnColor != color)
        {
          break;
        }
      result.push_back ({row, i});
    }
  return result;
}

/**
 * This function select Matched cells by Row
 * @param row
 * @param col
 * @param color
 * @return
 */
vector<Point> Board::FindRowMatchForCell (int row, int col, int color)
{
  vector<Point> result;
  for (int i = row + 1; i < GRID_DIMENSION; i++)
    {
      int nextRowColor = GetColorAt (i, col);
      if (nextRowColor != color)
        {
          break;
        }
      result.push_back ({i, col});
    }
  return result;
}

/**
 * This function is used to check if a match appear after a swap
 */
bool Board::CheckMatches (bool counted)
{
  vector<Point> matchedCells;

  for (int row = 0; row < GRID_DIMENSION; row++)
    {
      for (int col = 0; col < GRID_DIMENSION; col++)
        {
          int currentColor = GetColorAt (row, col);

          _aligned_candies_H = FindColumnMatchForCell (row, col, currentColor);

          if (_aligned_candies_H.size () >= 2)
            {
              for (auto alignedcell: _aligned_candies_H) if (count (matchedCells.begin (), matchedCells.end (),
                                                                    alignedcell) == 0) matchedCells.push_back (alignedcell);

              Point to_store{row, col};
              if (count (matchedCells.begin (), matchedCells.end (), to_store) == 0)
                matchedCells.push_back (to_store);
            }

          _aligned_candies_V = FindRowMatchForCell (row, col, currentColor);

          if (_aligned_candies_V.size () >= 2)
            {
              for (auto alignedcell: _aligned_candies_V) if (count (matchedCells.begin (), matchedCells.end (),
                                                                    alignedcell) == 0) matchedCells.push_back (alignedcell);

              Point to_store{row, col};
              if (count (matchedCells.begin (), matchedCells.end (), to_store) == 0)
                matchedCells.push_back (to_store);
            }
        }
    }

  for (auto CellToDelete: matchedCells)
    {
      _board[CellToDelete.x][CellToDelete.y] = -1;
      if (counted) copy_matchedCells.push_back (CellToDelete);
    }

  if (matchedCells.size () > 3)
//      if (!bombcause)
        {
          auto last = matchedCells.back ();
          _board[last.x][last.y] = -2;
        }

  if (counted) _score += int (matchedCells.size ());

  return !matchedCells.empty();

}

/**
 * This function drop cells and generate new ones
 */
void Board::FillGrid ()
{
  for (int col = 0; col < GRID_DIMENSION; col++)
    {
      for (int row = 0; row < GRID_DIMENSION; row++)
        {
          while (GetColorAt (row, col) < 0)
            {
              if (GetColorAt (row, col) == -1)
                {
                  for (int toFill = row; toFill > 0; toFill--)
                    {
                      auto aboveColor = GetColorAt (toFill - 1, col);
                      auto abovediagColor = GetColorAt (toFill-1, col + 1);

                      switch (aboveColor)
                        {
                          case 7: //Wall
                            if (abovediagColor != 7)
                              {
                                if (_board[toFill][col] != 7)
                                  {
                                    if (abovediagColor != -1)
                                      {
                                        _board[toFill][col] = abovediagColor;
                                        _board[toFill-1][col+1] = -1;
                                      }
                                    else _board[toFill][col] = COLORS_VECT[random() % TOTALCOLOR];
                                  }

                              }
                            else if (_board[toFill][col] != 7) _board[toFill][col] = COLORS_VECT[random() % TOTALCOLOR];
                          break;

                          case 8: //Bomb
//                            bombcause = true;
                            bomb ({toFill, col});
                          break;

                          default: //NormalColor
                            if (_board[toFill][col] != 7) _board[toFill][col] = aboveColor;
                          break;

                        }
                    }

                  _board[0][col] = COLORS_VECT[random() % TOTALCOLOR];
                }

              else if (GetColorAt (row, col) == -2) _board[row][col] = 8;

            }
        }
    }
}

/**
* method called when a swap is done
*/
bool Board::swaps (Point cell_1, Point cell_2)
{
  if (_board[cell_1.x][cell_1.y] == 7 or _board[cell_2.x][cell_2.y] == 7) return false; //Wall case

  if (_board[cell_1.x][cell_1.y] == 8 or _board[cell_2.x][cell_2.y] == 8) //Bomb case
    {
      if (_board[cell_1.x][cell_1.y] == 8) bomb (cell_1);
      if (_board[cell_2.x][cell_2.y] == 8) bomb (cell_2);
      loopFillGrid();
      return true;
    }

  cout << getScore () << endl;  //JUST A PRINT


  //Normal color swap
  int tmp = _board[cell_2.x][cell_2.y];
  _board[cell_2.x][cell_2.y] = _board[cell_1.x][cell_1.y];
  _board[cell_1.x][cell_1.y] = tmp;

  bool changesOccurs = CheckMatches (true);

  if (!changesOccurs)
    {
      tmp = _board[cell_1.x][cell_1.y];
      _board[cell_1.x][cell_1.y] = _board[cell_2.x][cell_2.y];
      _board[cell_2.x][cell_2.y] = tmp;
    }
  else
    {
      _nummoves--;
      cout << "moverest = " << _nummoves << endl;
//      bombcause = false;
      loopFillGrid();

      if (_nummoves <= 0) //For objectifs
        {
          _nummoves = 0;
          game_state = GAME_OVER;
        }
    }

  print_board (_board);

  return changesOccurs;
}

int Board::getScore () const
{
  return _score;
}

void Board::SetScore (int newscore)
{
  _score = newscore;
}

int Board::GetNumMoves () const
{
  return _nummoves;
}

void Board::SetNumMoves (int numMoves)
{
  _nummoves = numMoves;
}

void Board::bomb (Point bombpos)
{
//  bombcause = true;
  vector<Point> otherbomb;
  explosion.clear();
  explosion.push_back (bombpos);
  for (auto dir: BOMBDIR)
    {
      auto explosedCell = bombpos + dir;
      if (is_inBoard (explosedCell))
        {
          if (_board[explosedCell.x][explosedCell.y] < 7)
            {
              if (count (explosion.begin (), explosion.end (), explosedCell) == 0) explosion.push_back (explosedCell);
            }
          else if (_board[explosedCell.x][explosedCell.y] == 8) otherbomb.push_back (explosedCell);
        }
    }


  for (auto CellToDelete: explosion)
    _board[CellToDelete.x][CellToDelete.y] = -1;
    _score += 1;

  for (auto otherbmb : otherbomb)
    {
      bomb (otherbmb);
    }
}


void Board::addSwap (Point Source, Point Destination)
{
  pair<Point, Point> to_add{Source, Destination};
  if (count (_possibleswap.begin (), _possibleswap.end (), to_add) == 0)
    _possibleswap.push_back ({Source, Destination});
}


void Board::identifypossibleswap ()
{
  _possibleswap.clear ();
  for (int row = 0; row < GRID_DIMENSION; row++)
    {
      for (int col = 0; col < GRID_DIMENSION; col++)
        {
          for (auto dir: DIR)
            {
              Point destination{row + dir.x, col + dir.y};
              if (is_inBoard (destination))
                {
                  auto copy_board = new int *[GRID_DIMENSION];

                  for (int irow = 0; irow < GRID_DIMENSION; irow++)
                    {
                      copy_board[irow] = new int[GRID_DIMENSION];
                      for (int icol = 0; icol < GRID_DIMENSION; icol++)
                        {
                          copy_board[irow][icol] = _board[irow][icol];
                        }
                    }
                  if (_board[destination.x][destination.y] == 7 or _board[row][col] == 7) continue;

                  int tmp = _board[destination.x][destination.y];
                  _board[destination.x][destination.y] = _board[row][col];
                  _board[row][col] = tmp;

                  if (CheckMatches (false)) addSwap ({row, col}, destination);

                  for (int iirow = 0; iirow < GRID_DIMENSION; iirow++)
                    {
                      _board[iirow] = new int[GRID_DIMENSION];
                      for (int iicol = 0; iicol < GRID_DIMENSION; iicol++)
                        {
                          _board[iirow][iicol] = copy_board[iirow][iicol];
                        }
                    }
                }
            }
        }
    }
}


void Board::loopFillGrid ()
{
  do
    {
      FillGrid ();
    }
  while (CheckMatches (true));

  identifypossibleswap ();
}


vector<pair<Point, Point>> Board::get_possibleswap(){
  return _possibleswap;
}


vector<Point> Board::getMatchedCells()
{
  return copy_matchedCells;
}

void Board::clearMatchedCells()
{
  copy_matchedCells.clear();
}

GameState Board::getState () const
{
  return game_state;
}
















































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































