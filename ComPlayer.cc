#include "ComPlayer.hh"

ComPlayer::ComPlayer(char *filename, bool printTurn) {
  ifstream fin(filename);
  datafile = filename;
  if (!fin.is_open()) {
    cout << "Can't load data from " << filename << endl;
    exit(0);
  }
  fin >> *this;
  this->printTurn = printTurn;
  // cout << "Load complete from " << filename << endl;
}

ComPlayer::~ComPlayer() {
  // cout << "try to save" << datafile << endl;
  ofstream fout(datafile);
  // cout << "opened file" << endl;
  if (!fout.is_open()) {
    cout << "Failed to save data\n";
  } else {
    // cout << "Save complete to " << datafile << endl;
    for (int i = 0; i < 196; i++) {
      for (int j = 0; j < 8; j++) {
        fout << this->weight[i].action[j] << ' ';
      }
      fout << '\n';
    }
  }
}

Action ComPlayer::play(Status &st) {
  Action act;

  int weIdx = getWeightIndex(st);
  if (printTurn)
    cout << '\n';
  if (prevturn == st.turn && printTurn) {
    cout << "$$$$$tried to invalid action$$$$$\n";
    weight[weIdx].action[prevAction] = INVALIDACT;
  }

  if (printTurn) {
    cout << "$$ Turn " << st.turn << " $$\n";
    cout << "  Com: " << st.myHand[0] << " / " << st.myHand[1] << '\n';
    cout << "Enemy: " << st.enemyHand[0] << " / " << st.enemyHand[1] << '\n';
  }

  // random device initialize
  random_device rd;
  mt19937 gen(rd());

  // calculate probability with weight
  long long act_prob[8];
  for (int i = 0; i < 8; i++) {
    if (weight[weIdx].action[i] == INVALIDACT ||
        weight[weIdx].action[i] == DEFEATACT)
      act_prob[i] = (i ? act_prob[i - 1] : 0);
    else
      act_prob[i] = (i ? act_prob[i - 1] : 0) + 20 + weight[weIdx].action[i];
  }
  // if (act_prob[7] = 0) {
  //   cout << "I surrender..\n";
  //   act.action = SURRENDER;
  //   return act;
  // }

  // cout << "GO RANDOM!!\n";
  // get random result
  uniform_int_distribution<long long> dis(0, act_prob[7]);
  long long res = dis(gen);
  for (int i = 0; i < 8; i++) {
    if (act_prob[i] > res) {
      act.action = (i < 4 ? ATTACK : SPLIT);
      act.attackfrom = (i / 2 ? LEFT : RIGHT);
      act.attackto = (i % 2 ? LEFT : RIGHT);
      act.splitleft = i % 4;
      prevAction = i;
      break;
    }
  }

  // return act
  prevturn = st.turn;
  return act;
}