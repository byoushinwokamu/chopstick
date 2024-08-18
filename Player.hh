#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

typedef enum { ATTACK, SPLIT, SURRENDER } ActionType;
typedef enum { LEFT, RIGHT } Direction;

typedef struct {
  ActionType action;
  Direction attackfrom, attackto;
  int splitleft;
} Action;

typedef struct {
  int turn;
  int enemyHand[2];
  int myHand[2];
} Status;

class Player {
private:
  int hand[2] = {1, 1};
  void swapHand() {
    if (hand[1] < hand[0]) {
      int t = hand[0];
      hand[0] = hand[1];
      hand[1] = t;
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
    int tot = hand[0] + hand[1];
    hand[0] = lefthand;
    hand[1] = tot - lefthand;
  }
  bool isAlive() { return hand[0] + hand[1] != 0; }
  virtual Action play(Status &st) = 0;
  void victory() {}
  void defeat() {}
};
#endif