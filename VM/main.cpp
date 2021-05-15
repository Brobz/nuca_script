// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include "MemoryMap.h"
#include "MemoryMapSignature.h"

using namespace std;

/*/

-> Quads indices will be structured in a way that we can tell global from scoped variables and temps from vars apart

/*/

// MEMORY //
vector<MemoryMapSignature> MEMORY_MAP_SIGN = {
										MemoryMapSignature("PATITO", {{2,1,0,0}, {4,2,0,0}}),
										MemoryMapSignature("dos", {{4,0,0,0}, {5,0,0,1}}),
										MemoryMapSignature("uno", {{1,0,0,0}, {3,0,0,0}}),
										};
// MEMORY //

// QUADS //
vector<vector<string>> QUADS = {
										{"GOTO", "_", "_", "25"},
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
										{"GTF", "_", "t0", "24"},
										{"*", "b", "i", "t1"},
										{"+", "a", "t1", "t2"},
										{"+", "t2", "b", "t3"},
										{"=", "_", "t3", "a"},
										{"ERA", "_", "_", "uno"},
										{"*", "i", "2", "t4"},
										{"PARAM", "t4", "_", "1"},
										{"GOSUB", "uno", "_", "_"},
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
										{"WR", "_", "_", "a"},
										{"WR", "_", "_", "b"},
										{"*", "f", "2", "t5"},
										{"+", "t5", "1", "t6"},
										{"WR", "_", "_", "t6"},
										{"END", "_", "_", "_"},
										};
// QUADS //


stack<MemoryMap> MEMORY_STACK;

int main () {

  MEMORY_STACK.push(MemoryMap(MEMORY_MAP_SIGN[0].signature[0], MEMORY_MAP_SIGN[0].signature[1]));

  for(int i = 0; i < QUADS.size(); i++){
    cout << i << ": " << QUADS[i][0] << " " << QUADS[i][1] << " " << QUADS[i][2] << " " << QUADS[i][3] << endl;
  }
  MEMORY_STACK.top().local_mem.printout();
  MEMORY_STACK.top().temp_mem.printout();
  return 0;
}
