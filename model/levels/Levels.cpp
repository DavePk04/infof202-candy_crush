//
// Created by bdmr on 19/08/22.
//

#include <fstream>
#include "Levels.hpp"
#include <sstream>

Levels::Levels (int idx)
{
  _idx = idx;
  if (_idx != -1)
    {
      _level_filename = LEVELS.at (_idx);
      ifstream levelfile;
      levelfile.open (_level_filename);
      if (levelfile.is_open ())
        {
          int _obj;
          levelfile >> _maxMoves; //get max moves
          //get objectives
          for (int i = 0; i < OBJECTIVES; i++)
            {
              levelfile >> _obj;
              _objectives->at (i) = _obj;
            }

          for (int i = 0; i < GRID_DIMENSION; i++)
            {
              _board[i] = new int[GRID_DIMENSION];
              for (int j = 0; j < GRID_DIMENSION; j++)
                levelfile >> _board[i][j];
            }
        }

      levelfile.close ();
      _level = true;
    }
}

int **Levels::getBoard ()
{
  return _board;
}

bool Levels::islevel () const
{
  return _level;
}

float Levels::get_maxMoves () const
{
  return _maxMoves;
}

/**
 * Check if objectives are attended
 * @return
 */
bool Levels::goalAchieved ()
{
  for (int i = 0; i < OBJECTIVES; i++)
    {
      if (_objectives->at (i) != 0) return false;
    }

  return true;
}

vector<atomic_int> *Levels::getObjectives ()
{
  return _objectives;
}
