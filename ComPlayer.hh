#include "Player.hh"

class Player;

class ComPlayer : public Player {
private:
  typedef struct {
    int action[8];
  } Weight;
  typedef struct {
    int stat;
    int acti;
  } TurnLog;

  Weight weight[196];
  string datafile;
  TurnLog tlog[MAXTURN];
  bool printTurn = false;
  int prevAction = -1;
  int turncount = 0;

  const int INVALIDACT = INT32_MIN;
  const int DEFEATACT = INT32_MIN + 1;

  const int conversion[5][5] = {{-1, 0, 1, 2, 3},
                                {-1, 4, 5, 6, 7},
                                {-1, -1, 8, 9, 10},
                                {-1, -1, -1, 11, 12},
                                {-1, -1, -1, -1, 13}};

public:
  ComPlayer() {}
  ComPlayer(char *filename, bool printTurn);
  ~ComPlayer();

  Action play(Status &st);
  int getWeightIndex(Status &st);
  virtual void victory();
  virtual void defeat();
  virtual void draw();

  friend std::istream &operator>>(std::istream &in, ComPlayer &cpd) {
    for (int i = 0; i < 196; i++) {
      for (int j = 0; j < 8; j++) {
        in >> cpd.weight[i].action[j];
      }
    }
    return in;
  }
};