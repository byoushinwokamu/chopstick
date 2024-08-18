#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int weight[225];

int main() {
  // read weight data
  ifstream fin("./data");
  if (!fin.is_open()) {
    cout << "Can't load data" << endl;
    return 0;
  }
  for (int i = 0; i < 225; i++)
    fin >> weight[i];

  // main
  return 0;
}