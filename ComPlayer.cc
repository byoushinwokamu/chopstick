#include "ComPlayer.hh"

ComPlayer::ComPlayer(char *filename, bool printTurn) : printTurn(printTurn) {
  cout << "try to load from " << filename << endl;
  // load data
  ifstream fin(filename);
  datafile = filename;
  if (!fin.is_open()) {
    cout << "Can't load data from " << filename << endl;
    exit(0);
  }
  // fin >> *this;
  for (int i = 0; i < 1568; i++)
    fin >> prob[i];
}

ComPlayer::~ComPlayer() {
  cout << "try to save to " << datafile << endl;
  // save data
  ofstream fout(datafile);
  if (!fout.is_open()) {
    // cout << datafile;
    cout << " save failed\n";
    // cout << "Failed to save data to " << datafile << '\n';
  } else {
    for (int i = 0; i < 196; i++) {
      for (int j = 0; j < 8; j++) {
        fout << this->prob[i] << ' ';
      }
      fout << '\n';
    }
  }
}

Action ComPlayer::play(Status &st) {
  Action act;

  // get index(0*8~195*8)
  int weIdx = getWeightIndex(st);
  if (printTurn)
    cout << '\n';

  // if prev action was invalid, update weight data to invalid
  if (prevturn == st.turn) {
    if (printTurn)
      cout << "$$$$$tried to invalid action$$$$$\n";
    prob[weIdx + prevAction] = INVALIDACT;
    turncount--;
    tlog.erase(tlog.end() - 1);
  }

  // print turn stat
  if (printTurn) {
    cout << "$$ Turn " << st.turn << " $$\n";
    cout << "  Com: " << st.myHand[0] << " / " << st.myHand[1] << '\n';
    cout << "Enemy: " << st.enemyHand[0] << " / " << st.enemyHand[1] << '\n';
  }

  // random device initialize
  random_device rd;
  mt19937 gen(rd());

  // calculate probability with weight
  unsigned int act_prob[8];
  for (int i = 0; i < 8; i++) {
    if (prob[weIdx + i] == INVALIDACT || prob[weIdx + i] == DEFEATACT)
      act_prob[i] = (i ? act_prob[i - 1] : 0);
    else
      act_prob[i] = (i ? act_prob[i - 1] : 0) + 1 + prob[weIdx + i];
  }
  // if (act_prob[7] == 0) {
  //   // cout << "I surrender.." << turncount << "\n";
  //   act.action = SURRENDER;
  //   return act;
  // }

  // get random result
  uniform_int_distribution<long long> dis(0, act_prob[7]);
  long long res = dis(gen);
  int i;
  for (i = 0; i < 8; i++) {
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
  tlog.push_back(st);
  return act;
}

int ComPlayer::getWeightIndex(Status &st) {
  int mh = conversion[st.myHand[LEFT]][st.myHand[RIGHT]];
  int eh = conversion[st.enemyHand[LEFT]][st.enemyHand[RIGHT]] * 14;
  if (mh == -1 || eh == -8) {
    cout << "invalid index\n";
    return -1;
  }
  return (mh + eh) * 8;
}

void ComPlayer::victory() {
  for (auto i : tlog) {
    // prob[getWeightIndex(tlog[i])] += STUDYCOEFF * i;
    if (prob[getWeightIndex(i)] < 253 - STUDYCOEFF)
      prob[getWeightIndex(i)] += STUDYCOEFF;
    else
      prob[getWeightIndex(i)] = 253;
  }
}

void ComPlayer::defeat() {
  for (auto i : tlog) {
    // weight[getWeightIndex(tlog[i])] -= STUDYCOEFF * i;
    if (prob[getWeightIndex(i)] >= STUDYCOEFF)
      prob[getWeightIndex(i)] -= STUDYCOEFF;
    else
      prob[getWeightIndex(i)] = 0;
  }
}

void ComPlayer::draw() {}

void ComPlayer::reset() {
  this->Player::reset();
  prevAction = -1;
  turncount = 0;
}