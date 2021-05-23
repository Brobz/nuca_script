#include "Memory.h"

using namespace std;

const string STRING_BUFFER_PADDING = " ";

class MemoryContext{
    public:


      int return_addr = 0;
      bool active = true;
      vector<string> print_buffer;
      Memory const_mem, local_mem, temp_mem;
      vector<vector<int>> sizes;

      MemoryContext(){
        active = false;
      };

      MemoryContext(vector<int> local_size, vector<int> temp_size){
        sizes.push_back(local_size);
        sizes.push_back(temp_size);
        local_mem = Memory(local_size);
        temp_mem = Memory(temp_size);
      };

      MemoryContext(vector<int> local_size, vector<int> temp_size, vector<int> const_size){
        sizes.push_back(local_size);
        sizes.push_back(temp_size);
        sizes.push_back(const_size);
        local_mem = Memory(local_size);
        temp_mem = Memory(temp_size);
        const_mem = Memory(const_size);
      };

      void add_to_print_buffer(string s){
        print_buffer.push_back(s);
      }


      string flush_print_buffer(){
        int buffer_size = print_buffer.size();
        string temp_string = "";
        for(int i = 0; i < buffer_size; i++){
          temp_string += (i + 1 < buffer_size) ? print_buffer[i] + STRING_BUFFER_PADDING : print_buffer[i];
        }
        print_buffer.clear();
        return temp_string;
      }

      void set_return_addr(int rtn_addr){
        return_addr = rtn_addr;
      }
};
