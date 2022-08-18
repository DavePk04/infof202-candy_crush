#include "../view/cell.hpp"
#include "../model/Board.hpp"
#include <ctime>
#include <chrono>
#include <atomic>

class GameSessionController {
  static std::unique_ptr<GameSessionController> _instance;
  vector<vector<Cell>> cells;
  vector<Cell*> selected;
  Board bd{"../levels/level1"};
  int** board = nullptr;
  int possible_move_anim = 0;
  atomic<int> chrono_possiblemove;

 public:
  GameSessionController() = default;
  ~GameSessionController() = default;
  void draw();
  void mouseMove(Point mouseLoc);
  void mouseClick(Point mouseLoc);
  void keyPressed(int keyCode);
  void selectCell(Cell *c);
  void normalise();
  vector<Cell*> getSelectedCell();
  static GameSessionController &getInstance ();
  void initiate ();
  void possible_move ();
  void saveScore ();
  void reinitialiseScore ();
  int getScore ();
  void drop_anim ();
  int getNumMoves();
};