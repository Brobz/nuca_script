#include "Memory.h"

using namespace std;

class MemoryMap{
    public:
      Memory local_mem;
      Memory temp_mem;

        MemoryMap(vector<int> local_size, vector<int> temp_size){
          local_mem = Memory(local_size);
          temp_mem = Memory(temp_size);
        };
};
