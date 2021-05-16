#include <string>
#include <iostream>

using namespace std;

class Value{
    public:
      int type;

      int i = 0;
      float f = 0.0;
      string s = "";
      bool b = false;

      Value(){};

      Value(int _i){
        type = 0;
        i = _i;
      };

      Value(float _f){
        type = 1;
        f = _f;
      };

      Value(string _s){
        type = 2;
        s = _s;
      };

      Value(bool _b){
        type = 3;
        b = _b;
      };

      string to_str(){
        switch(type){
          case 0: // INT
          {
            return to_string(i);
          } break;
          case 1: // FLOAT
          {
            return to_string(f);
          } break;
          case 2: // STRING
          {
            return s;
          } break;
          case 3: // BOOLEAN
          {
            return to_string(b);
          } break;
          default:
          {
            cout << "Unknown type " << type << endl;
            abort();
          }
        }
      }


      Value operator+(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT + INT
          {
            temp.set_i(i + v.i);
          } break;
          case 1: // INT + FLOAT
          {
            temp.set_f(i + v.f);
          } break;
          case 10: // FLOAT + INT
          {
            temp.set_f(f + v.i);
          } break;
          case 11: // FLOAT + FLOAT
          {
            temp.set_f(f + v.f);
          } break;
          case 22: // STRING + STRING
          {
            temp.set_s(s + v.s);
          } break;
          default:
          {
            cout << "Cannot sum case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator-(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT - INT
          {
            temp.set_i(i - v.i);
          } break;
          case 1: // INT - FLOAT
          {
            temp.set_f(i - v.f);
          } break;
          case 10: // FLOAT - INT
          {
            temp.set_f(f - v.i);
          } break;
          case 11: // FLOAT - FLOAT
          {
            temp.set_f(f - v.f);
          } break;
          default:
          {
            cout << "Cannot subtract case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator*(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT * INT
          {
            temp.set_i(i * v.i);
          } break;
          case 2: // INT * STRING
          {
            string tmp_str = "";
            for(int x = 0; x < i; x++){
              tmp_str += v.s;
            }
            temp.set_s(tmp_str);
          } break;
          case 1: // INT * FLOAT
          {
            temp.set_f(i * v.f);
          } break;
          case 3: // INT * BOOLEAN
          {
            temp.set_i(i * (int) v.b);
          } break;
          case 10: // FLOAT * INT
          {
            temp.set_f(f * v.i);
          } break;
          case 11: // FLOAT * FLOAT
          {
            temp.set_f(f * v.f);
          } break;
          case 13: // FLOAT * BOOLEAN
          {
            temp.set_f(f * (int) v.b);
          } break;
          case 20: // STRING * INT
          {
            string tmp_str = "";
            for(int x = 0; x < v.i; x++){
              tmp_str += s;
            }
            temp.set_s(tmp_str);
          } break;
          case 23: // STRING * BOOLEAN
          {
            string tmp_str = "";
            if (v.b) tmp_str += s;
            temp.set_s(tmp_str);
          } break;
          case 30: // BOOLEAN * INT
          {
            temp.set_f((int) b * v.i);
          } break;
          case 31: // BOOLEAN * FLOAT
          {
            temp.set_f((int) b * v.f);
          } break;
          case 32: // BOOLEAN * STRING
          {
            string tmp_str = "";
            if (b) tmp_str += v.s;
            temp.set_s(tmp_str);
          } break;
          default:
          {
            cout << "Cannot multiply case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator/(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT / INT
          {
            temp.set_i(i / v.i);
          } break;
          case 1: // INT / FLOAT
          {
            temp.set_f(i / v.f);
          } break;
          case 10: // FLOAT / INT
          {
            temp.set_f(f / v.i);
          } break;
          case 11: // FLOAT / FLOAT
          {
            temp.set_f(f / v.f);
          } break;
          default:
          {
            cout << "Cannot divide case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator==(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT == INT
          {
            temp.set_b(i == v.i);
          } break;
          case 1: // INT == FLOAT
          {
            temp.set_b(i == v.f);
          } break;
          case 10: // FLOAT == INT
          {
            temp.set_b(f == v.i);
          } break;
          case 11: // FLOAT == FLOAT
          {
            temp.set_b(f == v.f);
          } break;
          case 22: // STRING == STRING
          {
            temp.set_b(s == v.s);
          } break;
          case 33: // BOOLEAN == BOOLEAN
          {
            temp.set_b(b == v.b);
          } break;
          default:
          {
            cout << "Cannot == case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator>(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT > INT
          {
            temp.set_b(i > v.i);
          } break;
          case 1: // INT > FLOAT
          {
            temp.set_b(i > v.f);
          } break;
          case 10: // FLOAT > INT
          {
            temp.set_b(f > v.i);
          } break;
          case 11: // FLOAT > FLOAT
          {
            temp.set_b(f > v.f);
          } break;
          case 22: // STRING > STRING
          {
            temp.set_b(s.size() > v.s.size());
          } break;
          default:
          {
            cout << "Cannot > case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator<(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT < INT
          {
            temp.set_b(i < v.i);
          } break;
          case 1: // INT < FLOAT
          {
            temp.set_b(i < v.f);
          } break;
          case 10: // FLOAT < INT
          {
            temp.set_b(f < v.i);
          } break;
          case 11: // FLOAT < FLOAT
          {
            temp.set_b(f < v.f);
          } break;
          case 22: // STRING < STRING
          {
            temp.set_b(s.size() < v.s.size());
          } break;
          default:
          {
            cout << "Cannot < case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator>=(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT >= INT
          {
            temp.set_b(i >= v.i);
          } break;
          case 1: // INT >= FLOAT
          {
            temp.set_b(i >= v.f);
          } break;
          case 10: // FLOAT >= INT
          {
            temp.set_b(f >= v.i);
          } break;
          case 11: // FLOAT >= FLOAT
          {
            temp.set_b(f >= v.f);
          } break;
          case 22: // STRING >= STRING
          {
            temp.set_b(s.size() >= v.s.size());
          } break;
          default:
          {
            cout << "Cannot >= case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator<=(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT <= INT
          {
            temp.set_b(i <= v.i);
          } break;
          case 1: // INT <= FLOAT
          {
            temp.set_b(i <= v.f);
          } break;
          case 10: // FLOAT <= INT
          {
            temp.set_b(f <= v.i);
          } break;
          case 11: // FLOAT <= FLOAT
          {
            temp.set_b(f <= v.f);
          } break;
          case 22: // STRING <= STRING
          {
            temp.set_b(s.size() <= v.s.size());
          } break;
          default:
          {
            cout << "Cannot <= case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator&&(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT && INT
          {
            temp.set_b(i && v.i);
          } break;
          case 1: // INT && FLOAT
          {
            temp.set_b(i && v.f);
          } break;
          case 2: // INT && STRING
          {
            temp.set_b(i && v.s.size());
          } break;
          case 3: // INT && BOOL
          {
            temp.set_b(i && v.b);
          } break;
          case 10: // FLOAT && INT
          {
            temp.set_b(f && v.i);
          } break;
          case 11: // FLOAT && FLOAT
          {
            temp.set_b(f && v.f);
          } break;
          case 12: // FLOAT && STRING
          {
            temp.set_b(f && v.s.size());
          } break;
          case 13: // FLOAT && BOOL
          {
            temp.set_b(f && v.b);
          } break;
          case 20: // STRING && INT
          {
            temp.set_b(s.size() && v.i);
          } break;
          case 21: // STRING && FLOAT
          {
            temp.set_b(s.size() && v.f);
          } break;
          case 22: // STRING && STRING
          {
            temp.set_b(s.size() && v.s.size());
          } break;
          case 23: // STRING && BOOL
          {
            temp.set_b(s.size() && v.b);
          } break;
          case 30: // BOOl && INT
          {
            temp.set_b(b && v.i);
          } break;
          case 31: // BOOl && FLOAT
          {
            temp.set_b(b && v.f);
          } break;
          case 32: // BOOl && STRING
          {
            temp.set_b(b && v.s.size());
          } break;
          case 33: // BOOl && BOOL
          {
            temp.set_b(b && v.b);
          } break;
          default:
          {
            cout << "Cannot && case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator||(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT || INT
          {
            temp.set_b(i || v.i);
          } break;
          case 1: // INT || FLOAT
          {
            temp.set_b(i || v.f);
          } break;
          case 2: // INT || STRING
          {
            temp.set_b(i || v.s.size());
          } break;
          case 3: // INT || BOOL
          {
            temp.set_b(i || v.b);
          } break;
          case 10: // FLOAT || INT
          {
            temp.set_b(f || v.i);
          } break;
          case 11: // FLOAT || FLOAT
          {
            temp.set_b(f || v.f);
          } break;
          case 12: // FLOAT || STRING
          {
            temp.set_b(f || v.s.size());
          } break;
          case 13: // FLOAT || BOOL
          {
            temp.set_b(f || v.b);
          } break;
          case 20: // STRING || INT
          {
            temp.set_b(s.size() || v.i);
          } break;
          case 21: // STRING || FLOAT
          {
            temp.set_b(s.size() || v.f);
          } break;
          case 22: // STRING || STRING
          {
            temp.set_b(s.size() || v.s.size());
          } break;
          case 23: // STRING || BOOL
          {
            temp.set_b(s.size() || v.b);
          } break;
          case 30: // BOOl || INT
          {
            temp.set_b(b || v.i);
          } break;
          case 31: // BOOl || FLOAT
          {
            temp.set_b(b || v.f);
          } break;
          case 32: // BOOl || STRING
          {
            temp.set_b(b || v.s.size());
          } break;
          case 33: // BOOl || BOOL
          {
            temp.set_b(b || v.b);
          } break;
          default:
          {
            cout << "Cannot && case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      Value operator!(){
        Value temp;
        int operation_case = type;
        switch(operation_case){
          case 0: // !INT
          {
            temp.set_b(!i);
          } break;
          case 1: // !FLOAT
          {
            temp.set_b(!f);
          } break;
          case 2: // !STRING
          {
            temp.set_b(!s.size());
          } break;
          case 3: // !BOOLEAN
          {
            temp.set_b(!b);
          } break;
          default:
          {
            cout << "Cannot ! case " <<  operation_case << endl;
            abort();
          }
        }
        return temp;
      }

      void set_i(int _i){
        i = _i;
        type = 0;
      }

      void set_f(float _f){
        f = _f;
        type = 1;
      }

      void set_s(string _s){
        s = _s;
        type = 2;
      }

      void set_b(bool _b){
        b = _b;
        type = 3;
      }
};
