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
										{63, {{6,3,1,1}, {12,1,4,1}, {7,1,20,0}}},
										{1, {{1,0,0,0}, {2,0,0,1}}},
										{9, {{3,0,1,0}, {9,0,11,1}}},
										{48, {{1,0,0,0}, {3,0,0,1}}},
										{60, {{3,0,1,0}, {0,0,0,0}}},
										};
// MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{0, "0"},
										{1, "1"},
										{2000, " * "},
										{2001, " = "},
										{2002, "\t"},
										{2, "2"},
										{2003, "-'hola' = "},
										{2004, "hola"},
										{3, "3"},
										{4, "15"},
										{5, "5"},
										{1000, "25.5"},
										{2005, ">> Enter an integer\n-- a = "},
										{2006, ">> Enter a string\n-- f = "},
										{6, "12"},
										{2007, "! = "},
										{2008, "Global a:"},
										{2009, "------------------------"},
										{2010, "HI "},
										{2011, " print() "},
										{2012, " prints inline,"},
										{2013, " and needs this next param for a newline:"},
										{2014, "\n"},
										{2015, "Hello from another line!"},
										{2016, " println() acts just like print, "},
										{2017, "but always adds a '\\n' parameter at the end!"},
										{2018, "And this will skip two lines!"},
										{2019, "Nice : )"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{23, -1, -1, 63},
										{7, 28000, 0, 49000},
										{24, -1, 49000, 7},
										{2, -1, 1, 40000},
										{3, 28000, 40000, 40001},
										{0, -1, 40001, 4003},
										{25, -1, -1, -1},
										{0, -1, 28000, 4003},
										{25, -1, -1, -1},
										{2, -1, 1, 40000},
										{3, 28001, 40000, 40001},
										{7, 28000, 40001, 49000},
										{24, -1, 49000, 18},
										{2, -1, 1, 40002},
										{3, 28001, 40002, 40003},
										{2, 40003, 1, 40004},
										{0, -1, 40004, 4004},
										{25, -1, -1, -1},
										{16, -1, -1, 9},
										{17, -1, 34000, 34000},
										{2, 28000, 1, 40005},
										{17, -1, 40005, 28000},
										{17, -1, 28001, 28001},
										{18, -1, -1, 9},
										{0, -1, 4004, 40006},
										{0, -1, 40006, 28002},
										{1, 34000, 2000, 46000},
										{1, 46000, 28002, 46001},
										{1, 46001, 2001, 46002},
										{3, 34000, 28002, 46003},
										{1, 46002, 46003, 46004},
										{20, -1, -1, 46004},
										{16, -1, -1, 1},
										{17, -1, 28000, 28000},
										{18, -1, -1, 1},
										{0, -1, 4003, 40007},
										{2, 28001, 40007, 40008},
										{3, 40008, 2002, 46005},
										{20, -1, -1, 46005},
										{3, 34000, 28002, 46006},
										{1, 46006, 2001, 46007},
										{1, 46007, 28002, 46008},
										{1, 46008, 2000, 46009},
										{1, 46009, 34000, 46010},
										{20, -1, -1, 46010},
										{22, -1, -1, -1},
										{0, -1, 28000, 4004},
										{25, -1, -1, -1},
										{7, 28000, 2, 49000},
										{24, -1, 49000, 52},
										{0, -1, 1, 4005},
										{25, -1, -1, -1},
										{16, -1, -1, 48},
										{2, 28000, 1, 40000},
										{17, -1, 40000, 28000},
										{18, -1, -1, 48},
										{0, -1, 4005, 40001},
										{3, 28000, 40001, 40002},
										{0, -1, 40002, 4005},
										{25, -1, -1, -1},
										{16, -1, -1, 60},
										{18, -1, -1, 60},
										{25, -1, -1, -1},
										{20, -1, -1, 2003},
										{2, -1, 2004, 22000},
										{20, -1, -1, 22000},
										{2, -1, 4, 16000},
										{3, 3, 16000, 16001},
										{1, 16001, 5, 16002},
										{2, -1, 5, 16003},
										{1, 16002, 16003, 16004},
										{20, -1, -1, 16004},
										{2, -1, 1000, 19000},
										{20, -1, -1, 19000},
										{16, -1, -1, 1},
										{2, -1, 1, 16005},
										{17, -1, 16005, 28000},
										{18, -1, -1, 1},
										{0, -1, 4003, 16006},
										{20, -1, -1, 16006},
										{16, -1, -1, 1},
										{17, -1, 0, 28000},
										{18, -1, -1, 1},
										{0, -1, 4003, 16007},
										{20, -1, -1, 16007},
										{16, -1, -1, 1},
										{17, -1, 1, 28000},
										{18, -1, -1, 1},
										{0, -1, 4003, 16008},
										{20, -1, -1, 16008},
										{22, -1, -1, -1},
										{20, -1, -1, 2005},
										{21, -1, -1, -1},
										{19, -1, -1, 4000},
										{20, -1, -1, 2006},
										{21, -1, -1, -1},
										{19, -1, -1, 10000},
										{16, -1, -1, 9},
										{17, -1, 10000, 34000},
										{17, -1, 4000, 28000},
										{17, -1, 4000, 28001},
										{18, -1, -1, 9},
										{0, -1, 4004, 16009},
										{0, -1, 0, 4000},
										{9, 4000, 6, 25000},
										{24, -1, 25000, 117},
										{1, 4000, 2007, 22001},
										{16, -1, -1, 48},
										{17, -1, 4000, 28000},
										{18, -1, -1, 48},
										{0, -1, 4005, 16011},
										{1, 22001, 16011, 22002},
										{20, -1, -1, 22002},
										{22, -1, -1, -1},
										{1, 4000, 1, 16010},
										{0, -1, 16010, 4000},
										{23, -1, -1, 104},
										{20, -1, -1, 2008},
										{20, -1, -1, 4000},
										{22, -1, -1, -1},
										{20, -1, -1, 2009},
										{22, -1, -1, -1},
										{20, -1, -1, 2010},
										{20, -1, -1, 2011},
										{20, -1, -1, 2012},
										{20, -1, -1, 2013},
										{20, -1, -1, 2014},
										{21, -1, -1, -1},
										{20, -1, -1, 2015},
										{1, 2016, 2017, 22003},
										{20, -1, -1, 22003},
										{22, -1, -1, -1},
										{20, -1, -1, 2018},
										{20, -1, -1, 2014},
										{22, -1, -1, -1},
										{20, -1, -1, 2019},
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
