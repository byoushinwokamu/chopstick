#include "Player.hh"

class Player;

class ComPlayer : public Player {
private:
  typedef struct {
    int action[8] = {
        0,
    };
  } Weight;
  Weight weight[196];
  string datafile;
  bool printTurn = false;
  int prevAction = -1;

  const int INVALIDACT = INT32_MIN;
  const int DEFEATACT = INT32_MIN + 1;

  int conversion[5][5] = {{-1, 0, 1, 2, 3},
                          {-1, 4, 5, 6, 7},
                          {-1, -1, 8, 9, 10},
                          {-1, -1, -1, 11, 12},
                          {-1, -1, -1, -1, 13}};

public:
  ComPlayer() {}
  ComPlayer(char *filename, bool printTurn);
  ~ComPlayer();

  Action play(Status &st);

  friend std::istream &operator>>(std::istream &in, ComPlayer &cpd) {
    for (int i = 0; i < 196; i++) {
      for (int j = 0; j < 8; j++) {
        in >> cpd.weight[i].action[j];
      }
    }
    return in;
  }

  int getWeightIndex(Status &st) {
    return conversion[st.myHand[LEFT]][st.myHand[RIGHT]] +
           conversion[st.enemyHand[LEFT]][st.enemyHand[RIGHT]] * 14;
  }

  void defeat();
};