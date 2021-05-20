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
										{11, {{138,0,0,0}, {119,0,0,0}, {13,0,1,0}}},
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
										{7, "6"},
										{8, "95"},
										{9, "20"},
										{10, "30"},
										{11, "28"},
										{2000, "------------------"},
										{12, "5"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{22, -1, -1, 11},
										{0, -1, 2, 28001},
										{7, 28001, 3, 49000},
										{23, -1, 49000, 7},
										{1, 28001, 4, 40000},
										{0, -1, 40000, 28001},
										{22, -1, -1, 2},
										{24, -1, -1, -1},
										{3, 28000, 5, 40000},
										{0, -1, 40000, 4137},
										{24, -1, -1, -1},
										{0, -1, 5, 4136},
										{19, -1, -1, 4136},
										{21, -1, -1, -1},
										{1, 16000, 4136, 16000},
										{14, 4000, 16000, 16001, 100},
										{0, 2, 4, 16001},
										{1, 16002, 4136, 16002},
										{14, 4000, 16002, 16003, 100},
										{0, 1, 16003, 16004},
										{19, -1, -1, 16004},
										{21, -1, -1, -1},
										{0, -1, 5, 16006},
										{3, 16006, 1, 16006},
										{1, 16005, 16006, 16005},
										{1, 16005, 5, 16005},
										{14, 4100, 16005, 16007, 9},
										{0, 2, 3, 16007},
										{0, -1, 2, 16009},
										{3, 16009, 1, 16009},
										{1, 16008, 16009, 16008},
										{1, 16008, 5, 16008},
										{14, 4100, 16008, 16010, 9},
										{15, -1, -1, 8},
										{16, -1, 4136, 28000},
										{17, -1, -1, 8},
										{0, -1, 4137, 16011},
										{0, 2, 16011, 16010},
										{0, -1, 2, 16013},
										{3, 16013, 1, 16013},
										{1, 16012, 16013, 16012},
										{1, 16012, 2, 16012},
										{14, 4100, 16012, 16014, 9},
										{1, 6, 1, 16015},
										{0, 2, 16015, 16014},
										{1, 16016, 2, 16016},
										{14, 4000, 16016, 16017, 100},
										{0, 1, 16017, 16018},
										{19, -1, -1, 16018},
										{1, 16019, 5, 16019},
										{14, 4000, 16019, 16020, 100},
										{0, 1, 16020, 16021},
										{19, -1, -1, 16021},
										{0, -1, 2, 16023},
										{3, 16023, 1, 16023},
										{1, 16022, 16023, 16022},
										{1, 16022, 2, 16022},
										{14, 4100, 16022, 16024, 9},
										{0, 1, 16024, 16025},
										{19, -1, -1, 16025},
										{0, -1, 2, 16027},
										{3, 16027, 1, 16027},
										{1, 16026, 16027, 16026},
										{1, 16026, 5, 16026},
										{14, 4100, 16026, 16028, 9},
										{0, 1, 16028, 16029},
										{19, -1, -1, 16029},
										{2, -1, 7, 16030},
										{0, -1, 5, 16032},
										{3, 16032, 1, 16032},
										{1, 16031, 16032, 16031},
										{1, 16031, 16030, 16031},
										{14, 4100, 16031, 16033, 9},
										{0, 1, 16033, 16034},
										{19, -1, -1, 16034},
										{0, -1, 4, 16036},
										{3, 16036, 1, 16036},
										{1, 16035, 16036, 16035},
										{1, 16035, 4, 16035},
										{14, 4100, 16035, 16037, 9},
										{0, 1, 16037, 16038},
										{19, -1, -1, 16038},
										{0, -1, 5, 16040},
										{3, 16040, 1, 16040},
										{1, 16039, 16040, 16039},
										{1, 16039, 2, 16039},
										{14, 4100, 16039, 16041, 9},
										{0, 1, 16041, 16042},
										{19, -1, -1, 16042},
										{0, -1, 5, 16044},
										{3, 16044, 1, 16044},
										{1, 16043, 16044, 16043},
										{1, 16043, 5, 16043},
										{14, 4100, 16043, 16045, 9},
										{0, 1, 16045, 16046},
										{19, -1, -1, 16046},
										{21, -1, -1, -1},
										{1, 16047, 8, 16047},
										{14, 4000, 16047, 16048, 100},
										{0, -1, 2, 16050},
										{3, 16050, 1, 16050},
										{1, 16049, 16050, 16049},
										{1, 16049, 2, 16049},
										{14, 4100, 16049, 16051, 9},
										{0, 1, 16051, 16052},
										{0, 2, 16052, 16048},
										{1, 16053, 3, 16053},
										{14, 4000, 16053, 16054, 100},
										{0, 2, 2, 16054},
										{1, 16055, 9, 16055},
										{14, 4000, 16055, 16056, 100},
										{0, 2, 1, 16056},
										{1, 16057, 10, 16057},
										{14, 4000, 16057, 16058, 100},
										{0, 2, 1, 16058},
										{0, -1, 2, 16060},
										{3, 16060, 1, 16060},
										{1, 16059, 16060, 16059},
										{1, 16059, 2, 16059},
										{14, 4100, 16059, 16061, 9},
										{0, 1, 16061, 16062},
										{1, 16063, 16062, 16063},
										{14, 4000, 16063, 16064, 100},
										{1, 16065, 3, 16065},
										{14, 4000, 16065, 16066, 100},
										{0, 1, 16066, 16067},
										{1, 16068, 10, 16068},
										{14, 4000, 16068, 16069, 100},
										{0, 1, 16069, 16070},
										{1, 16071, 9, 16071},
										{14, 4000, 16071, 16072, 100},
										{0, 1, 16072, 16073},
										{2, 16070, 16073, 16074},
										{0, -1, 16067, 16076},
										{3, 16076, 1, 16076},
										{1, 16075, 16076, 16075},
										{1, 16075, 16074, 16075},
										{14, 4100, 16075, 16077, 9},
										{0, 1, 16077, 16078},
										{0, 2, 16078, 16064},
										{1, 16079, 11, 16079},
										{14, 4000, 16079, 16080, 100},
										{0, 1, 16080, 16081},
										{19, -1, -1, 16081},
										{21, -1, -1, -1},
										{1, 16082, 8, 16082},
										{14, 4000, 16082, 16083, 100},
										{0, 1, 16083, 16084},
										{19, -1, -1, 16084},
										{21, -1, -1, -1},
										{19, -1, -1, 2000},
										{21, -1, -1, -1},
										{0, -1, 2, 16086},
										{3, 16086, 1, 16086},
										{3, 16086, 1, 16086},
										{1, 16085, 16086, 16085},
										{0, -1, 2, 16087},
										{3, 16087, 1, 16087},
										{1, 16085, 16087, 16085},
										{1, 16085, 2, 16085},
										{14, 4109, 16085, 16088, 27},
										{0, 2, 1, 16088},
										{0, -1, 2, 16090},
										{3, 16090, 1, 16090},
										{3, 16090, 1, 16090},
										{1, 16089, 16090, 16089},
										{0, -1, 2, 16091},
										{3, 16091, 1, 16091},
										{1, 16089, 16091, 16089},
										{1, 16089, 2, 16089},
										{14, 4109, 16089, 16092, 27},
										{0, 1, 16092, 16093},
										{19, -1, -1, 16093},
										{2, -1, 1, 16094},
										{0, -1, 2, 16096},
										{3, 16096, 1, 16096},
										{3, 16096, 1, 16096},
										{1, 16095, 16096, 16095},
										{0, -1, 4, 16097},
										{3, 16097, 1, 16097},
										{1, 16095, 16097, 16095},
										{1, 16095, 16094, 16095},
										{14, 4109, 16095, 16098, 27},
										{0, 1, 16098, 16099},
										{19, -1, -1, 16099},
										{2, -1, 7, 16100},
										{0, -1, 2, 16102},
										{3, 16102, 1, 16102},
										{3, 16102, 1, 16102},
										{1, 16101, 16102, 16101},
										{0, -1, 5, 16103},
										{3, 16103, 1, 16103},
										{1, 16101, 16103, 16101},
										{1, 16101, 16100, 16101},
										{14, 4109, 16101, 16104, 27},
										{0, 1, 16104, 16105},
										{19, -1, -1, 16105},
										{2, -1, 1, 16106},
										{0, -1, 4, 16108},
										{3, 16108, 1, 16108},
										{3, 16108, 1, 16108},
										{1, 16107, 16108, 16107},
										{0, -1, 16106, 16109},
										{3, 16109, 1, 16109},
										{1, 16107, 16109, 16107},
										{1, 16107, 2, 16107},
										{14, 4109, 16107, 16110, 27},
										{0, 1, 16110, 16111},
										{19, -1, -1, 16111},
										{2, -1, 12, 16112},
										{2, -1, 1, 16113},
										{0, -1, 5, 16115},
										{3, 16115, 1, 16115},
										{3, 16115, 1, 16115},
										{1, 16114, 16115, 16114},
										{0, -1, 16112, 16116},
										{3, 16116, 1, 16116},
										{1, 16114, 16116, 16114},
										{1, 16114, 16113, 16114},
										{14, 4109, 16114, 16117, 27},
										{0, 1, 16117, 16118},
										{19, -1, -1, 16118},
										{21, -1, -1, -1},
										{25, -1, -1, -1},
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

					Value arr_size =	QUADS[IP][4];
					Value arr_dir = QUADS[IP][1];
					Value access_value = read_from_memory(QUADS[IP][2]);

					if (access_value.i < 0 || access_value.i > arr_size.i){
						cout << ">> Error: array index out of bounds" << endl;
						cout << access_value.i << " " << arr_size.i << endl;
						exit(EXIT_FAILURE);
					}

					Value result = arr_dir + access_value;

					write_to_memory(result_dir, result.to_str());
					IP++;
        }
        break;

			case 15:		// ERA
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

			case 16:		// PARAM
				{

					Value param_value = read_from_memory(QUADS[IP][2]);
					int param_addr = QUADS[IP][3];

					write_to_param(param_addr, param_value.to_str());
					IP++;
				}
				break;

			case 17:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);
					IP = func_start_addr;
				}
				break;

			case 18:		// READ
				{

					int result_dir = QUADS[IP][3];

					string user_input;
					cin >> user_input;

					write_to_memory(result_dir, user_input);

					IP++;
				}
				break;

			case 19:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (LOCAL_MEM->active) LOCAL_MEM->add_to_print_buffer(printable.to_str());
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str());
					IP++;
				}
				break;

      case 20:			// PRNT
        {
          string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 21:			// PRNTLN
        {
					string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable << endl;
          IP++;
        }
        break;

      case 22:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 23:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 24:			// ENDFNC
				{
					int return_addr = LOCAL_MEM->return_addr;
					MEMORY_STACK.pop();
					LOCAL_MEM = (MEMORY_STACK.size()) ? &(MEMORY_STACK.top()) : new MemoryMap();
					IP = return_addr;
				}
				break;

      case 25:			// END
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
