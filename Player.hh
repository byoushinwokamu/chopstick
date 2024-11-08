#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Common.hh"

class Player {
protected:
  int playernum;
  int hand[2] = {1, 1};
  void swapHand() {
    if (hand[RIGHT] < hand[LEFT]) {
      int t = hand[LEFT];
      hand[LEFT] = hand[RIGHT];
      hand[RIGHT] = t;
    }
  }

protected:
  int prevturn = 0;

public:
  virtual ~Player() {}
  int getHand(Direction dir) { return hand[dir]; }
  void addHand(Direction dir, int dam) {
    hand[dir] += dam;
    hand[dir] = hand[dir] < 5 ? hand[dir] : 0;
    swapHand();
  }
  void splitHand(int lefthand) {
    int tot = hand[LEFT] + hand[RIGHT];
    hand[LEFT] = lefthand;
    hand[RIGHT] = tot - lefthand;
    swapHand();
  }
  bool isAlive() { return hand[0] + hand[1] != 0; }
  virtual Action play(Status &st) = 0;
  virtual void victory() {}
  virtual void defeat() {}
  virtual void draw() {}
  void reset() { prevturn = 0, hand[LEFT] = 1, hand[RIGHT] = 1; }
};

#endif