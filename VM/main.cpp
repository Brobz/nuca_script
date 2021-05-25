// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryContext.h"
#include "Value.h"

using namespace std;

// MEMORY_CONSTRAINTS //
const int MAX_CONSTANTS = 3000, MAX_SYMBOLS = 5000, MAX_TMP_SYMBOLS = 5000, MAX_OBJ_SYMBOLS = 5000, VAR_TYPES = 5, MEMORY_STACK_LIMIT = 100000;
// MEMORY_CONSTRAINTS //

// FUNCTION_MEMORY //
const map<int, vector<vector<int>>> FUNCTION_MEMORY_CONTEXT_SIGN = {
										{48, {{140,0,0,0,1}, {146,1,0,0,1}, {18,0,6,0,0}}},
										{26, {{2,0,0,0,0}, {7,0,0,1,0}}},
										{45, {{1,0,0,0,0}, {1,0,0,0,0}}},
										{1, {{0,0,0,0,0}, {0,0,0,0,0}}},
										{3, {{2,0,0,0,0}, {7,1,1,2,0}}},
										};
// FUNCTION_MEMORY //


// OBJECT_MEMORY //
const map<int, vector<int>> OBJECT_MEMORY_CONTEXT_SIGN = {
										{2, {100,100,0,0,0}},
										};
// OBJECT_MEMORY //

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
										{8, "6"},
										{9, "92"},
										{10, "93"},
										{11, "7"},
										{12, "25"},
										{13, "157"},
										{14, "95"},
										{15, "20"},
										{16, "30"},
										{6001, "mult:"},
										{17, "28"},
										{6002, "------------------"},
										{6003, ">>  Elements to read (max 100):\n-- "},
										{6004, "you read:"},
										{6005, "elements"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{27, -1, -1, 48},
										{0, 0, 2, 15137},
										{29, -1, -1, 1},
										{0, 0, 3, 65001},
										{7, 65001, 65000, 105000},
										{28, -1, 105000, 25},
										{24, -1, -1, 65001},
										{15, -1, 65001, 0},
										{0, -1, 65001, 90001},
										{14, 120000, 90001, 90002},
										{17, -1, 90002, 95000, 1},
										{19, -1, -1, 1},
										{22, -1, -1, 1},
										{0, 0, 15137, 90003},
										{6, 95000, 90003, 105001},
										{15, -1, 105001, 0},
										{0, -1, 105001, 90004},
										{14, 15000, 90004, 90005},
										{0, 1, 90005, 90006},
										{3, 90006, 6000, 100000},
										{24, -1, -1, 100000},
										{26, -1, -1, -1},
										{1, 65001, 4, 90000},
										{0, 0, 90000, 65001},
										{27, -1, -1, 4},
										{29, -1, -1, 1},
										{0, 0, 3, 65001},
										{7, 65001, 65000, 105000},
										{28, -1, 105000, 39},
										{24, -1, -1, 65001},
										{15, -1, 65001, 0},
										{0, -1, 65001, 90001},
										{14, 15000, 90001, 90002},
										{0, 1, 90002, 90003},
										{24, -1, -1, 90003},
										{26, -1, -1, -1},
										{1, 65001, 4, 90000},
										{0, 0, 90000, 65001},
										{27, -1, -1, 27},
										{15, -1, 5, 0},
										{0, -1, 5, 90004},
										{14, 15000, 90004, 90005},
										{0, 1, 90005, 90006},
										{0, 0, 90006, 15138},
										{29, -1, -1, 0},
										{3, 65000, 6, 90000},
										{0, 0, 90000, 15139},
										{29, -1, -1, 0},
										{16, -1, 2, 60000},
										{0, 0, 60000, 35000},
										{15, -1, 7, 0},
										{0, -1, 7, 40000},
										{14, 115000, 40000, 40001},
										{18, 35000, 8, 40001, 2},
										{15, -1, 7, 0},
										{0, -1, 7, 40002},
										{14, 115000, 40002, 40003},
										{17, 35000, 40003, 40004, 1},
										{15, -1, 40004, 0},
										{0, -1, 40004, 40005},
										{14, 15000, 40005, 40006},
										{0, 2, 9, 40006},
										{15, -1, 7, 0},
										{0, -1, 7, 40007},
										{14, 120000, 40007, 40008},
										{18, 35000, 10, 40008, 2},
										{15, -1, 8, 0},
										{0, -1, 8, 40009},
										{14, 15000, 40009, 40010},
										{0, 1, 40010, 40011},
										{24, -1, -1, 40011},
										{15, -1, 7, 0},
										{0, -1, 7, 40012},
										{14, 120000, 40012, 40013},
										{17, 35000, 40013, 45000, 1},
										{24, -1, -1, 45000},
										{26, -1, -1, -1},
										{19, -1, -1, 3},
										{20, -1, 11, 65000},
										{22, -1, 35000, 3},
										{0, 0, 6, 15136},
										{24, -1, -1, 15136},
										{26, -1, -1, -1},
										{15, -1, 15136, 0},
										{0, -1, 15136, 40014},
										{14, 15000, 40014, 40015},
										{0, 2, 6, 40015},
										{15, -1, 15136, 0},
										{0, -1, 15136, 40016},
										{14, 15000, 40016, 40017},
										{0, 1, 40017, 40018},
										{24, -1, -1, 40018},
										{26, -1, -1, -1},
										{15, -1, 6, 1},
										{0, -1, 6, 40020},
										{3, 40020, 1, 40020},
										{1, 40019, 40020, 40019},
										{15, -1, 6, 1},
										{1, 40019, 6, 40019},
										{14, 15100, 40019, 40021},
										{0, 2, 2, 40021},
										{15, -1, 3, 1},
										{0, -1, 3, 40023},
										{3, 40023, 1, 40023},
										{1, 40022, 40023, 40022},
										{15, -1, 6, 1},
										{1, 40022, 6, 40022},
										{14, 15100, 40022, 40024},
										{19, -1, -1, 45},
										{15, -1, 15136, 0},
										{0, -1, 15136, 40025},
										{14, 15000, 40025, 40026},
										{0, 1, 40026, 40027},
										{2, -1, 40027, 40028},
										{3, 40028, 2, 40029},
										{20, -1, 40029, 65000},
										{21, -1, -1, 45},
										{0, 0, 15139, 40030},
										{0, 2, 40030, 40024},
										{15, -1, 3, 1},
										{0, -1, 3, 40032},
										{3, 40032, 1, 40032},
										{1, 40031, 40032, 40031},
										{15, -1, 3, 1},
										{1, 40031, 3, 40031},
										{14, 15100, 40031, 40033},
										{1, 12, 1, 40034},
										{0, 2, 40034, 40033},
										{15, -1, 3, 1},
										{0, -1, 3, 40036},
										{3, 40036, 1, 40036},
										{1, 40035, 40036, 40035},
										{15, -1, 3, 1},
										{1, 40035, 3, 40035},
										{14, 15100, 40035, 40037},
										{0, 1, 40037, 40038},
										{24, -1, -1, 40038},
										{15, -1, 3, 1},
										{0, -1, 3, 40040},
										{3, 40040, 1, 40040},
										{1, 40039, 40040, 40039},
										{15, -1, 6, 1},
										{1, 40039, 6, 40039},
										{14, 15100, 40039, 40041},
										{0, 1, 40041, 40042},
										{24, -1, -1, 40042},
										{15, -1, 6, 1},
										{0, -1, 6, 40044},
										{3, 40044, 1, 40044},
										{1, 40043, 40044, 40043},
										{15, -1, 3, 1},
										{1, 40043, 3, 40043},
										{14, 15100, 40043, 40045},
										{0, 1, 40045, 40046},
										{24, -1, -1, 40046},
										{15, -1, 4, 1},
										{0, -1, 4, 40048},
										{3, 40048, 1, 40048},
										{1, 40047, 40048, 40047},
										{15, -1, 4, 1},
										{1, 40047, 4, 40047},
										{14, 15100, 40047, 40049},
										{0, 1, 40049, 40050},
										{24, -1, -1, 40050},
										{15, -1, 6, 1},
										{0, -1, 6, 40052},
										{3, 40052, 1, 40052},
										{1, 40051, 40052, 40051},
										{15, -1, 3, 1},
										{1, 40051, 3, 40051},
										{14, 15100, 40051, 40053},
										{0, 1, 40053, 40054},
										{24, -1, -1, 40054},
										{15, -1, 6, 1},
										{0, -1, 6, 40056},
										{3, 40056, 1, 40056},
										{1, 40055, 40056, 40055},
										{15, -1, 6, 1},
										{1, 40055, 6, 40055},
										{14, 15100, 40055, 40057},
										{0, 1, 40057, 40058},
										{24, -1, -1, 40058},
										{26, -1, -1, -1},
										{15, -1, 3, 1},
										{0, -1, 3, 40060},
										{3, 40060, 1, 40060},
										{1, 40059, 40060, 40059},
										{15, -1, 6, 1},
										{1, 40059, 6, 40059},
										{14, 15100, 40059, 40061},
										{19, -1, -1, 45},
										{15, -1, 15136, 0},
										{0, -1, 15136, 40062},
										{14, 15000, 40062, 40063},
										{0, 1, 40063, 40064},
										{2, -1, 40064, 40065},
										{3, 40065, 13, 40066},
										{20, -1, 40066, 65000},
										{21, -1, -1, 45},
										{0, 0, 15139, 40067},
										{0, 2, 40067, 40061},
										{15, -1, 14, 0},
										{0, -1, 14, 40068},
										{14, 15000, 40068, 40069},
										{15, -1, 3, 1},
										{0, -1, 3, 40071},
										{3, 40071, 1, 40071},
										{1, 40070, 40071, 40070},
										{15, -1, 3, 1},
										{1, 40070, 3, 40070},
										{14, 15100, 40070, 40072},
										{0, 1, 40072, 40073},
										{0, 2, 40073, 40069},
										{15, -1, 2, 0},
										{0, -1, 2, 40074},
										{14, 15000, 40074, 40075},
										{0, 2, 3, 40075},
										{15, -1, 15, 0},
										{0, -1, 15, 40076},
										{14, 15000, 40076, 40077},
										{0, 2, 4, 40077},
										{15, -1, 16, 0},
										{0, -1, 16, 40078},
										{14, 15000, 40078, 40079},
										{0, 2, 6, 40079},
										{24, -1, -1, 6001},
										{15, -1, 16, 0},
										{0, -1, 16, 40080},
										{14, 15000, 40080, 40081},
										{0, 1, 40081, 40082},
										{15, -1, 15, 0},
										{0, -1, 15, 40083},
										{14, 15000, 40083, 40084},
										{0, 1, 40084, 40085},
										{2, -1, 40085, 40086},
										{3, 40082, 40086, 40087},
										{24, -1, -1, 40087},
										{26, -1, -1, -1},
										{15, -1, 3, 1},
										{0, -1, 3, 40089},
										{3, 40089, 1, 40089},
										{1, 40088, 40089, 40088},
										{15, -1, 3, 1},
										{1, 40088, 3, 40088},
										{14, 15100, 40088, 40090},
										{0, 1, 40090, 40091},
										{15, -1, 40091, 0},
										{0, -1, 40091, 40092},
										{14, 15000, 40092, 40093},
										{15, -1, 16, 0},
										{0, -1, 16, 40094},
										{14, 15000, 40094, 40095},
										{0, 1, 40095, 40096},
										{15, -1, 15, 0},
										{0, -1, 15, 40097},
										{14, 15000, 40097, 40098},
										{0, 1, 40098, 40099},
										{3, 40096, 40099, 40100},
										{15, -1, 3, 1},
										{0, -1, 3, 40102},
										{3, 40102, 1, 40102},
										{1, 40101, 40102, 40101},
										{15, -1, 40100, 1},
										{1, 40101, 40100, 40101},
										{14, 15100, 40101, 40103},
										{0, 1, 40103, 40104},
										{0, 2, 40104, 40093},
										{15, -1, 17, 0},
										{0, -1, 17, 40105},
										{14, 15000, 40105, 40106},
										{0, 1, 40106, 40107},
										{24, -1, -1, 40107},
										{26, -1, -1, -1},
										{15, -1, 14, 0},
										{0, -1, 14, 40108},
										{14, 15000, 40108, 40109},
										{0, 1, 40109, 40110},
										{24, -1, -1, 40110},
										{26, -1, -1, -1},
										{24, -1, -1, 6002},
										{26, -1, -1, -1},
										{15, -1, 3, 1},
										{0, -1, 3, 40112},
										{3, 40112, 1, 40112},
										{3, 40112, 1, 40112},
										{1, 40111, 40112, 40111},
										{15, -1, 3, 1},
										{0, -1, 3, 40113},
										{3, 40113, 1, 40113},
										{1, 40111, 40113, 40111},
										{15, -1, 3, 1},
										{1, 40111, 3, 40111},
										{14, 15109, 40111, 40114},
										{0, 2, 1, 40114},
										{15, -1, 3, 1},
										{0, -1, 3, 40116},
										{3, 40116, 1, 40116},
										{3, 40116, 1, 40116},
										{1, 40115, 40116, 40115},
										{15, -1, 3, 1},
										{0, -1, 3, 40117},
										{3, 40117, 1, 40117},
										{1, 40115, 40117, 40115},
										{15, -1, 3, 1},
										{1, 40115, 3, 40115},
										{14, 15109, 40115, 40118},
										{0, 1, 40118, 40119},
										{24, -1, -1, 40119},
										{15, -1, 3, 1},
										{0, -1, 3, 40121},
										{3, 40121, 1, 40121},
										{3, 40121, 1, 40121},
										{1, 40120, 40121, 40120},
										{15, -1, 4, 1},
										{0, -1, 4, 40122},
										{3, 40122, 1, 40122},
										{1, 40120, 40122, 40120},
										{15, -1, 6, 1},
										{1, 40120, 6, 40120},
										{14, 15109, 40120, 40123},
										{0, 1, 40123, 40124},
										{24, -1, -1, 40124},
										{15, -1, 3, 1},
										{0, -1, 3, 40126},
										{3, 40126, 1, 40126},
										{3, 40126, 1, 40126},
										{1, 40125, 40126, 40125},
										{15, -1, 6, 1},
										{0, -1, 6, 40127},
										{3, 40127, 1, 40127},
										{1, 40125, 40127, 40125},
										{15, -1, 6, 1},
										{1, 40125, 6, 40125},
										{14, 15109, 40125, 40128},
										{0, 1, 40128, 40129},
										{24, -1, -1, 40129},
										{15, -1, 4, 1},
										{0, -1, 4, 40131},
										{3, 40131, 1, 40131},
										{3, 40131, 1, 40131},
										{1, 40130, 40131, 40130},
										{15, -1, 6, 1},
										{0, -1, 6, 40132},
										{3, 40132, 1, 40132},
										{1, 40130, 40132, 40130},
										{15, -1, 3, 1},
										{1, 40130, 3, 40130},
										{14, 15109, 40130, 40133},
										{0, 1, 40133, 40134},
										{24, -1, -1, 40134},
										{15, -1, 6, 1},
										{0, -1, 6, 40136},
										{3, 40136, 1, 40136},
										{3, 40136, 1, 40136},
										{1, 40135, 40136, 40135},
										{15, -1, 6, 1},
										{0, -1, 6, 40137},
										{3, 40137, 1, 40137},
										{1, 40135, 40137, 40135},
										{15, -1, 6, 1},
										{1, 40135, 6, 40135},
										{14, 15109, 40135, 40138},
										{0, 1, 40138, 40139},
										{24, -1, -1, 40139},
										{26, -1, -1, -1},
										{24, -1, -1, 6002},
										{26, -1, -1, -1},
										{24, -1, -1, 6003},
										{25, -1, -1, -1},
										{15, -1, 5, 0},
										{0, -1, 5, 40140},
										{14, 15000, 40140, 40141},
										{23, -1, 1, 40141},
										{24, -1, -1, 6004},
										{19, -1, -1, 26},
										{15, -1, 5, 0},
										{0, -1, 5, 40142},
										{14, 15000, 40142, 40143},
										{0, 1, 40143, 40144},
										{20, -1, 40144, 65000},
										{21, -1, -1, 26},
										{0, 0, 15138, 40145},
										{24, -1, -1, 40145},
										{24, -1, -1, 6005},
										{26, -1, -1, -1},
										{30, -1, -1, -1},
										};
// QUADS //

// GLOBAL VARS //
int PROGRAM_START; // Quad index of the start of main()
bool RUNNING = false;
int IP; // Instruction Pointer
int THIS_OPERATOR_COUNTER; // To count how many this. accesses have happened
MemoryContext GLOBAL_MEM;
MemoryContext* LOCAL_MEM;
Memory* THIS_MEM;
stack<MemoryContext> MEMORY_STACK;
stack<Memory*> OBJECT_MEMORY_STACK;
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
	else{ // CLAS ATTRIBUTES
		string mem_sign = "3" + to_string(((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2)) / MAX_OBJ_SYMBOLS) % (VAR_TYPES - 1));
		mem_sign += "0"; // There are no temporal class attributes
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

	int temp_displacement = 0;

	if (is_temp) temp_displacement = MAX_SYMBOLS * VAR_TYPES;


	index_displacement += temp_displacement;

	return index_displacement;
}

// HELPER METHODS //

Memory* get_object_memory(int index){
	string mem_sign = mem_index_to_mem_sign(index);
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

	switch (int_mem_sign) {
		case 140:
			{
				return &(GLOBAL_MEM.local_mem.objects[index - index_displacement]);
			}
			break;
		case 141:
			{
				return &(GLOBAL_MEM.temp_mem.objects[index - index_displacement]);
			}
			break;
		case 240:
			{
				return &(LOCAL_MEM->local_mem.objects[index - index_displacement]);
			}
			break;
		case 241:
			{
				return &(LOCAL_MEM->temp_mem.objects[index - index_displacement]);
			}
			break;
		default:
		{
			cout << ">> Error: could not get memory for object at " << index << endl;
			exit(EXIT_FAILURE);
		}
	}
}

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
				Memory obj = GLOBAL_MEM.local_mem.objects[index - index_displacement];
        v.set_o(obj);
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
				Memory obj = GLOBAL_MEM.temp_mem.objects[index - index_displacement];
        v.set_o(obj);
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
				Memory obj = LOCAL_MEM->local_mem.objects[index - index_displacement];
        v.set_o(obj);
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
				Memory obj = LOCAL_MEM->temp_mem.objects[index - index_displacement];
        v.set_o(obj);
      }
      break;
    default:
    {
      // ERROR! Nothing was read
      cout << ">> Error: could not read "  << index << " from memory" << endl;
      exit(EXIT_FAILURE);
    }
  }
  return v;
}

Value read_from_memory(Memory* this_mem, int index){
  string mem_sign = mem_index_to_mem_sign(index);
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

	Value v;

  switch (int_mem_sign) {
		case 300:
      {
				v.set_i(this_mem->ints[index - index_displacement]);
      }
      break;
		case 310:
      {
				v.set_f(this_mem->floats[index - index_displacement]);
      }
      break;
		case 320:
      {
				v.set_s(this_mem->strings[index - index_displacement]);
      }
      break;
		case 330:
      {
				v.set_b(this_mem->booleans[index - index_displacement]);
      }
    	break;
		default:
    {
      // ERROR! Nothing was read
      cout << ">> Error: could not read from " << index << endl;
      exit(EXIT_FAILURE);
    }
	}

	return v;
}

void write_to_memory(int index, string value){
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
				GLOBAL_MEM.local_mem.objects[index - index_displacement] = Memory(OBJECT_MEMORY_CONTEXT_SIGN.at(s_stoi(value)), s_stoi(value));
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
				GLOBAL_MEM.temp_mem.objects[index - index_displacement] = Memory(OBJECT_MEMORY_CONTEXT_SIGN.at(s_stoi(value)), s_stoi(value));
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
				LOCAL_MEM->local_mem.objects[index - index_displacement] = Memory(OBJECT_MEMORY_CONTEXT_SIGN.at(s_stoi(value)), s_stoi(value));
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
				LOCAL_MEM->temp_mem.objects[index - index_displacement] = Memory(OBJECT_MEMORY_CONTEXT_SIGN.at(s_stoi(value)), s_stoi(value));
      }
      break;
    default:
    {
      // ERROR! Nothing was written
      cout << ">> Error: could not write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE);
    }
  }
}

void write_to_memory(Memory* this_mem, int index, string value){
  string mem_sign = mem_index_to_mem_sign(index);
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
		case 300:
      {
				this_mem->ints[index - index_displacement] = s_stoi(value);
      }
      break;
		case 310:
      {
				this_mem->floats[index - index_displacement] = s_stof(value);
      }
      break;
		case 320:
      {
				this_mem->strings[index - index_displacement] = value;
      }
      break;
		case 330:
      {
				this_mem->booleans[index - index_displacement] = s_stoi(value);
      }
    	break;
		default:
    {
      // ERROR! Nothing was written
      cout << ">> Error: could not write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE);
    }
	}
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
		write_to_memory(pair.first, pair.second);
  }

	// SET INITIAL VALUES FOR GLOBAL VARS //

	RUNNING = true; // This will get the instruction pointer movin through the quads
  IP = 0; // Start execution at the first QUAD
	THIS_OPERATOR_COUNTER = 0; // No this.have been seen yet
	LOCAL_MEM = new MemoryContext(); // Initialize LOCAL_MEM without parameters so that LOCAL_MEM->active is set to false
	THIS_MEM = new Memory();
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

			case 14:			// ARR_ACCESS
        {
					int result_dir = QUADS[IP][3];

					int arr_dir = QUADS[IP][1];
					int access_value = read_from_memory(QUADS[IP][2]).i;

					int result = arr_dir + access_value;

					write_to_memory(result_dir, to_string(result));
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

			case 16:			// OBJ_INST
        {
					int object_sign  = QUADS[IP][2];
					int obj_dir = QUADS[IP][3];

					write_to_memory(obj_dir, to_string(object_sign));

					IP++;
        }
        break;

			case 17:			// OBJ_READ
        {

					Memory* this_mem;
					Value result;

					int obj_dir = QUADS[IP][1];
					int object_var_dir = QUADS[IP][2];
					int result_dir = QUADS[IP][3];

					int ptr_value = -1;

					if (QUADS[IP].size() == 5){
						ptr_value = QUADS[IP][4];
					}

					if (ptr_value == 1 || ptr_value == 3) object_var_dir = read_from_memory(object_var_dir).i;

					if (ptr_value == 2 || ptr_value == 3) result_dir = read_from_memory(result_dir).i;

					if (obj_dir != -1) this_mem = get_object_memory(obj_dir);
					else this_mem = THIS_MEM;

					result = read_from_memory(this_mem, object_var_dir);

					write_to_memory(result_dir, result.to_str());
					IP++;
        }
        break;

			case 18:			// OBJ_WRITE
        {

				 	Memory* this_mem;
					Value value;

					int obj_dir = QUADS[IP][1];
					int value_dir = QUADS[IP][2];
					int obj_var_dir = QUADS[IP][3];
					int ptr_value = -1;

					if (QUADS[IP].size() == 5){
						ptr_value = QUADS[IP][4];
					}

					if (ptr_value == 1 || ptr_value == 3) value = read_from_memory(read_from_memory(value_dir).i);
					else value = read_from_memory(value_dir);

					if (ptr_value == 2 || ptr_value == 3) obj_var_dir = read_from_memory(obj_var_dir).i;


					if (obj_dir != -1) this_mem = get_object_memory(obj_dir);
					else this_mem = THIS_MEM;

					write_to_memory(this_mem, obj_var_dir, value.to_str());

					IP++;
        }
        break;

			case 19:		// ERA
				{
					int func_start_addr = QUADS[IP][3];
					if (MEMORY_STACK.size() > MEMORY_STACK_LIMIT){
						// Too many functions on the stack!
						cout << ">> Error: Memory Stack Limit of " << MEMORY_STACK_LIMIT << " reached (infinite recursion?) Terminating..." << endl;
						exit(EXIT_FAILURE);
					}

					MemoryContext new_memory_context = MemoryContext(FUNCTION_MEMORY_CONTEXT_SIGN.at(func_start_addr).at(0), FUNCTION_MEMORY_CONTEXT_SIGN.at(func_start_addr).at(1));
					new_memory_context.return_scope = (LOCAL_MEM->active) ? LOCAL_MEM : &GLOBAL_MEM;

					MEMORY_STACK.push(new_memory_context);
					IP++;
				}
				break;

			case 20:		// PARAM
				{

					Value param_value;

					int parent_obj_dir = QUADS[IP][1];
					int param_addr = QUADS[IP][3];

					if (parent_obj_dir != -1) param_value = read_from_memory(get_object_memory(parent_obj_dir), QUADS[IP][2]);
					else param_value = read_from_memory(QUADS[IP][2]);

					write_to_param(param_addr, param_value.to_str());
					IP++;
				}
				break;

			case 21:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);

					IP = func_start_addr;
				}
				break;

			case 22:		// OBJ_GOSUB
				{

					int object_dir = QUADS[IP][2];
					int func_start_addr = QUADS[IP][3];

					if (object_dir != -1){
						if (!OBJECT_MEMORY_STACK.size()){
							OBJECT_MEMORY_STACK.push(get_object_memory(object_dir));
						}else{
							Memory* new_class_memory = get_object_memory(object_dir);
							new_class_memory->return_memory = OBJECT_MEMORY_STACK.top();
							OBJECT_MEMORY_STACK.push(new_class_memory);
						}
						THIS_MEM = OBJECT_MEMORY_STACK.top();
					} else{
						THIS_OPERATOR_COUNTER++;
					}

					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);

					IP = func_start_addr;
				}
				break;

			case 23:		// READ
				{

					int result_dir;
					int parent_obj_dir = QUADS[IP][1];
					int dir_is_ptr = QUADS[IP][2];

					if (dir_is_ptr == 1) result_dir = read_from_memory(QUADS[IP][3]).i;
					else result_dir = QUADS[IP][3];

					string user_input;
					cin >> user_input;

					if (parent_obj_dir != -1)  write_to_memory(get_object_memory(parent_obj_dir), result_dir, user_input);
					else write_to_memory(result_dir, user_input);

					IP++;
				}
				break;

			case 24:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (LOCAL_MEM->active) LOCAL_MEM->add_to_print_buffer(printable.to_str());
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str());
					IP++;
				}
				break;

      case 25:			// PRNT
        {
          string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 26:			// PRNTLN
        {
					string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
					cout << printable << endl;
					IP++;
        }
        break;

      case 27:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 28:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 29:			// ENDFNC
				{

					int was_class_func = QUADS[IP][3];
					int return_addr = LOCAL_MEM->return_addr;

					if (THIS_OPERATOR_COUNTER <= 0 && was_class_func){
						THIS_MEM = (OBJECT_MEMORY_STACK.size()) ? OBJECT_MEMORY_STACK.top()->return_memory : new Memory();
						if (OBJECT_MEMORY_STACK.size()) OBJECT_MEMORY_STACK.pop();
					}else if (was_class_func) {
						THIS_OPERATOR_COUNTER--;
					}


					LOCAL_MEM = (MEMORY_STACK.size()) ? MEMORY_STACK.top().return_scope : new MemoryContext();
					if (MEMORY_STACK.size()) MEMORY_STACK.pop();


					IP = return_addr;
				}
				break;

      case 30:			// END
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
  PROGRAM_START = FUNCTION_MEMORY_CONTEXT_SIGN.rbegin()->first;

  // Generates global memory context
  GLOBAL_MEM = MemoryContext(FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(0), FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(1), FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(2));

  // Setup virtual machine to run the program
  setup();

  // Run program
  run();

  return 0;
}
