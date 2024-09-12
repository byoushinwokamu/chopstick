#include "ChopstickGame.hh"

int ChopstickGame::startGame() {
  // p1 is attacker, p2 is defender
  Player *temp;
  Status st;
  Action act;
  turn = 0;
  while (true) {
    // init phase
    st.turn = ++turn;
    st.myHand[0] = p1->getHand(LEFT);
    st.myHand[1] = p1->getHand(RIGHT);
    st.enemyHand[0] = p2->getHand(LEFT);
    st.enemyHand[1] = p2->getHand(RIGHT);

    // play phase
    // check validity of action
    do {
      act = p1->play(st);
    } while (!validAction(act));

    // execute action
    if (act.action == ATTACK) {
      p2->addHand(act.attackto, p1->getHand(act.attackfrom));
    }
    if (act.action == SPLIT) {
      p1->splitHand(act.splitleft);
    }
    if (act.action == SURRENDER) {
      cout << "SURRENDER IN " << turn << "TURNS\n";
      p2->victory();
      p1->defeat();
      return turn % 2 + 1;
    }

    // end phase
    if (!p2->isAlive()) {
      // cout << "GAME SET IN " << turn << "TURNS\n";
      totturn += turn;
      p1->victory();
      p2->defeat();
      return (turn + 1) % 2 + 1;
    }
    temp = p1;
    p1 = p2;
    p2 = temp;

    if (turn > MAXTURN * 2) {
      return 0;
    }
  }
}

bool ChopstickGame::validAction(Action a) {
  if (a.action == ATTACK) {             // case of attack
    if (p1->getHand(a.attackfrom) == 0) // my hand is empty
      return false;
    if (p2->getHand(a.attackto) == 0) // enemy's hand is empty
      return false;
  } else if (a.action == SPLIT) { // case of split
    int sumofhand = p1->getHand(LEFT) + p1->getHand(RIGHT);
    if (p1->getHand(LEFT) == a.splitleft) // no move
      return false;
    if (a.splitleft * 2 > sumofhand) // left is larger
      return false;
    if (sumofhand - a.splitleft > 4) // right is over 4
      return false;
  } else if (a.action == SURRENDER) { // case of surrender
    return true;
  }
  return true;
}
