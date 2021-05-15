// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryMap.h"

using namespace std;

/*/
-> Quads indices will be structured in a way that we can tell global from scoped variables and temps from vars apart
/*/

// MEMORY //
map<string, vector<vector<int>>> MEMORY_MAP_SIGN = {
										{"PATITO", {{2,1,0,0}, {4,2,0,0}, {4,1,0,0}}},
										{"uno", {{1,0,0,0}, {3,0,0,0}}},
										{"dos", {{4,0,0,0}, {5,0,0,1}}},
										};
// MEMORY //

// CONSTANTS //
map<int, string> CONSTANTS = {
										{0, "0"},
										{1, "2"},
										{2, "1"},
										{3, "3"},
										{250, "3.14"},
										};
// CONSTANTS //

// QUADS //
vector<vector<string>> QUADS = {
										{"GOTO", "_", "_", "25"},
										{"*", "1001", "9000", "13000"},
										{"+", "9000", "13000", "13001"},
										{"=", "_", "13001", "9000"},
										{"WR", "_", "_", "9000"},
										{"WR", "_", "_", "1001"},
										{"+", "9000", "1001", "13002"},
										{"WR", "_", "_", "13002"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "9001", "9003"},
										{">", "9003", "0", "16000"},
										{"GTF", "_", "16000", "24"},
										{"*", "9001", "9003", "13000"},
										{"+", "9000", "13000", "13001"},
										{"+", "13001", "9001", "13002"},
										{"=", "_", "13002", "9000"},
										{"ERA", "_", "_", "uno"},
										{"*", "9003", "1", "13003"},
										{"PARAM", "13003", "_", "1"},
										{"GOSUB", "uno", "_", "_"},
										{"WR", "_", "_", "9000"},
										{"-", "9003", "2", "13004"},
										{"=", "_", "13004", "9003"},
										{"GOTO", "_", "_", "10"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "3", "1000"},
										{"+", "1000", "2", "5000"},
										{"=", "_", "5000", "1001"},
										{"WR", "_", "_", "1000"},
										{"WR", "_", "_", "1001"},
										{"=", "_", "250", "2000"},
										{"ERA", "_", "_", "dos"},
										{"*", "1001", "1", "5001"},
										{"+", "1000", "5001", "5002"},
										{"PARAM", "5002", "_", "1"},
										{"PARAM", "1001", "_", "2"},
										{"*", "3", "3", "5003"},
										{"PARAM", "5003", "_", "3"},
										{"GOSUB", "dos", "_", "_"},
										{"WR", "_", "_", "1000"},
										{"WR", "_", "_", "1001"},
										{"*", "2000", "1", "6000"},
										{"+", "6000", "2", "6001"},
										{"WR", "_", "_", "6001"},
										{"END", "_", "_", "_"},
										};
// QUADS //

// GLOBAL VARS //
string PROGRAM_NAME;
MemoryMap GLOBAL_MEM;
stack<MemoryMap> MEMORY_STACK;
// GLOBAL VARS //

int main () {

  // First memory signature is always GLOBAL scope
  PROGRAM_NAME = MEMORY_MAP_SIGN.begin()->first;

  // Pushes GLOBAL memory into the stack
  GLOBAL_MEM = MemoryMap(MEMORY_MAP_SIGN[PROGRAM_NAME][0], MEMORY_MAP_SIGN[PROGRAM_NAME][1]);

  for(int i = 0; i < QUADS.size(); i++){
    cout << i << ": " << QUADS[i][0] << " " << QUADS[i][1] << " " << QUADS[i][2] << " " << QUADS[i][3] << endl;
  }

  GLOBAL_MEM.local_mem.printout();
  GLOBAL_MEM.temp_mem.printout();

  return 0;
}
