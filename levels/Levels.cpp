//
// Created by bdmr on 19/08/22.
//

#include <fstream>
#include "Levels.hpp"
#include <sstream>

Levels::Levels(int idx)
{
  _idx = idx;
  if (_idx != -1)
    {
      _level_filename = LEVELS.at (_idx);
      ifstream levelfile;
      levelfile.open (_level_filename);
      if (levelfile.is_open ())
        {
          string _objstring;
          int _obj;
          levelfile >> _maxMoves; //get max moves
          //get objectives
          getline (levelfile , _objstring);
          stringstream stg( _objstring );
          while (stg >> _obj) _objectives.push_back (_obj);

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

int Levels::get_levelnumber () const
{
  return _idx;
}

float Levels::get_maxMoves () const
{
  return _maxMoves;
}
