// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryContext.h"
#include "Value.h"
#include "FileIO.h"

using namespace std;

// MEMORY_CONSTRAINTS //
const int MAX_CONSTANTS = 3000, MAX_SYMBOLS = 5000, MAX_TMP_SYMBOLS = 5000, MAX_OBJ_SYMBOLS = 5000, VAR_TYPES = 5, MEMORY_STACK_LIMIT = 100000;
// MEMORY_CONSTRAINTS //

// FUNCTION_MEMORY //
const map<int, vector<vector<int>>> FUNCTION_MEMORY_CONTEXT_SIGN = {
										{10, {{51,0,3,0,1}, {59,0,11,3,1}, {11,0,10,0,0}}},
										{1, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{4, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{7, {{1,0,0,0,0}, {0,0,1,0,0}}},
										};
// FUNCTION_MEMORY //


// OBJECT_MEMORY //
const map<int, vector<int>> OBJECT_MEMORY_CONTEXT_SIGN = {
										{2, {51,0,1501,0,0}},
										};
// OBJECT_MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{0, "1500"},
										{1, "50"},
										{6000, " "},
										{6001, "\n"},
										{6002, "\t"},
										{2, "10"},
										{3, "20"},
										{4, "49"},
										{5, "45"},
										{6, "5"},
										{7, "3"},
										{6003, ">> Enter file path:\n-- "},
										{6004, ">> Parsing file..."},
										{8, "1"},
										{9, "0"},
										{10, "999"},
										{6005, "END_OF_STREAM"},
										{6006, "Entry "},
										{6007, ": "},
										{6008, "file.txt"},
										{6009, " // An extra funny comment to confirm this works : ) //"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{31, -1, -1, 10},
										{3, 6000, 62000, 97000},
										{0, -1, 97000, 22000},
										{33, -1, -1, 1},
										{3, 6001, 62000, 97000},
										{0, -1, 97000, 22001},
										{33, -1, -1, 1},
										{3, 6002, 62000, 97000},
										{0, -1, 97000, 22002},
										{33, -1, -1, 1},
										{17, -1, 2, 32000},
										{16, -1, 0, 37000},
										{15, -1, 2, 50},
										{0, -1, 2, 37000},
										{16, -1, 0, 37001},
										{14, 112000, 37000, 37001},
										{19, 32000, 3, 37001, 2},
										{18, 32000, 112050, 37002},
										{16, -1, 0, 37003},
										{15, -1, 2, 50},
										{0, -1, 2, 37003},
										{16, -1, 0, 37004},
										{14, 112000, 37003, 37004},
										{16, -1, 0, 37005},
										{18, 32000, 37004, 37005, 1},
										{2, 37002, 37005, 37006},
										{19, 32000, 37006, 112050, -1},
										{16, -1, 0, 37007},
										{15, -1, 4, 50},
										{0, -1, 4, 37007},
										{16, -1, 0, 37008},
										{14, 12001, 37007, 37008},
										{0, 1, 37008, 37009},
										{18, 32000, 112050, 37010},
										{2, 37009, 37010, 37011},
										{0, 2, 37011, 37008},
										{16, -1, 0, 37012},
										{15, -1, 5, 50},
										{0, -1, 5, 37012},
										{16, -1, 0, 37013},
										{14, 112000, 37012, 37013},
										{18, 32000, 37013, 37014, 1},
										{16, -1, 0, 37015},
										{15, -1, 4, 50},
										{0, -1, 4, 37015},
										{16, -1, 0, 37016},
										{14, 12001, 37015, 37016},
										{16, -1, 0, 37017},
										{0, 1, 37016, 37017},
										{1, 37014, 37017, 37018},
										{19, 32000, 37018, 37013, 2},
										{16, -1, 0, 37019},
										{15, -1, 5, 50},
										{0, -1, 5, 37019},
										{16, -1, 0, 37020},
										{14, 112000, 37019, 37020},
										{18, 32000, 37020, 37021, 1},
										{16, -1, 0, 37022},
										{15, -1, 4, 50},
										{0, -1, 4, 37022},
										{16, -1, 0, 37023},
										{14, 12001, 37022, 37023},
										{16, -1, 0, 37024},
										{0, 1, 37023, 37024},
										{3, 37021, 37024, 37025},
										{19, 32000, 37025, 37020, 2},
										{16, -1, 0, 37026},
										{15, -1, 4, 50},
										{0, -1, 4, 37026},
										{16, -1, 0, 37027},
										{14, 12001, 37026, 37027},
										{16, -1, 0, 37028},
										{0, 1, 37027, 37028},
										{25, -1, -1, 37028},
										{16, -1, 0, 37029},
										{15, -1, 5, 50},
										{0, -1, 5, 37029},
										{16, -1, 0, 37030},
										{14, 112000, 37029, 37030},
										{16, -1, 0, 37031},
										{18, 32000, 37030, 37031, 1},
										{25, -1, -1, 37031},
										{27, -1, -1, -1},
										{3, 6, 7, 37032},
										{1, 12000, 37032, 37033},
										{0, -1, 37033, 12000},
										{25, -1, -1, 12000},
										{27, -1, -1, -1},
										{16, -1, 0, 37034},
										{15, -1, 2, 50},
										{0, -1, 2, 37034},
										{16, -1, 0, 37035},
										{14, 112000, 37034, 37035},
										{16, -1, 0, 37036},
										{18, 32000, 37035, 37036, 1},
										{2, 12000, 37036, 37037},
										{0, -1, 37037, 12000},
										{25, -1, -1, 12000},
										{27, -1, -1, -1},
										{16, -1, 0, 37038},
										{15, -1, 6, 50},
										{0, -1, 6, 37038},
										{16, -1, 0, 37039},
										{14, 112000, 37038, 37039},
										{18, 32000, 37039, 37040, 1},
										{16, -1, 0, 37041},
										{15, -1, 2, 50},
										{0, -1, 2, 37041},
										{16, -1, 0, 37042},
										{14, 112000, 37041, 37042},
										{16, -1, 0, 37043},
										{18, 32000, 37042, 37043, 1},
										{1, 37040, 37043, 37044},
										{19, 32000, 37044, 37039, 2},
										{18, 32000, 112050, 37045},
										{16, -1, 0, 37046},
										{15, -1, 2, 50},
										{0, -1, 2, 37046},
										{16, -1, 0, 37047},
										{14, 112000, 37046, 37047},
										{16, -1, 0, 37048},
										{18, 32000, 37047, 37048, 1},
										{4, 37045, 37048, 37049},
										{19, 32000, 37049, 112050, -1},
										{16, -1, 0, 37050},
										{15, -1, 6, 50},
										{0, -1, 6, 37050},
										{16, -1, 0, 37051},
										{14, 112000, 37050, 37051},
										{16, -1, 0, 37052},
										{18, 32000, 37051, 37052, 1},
										{25, -1, -1, 37052},
										{18, 32000, 112050, 37053},
										{25, -1, -1, 37053},
										{27, -1, -1, -1},
										{25, -1, -1, 6003},
										{26, -1, -1, -1},
										{24, 32000, -1, 122000},
										{25, -1, -1, 6004},
										{27, -1, -1, -1},
										{18, 32000, 122000, 47000},
										{20, -1, -1, 4},
										{21, -1, 8, 62000},
										{23, -1, 32000, 4},
										{0, -1, 22001, 47001},
										{29, 32000, 47000, 47001, 122001, 1500},
										{0, -1, 9, 12000},
										{7, 12000, 10, 52000},
										{16, -1, 0, 37054},
										{15, -1, 12000, 1500},
										{0, -1, 12000, 37054},
										{16, -1, 0, 37055},
										{14, 122001, 37054, 37055},
										{16, -1, 0, 47002},
										{18, 32000, 37055, 47002, 1},
										{12, 47002, 6005, 52001},
										{10, 52000, 52001, 52002},
										{32, -1, 52002, 173},
										{1, 6006, 12000, 47003},
										{1, 47003, 6007, 47004},
										{16, -1, 0, 37057},
										{15, -1, 12000, 1500},
										{0, -1, 12000, 37057},
										{16, -1, 0, 37058},
										{14, 122001, 37057, 37058},
										{16, -1, 0, 47005},
										{18, 32000, 37058, 47005, 1},
										{1, 47004, 47005, 47006},
										{25, -1, -1, 47006},
										{27, -1, -1, -1},
										{1, 12000, 8, 37056},
										{0, -1, 37056, 12000},
										{31, -1, -1, 147},
										{20, -1, -1, 7},
										{21, -1, 2, 62000},
										{23, -1, 32000, 7},
										{0, -1, 22002, 47007},
										{1, 47007, 6009, 47008},
										{20, -1, -1, 4},
										{21, -1, 8, 62000},
										{23, -1, 32000, 4},
										{0, -1, 22001, 47009},
										{1, 47008, 47009, 47010},
										{30, 32000, 6008, 47010, 112000, 50},
										{34, -1, -1, -1},
										};
// QUADS //

// GLOBAL VARS //
int PROGRAM_START; // Quad index of the start of main()
bool RUNNING = false;
int IP; // Instruction Pointer
int THIS_OPERATOR_COUNTER; // To count how many this. accesses have happened
int Memory::MEM_ID = 0; // Start the memory id counter at 0;
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
			if(!s.empty()) cout << ">> Fatal Error: Cannot resolve stoi(" << s << ")" << endl;
			else cout << ">> Fatal Error: Cannot resolve stoi of an empty string" << endl;
			exit(EXIT_FAILURE);
		}
}

// Safe String to Float
float s_stof(string s){
	try{
		return stof(s);
	}catch(...){
			if(!s.empty()) cout << ">> Fatal Error: Cannot resolve stof(" << s << ")" << endl;
			else cout << ">> Fatal Error: Cannot resolve stof of an empty string" << endl;
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
				if(!s.empty()) cout << ">> Fatal Error: Cannot resolve stob(" << s << ")" << endl;
				else cout << ">> Fatal Error: Cannot resolve stob of an empty string" << endl;
				exit(EXIT_FAILURE);
			}
	}
}

string mem_index_to_mem_sign(int index){
  if (index < MAX_CONSTANTS * (VAR_TYPES - 1)){ // CONSTANTS
		string mem_sign = "0" + to_string(index / MAX_CONSTANTS) + "0";
		return mem_sign;
  }
  else if (index < MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES){ // GLOBALS
		string mem_sign = "1" + to_string(((index - MAX_CONSTANTS * (VAR_TYPES - 1)) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - MAX_CONSTANTS * (VAR_TYPES - 1)) >= MAX_SYMBOLS * VAR_TYPES) ? "1" : "0";
		return mem_sign;
  }
  else if (index < MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2){ // LOCALS
		string mem_sign = "2" + to_string(((index - (MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES)) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - (MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES) >= MAX_SYMBOLS * VAR_TYPES)) ? "1" : "0";
		return mem_sign;
  }
	else{ // CLAS ATTRIBUTES
		string mem_sign = "3" + to_string(((index - (MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2)) / MAX_OBJ_SYMBOLS) % (VAR_TYPES - 1));
		mem_sign += "0"; // There are no temporal class attributes
		return mem_sign;
	}

  // ERROR! Nothing was written
  cout << ">> Fatal Error: could not locate "  << index << " in memory" << endl;
  exit(EXIT_FAILURE);
}

int mem_sign_to_index_displacement(string mem_sign){
	int index_displacement = 0;
	int mem_class = mem_sign[0] - '0', var_type = mem_sign[1] - '0', is_temp = mem_sign[2] - '0';

	switch (mem_class) {
		case 1: // GLOBAL
		{
			index_displacement += MAX_CONSTANTS * (VAR_TYPES - 1);
		} break;
		case 2: // LOCAL
		{
			index_displacement += MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES;
		} break;
		case 3: // OBJECT
		{
			index_displacement += MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2;
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
			cout << ">> Fatal Error: could not get memory for object at " << index << endl;
			exit(EXIT_FAILURE);
		}
	}
}

Value read_from_memory(int index){
  string mem_sign = mem_index_to_mem_sign(index);
  if(mem_sign[0] == '2'){
    if (!LOCAL_MEM->active){
      cout << ">> Fatal Error: No local context to read "  << index << " from memory" << endl;
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
      cout << ">> Fatal Error: could not read "  << index << " from memory" << endl;
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
      cout << ">> Fatal Error: could not read from " << index << endl;
      exit(EXIT_FAILURE);
    }
	}

	return v;
}

void write_to_memory(int index, string value){
  string mem_sign = mem_index_to_mem_sign(index);

	if(mem_sign[0] == '2'){
    if (!LOCAL_MEM->active){
      cout << ">> Fatal Error: No local context to write "  << value << " to " << index << endl;
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
      cout << ">> Fatal Error: could not write "  << value << " to " << index << endl;
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
      cout << ">> Fatal Error: could not write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE);
    }
	}
}

void write_to_param(int index, string value){
	string mem_sign = mem_index_to_mem_sign(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << ">> Fatal Error: No local context to write "  << value << " to " << index << endl;
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
	      cout << ">> Fatal Error: could not write "  << value << " to param at " << index << endl;
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
					int arr_dim_size = QUADS[IP][3];

					if (arr_access_value.i < 0 || arr_access_value.i >= arr_dim_size){
						// If this point is reached, an array index out of bounds error has ocurred
						cout << ">> Fatal Error: array index out of bounds!" << endl;
						exit(EXIT_FAILURE);
					}

					// Else, continue execution
					IP++;
        }
        break;

			case 16:			// TMP_RESET
        {

					int reset_value = QUADS[IP][2];
					int tmp_address = QUADS[IP][3];

					write_to_memory(tmp_address, to_string(reset_value));

					IP++;
        }
        break;

			case 17:			// OBJ_INST
        {
					int object_sign  = QUADS[IP][2];
					int obj_dir = QUADS[IP][3];

					// Here we check to see if the object we are instatiating is not currently referenced bu the "this." operator
					// This prevents weird behaviour, e.g. changing an object's type in the middle of its own type's function execution
					if (THIS_MEM->id != -1 && get_object_memory(obj_dir)->id == THIS_MEM->id){
							cout << ">> Fatal Error: Cannot re-instantiate object variable within it's own scope" << endl;
							exit(EXIT_FAILURE);
					}

					write_to_memory(obj_dir, to_string(object_sign));

					IP++;
        }
        break;

			case 18:			// OBJ_READ
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

			case 19:			// OBJ_WRITE
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

			case 20:		// ERA
				{
					int func_start_addr = QUADS[IP][3];
					if (MEMORY_STACK.size() > MEMORY_STACK_LIMIT){
						// Too many functions on the stack!
						cout << ">> Fatal Error: Memory Stack Limit of " << MEMORY_STACK_LIMIT << " reached (infinite recursion?) Terminating..." << endl;
						exit(EXIT_FAILURE);
					}

					MemoryContext new_memory_context = MemoryContext(FUNCTION_MEMORY_CONTEXT_SIGN.at(func_start_addr).at(0), FUNCTION_MEMORY_CONTEXT_SIGN.at(func_start_addr).at(1));
					new_memory_context.return_scope = (LOCAL_MEM->active) ? LOCAL_MEM : &GLOBAL_MEM;

					MEMORY_STACK.push(new_memory_context);
					IP++;
				}
				break;

			case 21:		// PARAM
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

			case 22:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);

					IP = func_start_addr;
				}
				break;

			case 23:		// OBJ_GOSUB
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

			case 24:		// READ
				{

					int result_dir;
					int parent_obj_dir = QUADS[IP][1];
					int dir_is_ptr = QUADS[IP][2];

					if (dir_is_ptr == 1) result_dir = read_from_memory(QUADS[IP][3]).i;
					else result_dir = QUADS[IP][3];

					string user_input;
					getline(cin, user_input);

					if (parent_obj_dir != -1)  write_to_memory(get_object_memory(parent_obj_dir), result_dir, user_input);
					else write_to_memory(result_dir, user_input);

					IP++;
				}
				break;

			case 25:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (LOCAL_MEM->active) LOCAL_MEM->add_to_print_buffer(printable.to_str());
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str());
					IP++;
				}
				break;

      case 26:			// PRNT
        {
          string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 27:			// PRNTLN
        {
					string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
					cout << printable << endl;
					IP++;
        }
        break;

			case 28:			// STOX
        {

					Memory* this_mem;
					int parent_obj_dir = QUADS[IP][1];
					int result_dir = QUADS[IP][3];

					string stox_arg = read_from_memory(QUADS[IP][2]).s;

					if (parent_obj_dir > 0) this_mem = get_object_memory(parent_obj_dir);
					else if (parent_obj_dir == 0) this_mem = THIS_MEM;
					else this_mem = new Memory();

					if (this_mem->id != -1) write_to_memory(this_mem, result_dir, stox_arg);
					else write_to_memory(result_dir, stox_arg);

					IP++;
        }
        break;

			case 29:			// F_OPEN
        {
					Memory* this_mem;
					int parent_obj_dir = QUADS[IP][1];
					int buffer_dir = QUADS[IP][4];
					int buffer_size = QUADS[IP][5];

					string file_path = read_from_memory(QUADS[IP][2]).s;
					string separator = read_from_memory(QUADS[IP][3]).s;

					if (parent_obj_dir > 0) this_mem = get_object_memory(parent_obj_dir);
					else if (parent_obj_dir == 0) this_mem = THIS_MEM;
					else this_mem = new Memory();

					vector<string> file_data = FileIO::parse_file(file_path, separator, buffer_size);

					for(int i = 0; i < file_data.size(); i++){
						if (this_mem->id != -1) write_to_memory(this_mem, buffer_dir + i, file_data[i]);
						else write_to_memory(buffer_dir + i, file_data[i]);
						if (file_data[i] == "END_OF_STREAM") break;
					}

					IP++;
        }
        break;

			case 30:			// F_WRITE
        {
					Memory* this_mem;
					int parent_obj_dir = QUADS[IP][1];
					int buffer_dir = QUADS[IP][4];
					int buffer_size = QUADS[IP][5];

					string file_path = read_from_memory(QUADS[IP][2]).s;
					string separator = read_from_memory(QUADS[IP][3]).s;

					if (parent_obj_dir > 0) this_mem = get_object_memory(parent_obj_dir);
					else if (parent_obj_dir == 0) this_mem = THIS_MEM;
					else this_mem = new Memory();

					vector<string> buffer;
					string next_entry;

					for(int i = 0; i < buffer_size; i++){
						if (this_mem->id != -1) next_entry = read_from_memory(this_mem, buffer_dir + i).to_str();
						else next_entry = read_from_memory(buffer_dir + i).to_str();
						if (next_entry == "END_OF_STREAM") break;
						buffer.push_back(next_entry);
					}

					FileIO::write_to_file(buffer, file_path, separator);

					IP++;
        }
        break;

      case 31:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 32:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 33:			// ENDFNC
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

      case 34:			// END
        {
          RUNNING = false;
        }
        break;

      default:
        {
        cout << ">> Fatal Error: Unknown Op: " << op << endl;
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
