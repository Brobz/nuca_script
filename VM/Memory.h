#include <vector>
#include <string>

#ifndef Memory_H_
#define Memory_H_

#include "MemoryContext.h"

using namespace std;

class MemoryContext;

class Memory{
  public:

    static int MEM_ID;

    int id, signature;
    Memory* return_memory;
    vector<int> ints;
    vector<float> floats;
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
