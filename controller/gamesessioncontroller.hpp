#include "../view/cell.hpp"
#include "../model/Board.hpp"

class GameSessionController {
  static std::unique_ptr<GameSessionController> _instance;
  vector<vector<Cell>> cells;
  //vector<Cell*> selected_cells;
  vector<Cell*> selected;
  Board bd;
  int** board;
  int possible_move_anim = 0;
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
  int handlePlayerAction(int action);
  static GameSessionController &getInstance ();
  void initiate ();
  void possible_move ();
  void drop_anim();
  int getScore();
};