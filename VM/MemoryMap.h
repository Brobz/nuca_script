#include "Memory.h"

using namespace std;

class MemoryMap{
    public:
      Memory const_mem, local_mem, temp_mem;

      MemoryMap(){};

      MemoryMap(vector<int> local_size, vector<int> temp_size){
        local_mem = Memory(local_size);
        temp_mem = Memory(temp_size);
      };

      MemoryMap(vector<int> local_size, vector<int> temp_size, vector<int> const_size){
        local_mem = Memory(local_size);
        temp_mem = Memory(temp_size);
        const_mem = Memory(const_size);
      };
};
