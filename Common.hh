#ifndef __COMMON_H__
#define __COMMON_H__

#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#define MAXTURN 100

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

#endif