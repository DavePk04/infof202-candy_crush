#include "../view/Cell.hpp"
#include "../model/Board.hpp"
#include <atomic>

class GameSessionController {
  static std::unique_ptr<GameSessionController> _instance;
  vector<vector<Cell>> cells;
  vector<Cell *> selected;
  Board bd{};
  int **board = nullptr;
  int possible_move_anim = 0;
  atomic<int> chrono_possiblemove;
  bool _endgame = false;

 public:
  GameSessionController () = default;
  ~GameSessionController () = default;
  void draw ();
  void mouseMove (Point mouseLoc);
  void mouseClick (Point mouseLoc);
  void keyPressed (int keyCode);
  void selectCell (Cell *c);
  void normalise ();
  static GameSessionController &getInstance ();
  void initiate (int levelidx = -1);
  void possible_move ();
  bool saveScore ();
  static void reinitialiseHightScore ();
  int getScore ();
  void explosion_anim ();
  int getNumMoves ();
  void mouseDrag (Point point);
  bool endgame ();
  bool win ();
  void reset ();
  void newLevelinit (int i);
  vector<atomic_int> *objectives ();
};