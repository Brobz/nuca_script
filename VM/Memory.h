#include <vector>

using namespace std;

class Memory{
  public:

    vector<int> ints;
    vector<float> floats;
    vector<string> strings;
    vector<bool> booleans;

    Memory(){};

    Memory(vector<int> size){
      for (int i = 0; i < size.size(); i++){
        if (!i) ints.resize(size[i]);
        else if (i == 1) floats.resize(size[i]);
        else if (i == 2) strings.resize(size[i]);
        else if (i == 3) booleans.resize(size[i]);
      }
    };

    void printout(){
      cout << "INTS: ";
      for (int i = 0; i < ints.size(); i++){
        cout << ints[i] << " ";
      }
      cout << endl;
      cout << "FLOATS: ";
      for (int i = 0; i < floats.size(); i++){
        cout << floats[i] << " ";
      }
      cout << endl;
      cout << "STRINGS: ";
      for (int i = 0; i < strings.size(); i++){
        cout << strings[i] << " ";
      }
      cout << endl;
      cout << "BOOLEANS: ";
      for (int i = 0; i < booleans.size(); i++){
        cout << booleans[i] << " ";
      }
      cout << endl;
    }
};
