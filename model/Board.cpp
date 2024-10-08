#include "Board.hpp"
#include <algorithm>
#include <unordered_set>
#include<set>
#include <fstream>

using namespace std;

/**
 * This function delete an element from a vector
 * @param vec
 * @param num
 * @return
 */
vector<int> delete_ele (vector<int> vec, int num)
{
  vector<int>::reverse_iterator itr1;

  for (itr1 = vec.rbegin (); itr1 < vec.rend (); itr1++)
    if (*itr1 == num) vec.erase ((itr1 + 1).base ());

  return vec;
}

int Board::getColorAt (int row, int col, int **bd)
{
  if (col < 0 || col >= GRID_DIMENSION
      || row < 0 || row >= GRID_DIMENSION)
    return -1;

  auto color = bd[row][col];

  return color;
}

/**
 * The grid generator function
 */
void Board::gen_color_grid ()
{
  for (int i = 0; i < GRID_DIMENSION; i++)
    {
      std::vector<int> copy_color_vect (COLORS_VECT);

      if (i == 0 or i == 8) copy_color_vect = delete_ele (copy_color_vect, 7);
      else copy_color_vect.push_back (7);

      _board[i] = new int[GRID_DIMENSION];
      for (int j = 0; j <= GRID_DIMENSION; j++)
        {
          if (j == 0 or j == 8) copy_color_vect = delete_ele (copy_color_vect, 7);
          else if (i != 0 and i != 8) copy_color_vect.push_back (7);

          int left1 = getColorAt (i, j - 1, _board);
          int left2 = getColorAt (i, j - 2, _board);
          if (left2 != -1 && left1 == left2)
            {
              copy_color_vect = delete_ele (copy_color_vect, left1);
            }

          if (left1 == 7 or left2 == 7)
            copy_color_vect = delete_ele (copy_color_vect, 7);

          int down1 = getColorAt (i - 1, j, _board);
          int down2 = getColorAt (i - 2, j, _board);
          if (down2 != -1 && down1 == down2)
            {
              copy_color_vect = delete_ele (copy_color_vect, down1);
            }

          if (down1 == 7 or down2 == 7)
            copy_color_vect = delete_ele (copy_color_vect, 7);

          int color = copy_color_vect[random () % copy_color_vect.size ()];
          _board[i][j] = color;
        }
    }
}

Board::Board (int idx)
{
  level = Levels{idx};
  if (level.islevel ())
    {
      _board = level.getBoard ();
      _nummoves = level.get_maxMoves ();
    }
  else
    {
      gen_color_grid ();
      _nummoves = 60;
    }

  game_state = RUNNING;

  identifypossibleswap ();
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
 * This function select Matched cells in Colomn
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
      int nextColumnColor = getColorAt (row, i, _board);
      if (nextColumnColor != color)
        {
          break;
        }
      result.push_back ({row, i});
    }
  return result;
}

/**
 * This function select Matched cells in Row
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
      int nextRowColor = getColorAt (i, col, _board);
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
          int currentColor = getColorAt (row, col, _board);

          _aligned_candies_H = FindColumnMatchForCell (row, col, currentColor);

          if (_aligned_candies_H.size () >= 2)
            {
              for (auto alignedcell: _aligned_candies_H)
                if (count (matchedCells.begin (), matchedCells.end (),
                           alignedcell) == 0)
                  matchedCells.push_back (alignedcell);

              Point to_store{row, col};
              if (count (matchedCells.begin (), matchedCells.end (), to_store) == 0)
                matchedCells.push_back (to_store);
            }

          _aligned_candies_V = FindRowMatchForCell (row, col, currentColor);

          if (_aligned_candies_V.size () >= 2)
            {
              for (auto alignedcell: _aligned_candies_V)
                if (count (matchedCells.begin (), matchedCells.end (),
                           alignedcell) == 0)
                  matchedCells.push_back (alignedcell);

              Point to_store{row, col};
              if (count (matchedCells.begin (), matchedCells.end (), to_store) == 0)
                matchedCells.push_back (to_store);
            }
        }
    }

  for (auto CellToDelete: matchedCells)
    {
      auto objidx = _board[CellToDelete.x][CellToDelete.y] - 1;
      if (objidx == 8) objidx = 7;

      _board[CellToDelete.x][CellToDelete.y] = -1;
      if (counted)
        {
          if (objidx > -1 and objidx < 7 and level.islevel () and level.getObjectives ()->at (objidx) > 0)
            if (level.getObjectives ()->at (objidx) > 0) level.getObjectives ()->at (objidx) = level.getObjectives ()->at (objidx) - 1;

          copy_matchedCells.push_back (CellToDelete);
          for (auto dir: DIR)
            {
              auto pos = CellToDelete + dir;
              if (is_inBoard (pos))
                {
                  if (_board[pos.x][pos.y] == 9)
                    {
                      _board[pos.x][pos.y] = -1;
                      copy_matchedCells.push_back (pos);
                      if (level.getObjectives ()->at (7) > 0) level.getObjectives ()->at (7) = level.getObjectives ()->at (7) - 1;
                    }
                  else if (_board[pos.x][pos.y] == 10)
                    _board[pos.x][pos.y] = 9;
                }
            }
        }
    }

  if (matchedCells.size () > MIN_CANDIES_ALIGNED)
    {
      auto last = matchedCells.at (random () % matchedCells.size ());
      _board[last.x][last.y] = -2;
    }

  if (counted) _score += int (matchedCells.size ());

  return !matchedCells.empty ();

}

/**
 * This function drop cells and generate new ones
 */
void Board::fillGrid ()
{
  for (int col = 0; col < GRID_DIMENSION; col++)
    {
      for (int row = 0; row < GRID_DIMENSION; row++)
        {
          while (getColorAt (row, col, _board) < 0)
            {
              if (getColorAt (row, col, _board) == -1)
                {
                  for (int toFill = row; toFill > 0; toFill--)
                    {
                      auto aboveColor = getColorAt (toFill - 1, col, _board);
                      auto abovediagColor = getColorAt (toFill - 1, col + 1, _board);
                      switch (aboveColor)
                        {
                          case 7: //Wall
                            if (abovediagColor != 7 and abovediagColor != 9 and abovediagColor != 10)
                              {
                                if (_board[toFill][col] != 7 and _board[toFill][col] != 9 and _board[toFill][col] != 10)
                                  {
                                    if (abovediagColor != -1)
                                      {
                                        _board[toFill][col] = abovediagColor;
                                        _board[toFill - 1][col + 1] = -1;
                                        if (abovediagColor == 8) bomb ({toFill, col});
                                      }
                                    else _board[toFill][col] = COLORS_VECT[random () % TOTALCOLOR];
                                  }
                              }
                            else if (_board[toFill][col] != 7 and _board[toFill][col] != 9
                                     and _board[toFill][col] != 10)
                              _board[toFill][col] = COLORS_VECT[random () % TOTALCOLOR];
                          break;
                          case 8: //Bomb
                            bomb ({toFill, col});
                          break;
                          case 9: //Simple Ice
                            if (abovediagColor != 7 and abovediagColor != 9 and abovediagColor != 10)
                              {
                                if (_board[toFill][col] != 7 and _board[toFill][col] != 9 and _board[toFill][col] != 10)
                                  {
                                    if (abovediagColor != -1)
                                      {
                                        _board[toFill][col] = abovediagColor;
                                        _board[toFill - 1][col + 1] = -1;
                                      }
                                    else _board[toFill][col] = COLORS_VECT[random () % TOTALCOLOR];
                                  }

                              }
                            else if (_board[toFill][col] != 7 and _board[toFill][col] != 9
                                     and _board[toFill][col] != 10)
                              _board[toFill][col] = COLORS_VECT[random () % TOTALCOLOR];
                          break;
                          case 10: //Double Ice
                            if (abovediagColor != 7 and abovediagColor != 9 and abovediagColor != 10)
                              {
                                if (_board[toFill][col] != 7 and _board[toFill][col] != 9 and _board[toFill][col] != 10)
                                  {
                                    if (abovediagColor != -1)
                                      {
                                        _board[toFill][col] = abovediagColor;
                                        _board[toFill - 1][col + 1] = -1;
                                      }
                                    else _board[toFill][col] = COLORS_VECT[random () % TOTALCOLOR];
                                  }

                              }
                            else if (_board[toFill][col] != 7 and _board[toFill][col] != 9
                                     and _board[toFill][col] != 10)
                              _board[toFill][col] = COLORS_VECT[random () % TOTALCOLOR];
                          break;
                          default: //NormalColor
                            if (_board[toFill][col] != 7 and _board[toFill][col] != 9
                                and _board[toFill][col] != 10)
                              _board[toFill][col] = aboveColor;
                          break;
                        }
                    }
                  _board[0][col] = COLORS_VECT[random () % TOTALCOLOR];
                }
              else if (getColorAt (row, col, _board) == -2) _board[row][col] = 8;

            }
        }
    }
}

/**
* method called when a swap is done
*/
bool Board::swaps (Point cell_1, Point cell_2)
{
  if (_board[cell_1.x][cell_1.y] == 7 or _board[cell_2.x][cell_2.y] == 7
      or _board[cell_1.x][cell_1.y] == 9 or _board[cell_2.x][cell_2.y] == 9
      or _board[cell_1.x][cell_1.y] == 10 or _board[cell_2.x][cell_2.y] == 10)
    return false; //Wall or Ice case

  if (_board[cell_1.x][cell_1.y] == 8 or _board[cell_2.x][cell_2.y] == 8) //Bomb case
    {
      if (_board[cell_1.x][cell_1.y] == 8) bomb (cell_1);
      if (_board[cell_2.x][cell_2.y] == 8) bomb (cell_2);
      loopFillGrid ();
      return true;
    }

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
      loopFillGrid ();

      if (_nummoves <= 0) //For objectifs
        {
          _nummoves = 0;
          game_state = GAME_OVER;

          if (level.islevel () and !level.goalAchieved ()) win = false;
          else if (!level.islevel ()) win = true;
          else if (level.islevel () and level.goalAchieved ()) win = true;
        }
      else if (level.islevel () and level.goalAchieved ())
        {
          _nummoves = 0;
          game_state = GAME_OVER;
          win = true;
        }
    }

  return changesOccurs;
}

int Board::getScore () const
{
  return _score;
}

int Board::getNumMoves () const
{
  return _nummoves;
}

/**
 * This fonction is called when a bomb explose
 * @param bombpos
 */
void Board::bomb (Point bombpos)
{
  vector<Point> otherbomb;
  explosion.clear ();
  explosion.push_back (bombpos);
  for (auto dir: BOMBDIR)
    {
      auto explosedCell = bombpos + dir;
      if (is_inBoard (explosedCell))
        {
          if (_board[explosedCell.x][explosedCell.y] != 8 and _board[explosedCell.x][explosedCell.y] != 7)
            {
              if (count (explosion.begin (), explosion.end (), explosedCell) == 0) explosion.push_back (explosedCell);
            }
          else if (_board[explosedCell.x][explosedCell.y] == 8) otherbomb.push_back (explosedCell);
        }
    }

  for (auto CellToDelete: explosion)
    {
      auto objidx = _board[CellToDelete.x][CellToDelete.y] - 1;
      if (objidx == 8) objidx = 7;

      if (_board[CellToDelete.x][CellToDelete.y] == 10) _board[CellToDelete.x][CellToDelete.y] = 9;
      else
        {
          if (objidx > -1 and objidx < 7 and level.islevel () and level.getObjectives ()->at (objidx) > 0)
            if (level.getObjectives ()->at (objidx) > 0) level.getObjectives ()->at (objidx) = level.getObjectives ()->at (objidx) - 1;

          _board[CellToDelete.x][CellToDelete.y] = -1;
          _score += 1;
          copy_matchedCells.push_back (CellToDelete);

          for (auto dir: DIR)
            {
              auto pos = CellToDelete + dir;
              if (is_inBoard (pos))
                {
                  if (_board[pos.x][pos.y] == 10) _board[pos.x][pos.y] = 9;
                  else if (_board[pos.x][pos.y] == 9)
                    {
                      _board[CellToDelete.x][CellToDelete.y] = -1;
                      if (level.getObjectives ()->at (7) > 0)
                        level.getObjectives ()->at (7) = level.getObjectives ()->at (7) - 1;
                    }
                }
            }
        }

    }

  for (auto otherbmb: otherbomb)
    {
      bomb (otherbmb);
    }
}

/*
 * This function add possible swap
 */
void Board::addSwap (Point Source, Point Destination)
{
  pair<Point, Point> to_add{Source, Destination};
  if (count (_possibleswap.begin (), _possibleswap.end (), to_add) == 0)
    _possibleswap.push_back ({Source, Destination});
}

/**
 * This function find all the possible swap
 */
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
                  if (_board[destination.x][destination.y] == 9 or _board[row][col] == 9) continue;
                  if (_board[destination.x][destination.y] == 10 or _board[row][col] == 10) continue;

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

/**
 * Loop for filling the grid
 */
void Board::loopFillGrid ()
{
  do
    {
      fillGrid ();
    }
  while (CheckMatches (true));

  identifypossibleswap ();
}

vector<pair<Point, Point>> Board::get_possibleswap ()
{
  return _possibleswap;
}

vector<Point> Board::getMatchedCells ()
{
  return copy_matchedCells;
}

void Board::clearMatchedCells ()
{
  copy_matchedCells.clear ();
}

GameState Board::getState () const
{
  return game_state;
}

/**
 * This function is called for generating a newboard
 */
void Board::regen_color_grid ()
{

  int **_newboard = new int *[GRID_DIMENSION];

  for (int i = 0; i < GRID_DIMENSION; i++)
    {
      std::vector<int> copy_color_vect (COLORS_VECT);
      delete_ele (copy_color_vect, 7);

      _newboard[i] = new int[GRID_DIMENSION];

      for (int j = 0; j < GRID_DIMENSION; j++)
        {

          int left1 = getColorAt (i, j - 1, _newboard); //2
          int left2 = getColorAt (i, j - 2, _newboard);
          if (left2 != -1 && left1 == left2) // 3
            {
              copy_color_vect = delete_ele (copy_color_vect, left1);
            }

          int down1 = getColorAt (i - 1, j, _newboard); // 5
          int down2 = getColorAt (i - 2, j, _newboard);
          if (down2 != -1 && down1 == down2)
            {
              copy_color_vect = delete_ele (copy_color_vect, down1);
            }

          int color = copy_color_vect[random () % copy_color_vect.size ()];
          if (_board[i][j] < 7)
            {
              while (color == 7)
                {
                  color = copy_color_vect[random () % copy_color_vect.size ()];
                }
              _newboard[i][j] = color;
            }
          else if (_board[i][j] == 7) _newboard[i][j] = 7;
          else if (_board[i][j] == 8) _newboard[i][j] = 8;
        }
    }

  for (int i = 0; i < GRID_DIMENSION; i++)
    for (int j = 0; j < GRID_DIMENSION; j++)
      _board[i][j] = _newboard[i][j];

}

bool Board::isWinner () const
{
  return win;
}

vector<atomic_int> *Board::getObjectives ()
{
  return level.getObjectives ();
}
















































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































