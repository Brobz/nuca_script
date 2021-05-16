// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryMap.h"

using namespace std;


// MEMORY //
map<int, vector<vector<int>>> MEMORY_MAP_SIGN = {
										{1, {{3,3,1,1}, {0,0,0,0}, {3,3,1,0}}},
										};
// MEMORY //

// CONSTANTS //
map<int, string> CONSTANTS = {
										{0, "1"},
										{1, "5"},
										{2, "10"},
										{250, "4.5"},
										{251, "1.3"},
										{252, "3.3"},
										{500, "HI!"},
										};
// CONSTANTS //

// QUADS //
vector<vector<int>> QUADS = {
										{20, -1, -1, 1},
										{0, -1, 0, 1000},
										{0, -1, 1, 1001},
										{0, -1, 2, 1002},
										{0, -1, 250, 2000},
										{0, -1, 251, 2001},
										{0, -1, 252, 2002},
										{0, -1, 500, 3000},
										{0, -1, 0, 4000},
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

vector<string> read_from_memory(int index){
  string mem_sign = mem_index_to_mem_signature(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << "Error: No local context to read "  << index << " from memory" << endl;
      abort(); // ERROR! No context to read local variable from
    }
  }

  vector<string> retn_obj;
  retn_obj.push_back(string(1, mem_sign[1]));

  switch (stoi(mem_sign)) {
    case 0:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.const_mem.ints[index]));
      }
      break;
    case 10:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.const_mem.floats[index - 250]));
      }
      break;
    case 20:
      {
        retn_obj.push_back(GLOBAL_MEM.const_mem.strings[index - 500]);
      }
      break;
    case 30:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.const_mem.booleans[index - 750]));
      }
      break;
    case 100:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.local_mem.ints[index - 1000]));
      }
      break;
    case 110:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.local_mem.floats[index - 2000]));
      }
      break;
    case 120:
      {
        retn_obj.push_back(GLOBAL_MEM.local_mem.strings[index - 3000]);
      }
      break;
    case 130:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.local_mem.booleans[index - 4000]));
      }
      break;
    case 101:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.temp_mem.ints[index - 5000]));
      }
      break;
    case 111:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.temp_mem.floats[index - 6000]));
      }
      break;
    case 121:
      {
        retn_obj.push_back(GLOBAL_MEM.temp_mem.strings[index - 7000]);
      }
      break;
    case 131:
      {
        retn_obj.push_back(to_string(GLOBAL_MEM.temp_mem.booleans[index - 8000]));
      }
      break;
    case 200:
      {
        retn_obj.push_back(to_string(MEMORY_STACK.top().local_mem.ints[index - 9000]));
      }
      break;
    case 210:
      {
        retn_obj.push_back(to_string(MEMORY_STACK.top().local_mem.floats[index - 10000]));
      }
      break;
    case 220:
      {
        retn_obj.push_back(MEMORY_STACK.top().local_mem.strings[index - 11000]);
      }
      break;
    case 230:
      {
        retn_obj.push_back(to_string(MEMORY_STACK.top().local_mem.booleans[index - 12000]));
      }
      break;
    case 201:
      {
        retn_obj.push_back(to_string(MEMORY_STACK.top().temp_mem.ints[index - 13000]));
      }
      break;
    case 211:
      {
        retn_obj.push_back(to_string(MEMORY_STACK.top().temp_mem.floats[index - 14000]));
      }
      break;
    case 221:
      {
        retn_obj.push_back(MEMORY_STACK.top().temp_mem.strings[index - 15000]);
      }
      break;
    case 231:
      {
        retn_obj.push_back(to_string(MEMORY_STACK.top().temp_mem.booleans[index - 16000]));
      }
      break;
    default:
    {
      // ERROR! Nothing was read
      cout << "Error: could not read "  << index << " from memory" << endl;
      abort();
    }
  }

  return retn_obj;
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

    switch(op) {
      case 0:
        // =
        {
        int result_dir = QUADS[IP][3];
        string value = read_from_memory(QUADS[IP][2])[1];

        write_to_memory(result_dir, value);

        IP++;
        }
        break;

      case 1:
        // +
        {
          // Sum!
          int result_dir = QUADS[IP][3];

          vector<string> left_operand = read_from_memory(QUADS[IP][1]);
          vector<string> right_operand = read_from_memory(QUADS[IP][2]);

          int result_type = stoi(string(1, mem_index_to_mem_signature(result_dir)[1]));
          int left_type = stoi(left_operand[0]) ;
          int right_type = stoi(right_operand[0]);

          /*/
          switch(result_type){
            case 0:
              {
                // INTS
                if (left_type == 0){
                  int left_value = stoi(left_operand[1]);
                }
                int value = (int) (str_to_val(left_operand[1], left_type) + str_to_val(right_operand[1], right_type));
                write_to_memory(result_dir, to_string(value));
              }
              break;
            case 1:
              {
                // FLOATS
                float value = (float) (str_to_val(left_operand[1], left_type) + str_to_val(right_operand[1], right_type));
                write_to_memory(result_dir, to_string(value));
              }
              break;
            case 2:
              {
                // STRINGS
                string value = str_to_val(left_operand[1], left_type) + str_to_val(right_operand[1], right_type);
                write_to_memory(result_dir, value);
              }
              break;
            case 3:
              {
                // BOOLEANS
                bool value = (bool) (str_to_val(left_operand[1], left_type) + str_to_val(right_operand[1], right_type));
                write_to_memory(result_dir, to_string(value));
              }
          }
          /*/

          IP++;
        }
        break;

      case 2:
        // -
        {
          // Subtract !
          IP++;
        }
        break;

      case 3:
        // *
        {
          // Mutiply!
          IP++;
        }
        break;

      case 4:
        // /
        {
          // Divide!
          IP++;
        }
        break;

      case 5:
        // ==
        {
          // Compare!
          IP++;
        }
        break;

      case 20:
        // GOTO
        {
          int to_dir = QUADS[IP][3];

          IP = to_dir;
        }
        break;

      case 22:
        // END
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

  GLOBAL_MEM.local_mem.printout();

  return 0;
}
