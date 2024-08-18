#include "ComPlayerData.hh"
#include <fstream>
#include <iostream>

using namespace std;

ComPlayer cpd;

int main() {
  // fstream file;
  // file.open("./data", ios::binary);
  ofstream fout("./data");
  if (fout.is_open())
    fout << cpd;
  return 0;
}