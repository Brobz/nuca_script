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
map<int, vector<vector<int>>> MEMORY_MAP_SIGN = {
										{1, {{3,3,1,1}, {7,2,7,9}, {6,3,10,0}}},
										};
// MEMORY //

// CONSTANTS //
map<int, string> CONSTANTS = {
										{0, "1"},
										{1, "3"},
										{2, "5"},
										{3, "10"},
										{250, "4.5"},
										{251, "1.3"},
										{500, "HI!"},
										{501, "lol"},
										{502, "\t"},
										{4, "2"},
										{503, "HAHA"},
										{5, "0"},
										{252, "0.1"},
										{504, "b is now:"},
										{505, "a is now:"},
										{506, "after while f value: "},
										{507, "a"},
										{508, "b"},
										{509, ""},
										};
// CONSTANTS //

// QUADS //
vector<vector<int>> QUADS = {
										{20, -1, -1, 1},
										{1, 0, 1, 5000},
										{0, -1, 5000, 1000},
										{0, -1, 2, 1001},
										{0, -1, 3, 1002},
										{0, -1, 250, 2000},
										{1, 2, 251, 6000},
										{0, -1, 6000, 2001},
										{0, -1, 3, 2002},
										{3, 500, 1001, 7000},
										{0, -1, 7000, 3000},
										{1, 1000, 0, 5001},
										{3, 500, 5001, 7001},
										{5, 3000, 7001, 8000},
										{0, -1, 8000, 4000},
										{3, 501, 4000, 7002},
										{3, 502, 4, 7003},
										{1, 7002, 7003, 7004},
										{3, 503, 0, 7005},
										{1, 7004, 7005, 7006},
										{0, -1, 7006, 3000},
										{0, -1, 0, 2001},
										{18, -1, -1, 2002},
										{0, -1, 5, 1000},
										{9, 1000, 3, 8001},
										{21, -1, 8001, 44},
										{0, -1, 3, 1001},
										{6, 1001, 5, 8002},
										{21, -1, 8002, 39},
										{6, 2002, 252, 8003},
										{21, -1, 8003, 34},
										{2, 2002, 252, 6001},
										{0, -1, 6001, 2002},
										{20, -1, -1, 29},
										{18, -1, -1, 504},
										{18, -1, -1, 1001},
										{2, 1001, 2, 5003},
										{0, -1, 5003, 1001},
										{20, -1, -1, 27},
										{18, -1, -1, 505},
										{18, -1, -1, 1000},
										{1, 1000, 2, 5002},
										{0, -1, 5002, 1000},
										{20, -1, -1, 24},
										{18, -1, -1, 506},
										{18, -1, -1, 2002},
										{5, 0, 0, 8004},
										{3, 1000, 8004, 5004},
										{5, 4, 4, 8005},
										{3, 1001, 8005, 5005},
										{1, 5004, 5005, 5006},
										{0, -1, 5006, 2002},
										{18, -1, -1, 1000},
										{18, -1, -1, 1001},
										{18, -1, -1, 1002},
										{18, -1, -1, 2000},
										{18, -1, -1, 2001},
										{18, -1, -1, 2002},
										{18, -1, -1, 3000},
										{18, -1, -1, 4000},
										{6, 507, 508, 8006},
										{18, -1, -1, 8006},
										{8, 507, 508, 8007},
										{18, -1, -1, 8007},
										{13, -1, 509, 8008},
										{18, -1, -1, 8008},
										{22, -1, -1, -1},
										};
// QUADS //

// GLOBAL VARS //
int PROGRAM_START; // Quad index of the start of main()
bool RUNNING = false;
int IP; // Instruction Pointer
MemoryMap GLOBAL_MEM;
stack<MemoryMap> MEMORY_STACK;
// GLOBAL VARS //


Value str_to_val(string str, int type){
  Value v;
  switch (type) {
    case 0: // INT
    {
      v.set_i(stoi(str));
    }  break;
    case 1: // FLOAT
    {
      v.set_f(stof(str));
    }  break;
    case 2: // STRING
    {
      v.set_s(str);
    }  break;
    case 3: // BOOL
    {
      v.set_b(stoi(str));
    }  break;
  }
  return v;
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
  cout << "Error: could not read "  << index << " from memory" << endl;
  abort();
}

Value read_from_memory(int index){
  string mem_sign = mem_index_to_mem_signature(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << "Error: No local context to read "  << index << " from memory" << endl;
      abort(); // ERROR! No context to read local variable from
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
        v.set_i(MEMORY_STACK.top().local_mem.ints[index - 9000]);
      }
      break;
    case 210:
      {
        v.set_f(MEMORY_STACK.top().local_mem.floats[index - 10000]);
      }
      break;
    case 220:
      {
        v.set_s(MEMORY_STACK.top().local_mem.strings[index - 11000]);
      }
      break;
    case 230:
      {
        v.set_b(MEMORY_STACK.top().local_mem.booleans[index - 12000]);
      }
      break;
    case 201:
      {
        v.set_i(MEMORY_STACK.top().temp_mem.ints[index - 13000]);
      }
      break;
    case 211:
      {
        v.set_f(MEMORY_STACK.top().temp_mem.floats[index - 14000]);
      }
      break;
    case 221:
      {
        v.set_s(MEMORY_STACK.top().temp_mem.strings[index - 15000]);
      }
      break;
    case 231:
      {
        v.set_b(MEMORY_STACK.top().temp_mem.booleans[index - 16000]);
      }
      break;
    default:
    {
      // ERROR! Nothing was read
      cout << "Error: could not read "  << index << " from memory" << endl;
      abort();
    }
  }

  return v;
}

int write_to_memory(int index, string value){
  string mem_sign = mem_index_to_mem_signature(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << "Error: No local context to write "  << index << " to memory" << endl;
      abort(); // ERROR! No context to write local variable to
    }
  }
  int int_mem_sign = stoi(mem_sign);
  switch (int_mem_sign) {
    case 0:
      {
        GLOBAL_MEM.const_mem.ints[index] = stoi(value);
      }
      break;
    case 10:
      {
        GLOBAL_MEM.const_mem.floats[index - 250] = stof(value);
      }
      break;
    case 20:
      {
        GLOBAL_MEM.const_mem.strings[index - 500] = value;
      }
      break;
    case 30:
      {
        GLOBAL_MEM.const_mem.booleans[index - 750] = stoi(value);
      }
      break;
    case 100:
      {
        GLOBAL_MEM.local_mem.ints[index - 1000] = stoi(value);
      }
      break;
    case 110:
      {
        GLOBAL_MEM.local_mem.floats[index - 2000] = stof(value);
      }
      break;
    case 120:
      {
        GLOBAL_MEM.local_mem.strings[index - 3000] = value;
      }
      break;
    case 130:
      {
        GLOBAL_MEM.local_mem.booleans[index - 4000] = stoi(value);
      }
      break;
    case 101:
      {
        GLOBAL_MEM.temp_mem.ints[index - 5000] = stoi(value);
      }
      break;
    case 111:
      {
        GLOBAL_MEM.temp_mem.floats[index - 6000] = stof(value);
      }
      break;
    case 121:
      {
        GLOBAL_MEM.temp_mem.strings[index - 7000] = value;
      }
      break;
    case 131:
      {
        GLOBAL_MEM.temp_mem.booleans[index - 8000] = stoi(value);
      }
      break;
    case 200:
      {
        MEMORY_STACK.top().local_mem.ints[index - 9000] = stoi(value);
      }
      break;
    case 210:
      {
        MEMORY_STACK.top().local_mem.floats[index - 10000] = stof(value);
      }
      break;
    case 220:
      {
        MEMORY_STACK.top().local_mem.strings[index - 11000] = value;
      }
      break;
    case 230:
      {
        MEMORY_STACK.top().local_mem.booleans[index - 12000] = stoi(value);
      }
      break;
    case 201:
      {
        MEMORY_STACK.top().temp_mem.ints[index - 13000] = stoi(value);
      }
      break;
    case 211:
      {
        MEMORY_STACK.top().temp_mem.floats[index - 14000] = stof(value);
      }
      break;
    case 221:
      {
        MEMORY_STACK.top().temp_mem.strings[index - 15000] = value;
      }
      break;
    case 231:
      {
        MEMORY_STACK.top().temp_mem.booleans[index - 16000] = stoi(value);
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

void setup(){
  for (auto const& pair : CONSTANTS){
    if (write_to_memory(pair.first, pair.second)){
      cout << "Error writting " << pair.second << " to " << pair.first << endl;
      abort();
    }
  }

  IP = 0;
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

      case 18:			// PRINT
        {
          Value printable = read_from_memory(QUADS[IP][3]);
          cout << printable.to_str() << endl;
          IP++;
        }
        break;

      case 20:			// GOTO
        {
          int to_dir = QUADS[IP][3];
          IP = to_dir;
        }
        break;

			case 21:			// GOTOF
				{
					int to_dir = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_dir;
					else IP++;
				}
				break;

      case 22:			// END
        {
          RUNNING = false;
        }
        break;

      default:
        {
        cout << "Unknown op: " << op << endl;
        abort();
        }
    }
  }
}

int main () {

  // Memory signature with highest value is always pointing to the start of the main() method
  PROGRAM_START = MEMORY_MAP_SIGN.rbegin()->first;

  // Pushes GLOBAL memory into the stack
  GLOBAL_MEM = MemoryMap(MEMORY_MAP_SIGN[PROGRAM_START][0], MEMORY_MAP_SIGN[PROGRAM_START][1], MEMORY_MAP_SIGN[PROGRAM_START][2]);

  // Write constants to memory
  setup();

  // Run program
  run();

  return 0;
}
