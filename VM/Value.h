#include <string>
#include <algorithm>
#include <iostream>

#ifndef Value_H_
#define Value_H_

#include "Memory.h"

class Memory;

using namespace std;

class Value{
    public:

      int type;

      long long i = 0;
      long double f = 0.0;
      string s = "";
      bool b = false;
      Memory o;

      Value(){
        type = -1;
      };

      Value(long long _i){
        type = 0;
        i = _i;
      };

      Value(long double _f){
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

      Value(Memory _o){
        type = 4;
        o = _o;
      };

      bool has_value(){
        return type >= 0;
      }

      string to_str(bool is_printable = false){
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
            if (is_printable) return b ? "True" : "False";
            else return to_string(b);
          } break;
          case 4: // OBJECT
          {
            return to_string(o.signature);
          } break;
          default:
          {
            cout << ">> Fatal Error: Unknown type " << type << endl;
            exit(EXIT_FAILURE);
          }
        }
      }


      Value operator+(const Value v){
        Value temp;
        int operation_case = stoi(to_string(type) + to_string(v.type));
        switch(operation_case){
          case 0: // INT + INT = INT
          {
            temp.set_i(i + v.i);
          } break;
          case 1: // INT + FLOAT = FLOAT
          {
            temp.set_f(i + v.f);
          } break;
          case 2: // INT + STRING = STRING
          {
            temp.set_s(to_string(i) + v.s);
          } break;
          case 10: // FLOAT + INT + FLOAT
          {
            temp.set_f(f + v.i);
          } break;
          case 11: // FLOAT + FLOAT = FLOAT
          {
            temp.set_f(f + v.f);
          } break;
          case 12: // FLOAT + STRING = STRING
          {
            temp.set_s(to_string(f) + v.s);
          } break;
          case 20: // STRING + INT = STRING
          {
            temp.set_s(s + to_string(v.i));
          } break;
          case 21: // STRING + FLOAT = STRING
          {
            temp.set_s(s + to_string(v.f));
          } break;
          case 22: // STRING + STRING = STRING
          {
            temp.set_s(s + v.s);
          } break;
          case 23: // STRING + BOOLEAN = STRING
          {
            temp.set_s(s + to_string(v.b));
          } break;
          case 32: // BOOLEAN + STRING = STRING
          {
            temp.set_s(to_string(b) + v.s);
          } break;
          default:
          {
            cout << ">> Fatal Error: Cannot sum case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            cout << ">> Fatal Error: Cannot subtract case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            if(i > 0){ // Multiply string
              for(int x = 0; x < i; x++){
                tmp_str += v.s;
              }
            }else{ // Multiply reversed string (negative coef)
              string copy(v.s);
              reverse(copy.begin(), copy.end());
              for(int x = 0; x > i; x--){
                tmp_str += copy;
              }
            }
            temp.set_s(tmp_str);
          } break;
          case 1: // INT * FLOAT
          {
            temp.set_f(i * v.f);
          } break;
          case 3: // INT * BOOLEAN
          {
            temp.set_i(i * (long long) v.b);
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
            temp.set_f(f * (long long) v.b);
          } break;
          case 20: // STRING * INT
          {
            string tmp_str = "";
            if(v.i > 0){ // Multiply string
              for(int x = 0; x < v.i; x++){
                tmp_str += s;
              }
            }else{ // Multiply reversed string (negative coef)
              string copy(s);
              reverse(copy.begin(), copy.end());
              for(int x = 0; x > v.i; x--){
                tmp_str += copy;
              }
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
            temp.set_f((long long) b * v.i);
          } break;
          case 31: // BOOLEAN * FLOAT
          {
            temp.set_f((long long) b * v.f);
          } break;
          case 32: // BOOLEAN * STRING
          {
            string tmp_str = "";
            if (b) tmp_str += v.s;
            temp.set_s(tmp_str);
          } break;
          default:
          {
            cout << ">> Fatal Error: Cannot multiply case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            if (v.i == 0){
              cout << ">> Fatal Error: division by zero" << endl;
              exit(EXIT_FAILURE);
            }
            temp.set_i(i / v.i);
          } break;
          case 1: // INT / FLOAT
          {
            if (v.f == 0){
              cout << ">> Fatal Error: division by zero" << endl;
              exit(EXIT_FAILURE);
            }
            temp.set_f(i / v.f);
          } break;
          case 10: // FLOAT / INT
          {
            if (v.i == 0){
              cout << ">> Fatal Error: division by zero" << endl;
              exit(EXIT_FAILURE);
            }
            temp.set_f(f / v.i);
          } break;
          case 11: // FLOAT / FLOAT
          {
            if (v.f == 0){
              cout << ">> Fatal Error: division by zero" << endl;
              exit(EXIT_FAILURE);
            }
            temp.set_f(f / v.f);
          } break;
          default:
          {
            cout << ">> Fatal Error: Cannot divide case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
          case 3: // INT == BOOLEAN
          {
            temp.set_b(i == v.b);
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
          case 30: // BOOLEAN == INT
          {
            temp.set_b(b == v.i);
          } break;
          case 33: // BOOLEAN == BOOLEAN
          {
            temp.set_b(b == v.b);
          } break;
          default:
          {
            cout << ">> Fatal Error: Cannot == case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            cout << ">> Fatal Error: Cannot > case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            cout << ">> Fatal Error: Cannot < case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            cout << ">> Fatal Error: Cannot >= case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            cout << ">> Fatal Error: Cannot <= case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            cout << ">> Fatal Error: Cannot && case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            cout << ">> Fatal Error: Cannot || case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
          }
        }
        return temp;
      }

      Value operator-(){
        Value temp;
        int operation_case = type;
        switch(operation_case){
          case 0: // -INT
          {
            temp.set_i(-i);
          } break;
          case 1: // -FLOAT
          {
            temp.set_f(-f);
          } break;
          case 2: // -STRING
          {
            string copy(s);
            reverse(copy.begin(), copy.end());
            temp.set_s(copy);
          } break;

          default:
          {
            cout << ">> Fatal Error: Cannot unary - case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
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
            cout << ">> Fatal Error: Cannot ! case " <<  operation_case << endl;
            exit(EXIT_FAILURE);
          }
        }
        return temp;
      }

      void set_i(long long _i){
        i = _i;
        type = 0;
      }

      void set_f(long double _f){
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

      void set_o(Memory _o){
        o = _o;
        type = 4;
      }
};

#endif /*Value_H_*/
