#include "Player.hh"

class ManPlayer : public Player {
private:
  int prevturn = 0;

public:
  Action play(Status st);
};