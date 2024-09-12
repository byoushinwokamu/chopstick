#ifndef __CGAME_H__
#define __CGAME_H__

#include "Common.hh"
#include "Player.hh"

class ChopstickGame {
private:
  int turn = 0;
  long long totturn = 0;

public:
  Player *p1;
  Player *p2;
  int startGame();
  void endGame();
  long long getTotTurn() const { return totturn; }
  void resetGame() {
    totturn = 0;
    p1->reset();
    p2->reset();
  }
  bool validAction(Action a);
};

#endif