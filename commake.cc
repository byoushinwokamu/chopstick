#include <fstream>

using namespace std;

int main(int argv, char **argc) {
  ofstream fout(argc[1]);
  for (int i = 0; i < 196; i++) {
    for (int j = 0; j < 8; j++) {
      fout << 128 << ' ';
    }
    fout << '\n';
  }
  return 0;
}