#include "ComPlayer.hh"
#include "ManPlayer.hh"

class ChopstickGame {
public:
  int turn = 0;
  Player *p1;
  Player *p2;
  int startGame();
  bool validAction(Action a);
};

int main(int argv, char **argc) {
  if (argv < 4) {
    cout << "Option: [gamecount] [datafile] [datafile] [printoption]\n";
    cout << "If you want to play directly, -h instead of "
            "[datafile].\n";
    cout << "If you want to robot's turn message, input -p on "
            "[printoption].\n";
    cout << "The order of game progression follows the order of "
            "the options.\n";
    return 0;
  }
  string str(argc[1]);
  int gamecount = stoi(str);
  int wincount[3] = {0, 0, 0};
  bool printTurn = argv == 5 ? (strcmp(argc[4], "-p") ? false : true) : false;
  ChopstickGame game;

  for (int i = 0; i < gamecount; i++) {
    game.turn = 0;
    if (!strcmp(argc[2], "-h"))
      game.p1 = new ManPlayer();
    else
      game.p1 = new ComPlayer(argc[2], printTurn);
    if (!strcmp(argc[3], "-h"))
      game.p2 = new ManPlayer();
    else
      game.p2 = new ComPlayer(argc[3], printTurn);
    wincount[game.startGame()]++;
  }

  cout << '\n';
  cout << "---- " << gamecount << " times play result ----\n";
  cout << "Player 1 won " << wincount[1] << " times\n";
  cout << "Player 2 won " << wincount[2] << " times\n";

  return 0;
}

int ChopstickGame::startGame() {
  // p1 is attacker, p2 is defender
  Player *temp;
  Status st;
  Action act;
  bool playisvalid = false;
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
      // cout << "Game terminated by surrender\n";
      p2->victory();
      p1->defeat();
      delete p1;
      delete p2;
      return turn % 2 + 1;
    }

    // end phase
    if (!p2->isAlive()) {
      // cout << "Game terminated by attack\n";
      p1->victory();
      p2->defeat();
      delete p1;
      delete p2;
      return (turn + 1) % 2 + 1;
    }
    temp = p1;
    p1 = p2;
    p2 = temp;
    playisvalid = false;

    if (turn > 100) {
      delete p1;
      delete p2;
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