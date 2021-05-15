// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryMap.h"

using namespace std;

/*/
-> Quads indices will be structured in a way that we can tell global from scoped variables and temps from vars apart
/*/

// MEMORY //
map<string, vector<vector<int>>> MEMORY_MAP_SIGN = {
										{"MYPROGRAM", {{4,7,6,3}, {13,23,9,17}}},
										{"void_FUNC", {{0,0,0,0}, {0,0,0,0}}},
										{"func", {{3,0,2,0}, {2,0,1,0}}},
										{"two_params", {{2,0,0,0}, {2,0,0,0}}},
										{"one_param", {{1,0,0,0}, {0,0,1,0}}},
										{"another_func", {{3,0,2,0}, {2,0,1,0}}},
										{"always_true", {{0,0,0,0}, {0,0,0,0}}},
										{"monster_void", {{0,0,0,0}, {0,0,0,0}}},
										};
// MEMORY //

// QUADS //
vector<vector<string>> QUADS = {
										{"GOTO", "_", "_", "32"},
										{"WR", "_", "_", "lol?"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "2", "c"},
										{"*", "func_param_int", "c", "t0"},
										{"=", "_", "t0", "func_var_int"},
										{"+", "func_var_int", "2", "t1"},
										{"*", "t1", "a", "t2"},
										{"=", "_", "t2", "b"},
										{"GTF", "_", "0", "12"},
										{"=", "_", "10", "func"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "5", "func"},
										{"ENDFNC", "_", "_", "_"},
										{"*", "a", "b", "t0"},
										{"+", "t0", "5", "t1"},
										{"=", "_", "t1", "two_params"},
										{"ENDFNC", "_", "_", "_"},
										{"*", "a", "HI!", "t0"},
										{"=", "_", "t0", "one_param"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "2", "c"},
										{"*", "func_param_int", "c", "t0"},
										{"=", "_", "t0", "func_var_int"},
										{"+", "func_var_int", "2", "t1"},
										{"*", "t1", "a", "t2"},
										{"=", "_", "t2", "b"},
										{"=", "_", "RETURN VALUE : )", "another_func"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "1", "always_true"},
										{"ENDFNC", "_", "_", "_"},
										{"ENDFNC", "_", "_", "_"},
										{"=", "_", "lol!", "lol"},
										{"*", "lol", "2", "t0"},
										{"=", "_", "t0", "lol_doubled"},
										{"+", "String manipulation is nice! Look: ", "lol_doubled", "t1"},
										{"*", "This will also be doubled", "2", "t2"},
										{"+", "t1", "t2", "t3"},
										{"=", "_", "t3", "another_str"},
										{"WR", "_", "_", "another_str"},
										{"RD", "_", "_", "a"},
										{"RD", "_", "_", "b"},
										{"RD", "_", "_", "c"},
										{"RD", "_", "_", "d"},
										{"RD", "_", "_", "e"},
										{"RD", "_", "_", "f"},
										{"RD", "_", "_", "g"},
										{"RD", "_", "_", "g"},
										{"!", "_", "test_bool", "t4"},
										{"!", "_", "res", "t5"},
										{"||", "t4", "t5", "t6"},
										{"!", "_", "t6", "t7"},
										{"!", "_", "t7", "t8"},
										{"=", "_", "t8", "res"},
										{"/", "c", "d", "t9"},
										{"+", "b", "t9", "t10"},
										{"-", "t10", "e", "t11"},
										{"*", "a", "t11", "t12"},
										{"/", "t12", "f", "t13"},
										{"*", "t13", "g", "t14"},
										{"-", "b", "c", "t15"},
										{"*", "a", "t15", "t16"},
										{"/", "t16", "d", "t17"},
										{"+", "t17", "e", "t18"},
										{">", "t14", "t18", "t19"},
										{"!", "_", "1", "t20"},
										{"||", "t19", "t20", "t21"},
										{"=", "_", "t21", "res"},
										{"*", "res", "5", "t22"},
										{"=", "_", "t22", "test_int"},
										{"*", "TRUE!", "res", "t23"},
										{"!", "_", "res", "t24"},
										{"*", "False!", "t24", "t25"},
										{"+", "t23", "t25", "t26"},
										{"=", "_", "t26", "test_str"},
										{"ERA", "_", "_", "func"},
										{"PARAM", "lol", "_", "1"},
										{"ERA", "_", "_", "one_param"},
										{"PARAM", "3", "_", "1"},
										{"GOSUB", "one_param", "_", "_"},
										{"=", "_", "one_param", "t27"},
										{"PARAM", "t27", "_", "2"},
										{"ERA", "_", "_", "two_params"},
										{"ERA", "_", "_", "func"},
										{"PARAM", "lol", "_", "1"},
										{"ERA", "_", "_", "one_param"},
										{"PARAM", "5", "_", "1"},
										{"GOSUB", "one_param", "_", "_"},
										{"=", "_", "one_param", "t28"},
										{"PARAM", "t28", "_", "2"},
										{"ERA", "_", "_", "two_params"},
										{"PARAM", "10", "_", "1"},
										{"PARAM", "20", "_", "2"},
										{"GOSUB", "two_params", "_", "_"},
										{"=", "_", "two_params", "t29"},
										{"PARAM", "t29", "_", "3"},
										{"GOSUB", "func", "_", "_"},
										{"=", "_", "func", "t30"},
										{"PARAM", "t30", "_", "1"},
										{"PARAM", "5", "_", "2"},
										{"GOSUB", "two_params", "_", "_"},
										{"=", "_", "two_params", "t31"},
										{"PARAM", "t31", "_", "3"},
										{"GOSUB", "func", "_", "_"},
										{"=", "_", "func", "t32"},
										{"=", "_", "t32", "func_result"},
										{"-", "2", "1", "t33"},
										{"==", "res", "t33", "t34"},
										{"+", "b", "c", "t35"},
										{"<", "t35", "10", "t36"},
										{"&&", "t34", "t36", "t37"},
										{"ERA", "_", "_", "always_true"},
										{"GOSUB", "always_true", "_", "_"},
										{"=", "_", "always_true", "t38"},
										{"||", "t37", "t38", "t39"},
										{"GTF", "_", "t39", "131"},
										{"+", "a", "b", "t40"},
										{">", "t40", "d", "t41"},
										{"GTF", "_", "t41", "128"},
										{"<", "a", "b", "t42"},
										{"GTF", "_", "t42", "125"},
										{"=", "_", "0.0", "a"},
										{"+", "b", "d", "t43"},
										{"=", "_", "t43", "b"},
										{"GOTO", "_", "_", "127"},
										{"+", "a", "b", "t44"},
										{"=", "_", "t44", "c"},
										{"GOTO", "_", "_", "130"},
										{"+", "b", "c", "t45"},
										{"=", "_", "t45", "a"},
										{"GOTO", "_", "_", "106"},
										{"*", "a", "c", "t46"},
										{"+", "b", "t46", "t47"},
										{"=", "_", "t47", "d"},
										{"=", "_", "1", "test_int"},
										{"*", "10", "5", "t48"},
										{"-", "t48", "40", "t49"},
										{"<", "test_int", "t49", "t50"},
										{"GTF", "_", "t50", "155"},
										{"WR", "_", "_", "loopin!"},
										{"*", "a", "c", "t56"},
										{"+", "b", "t56", "t57"},
										{"=", "_", "t57", "d"},
										{"WR", "_", "_", "test_int"},
										{"*", "a", "c", "t58"},
										{"+", "b", "t58", "t59"},
										{"=", "_", "t59", "d"},
										{"WR", "_", "_", "yeee!"},
										{"*", "1", "3", "t51"},
										{"+", "test_int", "t51", "t52"},
										{"/", "12", "3", "t53"},
										{"/", "t53", "2", "t54"},
										{"-", "t52", "t54", "t55"},
										{"=", "_", "t55", "test_int"},
										{"GOTO", "_", "_", "135"},
										{"*", "a", "c", "t60"},
										{"+", "b", "t60", "t61"},
										{"=", "_", "t61", "d"},
										{"WR", "_", "_", "The result is: "},
										{"WR", "_", "_", "test_int"},
										{"WR", "_", "_", "test_str"},
										{"END", "_", "_", "_"},
										};
// QUADS //

// GLOBAL VARS //
string PROGRAM_NAME;
stack<MemoryMap> MEMORY_STACK;
// GLOBAL VARS //

int main () {

  PROGRAM_NAME = MEMORY_MAP_SIGN.begin()->first;

  // Pushes GLOBAL memory into the stack
  MEMORY_STACK.push(MemoryMap(MEMORY_MAP_SIGN[PROGRAM_NAME][0], MEMORY_MAP_SIGN[PROGRAM_NAME][1]));

  for(int i = 0; i < QUADS.size(); i++){
    cout << i << ": " << QUADS[i][0] << " " << QUADS[i][1] << " " << QUADS[i][2] << " " << QUADS[i][3] << endl;
  }

  MEMORY_STACK.top().local_mem.printout();
  MEMORY_STACK.top().temp_mem.printout();
  
  return 0;
}
