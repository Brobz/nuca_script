// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <ctime>

#include "MemoryContext.h"
#include "Value.h"
#include "FileIO.h"

using namespace std;

/*/

		VM execution file for NucaScript

		!!! ATENTION !!!
		The next few code segments are automatically generated during compilation time,
		and should not be tampered with!
		Doing so migh mess up the following compilation cycle!
		!!! ATENTION !!!


/*/

// MEMORY_CONSTRAINTS //
const int MAX_CONSTANTS = 10000, MAX_SYMBOLS = 30000, MAX_TMP_SYMBOLS = 30000, MAX_OBJ_SYMBOLS = 30000, VAR_TYPES = 5, MEMORY_STACK_LIMIT = 100000;
// MEMORY_CONSTRAINTS //

// FUNCTION_MEMORY //
const map<int, vector<vector<int>>> FUNCTION_MEMORY_CONTEXT_SIGN = {
										{12, {{14,29,2,2,7}, {61,4,6,9,1}, {8,3,19,2,0}}},
										{1, {{1,0,0,0,0}, {1,0,0,0,0}}},
										{4, {{1,0,0,0,0}, {1,0,2,0,0}}},
										};
// FUNCTION_MEMORY //


// OBJECT_MEMORY //
const map<int, vector<int>> OBJECT_MEMORY_CONTEXT_SIGN = {
										{2, {1,0,10,0,0}},
										};
// OBJECT_MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{30000, "0"},
										{30001, "1"},
										{0, "10"},
										{1, "3"},
										{2, "2"},
										{20000, ">> Local int is: "},
										{20001, ">> Class Int is: "},
										{3, "5"},
										{160000, "2"},
										{160001, "2"},
										{160002, "2"},
										{20002, "Hello World!"},
										{10000, "3.14"},
										{10001, "0.0015"},
										{10002, "0.1618"},
										{20003, "blue"},
										{20004, "the result is:"},
										{4, "0"},
										{5, "1"},
										{20005, ">> Enter an integer: "},
										{20006, ">> It is less than zero!"},
										{20007, ">> It is exactly zero!"},
										{20008, ">> It is bigger than zero!"},
										{6, "4"},
										{7, "9"},
										{20009, ">> Entering while loop!"},
										{20010, ">> Inside while loop! i is now: "},
										{20011, ">> All done with the while loop!"},
										{20012, ">> Entering for loop!"},
										{20013, ">> Inside for loop! i is now: "},
										{20014, ">> All done with the for loop!"},
										{20015, ">> arr["},
										{20016, "] = "},
										{20017, ">> 10 doubled is: "},
										{20018, "Hi!"},
										{310000, "2"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{35, -1, -1, 12},
										{3, 340000, 2, 490000},
										{0, -1, 490000, 40013},
										{37, -1, -1, 0},
										{1, 20000, 340000, 550000},
										{26, -1, -1, 550000},
										{28, -1, -1, -1},
										{19, -1, 640000, 490000},
										{1, 20001, 490000, 550001},
										{26, -1, -1, 550001},
										{28, -1, -1, -1},
										{37, -1, -1, 1},
										{17, 5, 2, 160002},
										{26, -1, -1, 20002},
										{28, -1, -1, -1},
										{0, -1, 0, 40000},
										{3, 0, 3, 190000},
										{4, 190000, 3, 190001},
										{0, -1, 190001, 40001},
										{3, 40000, 40001, 190002},
										{4, 0, 2, 190003},
										{1, 190002, 190003, 190004},
										{2, 190004, 3, 190005},
										{0, -1, 190005, 40002},
										{1, 10000, 10001, 220000},
										{0, -1, 220000, 70000},
										{3, 10002, 0, 220001},
										{0, -1, 220001, 70001},
										{0, -1, 20003, 100000},
										{0, -1, 20004, 100001},
										{0, -1, 30000, 130000},
										{11, 130000, 30001, 280000},
										{6, 4, 5, 280001},
										{11, 30001, 280001, 280002},
										{10, 280000, 280002, 280003},
										{0, -1, 280003, 130001},
										{26, -1, -1, 130000},
										{26, -1, -1, 130001},
										{28, -1, -1, -1},
										{26, -1, -1, 20005},
										{27, -1, -1, -1},
										{25, -1, -1, 40002},
										{7, 40002, 4, 280004},
										{36, -1, 280004, 47},
										{26, -1, -1, 20006},
										{28, -1, -1, -1},
										{35, -1, -1, 54},
										{5, 40002, 4, 280005},
										{36, -1, 280005, 52},
										{26, -1, -1, 20007},
										{28, -1, -1, -1},
										{35, -1, -1, 54},
										{26, -1, -1, 20008},
										{28, -1, -1, -1},
										{16, -1, 0, 190006},
										{15, -1, 4, 10},
										{0, -1, 4, 190006},
										{16, -1, 0, 190007},
										{14, 40003, 190006, 190007},
										{0, 2, 3, 190007},
										{1, 3, 6, 190008},
										{16, -1, 0, 190009},
										{15, -1, 190008, 10},
										{0, -1, 190008, 190009},
										{16, -1, 0, 190010},
										{14, 40003, 190009, 190010},
										{0, 2, 0, 190010},
										{16, -1, 0, 190011},
										{15, -1, 4, 10},
										{0, -1, 4, 190011},
										{16, -1, 0, 190012},
										{14, 40003, 190011, 190012},
										{16, -1, 0, 190013},
										{0, 1, 190012, 190013},
										{26, -1, -1, 190013},
										{16, -1, 0, 190014},
										{15, -1, 7, 10},
										{0, -1, 7, 190014},
										{16, -1, 0, 190015},
										{14, 40003, 190014, 190015},
										{16, -1, 0, 190016},
										{0, 1, 190015, 190016},
										{26, -1, -1, 190016},
										{28, -1, -1, -1},
										{16, -1, 0, 190017},
										{15, -1, 4, 3},
										{16, -1, 0, 190018},
										{0, -1, 4, 190018},
										{3, 190018, 1, 190018},
										{3, 190018, 1, 190018},
										{1, 190017, 190018, 190017},
										{15, -1, 4, 3},
										{16, -1, 0, 190019},
										{0, -1, 4, 190019},
										{3, 190019, 1, 190019},
										{1, 190017, 190019, 190017},
										{15, -1, 4, 3},
										{1, 190017, 4, 190017},
										{16, -1, 0, 190020},
										{14, 70002, 190017, 190020},
										{0, 2, 3, 190020},
										{16, -1, 0, 190021},
										{15, -1, 5, 3},
										{16, -1, 0, 190022},
										{0, -1, 5, 190022},
										{3, 190022, 1, 190022},
										{3, 190022, 1, 190022},
										{1, 190021, 190022, 190021},
										{15, -1, 2, 3},
										{16, -1, 0, 190023},
										{0, -1, 2, 190023},
										{3, 190023, 1, 190023},
										{1, 190021, 190023, 190021},
										{15, -1, 4, 3},
										{1, 190021, 4, 190021},
										{16, -1, 0, 190024},
										{14, 70002, 190021, 190024},
										{0, 2, 0, 190024},
										{16, -1, 0, 190025},
										{15, -1, 4, 3},
										{16, -1, 0, 190026},
										{0, -1, 4, 190026},
										{3, 190026, 1, 190026},
										{3, 190026, 1, 190026},
										{1, 190025, 190026, 190025},
										{15, -1, 4, 3},
										{16, -1, 0, 190027},
										{0, -1, 4, 190027},
										{3, 190027, 1, 190027},
										{1, 190025, 190027, 190025},
										{15, -1, 4, 3},
										{1, 190025, 4, 190025},
										{16, -1, 0, 190028},
										{14, 70002, 190025, 190028},
										{16, -1, 0, 220002},
										{0, 1, 190028, 220002},
										{26, -1, -1, 220002},
										{16, -1, 0, 190029},
										{15, -1, 5, 3},
										{16, -1, 0, 190030},
										{0, -1, 5, 190030},
										{3, 190030, 1, 190030},
										{3, 190030, 1, 190030},
										{1, 190029, 190030, 190029},
										{15, -1, 2, 3},
										{16, -1, 0, 190031},
										{0, -1, 2, 190031},
										{3, 190031, 1, 190031},
										{1, 190029, 190031, 190029},
										{15, -1, 4, 3},
										{1, 190029, 4, 190029},
										{16, -1, 0, 190032},
										{14, 70002, 190029, 190032},
										{16, -1, 0, 220003},
										{0, 1, 190032, 220003},
										{26, -1, -1, 220003},
										{28, -1, -1, -1},
										{0, -1, 4, 40000},
										{26, -1, -1, 20009},
										{28, -1, -1, -1},
										{7, 40000, 0, 280006},
										{36, -1, 280006, 168},
										{1, 20010, 40000, 250000},
										{26, -1, -1, 250000},
										{28, -1, -1, -1},
										{1, 40000, 5, 190033},
										{0, -1, 190033, 40000},
										{35, -1, -1, 160},
										{26, -1, -1, 20011},
										{28, -1, -1, -1},
										{26, -1, -1, 20012},
										{28, -1, -1, -1},
										{0, -1, 4, 40000},
										{7, 40000, 0, 280007},
										{36, -1, 280007, 182},
										{1, 20013, 40000, 250001},
										{26, -1, -1, 250001},
										{28, -1, -1, -1},
										{16, -1, 1, 190034},
										{1, 40000, 190034, 190035},
										{0, -1, 190035, 40000},
										{35, -1, -1, 173},
										{26, -1, -1, 20014},
										{28, -1, -1, -1},
										{0, -1, 4, 40000},
										{7, 40000, 0, 280008},
										{36, -1, 280008, 202},
										{16, -1, 0, 190038},
										{15, -1, 40000, 10},
										{0, -1, 40000, 190038},
										{16, -1, 0, 190039},
										{14, 40003, 190038, 190039},
										{0, 2, 40000, 190039},
										{1, 20015, 40000, 250002},
										{1, 250002, 20016, 250003},
										{1, 250003, 40000, 250004},
										{26, -1, -1, 250004},
										{28, -1, -1, -1},
										{16, -1, 1, 190036},
										{1, 40000, 190036, 190037},
										{0, -1, 190037, 40000},
										{35, -1, -1, 185},
										{21, -1, -1, 1},
										{22, -1, 0, 340000},
										{23, -1, -1, 1},
										{0, -1, 40013, 190040},
										{1, 20017, 190040, 250005},
										{26, -1, -1, 250005},
										{28, -1, -1, -1},
										{20, 160000, 0, 640000, -1, -1},
										{16, -1, 0, 190041},
										{15, -1, 3, 10},
										{0, -1, 3, 190041},
										{16, -1, 0, 190042},
										{14, 700000, 190041, 190042},
										{20, 160000, 20018, 190042, 2, -1},
										{21, -1, -1, 4},
										{24, -1, 160000, 4},
										{18, -1, 2, 160000},
										{21, -1, -1, 4},
										{24, -1, 160000, 4},
										{16, -1, 0, 190043},
										{15, -1, 4, 5},
										{0, -1, 4, 190043},
										{16, -1, 0, 190044},
										{14, 160002, 190043, 190044},
										{19, 190044, 640000, 190045, -1, 1},
										{1, 190045, 3, 190046},
										{20, 190044, 190046, 640000, -1, 1},
										{16, -1, 0, 190047},
										{15, -1, 5, 5},
										{0, -1, 5, 190047},
										{16, -1, 0, 190048},
										{14, 160002, 190047, 190048},
										{19, 190048, 640000, 190049, -1, 1},
										{16, -1, 0, 190050},
										{15, -1, 4, 5},
										{0, -1, 4, 190050},
										{16, -1, 0, 190051},
										{14, 160002, 190050, 190051},
										{19, 190051, 640000, 190052, -1, 1},
										{3, 3, 190052, 190053},
										{1, 190049, 190053, 190054},
										{20, 190048, 190054, 640000, -1, 1},
										{16, -1, 0, 190055},
										{15, -1, 4, 5},
										{0, -1, 4, 190055},
										{16, -1, 0, 190056},
										{14, 160002, 190055, 190056},
										{19, 190056, 640000, 190057, -1, 1},
										{26, -1, -1, 190057},
										{16, -1, 0, 190058},
										{15, -1, 5, 5},
										{0, -1, 5, 190058},
										{16, -1, 0, 190059},
										{14, 160002, 190058, 190059},
										{19, 190059, 640000, 190060, -1, 1},
										{26, -1, -1, 190060},
										{28, -1, -1, -1},
										{0, -1, 30000, 130000},
										{38, -1, -1, -1},
										};
// QUADS //


/*/

		Auto-generated Section ends here!
		Fell free to tamper with the rest of the code!
		Break something, learn something!

/*/

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
							{"TRUE", 1},
							{"True", 1},
							{"true", 1},
							{"FALSE", 0},
							{"False", 0},
							{"false", 0},
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

// Safe String to Long Long
long long s_stoll(string s){
	try{
		return stoll(s);
	}catch(...){
			if(!s.empty()) cout << ">> Fatal Error: Cannot resolve stoi(" << s << ")" << endl;
			else cout << ">> Fatal Error: Cannot resolve stoi of an empty string" << endl;
			exit(EXIT_FAILURE);
		}
}

// Safe String to Long Double
long double s_stold(string s){
	try{
		return stold(s);
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

// Given a variable's memory index, calculates its signature
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

  // ERROR!
  cout << ">> Fatal Error: could not locate "  << index << " in memory" << endl;
  exit(EXIT_FAILURE);
}

// Given a variable's memory signature, calculates the displacement needed to convert from virtual memory to real memory
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

// Given a memory index, retrieves a pointer to the Object Memory instance located in it, if there is one
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

// Reads and returns the value of a memory index
// Responsible for figuring out which memory to read from (local / global, constant / var / temp, and type)
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

// Reads and returns the value of a memory index, in the given object memory
// Responsible for figuring out which memory to read from (types)
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

// Writes the given value into the given memory index
// Responsible for figuring out which memory to write into (local / global, constant / var / temp, and type)
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
        GLOBAL_MEM.const_mem.ints[index] = s_stoll(value);
      }
      break;
    case 10:
      {
        GLOBAL_MEM.const_mem.floats[index - index_displacement] = s_stold(value);
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
        GLOBAL_MEM.local_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 110:
      {
        GLOBAL_MEM.local_mem.floats[index - index_displacement] = s_stold(value);
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
        GLOBAL_MEM.temp_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 111:
      {
        GLOBAL_MEM.temp_mem.floats[index - index_displacement] = s_stold(value);
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
      	LOCAL_MEM->local_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 210:
      {
      	LOCAL_MEM->local_mem.floats[index - index_displacement] = s_stold(value);
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
      	LOCAL_MEM->temp_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 211:
      {
      	LOCAL_MEM->temp_mem.floats[index - index_displacement] = s_stold(value);
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


// Writes the given value into the given memory index of the given object memory
// Responsible for figuring out which memory to write into (types)
void write_to_memory(Memory* this_mem, int index, string value){
  string mem_sign = mem_index_to_mem_sign(index);
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
		case 300:
      {
				this_mem->ints[index - index_displacement] = s_stoll(value);
      }
      break;
		case 310:
      {
				this_mem->floats[index - index_displacement] = s_stold(value);
      }
      break;
		case 320:
      {
				this_mem->strings[index - index_displacement] = value;
      }
      break;
		case 330:
      {
				this_mem->booleans[index - index_displacement] = s_stoll(value);
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


// Writes the given value into the given memory index, but into the top of the memory stack instead of LOCAL_MEM
// Responsible for figuring out which memory to write into (types)
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
        MEMORY_STACK.top().local_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 210:
      {
        MEMORY_STACK.top().local_mem.floats[index - index_displacement] = s_stold(value);
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


// Does all of the needed initializations so that the program can be run
void setup(){

	// Memory signature with highest value is always pointing to the start of the main() method (no function can syntactically come after the main)
  PROGRAM_START = FUNCTION_MEMORY_CONTEXT_SIGN.rbegin()->first;

  // Generates global memory context
  GLOBAL_MEM = MemoryContext(FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(0), FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(1), FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(2));

	// WRITE CONSTANTS TO MEMORY //

	for (auto const& pair : CONSTANTS){
		write_to_memory(pair.first, pair.second);
  }

	// SEED THE PSEUDORANDOM GENERATOR //

	srand(time(NULL));

	// SET INITIAL VALUES FOR GLOBAL VARS //

	RUNNING = true; // This will get the instruction pointer movin through the quads
  IP = 0; // Start execution at the first QUAD
	THIS_OPERATOR_COUNTER = 0; // No this.have been seen yet
	LOCAL_MEM = new MemoryContext(); // Initialize LOCAL_MEM without parameters so that LOCAL_MEM->active is set to false
	THIS_MEM = new Memory();
}

// Runs the program, starting from QUAD 0
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

			case 17:			// USNG_AS
        {

					int arr_size = QUADS[IP][1];
					int class_sign = QUADS[IP][2];
					int obj_address = QUADS[IP][3];

					int obj_mem_sign = get_object_memory(obj_address)->signature;

					if (obj_mem_sign == -1 && arr_size == -1){
						cout << ">> Fatal Error: 'using as' employement exception; symbol is not instantiated" << endl;
						exit(EXIT_FAILURE);
					}

					if (obj_mem_sign != -1 && obj_mem_sign != class_sign){
						cout << ">> Fatal Error: 'using as' employement exception; symbol is instantiated as a different class type" << endl;
						exit(EXIT_FAILURE);
					}

					if (arr_size != -1){
						Memory* obj_mem;
						for (int i = 0; i < arr_size; i++){
							obj_mem = get_object_memory(obj_address + i);
							if (obj_mem->id == -1){
								// Here we must instantiate these array entrie with the appropriate class type
								write_to_memory(obj_address + i, to_string(class_sign));
							}
						}
					}

					IP++;
        }
        break;

			case 18:			// OBJ_INST
        {

					Memory* obj_mem;
					int obj_dir_is_ptr = QUADS[IP][1];
					int object_sign  = QUADS[IP][2];
					int obj_dir = QUADS[IP][3];

					if (obj_dir_is_ptr != -1) obj_dir = read_from_memory(obj_dir).i;

					obj_mem = get_object_memory(obj_dir);

					// Here we check to see if the object we are instatiating is not currently referenced bu the "this." operator
					// This prevents weird behaviour, e.g. changing an object's type in the middle of its own type's function execution
					if (THIS_MEM->id != -1 && obj_mem->id == THIS_MEM->id){
							cout << ">> Fatal Error: Cannot re-instantiate object variable within it's own scope" << endl;
							exit(EXIT_FAILURE);
					}

					write_to_memory(obj_dir, to_string(object_sign));

					IP++;
        }
        break;

			case 19:			// OBJ_READ
        {

					Memory* this_mem;
					Value result;

					int obj_dir = QUADS[IP][1];
					int object_var_dir = QUADS[IP][2];
					int result_dir = QUADS[IP][3];
					int ptr_value = -1;
					int obj_dir_is_ptr = -1;


					if (QUADS[IP].size() >= 5){
						ptr_value = QUADS[IP][4];
					}

					if (QUADS[IP].size() >= 6){
						obj_dir_is_ptr = QUADS[IP][5];
					}

					if (ptr_value == 1 || ptr_value == 3) object_var_dir = read_from_memory(object_var_dir).i;

					if (ptr_value == 2 || ptr_value == 3) result_dir = read_from_memory(result_dir).i;

					if (obj_dir != -1){
						if (obj_dir_is_ptr == -1) this_mem = get_object_memory(obj_dir);
						else this_mem = get_object_memory(read_from_memory(obj_dir).i);
					}
					else this_mem = THIS_MEM;

					result = read_from_memory(this_mem, object_var_dir);

					write_to_memory(result_dir, result.to_str());
					IP++;
        }
        break;

			case 20:			// OBJ_WRITE
        {

				 	Memory* this_mem;
					Value value;

					int obj_dir = QUADS[IP][1];
					int value_dir = QUADS[IP][2];
					int obj_var_dir = QUADS[IP][3];
					int ptr_value = -1;
					int obj_dir_is_ptr = -1;

					if (QUADS[IP].size() >= 5){
						ptr_value = QUADS[IP][4];
					}
					if (QUADS[IP].size() >= 6){
						obj_dir_is_ptr = QUADS[IP][5];
					}

					if (ptr_value == 1 || ptr_value == 3) value = read_from_memory(read_from_memory(value_dir).i);
					else value = read_from_memory(value_dir);

					if (ptr_value == 2 || ptr_value == 3) obj_var_dir = read_from_memory(obj_var_dir).i;

					if (obj_dir != -1){
						if (obj_dir_is_ptr == -1) this_mem = get_object_memory(obj_dir);
						else this_mem = get_object_memory(read_from_memory(obj_dir).i);
					}
					else this_mem = THIS_MEM;

					write_to_memory(this_mem, obj_var_dir, value.to_str());

					IP++;
        }
        break;

			case 21:		// ERA
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

			case 22:		// PARAM
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

			case 23:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);

					IP = func_start_addr;
				}
				break;

			case 24:		// OBJ_GOSUB
				{

					int obj_dir_is_ptr = QUADS[IP][1];
					int object_dir = QUADS[IP][2];
					int func_start_addr = QUADS[IP][3];

					if (object_dir != -1){
						if (!OBJECT_MEMORY_STACK.size()){

							if (obj_dir_is_ptr == -1) OBJECT_MEMORY_STACK.push(get_object_memory(object_dir));
							else OBJECT_MEMORY_STACK.push(get_object_memory(read_from_memory(object_dir).i));

						}else{

							Memory* new_class_memory;

							if (obj_dir_is_ptr == -1) new_class_memory = get_object_memory(object_dir);
							else new_class_memory = get_object_memory(read_from_memory(object_dir).i);

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

			case 25:		// READ
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

			case 26:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (LOCAL_MEM->active) LOCAL_MEM->add_to_print_buffer(printable.to_str(true));
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str(true));
					IP++;
				}
				break;

      case 27:			// PRNT
        {
          string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 28:			// PRNTLN
        {
					string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
					cout << printable << endl;
					IP++;
        }
        break;

			case 29:			// STOX
        {
					int parent_obj_dir = QUADS[IP][1];
					int result_dir = QUADS[IP][3];

					string stox_arg = read_from_memory(QUADS[IP][2]).s;

					write_to_memory(result_dir, stox_arg);

					IP++;
        }
        break;

			case 30:			// SUBSTR
        {
					int start_index = s_stoi(read_from_memory(QUADS[IP][2]).to_str());
					int size = s_stoi(read_from_memory(QUADS[IP][3]).to_str());
					int result_dir = QUADS[IP][4];

					string substr_arg = read_from_memory(QUADS[IP][1]).s;

					write_to_memory(result_dir, substr_arg.substr(start_index, size));

					IP++;
        }
        break;

			case 31:			// STRLEN
        {
					string string_arg = read_from_memory(QUADS[IP][2]).s;
					int result_dir = QUADS[IP][3];

					write_to_memory(result_dir, to_string(string_arg.length()));

					IP++;
        }
        break;

			case 32:			// RANDINT
        {
					int lower_bound = read_from_memory(QUADS[IP][1]).i;
					int upper_bound = read_from_memory(QUADS[IP][2]).i;
					int result_dir = QUADS[IP][3];

					int rand_num = rand() % (upper_bound - lower_bound + 1) + lower_bound; // Generate the number, assign to variable.

					write_to_memory(result_dir, to_string(rand_num));

					IP++;
        }
        break;

			case 33:			// F_OPEN
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

			case 34:			// F_WRITE
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

      case 35:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 36:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 37:			// ENDFNC
				{

					int was_class_func = QUADS[IP][3];
					int return_addr = LOCAL_MEM->return_addr;

					if (THIS_OPERATOR_COUNTER <= 0 && was_class_func){
						THIS_MEM = (OBJECT_MEMORY_STACK.size() > 1) ? OBJECT_MEMORY_STACK.top()->return_memory : new Memory();
						if (OBJECT_MEMORY_STACK.size()) OBJECT_MEMORY_STACK.pop();
					}else if (was_class_func) {
						THIS_OPERATOR_COUNTER--;
					}

					LOCAL_MEM = (MEMORY_STACK.size()) ? MEMORY_STACK.top().return_scope : new MemoryContext();
					if (MEMORY_STACK.size()) MEMORY_STACK.pop();

					IP = return_addr;
				}
				break;

      case 38:			// END
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

  // Setup virtual machine to run the program
  setup();

  // Run program
  run();

  return 0;
}
