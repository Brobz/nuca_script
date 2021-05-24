// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryContext.h"
#include "Value.h"

using namespace std;


// MEMORY //
const int MAX_CONSTANTS = 3000, MAX_SYMBOLS = 5000, MAX_TMP_SYMBOLS = 5000, MAX_OBJ_SYMBOLS = 5000, MAX_OBJ_TMP_SYMBOLS = 5000, VAR_TYPES = 5, MEMORY_STACK_LIMIT = 100000;

const map<int, vector<vector<int>>> MEMORY_CONTEXT_SIGN = {
										{48, {{140,0,0,0,1}, {133,1,0,0,1}, {16,0,6,0,0}}},
										{26, {{2,0,0,0,0}, {7,0,0,1,0}}},
										{45, {{1,0,0,0,0}, {1,0,0,0,0}}},
										{1, {{0,0,0,0,0}, {0,0,0,0,0}}},
										{3, {{2,0,0,0,0}, {6,2,1,2,0}}},
										};
// MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{0, "100"},
										{1, "3"},
										{2, "10"},
										{3, "0"},
										{4, "1"},
										{6000, "HI"},
										{5, "96"},
										{6, "2"},
										{7, "5"},
										{8, "93"},
										{9, "7"},
										{10, "25"},
										{11, "157"},
										{12, "95"},
										{13, "20"},
										{14, "30"},
										{6001, "mult:"},
										{15, "28"},
										{6002, "------------------"},
										{6003, ">>  Elements to read (max 100):\n-- "},
										{6004, "you read:"},
										{6005, "elements"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{23, -1, -1, 48},
										{0, 0, 2, 15137},
										{25, -1, -1, -1},
										{0, 0, 3, 65001},
										{7, 65001, 65000, 105000},
										{24, -1, 105000, 25},
										{20, -1, -1, 65001},
										{15, -1, 65001, 0},
										{0, -1, 65001, 90001},
										{14, 15000, 90001, 95000},
										{0, 1, 95000, 95001},
										{16, -1, -1, 1},
										{18, -1, -1, 1},
										{0, 0, 15137, 90002},
										{6, 95001, 90002, 105001},
										{15, -1, 105001, 0},
										{0, -1, 105001, 90003},
										{14, 15000, 90003, 90004},
										{0, 1, 90004, 90005},
										{3, 90005, 6000, 100000},
										{20, -1, -1, 100000},
										{22, -1, -1, -1},
										{1, 65001, 4, 90000},
										{0, 0, 90000, 65001},
										{23, -1, -1, 4},
										{25, -1, -1, -1},
										{0, 0, 3, 65001},
										{7, 65001, 65000, 105000},
										{24, -1, 105000, 39},
										{20, -1, -1, 65001},
										{15, -1, 65001, 0},
										{0, -1, 65001, 90001},
										{14, 15000, 90001, 90002},
										{0, 1, 90002, 90003},
										{20, -1, -1, 90003},
										{22, -1, -1, -1},
										{1, 65001, 4, 90000},
										{0, 0, 90000, 65001},
										{23, -1, -1, 27},
										{15, -1, 5, 0},
										{0, -1, 5, 90004},
										{14, 15000, 90004, 90005},
										{0, 1, 90005, 90006},
										{0, 0, 90006, 15138},
										{25, -1, -1, -1},
										{3, 65000, 6, 90000},
										{0, 0, 90000, 15139},
										{25, -1, -1, -1},
										{0, 0, 60000, 35000},
										{15, -1, 7, 0},
										{0, -1, 7, 40000},
										{14, 15000, 40000, 45000},
										{0, 2, 8, 45000},
										{16, -1, -1, 3},
										{17, -1, 9, 65000},
										{18, -1, -1, 3},
										{0, 0, 6, 15136},
										{20, -1, -1, 15136},
										{22, -1, -1, -1},
										{15, -1, 15136, 0},
										{0, -1, 15136, 40001},
										{14, 15000, 40001, 40002},
										{0, 2, 6, 40002},
										{15, -1, 15136, 0},
										{0, -1, 15136, 40003},
										{14, 15000, 40003, 40004},
										{0, 1, 40004, 40005},
										{20, -1, -1, 40005},
										{22, -1, -1, -1},
										{15, -1, 6, 1},
										{0, -1, 6, 40007},
										{3, 40007, 1, 40007},
										{1, 40006, 40007, 40006},
										{15, -1, 6, 1},
										{1, 40006, 6, 40006},
										{14, 15100, 40006, 40008},
										{0, 2, 2, 40008},
										{15, -1, 3, 1},
										{0, -1, 3, 40010},
										{3, 40010, 1, 40010},
										{1, 40009, 40010, 40009},
										{15, -1, 6, 1},
										{1, 40009, 6, 40009},
										{14, 15100, 40009, 40011},
										{16, -1, -1, 45},
										{15, -1, 15136, 0},
										{0, -1, 15136, 40012},
										{14, 15000, 40012, 40013},
										{0, 1, 40013, 40014},
										{2, -1, 40014, 40015},
										{3, 40015, 2, 40016},
										{17, -1, 40016, 65000},
										{18, -1, -1, 45},
										{0, 0, 15139, 40017},
										{0, 2, 40017, 40011},
										{15, -1, 3, 1},
										{0, -1, 3, 40019},
										{3, 40019, 1, 40019},
										{1, 40018, 40019, 40018},
										{15, -1, 3, 1},
										{1, 40018, 3, 40018},
										{14, 15100, 40018, 40020},
										{1, 10, 1, 40021},
										{0, 2, 40021, 40020},
										{15, -1, 3, 1},
										{0, -1, 3, 40023},
										{3, 40023, 1, 40023},
										{1, 40022, 40023, 40022},
										{15, -1, 3, 1},
										{1, 40022, 3, 40022},
										{14, 15100, 40022, 40024},
										{0, 1, 40024, 40025},
										{20, -1, -1, 40025},
										{15, -1, 3, 1},
										{0, -1, 3, 40027},
										{3, 40027, 1, 40027},
										{1, 40026, 40027, 40026},
										{15, -1, 6, 1},
										{1, 40026, 6, 40026},
										{14, 15100, 40026, 40028},
										{0, 1, 40028, 40029},
										{20, -1, -1, 40029},
										{15, -1, 6, 1},
										{0, -1, 6, 40031},
										{3, 40031, 1, 40031},
										{1, 40030, 40031, 40030},
										{15, -1, 3, 1},
										{1, 40030, 3, 40030},
										{14, 15100, 40030, 40032},
										{0, 1, 40032, 40033},
										{20, -1, -1, 40033},
										{15, -1, 4, 1},
										{0, -1, 4, 40035},
										{3, 40035, 1, 40035},
										{1, 40034, 40035, 40034},
										{15, -1, 4, 1},
										{1, 40034, 4, 40034},
										{14, 15100, 40034, 40036},
										{0, 1, 40036, 40037},
										{20, -1, -1, 40037},
										{15, -1, 6, 1},
										{0, -1, 6, 40039},
										{3, 40039, 1, 40039},
										{1, 40038, 40039, 40038},
										{15, -1, 3, 1},
										{1, 40038, 3, 40038},
										{14, 15100, 40038, 40040},
										{0, 1, 40040, 40041},
										{20, -1, -1, 40041},
										{15, -1, 6, 1},
										{0, -1, 6, 40043},
										{3, 40043, 1, 40043},
										{1, 40042, 40043, 40042},
										{15, -1, 6, 1},
										{1, 40042, 6, 40042},
										{14, 15100, 40042, 40044},
										{0, 1, 40044, 40045},
										{20, -1, -1, 40045},
										{22, -1, -1, -1},
										{15, -1, 3, 1},
										{0, -1, 3, 40047},
										{3, 40047, 1, 40047},
										{1, 40046, 40047, 40046},
										{15, -1, 6, 1},
										{1, 40046, 6, 40046},
										{14, 15100, 40046, 40048},
										{16, -1, -1, 45},
										{15, -1, 15136, 0},
										{0, -1, 15136, 40049},
										{14, 15000, 40049, 40050},
										{0, 1, 40050, 40051},
										{2, -1, 40051, 40052},
										{3, 40052, 11, 40053},
										{17, -1, 40053, 65000},
										{18, -1, -1, 45},
										{0, 0, 15139, 40054},
										{0, 2, 40054, 40048},
										{15, -1, 12, 0},
										{0, -1, 12, 40055},
										{14, 15000, 40055, 40056},
										{15, -1, 3, 1},
										{0, -1, 3, 40058},
										{3, 40058, 1, 40058},
										{1, 40057, 40058, 40057},
										{15, -1, 3, 1},
										{1, 40057, 3, 40057},
										{14, 15100, 40057, 40059},
										{0, 1, 40059, 40060},
										{0, 2, 40060, 40056},
										{15, -1, 2, 0},
										{0, -1, 2, 40061},
										{14, 15000, 40061, 40062},
										{0, 2, 3, 40062},
										{15, -1, 13, 0},
										{0, -1, 13, 40063},
										{14, 15000, 40063, 40064},
										{0, 2, 4, 40064},
										{15, -1, 14, 0},
										{0, -1, 14, 40065},
										{14, 15000, 40065, 40066},
										{0, 2, 6, 40066},
										{20, -1, -1, 6001},
										{15, -1, 14, 0},
										{0, -1, 14, 40067},
										{14, 15000, 40067, 40068},
										{0, 1, 40068, 40069},
										{15, -1, 13, 0},
										{0, -1, 13, 40070},
										{14, 15000, 40070, 40071},
										{0, 1, 40071, 40072},
										{2, -1, 40072, 40073},
										{3, 40069, 40073, 40074},
										{20, -1, -1, 40074},
										{22, -1, -1, -1},
										{15, -1, 3, 1},
										{0, -1, 3, 40076},
										{3, 40076, 1, 40076},
										{1, 40075, 40076, 40075},
										{15, -1, 3, 1},
										{1, 40075, 3, 40075},
										{14, 15100, 40075, 40077},
										{0, 1, 40077, 40078},
										{15, -1, 40078, 0},
										{0, -1, 40078, 40079},
										{14, 15000, 40079, 40080},
										{15, -1, 14, 0},
										{0, -1, 14, 40081},
										{14, 15000, 40081, 40082},
										{0, 1, 40082, 40083},
										{15, -1, 13, 0},
										{0, -1, 13, 40084},
										{14, 15000, 40084, 40085},
										{0, 1, 40085, 40086},
										{3, 40083, 40086, 40087},
										{15, -1, 3, 1},
										{0, -1, 3, 40089},
										{3, 40089, 1, 40089},
										{1, 40088, 40089, 40088},
										{15, -1, 40087, 1},
										{1, 40088, 40087, 40088},
										{14, 15100, 40088, 40090},
										{0, 1, 40090, 40091},
										{0, 2, 40091, 40080},
										{15, -1, 15, 0},
										{0, -1, 15, 40092},
										{14, 15000, 40092, 40093},
										{0, 1, 40093, 40094},
										{20, -1, -1, 40094},
										{22, -1, -1, -1},
										{15, -1, 12, 0},
										{0, -1, 12, 40095},
										{14, 15000, 40095, 40096},
										{0, 1, 40096, 40097},
										{20, -1, -1, 40097},
										{22, -1, -1, -1},
										{20, -1, -1, 6002},
										{22, -1, -1, -1},
										{15, -1, 3, 1},
										{0, -1, 3, 40099},
										{3, 40099, 1, 40099},
										{3, 40099, 1, 40099},
										{1, 40098, 40099, 40098},
										{15, -1, 3, 1},
										{0, -1, 3, 40100},
										{3, 40100, 1, 40100},
										{1, 40098, 40100, 40098},
										{15, -1, 3, 1},
										{1, 40098, 3, 40098},
										{14, 15109, 40098, 40101},
										{0, 2, 1, 40101},
										{15, -1, 3, 1},
										{0, -1, 3, 40103},
										{3, 40103, 1, 40103},
										{3, 40103, 1, 40103},
										{1, 40102, 40103, 40102},
										{15, -1, 3, 1},
										{0, -1, 3, 40104},
										{3, 40104, 1, 40104},
										{1, 40102, 40104, 40102},
										{15, -1, 3, 1},
										{1, 40102, 3, 40102},
										{14, 15109, 40102, 40105},
										{0, 1, 40105, 40106},
										{20, -1, -1, 40106},
										{15, -1, 3, 1},
										{0, -1, 3, 40108},
										{3, 40108, 1, 40108},
										{3, 40108, 1, 40108},
										{1, 40107, 40108, 40107},
										{15, -1, 4, 1},
										{0, -1, 4, 40109},
										{3, 40109, 1, 40109},
										{1, 40107, 40109, 40107},
										{15, -1, 6, 1},
										{1, 40107, 6, 40107},
										{14, 15109, 40107, 40110},
										{0, 1, 40110, 40111},
										{20, -1, -1, 40111},
										{15, -1, 3, 1},
										{0, -1, 3, 40113},
										{3, 40113, 1, 40113},
										{3, 40113, 1, 40113},
										{1, 40112, 40113, 40112},
										{15, -1, 6, 1},
										{0, -1, 6, 40114},
										{3, 40114, 1, 40114},
										{1, 40112, 40114, 40112},
										{15, -1, 6, 1},
										{1, 40112, 6, 40112},
										{14, 15109, 40112, 40115},
										{0, 1, 40115, 40116},
										{20, -1, -1, 40116},
										{15, -1, 4, 1},
										{0, -1, 4, 40118},
										{3, 40118, 1, 40118},
										{3, 40118, 1, 40118},
										{1, 40117, 40118, 40117},
										{15, -1, 6, 1},
										{0, -1, 6, 40119},
										{3, 40119, 1, 40119},
										{1, 40117, 40119, 40117},
										{15, -1, 3, 1},
										{1, 40117, 3, 40117},
										{14, 15109, 40117, 40120},
										{0, 1, 40120, 40121},
										{20, -1, -1, 40121},
										{15, -1, 6, 1},
										{0, -1, 6, 40123},
										{3, 40123, 1, 40123},
										{3, 40123, 1, 40123},
										{1, 40122, 40123, 40122},
										{15, -1, 6, 1},
										{0, -1, 6, 40124},
										{3, 40124, 1, 40124},
										{1, 40122, 40124, 40122},
										{15, -1, 6, 1},
										{1, 40122, 6, 40122},
										{14, 15109, 40122, 40125},
										{0, 1, 40125, 40126},
										{20, -1, -1, 40126},
										{22, -1, -1, -1},
										{20, -1, -1, 6002},
										{22, -1, -1, -1},
										{20, -1, -1, 6003},
										{21, -1, -1, -1},
										{15, -1, 5, 0},
										{0, -1, 5, 40127},
										{14, 15000, 40127, 40128},
										{19, -1, 1, 40128},
										{20, -1, -1, 6004},
										{16, -1, -1, 26},
										{15, -1, 5, 0},
										{0, -1, 5, 40129},
										{14, 15000, 40129, 40130},
										{0, 1, 40130, 40131},
										{17, -1, 40131, 65000},
										{18, -1, -1, 26},
										{0, 0, 15138, 40132},
										{20, -1, -1, 40132},
										{20, -1, -1, 6005},
										{22, -1, -1, -1},
										{26, -1, -1, -1},
										};
// QUADS //

// GLOBAL VARS //
int PROGRAM_START; // Quad index of the start of main()
bool RUNNING = false;
int IP; // Instruction Pointer
MemoryContext GLOBAL_MEM;
MemoryContext* LOCAL_MEM;
MemoryContext* THIS_MEM;
stack<MemoryContext> MEMORY_STACK;
// GLOBAL VARS //


// HELPER METHODS //
const map<string, bool> STOB_MAP = {
							{"true", 1},
							{"True", 1},
							{"false", 0},
							{"False", 0},
};

// Safe String to Int
int s_stoi(string s){
	try{
		return stoi(s);
	}catch(...){
			cout << ">> Error: Cannot resolve stoi(" << s << ")" << endl;
			exit(EXIT_FAILURE);
		}
}

// Safe String to Float
float s_stof(string s){
	try{
		return stof(s);
	}catch(...){
			cout << ">> Error: Cannot resolve stof(" << s << ")" << endl;
			exit(EXIT_FAILURE);
		}
	}

// Safe String to Bool
bool s_stob(string s){
	try{
		return stoi(s);
	}catch(...){
			if (STOB_MAP.count(s)){
				return STOB_MAP.at(s);
			}else{
				cout << ">> Error: Cannot resolve stob(" << s << ")" << endl;
				exit(EXIT_FAILURE);
			}
	}
}

string mem_index_to_mem_sign(int index){
  if (index < MAX_CONSTANTS * VAR_TYPES){ // CONSTANTS
		string mem_sign = "0" + to_string(index / MAX_CONSTANTS) + "0";
		return mem_sign;
  }
  else if (index < MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES){ // GLOBALS
		string mem_sign = "1" + to_string(((index - MAX_CONSTANTS * VAR_TYPES) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - MAX_CONSTANTS * VAR_TYPES) >= MAX_SYMBOLS * VAR_TYPES) ? "1" : "0";
		return mem_sign;
  }
  else if (index < MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2){ // LOCALS
		string mem_sign = "2" + to_string(((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES)) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES) >= MAX_SYMBOLS * VAR_TYPES)) ? "1" : "0";
		return mem_sign;
  }
	else{ // OBJECT
		string mem_sign = "3" + to_string(((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2)) / MAX_OBJ_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2) >= MAX_OBJ_SYMBOLS * VAR_TYPES)) ? "1" : "0";
		return mem_sign;
	}

  // ERROR! Nothing was written
  cout << ">> Error: could not locate "  << index << " in memory" << endl;
  exit(EXIT_FAILURE);
}

int mem_sign_to_index_displacement(string mem_sign){
	int index_displacement = 0;
	int mem_class = mem_sign[0] - '0', var_type = mem_sign[1] - '0', is_temp = mem_sign[2] - '0';

	switch (mem_class) {
		case 1: // GLOBAL
		{
			index_displacement += MAX_CONSTANTS * VAR_TYPES;
		} break;
		case 2: // LOCAL
		{
			index_displacement += MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES;
		} break;
		case 3: // OBJECT
		{
			index_displacement += MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2;
		} break;
	}

	int type_displacement_mult = (mem_class) ? MAX_SYMBOLS : MAX_CONSTANTS;

	index_displacement += var_type * type_displacement_mult;
	index_displacement += (is_temp) ? MAX_SYMBOLS * VAR_TYPES : 0;

	return index_displacement;
}

// HELPER METHODS //

Value read_from_memory(int index){
  string mem_sign = mem_index_to_mem_sign(index);
  if(mem_sign[0] == '2'){
    if (!LOCAL_MEM->active){
      cout << ">> Error: No local context to read "  << index << " from memory" << endl;
      exit(EXIT_FAILURE); // ERROR! No context to read local variable from
    }
  }

  Value v;
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
    case 0:
      {
        v.set_i(GLOBAL_MEM.const_mem.ints[index]);
      }
      break;
    case 10:
      {
        v.set_f(GLOBAL_MEM.const_mem.floats[index - index_displacement]);
      }
      break;
    case 20:
      {
        v.set_s(GLOBAL_MEM.const_mem.strings[index - index_displacement]);
      }
      break;
    case 30:
      {
        v.set_b(GLOBAL_MEM.const_mem.booleans[index - index_displacement]);
      }
      break;
		case 40:
      {
				cout << ">> Cannot read case 40" << endl;
				exit(EXIT_FAILURE);
      }
      break;
    case 100:
      {
        v.set_i(GLOBAL_MEM.local_mem.ints[index - index_displacement]);
      }
      break;
    case 110:
      {
        v.set_f(GLOBAL_MEM.local_mem.floats[index - index_displacement]);
      }
      break;
    case 120:
      {
        v.set_s(GLOBAL_MEM.local_mem.strings[index - index_displacement]);
      }
      break;
    case 130:
      {
        v.set_b(GLOBAL_MEM.local_mem.booleans[index - index_displacement]);
      }
      break;
		case 140:
      {
				cout << ">> Cannot read case 140" << endl;
				exit(EXIT_FAILURE);
      }
      break;
    case 101:
      {
        v.set_i(GLOBAL_MEM.temp_mem.ints[index - index_displacement]);
      }
      break;
    case 111:
      {
        v.set_f(GLOBAL_MEM.temp_mem.floats[index - index_displacement]);
      }
      break;
    case 121:
      {
        v.set_s(GLOBAL_MEM.temp_mem.strings[index - index_displacement]);
      }
      break;
    case 131:
      {
        v.set_b(GLOBAL_MEM.temp_mem.booleans[index - index_displacement]);
      }
      break;
		case 141:
      {
				cout << ">> Cannot read case 141" << endl;
				exit(EXIT_FAILURE);
      }
      break;
    case 200:
      {
        v.set_i(LOCAL_MEM->local_mem.ints[index - index_displacement]);
      }
      break;
    case 210:
      {
        v.set_f(LOCAL_MEM->local_mem.floats[index - index_displacement]);
      }
      break;
    case 220:
      {
        v.set_s(LOCAL_MEM->local_mem.strings[index - index_displacement]);
      }
      break;
    case 230:
      {
        v.set_b(LOCAL_MEM->local_mem.booleans[index - index_displacement]);
      }
      break;
		case 240:
      {
				cout << ">> Cannot read case 240" << endl;
				exit(EXIT_FAILURE);
      }
      break;
    case 201:
      {
        v.set_i(LOCAL_MEM->temp_mem.ints[index - index_displacement]);
      }
      break;
    case 211:
      {
        v.set_f(LOCAL_MEM->temp_mem.floats[index - index_displacement]);
      }
      break;
    case 221:
      {
        v.set_s(LOCAL_MEM->temp_mem.strings[index - index_displacement]);
      }
      break;
    case 231:
      {
        v.set_b(LOCAL_MEM->temp_mem.booleans[index - index_displacement]);
      }
      break;
		case 241:
      {
				cout << ">> Cannot read case 241" << endl;
				exit(EXIT_FAILURE);
      }
      break;
		case 300:
			{
				cout << ">> Cannot read case 300" << endl;
				exit(EXIT_FAILURE);
			}
		case 310:
			{
				cout << ">> Cannot read case 310" << endl;
				exit(EXIT_FAILURE);
			}
		case 320:
			{
				cout << ">> Cannot read case 320" << endl;
				exit(EXIT_FAILURE);
			}
		case 330:
			{
				cout << ">> Cannot read case 330" << endl;
				exit(EXIT_FAILURE);
			}
		case 340:
			{
				cout << ">> Cannot read case 340" << endl;
				exit(EXIT_FAILURE);
			}
		case 301:
			{
				cout << ">> Cannot read case 301" << endl;
				exit(EXIT_FAILURE);
			}
		case 311:
			{
				cout << ">> Cannot read case 311" << endl;
				exit(EXIT_FAILURE);
			}
		case 321:
			{
				cout << ">> Cannot read case 321" << endl;
				exit(EXIT_FAILURE);
			}
		case 331:
			{
				cout << ">> Cannot read case 331" << endl;
				exit(EXIT_FAILURE);
			}
		case 341:
			{
				cout << ">> Cannot read case 341" << endl;
				exit(EXIT_FAILURE);
			}
    default:
    {
      // ERROR! Nothing was read
      cout << ">> Error: could not read "  << index << " from memory" << endl;
      exit(EXIT_FAILURE);
    }
  }

  return v;
}

int write_to_memory(int index, string value){
  string mem_sign = mem_index_to_mem_sign(index);

	if(mem_sign[0] == '2'){
    if (!LOCAL_MEM->active){
      cout << ">> Error: No local context to write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE); // ERROR! No context to write local variable to
    }
  }

	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
    case 0:
      {
        GLOBAL_MEM.const_mem.ints[index] = s_stoi(value);
      }
      break;
    case 10:
      {
        GLOBAL_MEM.const_mem.floats[index - index_displacement] = s_stof(value);
      }
      break;
    case 20:
      {
        GLOBAL_MEM.const_mem.strings[index - index_displacement] = value;
      }
      break;
    case 30:
      {
        GLOBAL_MEM.const_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 40:
      {
				cout << ">> Cannot write case 40" << endl;
				exit(EXIT_FAILURE);
      }
      break;
    case 100:
      {
        GLOBAL_MEM.local_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 110:
      {
        GLOBAL_MEM.local_mem.floats[index - index_displacement] = s_stof(value);
      }
      break;
    case 120:
      {
        GLOBAL_MEM.local_mem.strings[index - index_displacement] = value;
      }
      break;
    case 130:
      {
        GLOBAL_MEM.local_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 140:
      {
				cout << ">> Cannot write case 140" << endl;
				exit(EXIT_FAILURE);
      }
      break;
    case 101:
      {
        GLOBAL_MEM.temp_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 111:
      {
        GLOBAL_MEM.temp_mem.floats[index - index_displacement] = s_stof(value);
      }
      break;
    case 121:
      {
        GLOBAL_MEM.temp_mem.strings[index - index_displacement] = value;
      }
      break;
    case 131:
      {
        GLOBAL_MEM.temp_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 141:
      {
				cout << ">> Cannot write case 141" << endl;
				exit(EXIT_FAILURE);
      }
      break;
    case 200:
      {
      	LOCAL_MEM->local_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 210:
      {
      	LOCAL_MEM->local_mem.floats[index - index_displacement] = s_stof(value);
      }
      break;
    case 220:
      {
      	LOCAL_MEM->local_mem.strings[index - index_displacement] = value;
      }
      break;
    case 230:
      {
      	LOCAL_MEM->local_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 240:
      {
				cout << ">> Cannot write case 240" << endl;
				exit(EXIT_FAILURE);
      }
      break;
    case 201:
      {
      	LOCAL_MEM->temp_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 211:
      {
      	LOCAL_MEM->temp_mem.floats[index - index_displacement] = s_stof(value);
      }
      break;
    case 221:
      {
      	LOCAL_MEM->temp_mem.strings[index - index_displacement] = value;
      }
      break;
    case 231:
      {
      	LOCAL_MEM->temp_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 241:
      {
				cout << ">> Cannot write case 241" << endl;
				exit(EXIT_FAILURE);
      }
      break;
		case 300:
			{
				cout << ">> Cannot write case 300" << endl;
				exit(EXIT_FAILURE);
			}
		case 310:
			{
				cout << ">> Cannot write case 310" << endl;
				exit(EXIT_FAILURE);
			}
		case 320:
			{
				cout << ">> Cannot write case 320" << endl;
				exit(EXIT_FAILURE);
			}
		case 330:
			{
				cout << ">> Cannot write case 330" << endl;
				exit(EXIT_FAILURE);
			}
		case 340:
			{
				cout << ">> Cannot write case 340" << endl;
				exit(EXIT_FAILURE);
			}
		case 301:
			{
				cout << ">> Cannot write case 301" << endl;
				exit(EXIT_FAILURE);
			}
		case 311:
			{
				cout << ">> Cannot write case 311" << endl;
				exit(EXIT_FAILURE);
			}
		case 321:
			{
				cout << ">> Cannot write case 321" << endl;
				exit(EXIT_FAILURE);
			}
		case 331:
			{
				cout << ">> Cannot write case 331" << endl;
				exit(EXIT_FAILURE);
			}
		case 341:
			{
				cout << ">> Cannot write case 341" << endl;
				exit(EXIT_FAILURE);
			}
    default:
    {
      // ERROR! Nothing was written
      return 1;
    }
  }

  return 0; // Success!
}

void write_to_param(int index, string value){
	string mem_sign = mem_index_to_mem_sign(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << ">> Error: No local context to write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE); // ERROR! No context to write local variable to
    }
  }

	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
		case 200:
      {
        MEMORY_STACK.top().local_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 210:
      {
        MEMORY_STACK.top().local_mem.floats[index - index_displacement] = s_stof(value);
      }
      break;
    case 220:
      {
        MEMORY_STACK.top().local_mem.strings[index - index_displacement] = value;
      }
      break;
    case 230:
      {
        MEMORY_STACK.top().local_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		default:
			{
				// ERROR! Nothing was written
	      cout << ">> Error: could not write "  << value << " to param at " << index << endl;
	      exit(EXIT_FAILURE);
			}
			break;
	}
}

void setup(){

	// WRITE CONSTANTS TO MEMORY //

	for (auto const& pair : CONSTANTS){
		if (write_to_memory(pair.first, pair.second)){
      cout << ">> Error writting " << pair.second << " to " << pair.first << endl;
      exit(EXIT_FAILURE);
    }
  }

	// SET INITIAL VALUES FOR GLOBAL VARS //

	RUNNING = true; // This will get the instruction pointer movin through the quads
  IP = 0; // Start execution at the first QUAD
	LOCAL_MEM = new MemoryContext(); // Initialize LOCAL_MEM without parameters so that LOCAL_MEM->active is set to false
}

void run(){
  while(RUNNING){
    int op = QUADS[IP][0];

		if (!op){
			// =

			int  is_ptr = QUADS[IP][1];
			int result_dir;
			Value value;

			if (is_ptr == 1 || is_ptr == 3) value = read_from_memory(read_from_memory(QUADS[IP][2]).i);
			else value = read_from_memory(QUADS[IP][2]);

			if (is_ptr == 2 || is_ptr == 3) result_dir = read_from_memory(QUADS[IP][3]).i;
			else result_dir = QUADS[IP][3];

			write_to_memory(result_dir, value.to_str());

			IP++;
			continue;
		}

		else if (op <= 13){
			// Arithmetic Epxressions (unary and binary)

			int result_dir = QUADS[IP][3];

			Value left_value, right_value;

			// May be a unary expression
			if (QUADS[IP][1] >= 0){
				left_value = read_from_memory(QUADS[IP][1]);
			}

			right_value = read_from_memory(QUADS[IP][2]);

			switch (op) {
				case 1:				// +
					{
						// Sum!
						Value res_value = left_value + right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 2:				// -
					{
						Value res_value;
						if (left_value.has_value())
							// Subtract !
							res_value = left_value - right_value;
						else
							// Negate !
							res_value = -right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 3:				// *
					{
						// Mutiply!
						Value res_value = left_value * right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 4:				// /
					{
						// Divide!
						Value res_value = left_value / right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 5:				// ==
					{
						// Compare (equals to)!
						Value res_value = left_value == right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 6:				// >
					{
						// Compare (bigger than)!
						Value res_value = left_value > right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 7:				// <
					{
						// Compare (less than)!
						Value res_value = left_value < right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 8:				// >=
					{
						// Compare (bigger than or equal to)!
						Value res_value = left_value >= right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 9:				// <=
					{
						// Compare (less than or equal to)!
						Value res_value = left_value <= right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 10:			// &&
					{
						// Compare (and)!
						Value res_value = left_value && right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 11:			// ||
					{
						// Compare (or)!
						Value res_value = left_value || right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 12:			// !=
					{
						// Compare (not equal to)!
						Value res_value = !(left_value == right_value);
						write_to_memory(result_dir, res_value.to_str());
					}
					break;
				case 13:			// !
					{
						// Negate!
						Value res_value = !right_value;
						write_to_memory(result_dir, res_value.to_str());
						IP++;
					}
					break;
			}
			IP++;
			continue;
		}

    switch(op) {
			// Other operations

			case 14:			// ACCESS
        {
					int result_dir = QUADS[IP][3];

					Value arr_dir = QUADS[IP][1];
					Value access_value = read_from_memory(QUADS[IP][2]);

					Value result = arr_dir + access_value;

					write_to_memory(result_dir, result.to_str());
					IP++;
        }
        break;

			case 15:			// ARR_BNDS
        {

					Value arr_access_value = read_from_memory(QUADS[IP][2]);
					Value arr_dim_size = read_from_memory(QUADS[IP][3]);

					if (arr_access_value.i < 0 || arr_access_value.i >= arr_dim_size.i){
						// If this point is reached, an array index out of bounds error has ocurred
						cout << ">> Error: array index out of bounds!" << endl;
						exit(EXIT_FAILURE);
					}

					// Else, continue execution
					IP++;
        }
        break;

			case 16:		// ERA
				{
					int func_start_addr = QUADS[IP][3];
					if (MEMORY_STACK.size() > MEMORY_STACK_LIMIT){
						// Too many functions on the stack!
						cout << ">> Error: Memory Stack Limit reached (infinite recursion?). Terminating..." << endl;
						exit(EXIT_FAILURE);
					}

					MEMORY_STACK.push(MemoryContext(MEMORY_CONTEXT_SIGN.at(func_start_addr).at(0), MEMORY_CONTEXT_SIGN.at(func_start_addr).at(1)));
					IP++;
				}
				break;

			case 17:		// PARAM
				{
					Value param_value = read_from_memory(QUADS[IP][2]);
					int param_addr = QUADS[IP][3];

					write_to_param(param_addr, param_value.to_str());
					IP++;
				}
				break;

			case 18:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);
					IP = func_start_addr;
				}
				break;

			case 19:		// READ
				{

					int result_dir;
					int dir_is_ptr = QUADS[IP][2];

					if (dir_is_ptr == 1) result_dir = read_from_memory(QUADS[IP][3]).i;
					else result_dir = QUADS[IP][3];

					string user_input;
					cin >> user_input;

					write_to_memory(result_dir, user_input);

					IP++;
				}
				break;

			case 20:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (LOCAL_MEM->active) LOCAL_MEM->add_to_print_buffer(printable.to_str());
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str());
					IP++;
				}
				break;

      case 21:			// PRNT
        {
          string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 22:			// PRNTLN
        {
					string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable << endl;
          IP++;
        }
        break;

      case 23:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 24:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 25:			// ENDFNC
				{
					int return_addr = LOCAL_MEM->return_addr;
					MEMORY_STACK.pop();
					LOCAL_MEM = (MEMORY_STACK.size()) ? &(MEMORY_STACK.top()) : new MemoryContext();
					IP = return_addr;
				}
				break;

      case 26:			// END
        {
          RUNNING = false;
        }
        break;

      default:
        {
        cout << ">> Error: Unknown Op: " << op << endl;
        exit(EXIT_FAILURE);
        }
    }
  }
}

int main () {

  // Memory signature with highest value is always pointing to the start of the main() method (no function can syntactically come after the main)
  PROGRAM_START = MEMORY_CONTEXT_SIGN.rbegin()->first;

  // Generates global memory context
  GLOBAL_MEM = MemoryContext(MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(0), MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(1), MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(2));

  // Setup virtual machine to run the program
  setup();

  // Run program
  run();

  return 0;
}
