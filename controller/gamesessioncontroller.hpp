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
  // Fl_Color generateColor();
  // void check(Cell *c);
  // void swim(Cell *c);
  // void swap(Cell *c1, Cell *c2);
  // void swap_(Cell &c1, Cell &c2);
  // void delete_(Cell *c);
  static GameSessionController &getInstance ();
  void initiate ();
  void possible_move ();
  Point p1_;
  Point p2_;
};