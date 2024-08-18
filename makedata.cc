#include "ComPlayer.cc"
#include <fstream>
#include <iostream>

using namespace std;

ComPlayer cpd;

int main(int argv, char **argc) {
  ofstream fout(argc[1]);
  if (fout.is_open()) {
    cout << "HI\n";
    fout << cpd;
  }
  return 0;
}