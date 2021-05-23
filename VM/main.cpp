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
										{63, {{6,3,1,1,0}, {12,1,4,1,0}, {7,1,20,0,0}}},
										{1, {{1,0,0,0,0}, {2,0,0,1,0}}},
										{9, {{3,0,1,0,0}, {9,0,11,1,0}}},
										{48, {{1,0,0,0,0}, {3,0,0,1,0}}},
										{60, {{3,0,1,0,0}, {0,0,0,0,0}}},
										};
// MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{0, "0"},
										{1, "1"},
										{6000, " * "},
										{6001, " = "},
										{6002, "\t"},
										{2, "2"},
										{6003, "-'hola' = "},
										{6004, "hola"},
										{3, "3"},
										{4, "15"},
										{5, "5"},
										{3000, "25.5"},
										{6005, ">> Enter an integer\n-- a = "},
										{6006, ">> Enter a string\n-- f = "},
										{6, "12"},
										{6007, "! = "},
										{6008, "Global a:"},
										{6009, "------------------------"},
										{6010, "HI "},
										{6011, " print() "},
										{6012, " prints inline,"},
										{6013, " and needs this next param for a newline:"},
										{6014, "\n"},
										{6015, "Hello from another line!"},
										{6016, " println() acts just like print, "},
										{6017, "but always adds a '\\n' parameter at the end!"},
										{6018, "And this will skip two lines!"},
										{6019, "Nice : )"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{23, -1, -1, 63},
										{7, 65000, 0, 105000},
										{24, -1, 105000, 7},
										{2, -1, 1, 90000},
										{3, 65000, 90000, 90001},
										{0, -1, 90001, 15003},
										{25, -1, -1, -1},
										{0, -1, 65000, 15003},
										{25, -1, -1, -1},
										{2, -1, 1, 90000},
										{3, 65001, 90000, 90001},
										{7, 65000, 90001, 105000},
										{24, -1, 105000, 18},
										{2, -1, 1, 90002},
										{3, 65001, 90002, 90003},
										{2, 90003, 1, 90004},
										{0, -1, 90004, 15004},
										{25, -1, -1, -1},
										{16, -1, -1, 9},
										{17, -1, 75000, 75000},
										{2, 65000, 1, 90005},
										{17, -1, 90005, 65000},
										{17, -1, 65001, 65001},
										{18, -1, -1, 9},
										{0, -1, 15004, 90006},
										{0, -1, 90006, 65002},
										{1, 75000, 6000, 100000},
										{1, 100000, 65002, 100001},
										{1, 100001, 6001, 100002},
										{3, 75000, 65002, 100003},
										{1, 100002, 100003, 100004},
										{20, -1, -1, 100004},
										{16, -1, -1, 1},
										{17, -1, 65000, 65000},
										{18, -1, -1, 1},
										{0, -1, 15003, 90007},
										{2, 65001, 90007, 90008},
										{3, 90008, 6002, 100005},
										{20, -1, -1, 100005},
										{3, 75000, 65002, 100006},
										{1, 100006, 6001, 100007},
										{1, 100007, 65002, 100008},
										{1, 100008, 6000, 100009},
										{1, 100009, 75000, 100010},
										{20, -1, -1, 100010},
										{22, -1, -1, -1},
										{0, -1, 65000, 15004},
										{25, -1, -1, -1},
										{7, 65000, 2, 105000},
										{24, -1, 105000, 52},
										{0, -1, 1, 15005},
										{25, -1, -1, -1},
										{16, -1, -1, 48},
										{2, 65000, 1, 90000},
										{17, -1, 90000, 65000},
										{18, -1, -1, 48},
										{0, -1, 15005, 90001},
										{3, 65000, 90001, 90002},
										{0, -1, 90002, 15005},
										{25, -1, -1, -1},
										{16, -1, -1, 60},
										{18, -1, -1, 60},
										{25, -1, -1, -1},
										{20, -1, -1, 6003},
										{2, -1, 6004, 50000},
										{20, -1, -1, 50000},
										{2, -1, 4, 40000},
										{3, 3, 40000, 40001},
										{1, 40001, 5, 40002},
										{2, -1, 5, 40003},
										{1, 40002, 40003, 40004},
										{20, -1, -1, 40004},
										{2, -1, 3000, 45000},
										{20, -1, -1, 45000},
										{16, -1, -1, 1},
										{2, -1, 1, 40005},
										{17, -1, 40005, 65000},
										{18, -1, -1, 1},
										{0, -1, 15003, 40006},
										{20, -1, -1, 40006},
										{16, -1, -1, 1},
										{17, -1, 0, 65000},
										{18, -1, -1, 1},
										{0, -1, 15003, 40007},
										{20, -1, -1, 40007},
										{16, -1, -1, 1},
										{17, -1, 1, 65000},
										{18, -1, -1, 1},
										{0, -1, 15003, 40008},
										{20, -1, -1, 40008},
										{22, -1, -1, -1},
										{20, -1, -1, 6005},
										{21, -1, -1, -1},
										{19, -1, -1, 15000},
										{20, -1, -1, 6006},
										{21, -1, -1, -1},
										{19, -1, -1, 25000},
										{16, -1, -1, 9},
										{17, -1, 25000, 75000},
										{17, -1, 15000, 65000},
										{17, -1, 15000, 65001},
										{18, -1, -1, 9},
										{0, -1, 15004, 40009},
										{0, -1, 0, 15000},
										{9, 15000, 6, 55000},
										{24, -1, 55000, 117},
										{1, 15000, 6007, 50001},
										{16, -1, -1, 48},
										{17, -1, 15000, 65000},
										{18, -1, -1, 48},
										{0, -1, 15005, 40011},
										{1, 50001, 40011, 50002},
										{20, -1, -1, 50002},
										{22, -1, -1, -1},
										{1, 15000, 1, 40010},
										{0, -1, 40010, 15000},
										{23, -1, -1, 104},
										{20, -1, -1, 6008},
										{20, -1, -1, 15000},
										{22, -1, -1, -1},
										{20, -1, -1, 6009},
										{22, -1, -1, -1},
										{20, -1, -1, 6010},
										{20, -1, -1, 6011},
										{20, -1, -1, 6012},
										{20, -1, -1, 6013},
										{20, -1, -1, 6014},
										{21, -1, -1, -1},
										{20, -1, -1, 6015},
										{1, 6016, 6017, 50003},
										{20, -1, -1, 50003},
										{22, -1, -1, -1},
										{20, -1, -1, 6018},
										{20, -1, -1, 6014},
										{22, -1, -1, -1},
										{20, -1, -1, 6019},
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
