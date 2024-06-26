#include <vector>
#include <string>

#ifndef Memory_H_
#define Memory_H_

#include "MemoryContext.h"

using namespace std;

class MemoryContext;

class Memory{

  /*/

        The bottom of the VM memory architecture:
        This class contains all of the values for a specific segment of memory,
        and is constantly instantiated by the MemoryContext instances that control
        the flow of memory during execution
        
  

    #                                   // Memory Signature Translation
    #
    #                                           0 -> INT
    #                       0 -> CONSANT        1 -> FLOAT
    #                       1 -> GLOBAL         2 -> STRING
    #                       2 -> LOCAL          3 -> BOOLEAN        0 -> VAR
    #                       3 -> CLASS          4 -> OBJECT         1 -> TMP
  
  /*/

  public:

    static int MEM_ID;

    int id, signature;
    Memory* return_memory;
    vector<long long> ints;
    vector<long double> floats;
    vector<string> strings;
    vector<bool> booleans;
    vector<Memory> objects;

    Memory(){
      id = -1;
      signature = -1;
    };

    Memory(vector<int> size, int sign = -1){
      for (int i = 0; i < size.size(); i++){
        if (!i) ints.resize(size[i]);
        else if (i == 1) floats.resize(size[i]);
        else if (i == 2) strings.resize(size[i]);
        else if (i == 3) booleans.resize(size[i]);
        else if (i == 4) objects.resize(size[i]);
      }
      signature = sign;
      id = Memory::MEM_ID;
      Memory::MEM_ID++;
    };

    void printout(){
      cout << "MEMORY ID " << id << endl;

      cout << "INTS: ";
      for (int i = 0; i < ints.size(); i++){
        cout << ints[i] << " | ";
      }
      cout << endl;
      cout << "FLOATS: ";
      for (int i = 0; i < floats.size(); i++){
        cout << floats[i] << " | ";
      }
      cout << endl;
      cout << "STRINGS: ";
      for (int i = 0; i < strings.size(); i++){
        cout << strings[i] << " | ";
      }
      cout << endl;
      cout << "BOOLEANS: ";
      for (int i = 0; i < booleans.size(); i++){
        cout << booleans[i] << " | ";
      }
    }
};

#endif /*Memory_H_*/
