#include "ManPlayer.hh"

Action ManPlayer::play(Status st) {
  Action act;
  char actstr[4];
  bool validinput = false;
  if (prevturn == st.turn)
    cout << "\n*****Invalid action*****\n\n";

  while (!validinput) {
    validinput = true;
    cout << "** Turn " << st.turn << " **\n";
    cout << "Enemy: " << st.enemyHand[0] << " / " << st.enemyHand[1] << '\n';
    cout << "  You: " << st.myHand[0] << " / " << st.myHand[1] << '\n';
    cout << "Attack(a[l/r][l/r]) or Split(s[lefthand][righthand])? ";
    cin >> actstr;

    switch (actstr[0]) {
    case 'a':
      act.action = ATTACK;

      if (actstr[1] == 'l') {
        act.attackfrom = LEFT;
        if (this->getHand(LEFT) == 0)
          validinput = false;
      } else if (actstr[1] == 'r') {
        act.attackfrom = RIGHT;
        if (this->getHand(RIGHT) == 0)
          validinput = false;
      } else
        validinput = false;

      if (actstr[2] == 'l')
        act.attackto = LEFT;
      else if (actstr[2] == 'r')
        act.attackto = RIGHT;
      else
        validinput = false;
      break;

    case 's': {
      act.action = SPLIT;

      int smallhand = min(actstr[1] - '0', actstr[2] - '0');
      int sumofhand = st.myHand[0] + st.myHand[1];
      if (smallhand > 3 || smallhand < 0) {
        validinput = false;
        break;
      }
      if (smallhand > sumofhand / 2) {
        validinput = false;
        break;
      }
      act.splitleft = smallhand;
      break;
    }
    default:
      validinput = false;
    }
    if (!validinput)
      cout << "\n*****Invalid action*****\n\n";
  } // while

  prevturn = st.turn;

  return act;
}