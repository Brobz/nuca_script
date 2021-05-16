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


int write_to_memory(int index, string value){
  if (index < 1000){ // CONSTANTS
    if (index < 250){
      GLOBAL_MEM.const_mem.ints[index] = stoi(value);
    }
    else if (index < 500){
      GLOBAL_MEM.const_mem.floats[index - 250] = stof(value);
    }
    else if (index < 750){
      GLOBAL_MEM.const_mem.strings[index - 500] = value;
    }
    else{
      GLOBAL_MEM.const_mem.booleans[index - 750] = stoi(value);
    }
    return 0;
  }
  else if (index < 9000){ // GLOBALS
    // VARIABLES
    if (index < 2000){
      GLOBAL_MEM.local_mem.ints[index] = stoi(value);
    }
    else if (index < 3000){
      GLOBAL_MEM.local_mem.floats[index - 2000] = stof(value);
    }
    else if (index < 4000){
      GLOBAL_MEM.local_mem.strings[index - 3000] = value;
    }
    else if (index < 5000){
      GLOBAL_MEM.local_mem.booleans[index - 4000] = stoi(value);
    }
    // TEMPS
    else if (index < 6000){
      GLOBAL_MEM.temp_mem.ints[index] = stoi(value);
    }
    else if (index < 7000){
      GLOBAL_MEM.temp_mem.floats[index - 6000] = stof(value);
    }
    else if (index < 8000){
      GLOBAL_MEM.temp_mem.strings[index - 7000] = value;
    }
    else {
      GLOBAL_MEM.temp_mem.booleans[index - 8000] = stoi(value);
    }
    return 0;
  }
  else{ // LOCALS
    // VARIABLES
    if (index < 10000){
      MEMORY_STACK.top().local_mem.ints[index] = stoi(value);
    }
    else if (index < 11000){
      MEMORY_STACK.top().local_mem.floats[index - 10000] = stof(value);
    }
    else if (index < 12000){
      MEMORY_STACK.top().local_mem.strings[index - 11000] = value;
    }
    else if (index < 13000){
      MEMORY_STACK.top().local_mem.booleans[index - 12000] = stoi(value);
    }
    // TEMPS
    else if (index < 14000){
      MEMORY_STACK.top().temp_mem.ints[index] = stoi(value);
    }
    else if (index < 15000){
      MEMORY_STACK.top().temp_mem.floats[index - 14000] = stof(value);
    }
    else if (index < 16000){
      MEMORY_STACK.top().temp_mem.strings[index - 15000] = value;
    }
    else {
      MEMORY_STACK.top().temp_mem.booleans[index - 16000] = stoi(value);
    }
    return 0;
  }

  // ERROR! Nothing was written
  return 1;
}

void setup(){
  for (auto const& pair : CONSTANTS){
    if (write_to_memory(pair.first, pair.second)){
      cout << "Error writting " << pair.second << " to " << pair.first << endl;
      abort();
    }
  }
}

int main () {

  // First memory signature is always GLOBAL scope
  PROGRAM_NAME = MEMORY_MAP_SIGN.begin()->first;

  // Pushes GLOBAL memory into the stack
  GLOBAL_MEM = MemoryMap(MEMORY_MAP_SIGN[PROGRAM_NAME][0], MEMORY_MAP_SIGN[PROGRAM_NAME][1], MEMORY_MAP_SIGN[PROGRAM_NAME][2]);

  // Write constants to memory
  setup();

  for(int i = 0; i < QUADS.size(); i++){
    cout << i << ": " << QUADS[i][0] << " " << QUADS[i][1] << " " << QUADS[i][2] << " " << QUADS[i][3] << endl;
  }

  GLOBAL_MEM.const_mem.printout();

  return 0;
}
