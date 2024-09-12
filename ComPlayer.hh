#include "Player.hh"

class Player;

class ComPlayer : public Player {
private:
  unsigned int prob[1568];
  string datafile;
  vector<Status> tlog;
  bool printTurn = false;
  int prevAction = -1;
  int turncount = 0;

  const int INVALIDACT = UINT8_MAX;
  const int DEFEATACT = UINT8_MAX - 1;
  const int STUDYCOEFF = 1;

  const int conversion[5][5] = {{-1, 0, 1, 2, 3},
                                {-1, 4, 5, 6, 7},
                                {-1, -1, 8, 9, 10},
                                {-1, -1, -1, 11, 12},
                                {-1, -1, -1, -1, 13}};

public:
  ComPlayer() {
    for (int i = 0; i < 1568; i++)
      prob[i] = 128;
  }
  ComPlayer(char *filename, bool printTurn);
  ~ComPlayer();

  Action play(Status &st);
  int getWeightIndex(Status &st);
  virtual void victory();
  virtual void defeat();
  virtual void draw();
  virtual void reset();

  // friend std::istream &operator>>(std::istream &in, ComPlayer &cpd) {
  //   for (int i = 0; i < 196; i++) {
  //     for (int j = 0; j < 8; j++) {
  //       in >> cpd.prob[i];
  //     }
  //   }
  //   return in;
  // }
};