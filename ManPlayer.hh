#include "Player.hh"

class ManPlayer : public Player {
public:
  ~ManPlayer();
  Action play(Status &st);
  void victory() {}
  void defeat() {}
  void draw() {}
};