#include "ChopstickGame.hh"
#include "ComPlayer.hh"
#include "ManPlayer.hh"

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
  Player *com1, *com2;
  int gamecount = stoi(str);
  int wincount[3] = {0, 0, 0};
  bool printTurn = (argv == 5);
  ChopstickGame game;

  if (strcmp(argc[2], "-h"))
    game.p1 = new ComPlayer(argc[2], printTurn);
  else
    game.p1 = new ManPlayer();
  if (strcmp(argc[3], "-h"))
    game.p2 = new ComPlayer(argc[3], printTurn);
  else
    game.p2 = new ManPlayer();

  for (int i = 0; i < gamecount; i++) {
    game.resetGame();
    wincount[game.startGame()]++;
    if ((i + 1) % 10000 == 0) {
      cout << "Game " << i + 1 << '\n';
      cout << "Avg turn " << game.getTotTurn() / 10000.0 << '\n';
    }
  }

  cout << '\n';
  cout << "---- " << gamecount << " times play result ----\n";
  cout << "Player 1 won " << wincount[1] << " times\n";
  cout << "Player 2 won " << wincount[2] << " times\n";
  delete (game.p1);
  delete (game.p2);

  return 0;
}
