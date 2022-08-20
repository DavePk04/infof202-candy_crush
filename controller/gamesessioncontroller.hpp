#include "../view/cell.hpp"
#include "../model/Board.hpp"
#include <atomic>


class GameSessionController {
  static std::unique_ptr<GameSessionController> _instance;
  vector<vector<Cell>> cells;
  vector<Cell*> selected;
//  Board bd;
  Board bd{"../levels/level3"};
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
  static void reinitialiseHightScore ();
  int getScore ();
  void drop_anim ();
  int getNumMoves();
};