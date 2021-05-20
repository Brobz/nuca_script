// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryMap.h"
#include "Value.h"

using namespace std;


// MEMORY //
const int MAX_CONSTANTS = 1000, MAX_SYMBOLS = 3000, MAX_TMP_SYMBOLS = 3000, VAR_TYPES = 4, MEMORY_STACK_LIMIT = 100000;

const map<int, vector<vector<int>>> MEMORY_MAP_SIGN = {
										{11, {{138,0,0,0}, {118,0,0,0}, {11,0,2,0}}},
										{1, {{2,0,0,0}, {1,0,0,1}}},
										{8, {{1,0,0,0}, {1,0,0,0}}},
										};
// MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{0, "100"},
										{1, "3"},
										{2, "0"},
										{3, "10"},
										{4, "1"},
										{5, "2"},
										{6, "25"},
										{7, "95"},
										{8, "20"},
										{9, "30"},
										{2000, "mult:"},
										{10, "28"},
										{2001, "------------------"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{23, -1, -1, 11},
										{0, -1, 2, 28001},
										{7, 28001, 3, 49000},
										{24, -1, 49000, 7},
										{1, 28001, 4, 40000},
										{0, -1, 40000, 28001},
										{23, -1, -1, 2},
										{25, -1, -1, -1},
										{3, 28000, 5, 40000},
										{0, -1, 40000, 4137},
										{25, -1, -1, -1},
										{0, -1, 5, 4136},
										{20, -1, -1, 4136},
										{22, -1, -1, -1},
										{15, -1, 4136, 0},
										{1, 16000, 4136, 16000},
										{14, 4000, 16000, 16001},
										{0, 2, 4, 16001},
										{15, -1, 4136, 0},
										{1, 16002, 4136, 16002},
										{14, 4000, 16002, 16003},
										{0, 1, 16003, 16004},
										{20, -1, -1, 16004},
										{22, -1, -1, -1},
										{15, -1, 5, 1},
										{0, -1, 5, 16006},
										{3, 16006, 1, 16006},
										{1, 16005, 16006, 16005},
										{15, -1, 5, 1},
										{1, 16005, 5, 16005},
										{14, 4100, 16005, 16007},
										{0, 2, 3, 16007},
										{15, -1, 2, 1},
										{0, -1, 2, 16009},
										{3, 16009, 1, 16009},
										{1, 16008, 16009, 16008},
										{15, -1, 5, 1},
										{1, 16008, 5, 16008},
										{14, 4100, 16008, 16010},
										{16, -1, -1, 8},
										{17, -1, 4136, 28000},
										{18, -1, -1, 8},
										{0, -1, 4137, 16011},
										{0, 2, 16011, 16010},
										{15, -1, 2, 1},
										{0, -1, 2, 16013},
										{3, 16013, 1, 16013},
										{1, 16012, 16013, 16012},
										{15, -1, 2, 1},
										{1, 16012, 2, 16012},
										{14, 4100, 16012, 16014},
										{1, 6, 1, 16015},
										{0, 2, 16015, 16014},
										{15, -1, 2, 0},
										{1, 16016, 2, 16016},
										{14, 4000, 16016, 16017},
										{0, 1, 16017, 16018},
										{20, -1, -1, 16018},
										{15, -1, 5, 0},
										{1, 16019, 5, 16019},
										{14, 4000, 16019, 16020},
										{0, 1, 16020, 16021},
										{20, -1, -1, 16021},
										{15, -1, 2, 1},
										{0, -1, 2, 16023},
										{3, 16023, 1, 16023},
										{1, 16022, 16023, 16022},
										{15, -1, 2, 1},
										{1, 16022, 2, 16022},
										{14, 4100, 16022, 16024},
										{0, 1, 16024, 16025},
										{20, -1, -1, 16025},
										{15, -1, 2, 1},
										{0, -1, 2, 16027},
										{3, 16027, 1, 16027},
										{1, 16026, 16027, 16026},
										{15, -1, 5, 1},
										{1, 16026, 5, 16026},
										{14, 4100, 16026, 16028},
										{0, 1, 16028, 16029},
										{20, -1, -1, 16029},
										{15, -1, 5, 1},
										{0, -1, 5, 16031},
										{3, 16031, 1, 16031},
										{1, 16030, 16031, 16030},
										{15, -1, 2, 1},
										{1, 16030, 2, 16030},
										{14, 4100, 16030, 16032},
										{0, 1, 16032, 16033},
										{20, -1, -1, 16033},
										{15, -1, 4, 1},
										{0, -1, 4, 16035},
										{3, 16035, 1, 16035},
										{1, 16034, 16035, 16034},
										{15, -1, 4, 1},
										{1, 16034, 4, 16034},
										{14, 4100, 16034, 16036},
										{0, 1, 16036, 16037},
										{20, -1, -1, 16037},
										{15, -1, 5, 1},
										{0, -1, 5, 16039},
										{3, 16039, 1, 16039},
										{1, 16038, 16039, 16038},
										{15, -1, 2, 1},
										{1, 16038, 2, 16038},
										{14, 4100, 16038, 16040},
										{0, 1, 16040, 16041},
										{20, -1, -1, 16041},
										{15, -1, 5, 1},
										{0, -1, 5, 16043},
										{3, 16043, 1, 16043},
										{1, 16042, 16043, 16042},
										{15, -1, 5, 1},
										{1, 16042, 5, 16042},
										{14, 4100, 16042, 16044},
										{0, 1, 16044, 16045},
										{20, -1, -1, 16045},
										{22, -1, -1, -1},
										{15, -1, 7, 0},
										{1, 16046, 7, 16046},
										{14, 4000, 16046, 16047},
										{15, -1, 2, 1},
										{0, -1, 2, 16049},
										{3, 16049, 1, 16049},
										{1, 16048, 16049, 16048},
										{15, -1, 2, 1},
										{1, 16048, 2, 16048},
										{14, 4100, 16048, 16050},
										{0, 1, 16050, 16051},
										{0, 2, 16051, 16047},
										{15, -1, 3, 0},
										{1, 16052, 3, 16052},
										{14, 4000, 16052, 16053},
										{0, 2, 2, 16053},
										{15, -1, 8, 0},
										{1, 16054, 8, 16054},
										{14, 4000, 16054, 16055},
										{0, 2, 4, 16055},
										{15, -1, 9, 0},
										{1, 16056, 9, 16056},
										{14, 4000, 16056, 16057},
										{0, 2, 5, 16057},
										{20, -1, -1, 2000},
										{15, -1, 9, 0},
										{1, 16058, 9, 16058},
										{14, 4000, 16058, 16059},
										{0, 1, 16059, 16060},
										{15, -1, 8, 0},
										{1, 16061, 8, 16061},
										{14, 4000, 16061, 16062},
										{0, 1, 16062, 16063},
										{2, -1, 16063, 16064},
										{3, 16060, 16064, 16065},
										{20, -1, -1, 16065},
										{22, -1, -1, -1},
										{15, -1, 2, 1},
										{0, -1, 2, 16067},
										{3, 16067, 1, 16067},
										{1, 16066, 16067, 16066},
										{15, -1, 2, 1},
										{1, 16066, 2, 16066},
										{14, 4100, 16066, 16068},
										{0, 1, 16068, 16069},
										{15, -1, 16069, 0},
										{1, 16070, 16069, 16070},
										{14, 4000, 16070, 16071},
										{15, -1, 9, 0},
										{1, 16072, 9, 16072},
										{14, 4000, 16072, 16073},
										{0, 1, 16073, 16074},
										{15, -1, 8, 0},
										{1, 16075, 8, 16075},
										{14, 4000, 16075, 16076},
										{0, 1, 16076, 16077},
										{3, 16074, 16077, 16078},
										{15, -1, 2, 1},
										{0, -1, 2, 16080},
										{3, 16080, 1, 16080},
										{1, 16079, 16080, 16079},
										{15, -1, 16078, 1},
										{1, 16079, 16078, 16079},
										{14, 4100, 16079, 16081},
										{0, 1, 16081, 16082},
										{0, 2, 16082, 16071},
										{15, -1, 10, 0},
										{1, 16083, 10, 16083},
										{14, 4000, 16083, 16084},
										{0, 1, 16084, 16085},
										{20, -1, -1, 16085},
										{22, -1, -1, -1},
										{15, -1, 7, 0},
										{1, 16086, 7, 16086},
										{14, 4000, 16086, 16087},
										{0, 1, 16087, 16088},
										{20, -1, -1, 16088},
										{22, -1, -1, -1},
										{20, -1, -1, 2001},
										{22, -1, -1, -1},
										{15, -1, 2, 1},
										{0, -1, 2, 16090},
										{3, 16090, 1, 16090},
										{3, 16090, 1, 16090},
										{1, 16089, 16090, 16089},
										{15, -1, 2, 1},
										{0, -1, 2, 16091},
										{3, 16091, 1, 16091},
										{1, 16089, 16091, 16089},
										{15, -1, 2, 1},
										{1, 16089, 2, 16089},
										{14, 4109, 16089, 16092},
										{0, 2, 1, 16092},
										{15, -1, 2, 1},
										{0, -1, 2, 16094},
										{3, 16094, 1, 16094},
										{3, 16094, 1, 16094},
										{1, 16093, 16094, 16093},
										{15, -1, 2, 1},
										{0, -1, 2, 16095},
										{3, 16095, 1, 16095},
										{1, 16093, 16095, 16093},
										{15, -1, 2, 1},
										{1, 16093, 2, 16093},
										{14, 4109, 16093, 16096},
										{0, 1, 16096, 16097},
										{20, -1, -1, 16097},
										{15, -1, 2, 1},
										{0, -1, 2, 16099},
										{3, 16099, 1, 16099},
										{3, 16099, 1, 16099},
										{1, 16098, 16099, 16098},
										{15, -1, 4, 1},
										{0, -1, 4, 16100},
										{3, 16100, 1, 16100},
										{1, 16098, 16100, 16098},
										{15, -1, 5, 1},
										{1, 16098, 5, 16098},
										{14, 4109, 16098, 16101},
										{0, 1, 16101, 16102},
										{20, -1, -1, 16102},
										{15, -1, 2, 1},
										{0, -1, 2, 16104},
										{3, 16104, 1, 16104},
										{3, 16104, 1, 16104},
										{1, 16103, 16104, 16103},
										{15, -1, 5, 1},
										{0, -1, 5, 16105},
										{3, 16105, 1, 16105},
										{1, 16103, 16105, 16103},
										{15, -1, 5, 1},
										{1, 16103, 5, 16103},
										{14, 4109, 16103, 16106},
										{0, 1, 16106, 16107},
										{20, -1, -1, 16107},
										{15, -1, 4, 1},
										{0, -1, 4, 16109},
										{3, 16109, 1, 16109},
										{3, 16109, 1, 16109},
										{1, 16108, 16109, 16108},
										{15, -1, 5, 1},
										{0, -1, 5, 16110},
										{3, 16110, 1, 16110},
										{1, 16108, 16110, 16108},
										{15, -1, 2, 1},
										{1, 16108, 2, 16108},
										{14, 4109, 16108, 16111},
										{0, 1, 16111, 16112},
										{20, -1, -1, 16112},
										{15, -1, 5, 1},
										{0, -1, 5, 16114},
										{3, 16114, 1, 16114},
										{3, 16114, 1, 16114},
										{1, 16113, 16114, 16113},
										{15, -1, 5, 1},
										{0, -1, 5, 16115},
										{3, 16115, 1, 16115},
										{1, 16113, 16115, 16113},
										{15, -1, 5, 1},
										{1, 16113, 5, 16113},
										{14, 4109, 16113, 16116},
										{0, 1, 16116, 16117},
										{20, -1, -1, 16117},
										{22, -1, -1, -1},
										{26, -1, -1, -1},
										};
// QUADS //

// GLOBAL VARS //
int PROGRAM_START; // Quad index of the start of main()
bool RUNNING = false;
int IP; // Instruction Pointer
MemoryMap GLOBAL_MEM;
MemoryMap* LOCAL_MEM;
stack<MemoryMap> MEMORY_STACK;
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
  else{ // LOCALS
		string mem_sign = "2" + to_string(((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES)) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES) >= MAX_SYMBOLS * VAR_TYPES)) ? "1" : "0";
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
	LOCAL_MEM = new MemoryMap(); // Initialize LOCAL_MEM without parameters so that LOCAL_MEM->active is set to false
}

void run(){
  while(RUNNING){
    int op = QUADS[IP][0];

		if (!op){
			// =

			int  is_ptr = QUADS[IP][1];
			int result_dir;
			Value value;

			if (is_ptr == 1 || is_ptr == 3) {
				value = read_from_memory(read_from_memory(QUADS[IP][2]).i);
			}else{
				value = read_from_memory(QUADS[IP][2]);
			}

			if (is_ptr == 2 || is_ptr == 3){
				result_dir = read_from_memory(QUADS[IP][3]).i;
			}else{
				result_dir = QUADS[IP][3];
			}

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

					MEMORY_STACK.push(MemoryMap(MEMORY_MAP_SIGN.at(func_start_addr).at(0), MEMORY_MAP_SIGN.at(func_start_addr).at(1)));
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

					int result_dir = QUADS[IP][3];

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
					LOCAL_MEM = (MEMORY_STACK.size()) ? &(MEMORY_STACK.top()) : new MemoryMap();
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
  PROGRAM_START = MEMORY_MAP_SIGN.rbegin()->first;

  // Generates global memory map
  GLOBAL_MEM = MemoryMap(MEMORY_MAP_SIGN.at(PROGRAM_START).at(0), MEMORY_MAP_SIGN.at(PROGRAM_START).at(1), MEMORY_MAP_SIGN.at(PROGRAM_START).at(2));

  // Setup virtual machine to run the program
  setup();

  // Run program
  run();

  return 0;
}
