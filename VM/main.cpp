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
const map<int, vector<vector<int>>> MEMORY_MAP_SIGN = {
										{19, {{4,3,2,1}, {2,0,2,1}, {4,0,1,0}}},
										{1, {{0,0,1,0}, {0,0,1,0}}},
										{4, {{1,0,0,0}, {3,0,0,1}}},
										{16, {{3,0,1,0}, {0,0,0,0}}},
										};
// MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{0, "2"},
										{1, "1"},
										{2, "0"},
										{3, "12"},
										{500, "! = "},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{21, -1, -1, 19},
										{3, 11000, 0, 15000},
										{0, -1, 15000, 3001},
										{23, -1, -1, -1},
										{7, 9000, 0, 16000},
										{22, -1, 16000, 8},
										{0, -1, 1, 1003},
										{23, -1, -1, -1},
										{14, -1, -1, 4},
										{2, 9000, 1, 13000},
										{15, -1, 13000, 9000},
										{16, -1, -1, 4},
										{0, -1, 1003, 13001},
										{3, 9000, 13001, 13002},
										{0, -1, 13002, 1003},
										{23, -1, -1, -1},
										{14, -1, -1, 16},
										{16, -1, -1, 16},
										{23, -1, -1, -1},
										{0, -1, 2, 1000},
										{9, 1000, 3, 8000},
										{22, -1, 8000, 33},
										{1, 1000, 500, 7000},
										{14, -1, -1, 4},
										{15, -1, 1000, 9000},
										{16, -1, -1, 4},
										{0, -1, 1003, 5001},
										{1, 7000, 5001, 7001},
										{18, -1, -1, 7001},
										{20, -1, -1, -1},
										{1, 1000, 1, 5000},
										{0, -1, 5000, 1000},
										{21, -1, -1, 20},
										{24, -1, -1, -1},
										};
// QUADS //

// GLOBAL VARS //
int PROGRAM_START; // Quad index of the start of main()
bool RUNNING = false;
int IP, MEMORY_STACK_LIMIT; // Instruction Pointer, Recursion Limit
MemoryMap GLOBAL_MEM, LOCAL_MEM;
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

string mem_index_to_mem_signature(int index){
  if (index < 1000){ // CONSTANTS
    if (index < 250){
      return "000";
    }
    else if (index < 500){
      return "010";
    }
    else if (index < 750){
      return "020";
    }
    else{
      return "030";
    }
  }
  else if (index < 9000){ // GLOBALS
    // VARIABLES
    if (index < 2000){
      return "100";
    }
    else if (index < 3000){
      return "110";
    }
    else if (index < 4000){
      return "120";
    }
    else if (index < 5000){
      return "130";
    }
    // TEMPS
    else if (index < 6000){
      return "101";
    }
    else if (index < 7000){
      return "111";
    }
    else if (index < 8000){
      return "121";
    }
    else {
      return "131";
    }
  }
  else{ // LOCALS
    // VARIABLES
    if (index < 10000){
      return "200";
    }
    else if (index < 11000){
      return "210";
    }
    else if (index < 12000){
      return "220";
    }
    else if (index < 13000){
      return "230";
    }
    // TEMPS
    else if (index < 14000){
      return "201";
    }
    else if (index < 15000){
      return "211";
    }
    else if (index < 16000){
      return "221";
    }
    else {
      return "231";
    }
  }

  // ERROR! Nothing was written
  cout << ">> Error: could not read "  << index << " from memory" << endl;
  exit(EXIT_FAILURE);
}
// HELPER METHODS //

Value read_from_memory(int index){
  string mem_sign = mem_index_to_mem_signature(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << ">> Error: No local context to read "  << index << " from memory" << endl;
      exit(EXIT_FAILURE); // ERROR! No context to read local variable from
    }
  }

  Value v;

  switch (stoi(mem_sign)) {
    case 0:
      {
        v.set_i(GLOBAL_MEM.const_mem.ints[index]);
      }
      break;
    case 10:
      {
        v.set_f(GLOBAL_MEM.const_mem.floats[index - 250]);
      }
      break;
    case 20:
      {
        v.set_s(GLOBAL_MEM.const_mem.strings[index - 500]);
      }
      break;
    case 30:
      {
        v.set_b(GLOBAL_MEM.const_mem.booleans[index - 750]);
      }
      break;
    case 100:
      {
        v.set_i(GLOBAL_MEM.local_mem.ints[index - 1000]);
      }
      break;
    case 110:
      {
        v.set_f(GLOBAL_MEM.local_mem.floats[index - 2000]);
      }
      break;
    case 120:
      {
        v.set_s(GLOBAL_MEM.local_mem.strings[index - 3000]);
      }
      break;
    case 130:
      {
        v.set_b(GLOBAL_MEM.local_mem.booleans[index - 4000]);
      }
      break;
    case 101:
      {
        v.set_i(GLOBAL_MEM.temp_mem.ints[index - 5000]);
      }
      break;
    case 111:
      {
        v.set_f(GLOBAL_MEM.temp_mem.floats[index - 6000]);
      }
      break;
    case 121:
      {
        v.set_s(GLOBAL_MEM.temp_mem.strings[index - 7000]);
      }
      break;
    case 131:
      {
        v.set_b(GLOBAL_MEM.temp_mem.booleans[index - 8000]);
      }
      break;
    case 200:
      {
        v.set_i(LOCAL_MEM.local_mem.ints[index - 9000]);
      }
      break;
    case 210:
      {
        v.set_f(LOCAL_MEM.local_mem.floats[index - 10000]);
      }
      break;
    case 220:
      {
        v.set_s(LOCAL_MEM.local_mem.strings[index - 11000]);
      }
      break;
    case 230:
      {
        v.set_b(LOCAL_MEM.local_mem.booleans[index - 12000]);
      }
      break;
    case 201:
      {
        v.set_i(LOCAL_MEM.temp_mem.ints[index - 13000]);
      }
      break;
    case 211:
      {
        v.set_f(LOCAL_MEM.temp_mem.floats[index - 14000]);
      }
      break;
    case 221:
      {
        v.set_s(LOCAL_MEM.temp_mem.strings[index - 15000]);
      }
      break;
    case 231:
      {
        v.set_b(LOCAL_MEM.temp_mem.booleans[index - 16000]);
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
  string mem_sign = mem_index_to_mem_signature(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << ">> Error: No local context to write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE); // ERROR! No context to write local variable to
    }
  }
  int int_mem_sign = stoi(mem_sign);
  switch (int_mem_sign) {
    case 0:
      {
        GLOBAL_MEM.const_mem.ints[index] = s_stoi(value);
      }
      break;
    case 10:
      {
        GLOBAL_MEM.const_mem.floats[index - 250] = s_stof(value);
      }
      break;
    case 20:
      {
        GLOBAL_MEM.const_mem.strings[index - 500] = value;
      }
      break;
    case 30:
      {
        GLOBAL_MEM.const_mem.booleans[index - 750] = s_stob(value);
      }
      break;
    case 100:
      {
        GLOBAL_MEM.local_mem.ints[index - 1000] = s_stoi(value);
      }
      break;
    case 110:
      {
        GLOBAL_MEM.local_mem.floats[index - 2000] = s_stof(value);
      }
      break;
    case 120:
      {
        GLOBAL_MEM.local_mem.strings[index - 3000] = value;
      }
      break;
    case 130:
      {
        GLOBAL_MEM.local_mem.booleans[index - 4000] = s_stob(value);
      }
      break;
    case 101:
      {
        GLOBAL_MEM.temp_mem.ints[index - 5000] = s_stoi(value);
      }
      break;
    case 111:
      {
        GLOBAL_MEM.temp_mem.floats[index - 6000] = s_stof(value);
      }
      break;
    case 121:
      {
        GLOBAL_MEM.temp_mem.strings[index - 7000] = value;
      }
      break;
    case 131:
      {
        GLOBAL_MEM.temp_mem.booleans[index - 8000] = s_stob(value);
      }
      break;
    case 200:
      {
      LOCAL_MEM.local_mem.ints[index - 9000] = s_stoi(value);
      }
      break;
    case 210:
      {
      LOCAL_MEM.local_mem.floats[index - 10000] = s_stof(value);
      }
      break;
    case 220:
      {
      LOCAL_MEM.local_mem.strings[index - 11000] = value;
      }
      break;
    case 230:
      {
      LOCAL_MEM.local_mem.booleans[index - 12000] = s_stob(value);
      }
      break;
    case 201:
      {
      LOCAL_MEM.temp_mem.ints[index - 13000] = s_stoi(value);
      }
      break;
    case 211:
      {
      LOCAL_MEM.temp_mem.floats[index - 14000] = s_stof(value);
      }
      break;
    case 221:
      {
      LOCAL_MEM.temp_mem.strings[index - 15000] = value;
      }
      break;
    case 231:
      {
      LOCAL_MEM.temp_mem.booleans[index - 16000] = s_stob(value);
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
	string mem_sign = mem_index_to_mem_signature(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << ">> Error: No local context to write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE); // ERROR! No context to write local variable to
    }
  }

	int int_mem_sign = stoi(mem_sign);
  switch (int_mem_sign) {
		case 200:
      {
        MEMORY_STACK.top().local_mem.ints[index - 9000] = s_stoi(value);
      }
      break;
    case 210:
      {
        MEMORY_STACK.top().local_mem.floats[index - 10000] = s_stof(value);
      }
      break;
    case 220:
      {
        MEMORY_STACK.top().local_mem.strings[index - 11000] = value;
      }
      break;
    case 230:
      {
        MEMORY_STACK.top().local_mem.booleans[index - 12000] = s_stob(value);
      }
      break;
		default:
			{
				// ERROR! Nothing was read
	      cout << ">> Error: could not write "  << index << " to memory" << endl;
	      exit(EXIT_FAILURE);
			}
			break;
	}
}

void setup(){
  for (auto const& pair : CONSTANTS){
    if (write_to_memory(pair.first, pair.second)){
      cout << ">> Error writting " << pair.second << " to " << pair.first << endl;
      exit(EXIT_FAILURE);
    }
  }

  IP = 0; // Start execution at the first QUAD
	MEMORY_STACK_LIMIT = 100000;
}

void run(){

  RUNNING = true;
  while(RUNNING){
    int op = QUADS[IP][0];

		if (!op){
			// =

			int result_dir = QUADS[IP][3];
			Value value = read_from_memory(QUADS[IP][2]);

			write_to_memory(result_dir, value.to_str());

			IP++;
			continue;
		}

		else if (op < 13){
			// Arithmetic Epxressions (two operands, one solution)

			int result_dir = QUADS[IP][3];

			Value left_value = read_from_memory(QUADS[IP][1]);
			Value right_value = read_from_memory(QUADS[IP][2]);

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
						// Subtract !
						Value res_value = left_value - right_value;
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
			}
			IP++;
			continue;
		}

    switch(op) {
			case 13:			// !
				{
					// Negate!
					int result_dir = QUADS[IP][3];

					Value right_value = read_from_memory(QUADS[IP][2]);

					Value res_value = !right_value;

					write_to_memory(result_dir, res_value.to_str());

					IP++;
				}
				break;

			case 14:		// ERA
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

			case 15:		// PARAM
				{

					Value param_value = read_from_memory(QUADS[IP][2]);
					int param_addr = QUADS[IP][3];

					write_to_param(param_addr, param_value.to_str());
					IP++;
				}
				break;

			case 16:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					MEMORY_STACK.top().set_return_addr(IP + 1);
					LOCAL_MEM = MEMORY_STACK.top();
					IP = func_start_addr;
				}
				break;

			case 17:		// READ
				{

					int result_dir = QUADS[IP][3];

					string user_input;
					cin >> user_input;

					write_to_memory(result_dir, user_input);

					IP++;
				}
				break;

			case 18:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (MEMORY_STACK.size()) MEMORY_STACK.top().add_to_print_buffer(printable.to_str());
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str());
					IP++;
				}
				break;

      case 19:			// PRNT
        {
          string printable = (MEMORY_STACK.size()) ? MEMORY_STACK.top().flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 20:			// PRNTLN
        {
					string printable = (MEMORY_STACK.size()) ? MEMORY_STACK.top().flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable << endl;
          IP++;
        }
        break;

      case 21:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 22:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;


			case 23:			// ENDFNC
				{
					int return_addr = MEMORY_STACK.top().return_addr;
					MEMORY_STACK.pop();
					LOCAL_MEM = (MEMORY_STACK.size()) ? MEMORY_STACK.top() : MemoryMap();
					IP = return_addr;
				}
				break;

      case 24:			// END
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

  // Memory signature with highest value is always pointing to the start of the main() method
  PROGRAM_START = MEMORY_MAP_SIGN.rbegin()->first;

  // Pushes GLOBAL memory into the stack
  GLOBAL_MEM = MemoryMap(MEMORY_MAP_SIGN.at(PROGRAM_START).at(0), MEMORY_MAP_SIGN.at(PROGRAM_START).at(1), MEMORY_MAP_SIGN.at(PROGRAM_START).at(2));

  // Write constants to memory
  setup();

  // Run program
  run();

  return 0;
}
