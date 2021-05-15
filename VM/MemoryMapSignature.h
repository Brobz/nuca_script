#include <string>
#include <vector>


using namespace std;

class MemoryMapSignature{
    public:
      string ID;
      vector<vector<int>> signature;

      MemoryMapSignature(){};
      MemoryMapSignature(string id, vector<vector<int>> sign){
        ID = id;
        signature = sign;
      };
};
