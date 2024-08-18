#include "Player.hh"

class Player;

class ComPlayer : public Player {
private:
  typedef struct {
    int action[8] = {
        0,
    };
  } Weight;
  Weight weight[225];
  string datafile;
  bool printTurn = false;

public:
  ComPlayer(char *filename, bool printTurn) {
    ifstream fin(filename);
    datafile = filename;
    if (!fin.is_open()) {
      cout << "Can't load data from " << filename << endl;
      exit(0);
    }
    fin >> *this;
    this->printTurn = printTurn;
  }

  ~ComPlayer() {
    ofstream fout(datafile);
    if (!fout.is_open()) {
      cout << "Failed to save data";
    } else {
      fout << *this;
    }
  }

  Action play(Status st);

  friend std::ostream &operator<<(std::ostream &out, const ComPlayer &cpd) {
    for (int i = 0; i < 225; i++) {
      for (int j = 0; j < 8; j++) {
        out << cpd.weight[i].action[j] << ' ';
      }
      out << '\n';
    }
    return out;
  }

  friend std::istream &operator>>(std::istream &in, ComPlayer &cpd) {
    for (int i = 0; i < 225; i++) {
      for (int j = 0; j < 8; j++) {
        in >> cpd.weight[i].action[j];
      }
    }
    return in;
  }
};