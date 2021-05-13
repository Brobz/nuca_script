// NucaScript VM
// To compile: g++ main.cpp -o out_file_path

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// QUADS //
vector<vector<string>> QUADS = {
										{"GOTO", "_", "_", "26"},
										{"*", "b", "a", "t0"},
										{"+", "a", "t0", "t1"},
										{"=", "_", "t1", "a"},
										{"WR", "_", "_", "a"},
										{"WR", "_", "_", "b"},
										{"+", "a", "b", "t2"},
										{"WR", "_", "_", "t2"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "b", "i"},
										{">", "i", "0", "t0"},
										{"GTF", "_", "t0", "25"},
										{"*", "b", "i", "t1"},
										{"+", "a", "t1", "t2"},
										{"+", "t2", "b", "t3"},
										{"=", "_", "t3", "a"},
										{"ERA", "_", "_", "uno"},
										{"*", "i", "2", "t4"},
										{"PARAM", "t4", "_", "1"},
										{"GOSUB", "uno", "_", "_"},
										{"=", "_", "uno", "t5"},
										{"WR", "_", "_", "a"},
										{"-", "i", "1", "t6"},
										{"=", "_", "t6", "i"},
										{"GOTO", "_", "_", "10"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "3", "a"},
										{"+", "a", "1", "t0"},
										{"=", "_", "t0", "b"},
										{"WR", "_", "_", "a"},
										{"WR", "_", "_", "b"},
										{"=", "_", "3.14", "f"},
										{"ERA", "_", "_", "dos"},
										{"*", "b", "2", "t1"},
										{"+", "a", "t1", "t2"},
										{"PARAM", "t2", "_", "1"},
										{"PARAM", "b", "_", "2"},
										{"*", "3", "3", "t3"},
										{"PARAM", "t3", "_", "3"},
										{"GOSUB", "dos", "_", "_"},
										{"=", "_", "dos", "t4"},
										{"WR", "_", "_", "a"},
										{"WR", "_", "_", "b"},
										{"*", "f", "2", "t5"},
										{"+", "t5", "1", "t6"},
										{"WR", "_", "_", "t6"},
										{"END", "_", "_", "_"},
										};
// QUADS //

int main () {
  cout << "GENERATED QUADS:" << endl;
  for(int i = 0; i < QUADS.size(); i++){
    cout << i << ": " << QUADS[i][0] << " " << QUADS[i][1] << " " << QUADS[i][2] << " " << QUADS[i][3] << endl;
  }
  return 0;
}
