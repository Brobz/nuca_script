// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryContext.h"
#include "Value.h"
#include "FileIO.h"

using namespace std;

// MEMORY_CONSTRAINTS //
const int MAX_CONSTANTS = 10000, MAX_SYMBOLS = 30000, MAX_TMP_SYMBOLS = 30000, MAX_OBJ_SYMBOLS = 30000, VAR_TYPES = 5, MEMORY_STACK_LIMIT = 100000;
// MEMORY_CONSTRAINTS //

// FUNCTION_MEMORY //
const map<int, vector<vector<int>>> FUNCTION_MEMORY_CONTEXT_SIGN = {
										{112, {{52,0,4,0,2}, {80,0,18,8,2}, {15,1,19,2,0}}},
										{1, {{0,0,1,0,0}, {49,0,1,0,1}}},
										{96, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{99, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{102, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{105, {{0,0,0,0,0}, {0,0,2,0,0}}},
										};
// FUNCTION_MEMORY //


// OBJECT_MEMORY //
const map<int, vector<int>> OBJECT_MEMORY_CONTEXT_SIGN = {
										{2, {51,0,1501,0,0}},
										};
// OBJECT_MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{30000, "0"},
										{30001, "1"},
										{0, "1500"},
										{1, "50"},
										{20000, "lol!"},
										{20001, "n:"},
										{2, "2"},
										{3, "10"},
										{4, "3"},
										{5, "44"},
										{6, "33"},
										{7, "22"},
										{20002, "05"},
										{20003, " "},
										{20004, "\n"},
										{20005, "\t"},
										{8, "1"},
										{10000, "2.33"},
										{20006, "lol"},
										{20007, "lolo"},
										{20008, "HI!"},
										{20009, "hilo"},
										{9, "20"},
										{10, "49"},
										{11, "45"},
										{12, "5"},
										{20010, "100"},
										{20011, ">> Enter file path:\n-- "},
										{20012, ">> Parsing file..."},
										{13, "0"},
										{14, "1499"},
										{20013, "END_OF_STREAM"},
										{20014, "Entry "},
										{20015, ": "},
										{20016, "file.txt"},
										{20017, " // An extra funny comment to confirm this works : ) "},
										{20018, " //"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{32, -1, -1, 112},
										{17, -1, 2, 160001},
										{18, -1, 640050, 490000},
										{16, -1, 1, 490001},
										{1, 490000, 490001, 490002},
										{19, -1, 490002, 640050, -1},
										{18, -1, 640050, 490003},
										{16, -1, 1, 490004},
										{2, 490003, 490004, 490005},
										{19, -1, 490005, 640050, -1},
										{1, 400000, 20000, 550000},
										{0, -1, 550000, 400000},
										{25, -1, -1, 20001},
										{18, -1, 640050, 490006},
										{25, -1, -1, 490006},
										{27, -1, -1, -1},
										{18, -1, 640050, 490007},
										{3, 490007, 2, 490008},
										{19, -1, 490008, 640050, -1},
										{16, -1, 0, 490009},
										{15, -1, 3, 50},
										{0, -1, 3, 490009},
										{16, -1, 0, 490010},
										{14, 640000, 490009, 490010},
										{18, 160001, 490010, 490011, 1},
										{16, -1, 0, 490012},
										{15, -1, 3, 50},
										{0, -1, 3, 490012},
										{16, -1, 0, 490013},
										{14, 640000, 490012, 490013},
										{16, -1, 0, 490014},
										{18, -1, 490013, 490014, 1},
										{3, 490014, 4, 490015},
										{1, 490011, 490015, 490016},
										{19, 160001, 490016, 490010, 2},
										{16, -1, 0, 490017},
										{15, -1, 5, 50},
										{0, -1, 5, 490017},
										{16, -1, 0, 490018},
										{14, 640000, 490017, 490018},
										{18, -1, 490018, 490019, 1},
										{2, -1, 6, 490020},
										{2, 490019, 490020, 490021},
										{19, -1, 490021, 490018, 2},
										{16, -1, 0, 490022},
										{15, -1, 3, 50},
										{0, -1, 3, 490022},
										{16, -1, 0, 490023},
										{14, 640000, 490022, 490023},
										{18, 160001, 490023, 490024, 1},
										{3, 7, 2, 490025},
										{16, -1, 0, 490026},
										{15, -1, 490025, 50},
										{0, -1, 490025, 490026},
										{16, -1, 0, 490027},
										{14, 640000, 490026, 490027},
										{16, -1, 0, 490028},
										{18, -1, 490027, 490028, 1},
										{1, 490024, 490028, 490029},
										{19, 160001, 490029, 490023, 2},
										{16, -1, 0, 490030},
										{15, -1, 3, 50},
										{0, -1, 3, 490030},
										{16, -1, 0, 490031},
										{14, 640000, 490030, 490031},
										{16, -1, 0, 490032},
										{18, 160001, 490031, 490032, 1},
										{25, -1, -1, 490032},
										{27, -1, -1, -1},
										{18, -1, 640050, 490033},
										{28, -1, 400000, 490034},
										{1, 490033, 490034, 490035},
										{18, -1, 640050, 490036},
										{1, 490035, 490036, 490037},
										{16, -1, 0, 490038},
										{15, -1, 3, 50},
										{0, -1, 3, 490038},
										{16, -1, 0, 490039},
										{14, 640000, 490038, 490039},
										{16, -1, 0, 490040},
										{18, -1, 490039, 490040, 1},
										{1, 490037, 490040, 490041},
										{19, -1, 490041, 640050, -1},
										{28, -1, 20002, 490042},
										{16, -1, 0, 490043},
										{15, -1, 3, 50},
										{0, -1, 3, 490043},
										{16, -1, 0, 490044},
										{14, 640000, 490043, 490044},
										{16, -1, 0, 490045},
										{18, -1, 490044, 490045, 1},
										{1, 490042, 490045, 490046},
										{18, -1, 640050, 490047},
										{1, 490046, 490047, 490048},
										{0, -1, 490048, 40000},
										{34, -1, -1, 1},
										{3, 20003, 340000, 550000},
										{0, -1, 550000, 100000},
										{34, -1, -1, 1},
										{3, 20004, 340000, 550000},
										{0, -1, 550000, 100001},
										{34, -1, -1, 1},
										{3, 20005, 340000, 550000},
										{0, -1, 550000, 100002},
										{34, -1, -1, 1},
										{18, -1, 700000, 550000},
										{20, -1, -1, 99},
										{21, -1, 8, 340000},
										{23, -1, -1, 99},
										{0, -1, 100001, 550001},
										{30, 0, 550000, 550001, 700001, 1500},
										{34, -1, -1, 1},
										{13, -1, 30000, 280000},
										{11, 30000, 30001, 280001},
										{11, 280000, 280001, 280002},
										{0, -1, 280002, 40001},
										{25, -1, -1, 40001},
										{27, -1, -1, -1},
										{33, -1, 30000, 122},
										{25, -1, -1, 30000},
										{27, -1, -1, -1},
										{32, -1, -1, 126},
										{33, -1, 30001, 126},
										{5, 10000, 10000, 280003},
										{25, -1, -1, 280003},
										{27, -1, -1, -1},
										{33, -1, 30000, 128},
										{32, -1, -1, 131},
										{5, 20006, 20007, 280004},
										{25, -1, -1, 280004},
										{27, -1, -1, -1},
										{17, -1, 2, 160000},
										{17, -1, 2, 160001},
										{1, 100003, 20008, 250000},
										{0, -1, 250000, 100003},
										{3, 100003, 4, 250001},
										{0, -1, 250001, 100003},
										{19, 160000, 20009, 700000, -1},
										{18, 160000, 700000, 250002},
										{25, -1, -1, 250002},
										{18, 160000, 700000, 250003},
										{18, 160000, 640050, 190000},
										{29, -1, 250003, 190000, 4, 250004},
										{25, -1, -1, 250004},
										{27, -1, -1, -1},
										{16, -1, 0, 190001},
										{15, -1, 3, 50},
										{0, -1, 3, 190001},
										{16, -1, 0, 190002},
										{14, 640000, 190001, 190002},
										{19, 160000, 9, 190002, 2},
										{18, 160000, 640050, 190003},
										{16, -1, 0, 190004},
										{15, -1, 3, 50},
										{0, -1, 3, 190004},
										{16, -1, 0, 190005},
										{14, 640000, 190004, 190005},
										{16, -1, 0, 190006},
										{18, 160000, 190005, 190006, 1},
										{2, 190003, 190006, 190007},
										{19, 160000, 190007, 640050, -1},
										{16, -1, 0, 190008},
										{15, -1, 10, 50},
										{0, -1, 10, 190008},
										{16, -1, 0, 190009},
										{14, 40002, 190008, 190009},
										{0, 1, 190009, 190010},
										{18, 160000, 640050, 190011},
										{2, 190010, 190011, 190012},
										{0, 2, 190012, 190009},
										{16, -1, 0, 190013},
										{15, -1, 11, 50},
										{0, -1, 11, 190013},
										{16, -1, 0, 190014},
										{14, 640000, 190013, 190014},
										{18, 160000, 190014, 190015, 1},
										{16, -1, 0, 190016},
										{15, -1, 10, 50},
										{0, -1, 10, 190016},
										{16, -1, 0, 190017},
										{14, 40002, 190016, 190017},
										{16, -1, 0, 190018},
										{0, 1, 190017, 190018},
										{1, 190015, 190018, 190019},
										{19, 160000, 190019, 190014, 2},
										{16, -1, 0, 190020},
										{15, -1, 11, 50},
										{0, -1, 11, 190020},
										{16, -1, 0, 190021},
										{14, 640000, 190020, 190021},
										{18, 160000, 190021, 190022, 1},
										{16, -1, 0, 190023},
										{15, -1, 10, 50},
										{0, -1, 10, 190023},
										{16, -1, 0, 190024},
										{14, 40002, 190023, 190024},
										{16, -1, 0, 190025},
										{0, 1, 190024, 190025},
										{3, 190022, 190025, 190026},
										{19, 160000, 190026, 190021, 2},
										{16, -1, 0, 190027},
										{15, -1, 10, 50},
										{0, -1, 10, 190027},
										{16, -1, 0, 190028},
										{14, 40002, 190027, 190028},
										{16, -1, 0, 190029},
										{0, 1, 190028, 190029},
										{25, -1, -1, 190029},
										{16, -1, 0, 190030},
										{15, -1, 11, 50},
										{0, -1, 11, 190030},
										{16, -1, 0, 190031},
										{14, 640000, 190030, 190031},
										{16, -1, 0, 190032},
										{18, 160000, 190031, 190032, 1},
										{25, -1, -1, 190032},
										{27, -1, -1, -1},
										{3, 12, 4, 190033},
										{1, 40001, 190033, 190034},
										{0, -1, 190034, 40001},
										{25, -1, -1, 40001},
										{27, -1, -1, -1},
										{16, -1, 0, 190035},
										{15, -1, 3, 50},
										{0, -1, 3, 190035},
										{16, -1, 0, 190036},
										{14, 640000, 190035, 190036},
										{16, -1, 0, 190037},
										{18, 160000, 190036, 190037, 1},
										{2, 40001, 190037, 190038},
										{0, -1, 190038, 40001},
										{25, -1, -1, 40001},
										{27, -1, -1, -1},
										{16, -1, 0, 190039},
										{15, -1, 12, 50},
										{0, -1, 12, 190039},
										{16, -1, 0, 190040},
										{14, 640000, 190039, 190040},
										{18, 160000, 190040, 190041, 1},
										{16, -1, 0, 190042},
										{15, -1, 3, 50},
										{0, -1, 3, 190042},
										{16, -1, 0, 190043},
										{14, 640000, 190042, 190043},
										{16, -1, 0, 190044},
										{18, 160000, 190043, 190044, 1},
										{1, 190041, 190044, 190045},
										{19, 160000, 190045, 190040, 2},
										{18, 160000, 640050, 190046},
										{16, -1, 0, 190047},
										{15, -1, 3, 50},
										{0, -1, 3, 190047},
										{16, -1, 0, 190048},
										{14, 640000, 190047, 190048},
										{16, -1, 0, 190049},
										{18, 160000, 190048, 190049, 1},
										{4, 190046, 190049, 190050},
										{19, 160000, 190050, 640050, -1},
										{16, -1, 0, 190051},
										{15, -1, 12, 50},
										{0, -1, 12, 190051},
										{16, -1, 0, 190052},
										{14, 640000, 190051, 190052},
										{18, 160000, 190052, 190053, 1},
										{16, -1, 1, 190054},
										{1, 190053, 190054, 190055},
										{19, 160000, 190055, 190052, 2},
										{16, -1, 0, 190056},
										{15, -1, 4, 50},
										{0, -1, 4, 190056},
										{16, -1, 0, 190057},
										{14, 40002, 190056, 190057},
										{16, -1, 0, 190058},
										{0, 1, 190057, 190058},
										{25, -1, -1, 190058},
										{16, -1, 0, 190059},
										{15, -1, 2, 50},
										{0, -1, 2, 190059},
										{16, -1, 0, 190060},
										{14, 40002, 190059, 190060},
										{16, -1, 0, 190061},
										{0, 1, 190060, 190061},
										{25, -1, -1, 190061},
										{27, -1, -1, -1},
										{16, -1, 0, 190062},
										{15, -1, 12, 50},
										{0, -1, 12, 190062},
										{16, -1, 0, 190063},
										{14, 640000, 190062, 190063},
										{16, -1, 0, 190064},
										{18, 160000, 190063, 190064, 1},
										{25, -1, -1, 190064},
										{18, 160000, 640050, 190065},
										{25, -1, -1, 190065},
										{27, -1, -1, -1},
										{20, -1, -1, 1},
										{21, -1, 20010, 400000},
										{23, -1, 160000, 1},
										{0, -1, 40000, 190066},
										{25, -1, -1, 190066},
										{27, -1, -1, -1},
										{25, -1, -1, 20011},
										{26, -1, -1, -1},
										{24, 160000, -1, 700000},
										{25, -1, -1, 20012},
										{27, -1, -1, -1},
										{20, -1, -1, 105},
										{23, -1, 160000, 105},
										{0, -1, 13, 40001},
										{7, 40001, 14, 280005},
										{16, -1, 0, 190067},
										{15, -1, 40001, 1500},
										{0, -1, 40001, 190067},
										{16, -1, 0, 190068},
										{14, 700001, 190067, 190068},
										{16, -1, 0, 250005},
										{18, 160000, 190068, 250005, 1},
										{12, 250005, 20013, 280006},
										{10, 280005, 280006, 280007},
										{33, -1, 280007, 350},
										{1, 20014, 40001, 250006},
										{1, 250006, 20015, 250007},
										{16, -1, 0, 190071},
										{15, -1, 40001, 1500},
										{0, -1, 40001, 190071},
										{16, -1, 0, 190072},
										{14, 700001, 190071, 190072},
										{16, -1, 0, 250008},
										{18, 160000, 190072, 250008, 1},
										{1, 250007, 250008, 250009},
										{25, -1, -1, 250009},
										{27, -1, -1, -1},
										{16, -1, 0, 190073},
										{15, -1, 40001, 1500},
										{0, -1, 40001, 190073},
										{16, -1, 0, 190074},
										{14, 700001, 190073, 190074},
										{16, -1, 0, 190075},
										{15, -1, 40001, 1500},
										{0, -1, 40001, 190075},
										{16, -1, 0, 190076},
										{14, 700001, 190075, 190076},
										{16, -1, 0, 250010},
										{18, 160000, 190076, 250010, 1},
										{29, -1, 250010, 13, 3, 250011},
										{19, 160000, 250011, 190074, 2},
										{16, -1, 1, 190069},
										{1, 40001, 190069, 190070},
										{0, -1, 190070, 40001},
										{32, -1, -1, 309},
										{20, -1, -1, 102},
										{21, -1, 3, 340000},
										{23, -1, 160000, 102},
										{0, -1, 100002, 250012},
										{1, 250012, 20017, 250013},
										{16, -1, 0, 190077},
										{15, -1, 3, 50},
										{0, -1, 3, 190077},
										{16, -1, 0, 190078},
										{14, 640000, 190077, 190078},
										{16, -1, 0, 190079},
										{18, 160001, 190078, 190079, 1},
										{1, 250013, 190079, 250014},
										{1, 250014, 20018, 250015},
										{20, -1, -1, 99},
										{21, -1, 8, 340000},
										{23, -1, 160000, 99},
										{0, -1, 100001, 250016},
										{1, 250015, 250016, 250017},
										{31, 160000, 20016, 250017, 700001, 1500},
										{35, -1, -1, -1},
										};
// QUADS //

// GLOBAL VARS //
int PROGRAM_START; // Quad index of the start of main()
bool RUNNING = false;
int IP; // Instruction Pointer
int THIS_OPERATOR_COUNTER; // To count how many this. accesses have happened
int Memory::MEM_ID = 0; // Start the memory id counter at 0;
MemoryContext GLOBAL_MEM;
MemoryContext* LOCAL_MEM;
Memory* THIS_MEM;
stack<MemoryContext> MEMORY_STACK;
stack<Memory*> OBJECT_MEMORY_STACK;
// GLOBAL VARS //


// HELPER METHODS //
const map<string, bool> STOB_MAP = {
							{"TRUE", 1},
							{"True", 1},
							{"true", 1},
							{"FALSE", 0},
							{"False", 0},
							{"false", 0},
};

// Safe String to Int
int s_stoi(string s){
	try{
		return stoi(s);
	}catch(...){
			if(!s.empty()) cout << ">> Fatal Error: Cannot resolve stoi(" << s << ")" << endl;
			else cout << ">> Fatal Error: Cannot resolve stoi of an empty string" << endl;
			exit(EXIT_FAILURE);
		}
}

// Safe String to Long Long
long long s_stoll(string s){
	try{
		return stoll(s);
	}catch(...){
			if(!s.empty()) cout << ">> Fatal Error: Cannot resolve stoi(" << s << ")" << endl;
			else cout << ">> Fatal Error: Cannot resolve stoi of an empty string" << endl;
			exit(EXIT_FAILURE);
		}
}

// Safe String to Long Double
long double s_stold(string s){
	try{
		return stold(s);
	}catch(...){
			if(!s.empty()) cout << ">> Fatal Error: Cannot resolve stof(" << s << ")" << endl;
			else cout << ">> Fatal Error: Cannot resolve stof of an empty string" << endl;
			exit(EXIT_FAILURE);
		}
	}

// Safe String to Bool
bool s_stob(string s){
	try{
		return stoi(s);
	}catch(...){
			if (STOB_MAP.count(s)){
				return STOB_MAP.at(s);
			}else{
				if(!s.empty()) cout << ">> Fatal Error: Cannot resolve stob(" << s << ")" << endl;
				else cout << ">> Fatal Error: Cannot resolve stob of an empty string" << endl;
				exit(EXIT_FAILURE);
			}
	}
}

string mem_index_to_mem_sign(int index){
  if (index < MAX_CONSTANTS * (VAR_TYPES - 1)){ // CONSTANTS
		string mem_sign = "0" + to_string(index / MAX_CONSTANTS) + "0";
		return mem_sign;
  }
  else if (index < MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES){ // GLOBALS
		string mem_sign = "1" + to_string(((index - MAX_CONSTANTS * (VAR_TYPES - 1)) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - MAX_CONSTANTS * (VAR_TYPES - 1)) >= MAX_SYMBOLS * VAR_TYPES) ? "1" : "0";
		return mem_sign;
  }
  else if (index < MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2){ // LOCALS
		string mem_sign = "2" + to_string(((index - (MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES)) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - (MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES) >= MAX_SYMBOLS * VAR_TYPES)) ? "1" : "0";
		return mem_sign;
  }
	else{ // CLAS ATTRIBUTES
		string mem_sign = "3" + to_string(((index - (MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2)) / MAX_OBJ_SYMBOLS) % (VAR_TYPES - 1));
		mem_sign += "0"; // There are no temporal class attributes
		return mem_sign;
	}

  // ERROR! Nothing was written
  cout << ">> Fatal Error: could not locate "  << index << " in memory" << endl;
  exit(EXIT_FAILURE);
}

int mem_sign_to_index_displacement(string mem_sign){
	int index_displacement = 0;
	int mem_class = mem_sign[0] - '0', var_type = mem_sign[1] - '0', is_temp = mem_sign[2] - '0';

	switch (mem_class) {
		case 1: // GLOBAL
		{
			index_displacement += MAX_CONSTANTS * (VAR_TYPES - 1);
		} break;
		case 2: // LOCAL
		{
			index_displacement += MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES;
		} break;
		case 3: // OBJECT
		{
			index_displacement += MAX_CONSTANTS * (VAR_TYPES - 1) + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES * 2;
		} break;
	}

	int type_displacement_mult = (mem_class) ? MAX_SYMBOLS : MAX_CONSTANTS;

	index_displacement += var_type * type_displacement_mult;

	int temp_displacement = 0;

	if (is_temp) temp_displacement = MAX_SYMBOLS * VAR_TYPES;

	index_displacement += temp_displacement;

	return index_displacement;
}

// HELPER METHODS //

Memory* get_object_memory(int index){
	string mem_sign = mem_index_to_mem_sign(index);
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

	switch (int_mem_sign) {
		case 140:
			{
				return &(GLOBAL_MEM.local_mem.objects[index - index_displacement]);
			}
			break;
		case 141:
			{
				return &(GLOBAL_MEM.temp_mem.objects[index - index_displacement]);
			}
			break;
		case 240:
			{
				return &(LOCAL_MEM->local_mem.objects[index - index_displacement]);
			}
			break;
		case 241:
			{
				return &(LOCAL_MEM->temp_mem.objects[index - index_displacement]);
			}
			break;
		default:
		{
			cout << ">> Fatal Error: could not get memory for object at " << index << endl;
			exit(EXIT_FAILURE);
		}
	}
}

Value read_from_memory(int index){
  string mem_sign = mem_index_to_mem_sign(index);
  if(mem_sign[0] == '2'){
    if (!LOCAL_MEM->active){
      cout << ">> Fatal Error: No local context to read "  << index << " from memory" << endl;
      exit(EXIT_FAILURE); // ERROR! No context to read local variable from
    }
  }


  Value v;
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);
  switch (int_mem_sign) {
    case 0:
      {
        v.set_i(GLOBAL_MEM.const_mem.ints[index]);
      }
      break;
    case 10:
      {
        v.set_f(GLOBAL_MEM.const_mem.floats[index - index_displacement]);
      }
      break;
    case 20:
      {
        v.set_s(GLOBAL_MEM.const_mem.strings[index - index_displacement]);
      }
      break;
    case 30:
      {
        v.set_b(GLOBAL_MEM.const_mem.booleans[index - index_displacement]);
      }
      break;
    case 100:
      {
        v.set_i(GLOBAL_MEM.local_mem.ints[index - index_displacement]);
      }
      break;
    case 110:
      {
        v.set_f(GLOBAL_MEM.local_mem.floats[index - index_displacement]);
      }
      break;
    case 120:
      {
        v.set_s(GLOBAL_MEM.local_mem.strings[index - index_displacement]);
      }
      break;
    case 130:
      {
        v.set_b(GLOBAL_MEM.local_mem.booleans[index - index_displacement]);
      }
      break;
		case 140:
      {
				Memory obj = GLOBAL_MEM.local_mem.objects[index - index_displacement];
        v.set_o(obj);
      }
      break;
    case 101:
      {
        v.set_i(GLOBAL_MEM.temp_mem.ints[index - index_displacement]);
      }
      break;
    case 111:
      {
        v.set_f(GLOBAL_MEM.temp_mem.floats[index - index_displacement]);
      }
      break;
    case 121:
      {
        v.set_s(GLOBAL_MEM.temp_mem.strings[index - index_displacement]);
      }
      break;
    case 131:
      {
        v.set_b(GLOBAL_MEM.temp_mem.booleans[index - index_displacement]);
      }
      break;
		case 141:
      {
				Memory obj = GLOBAL_MEM.temp_mem.objects[index - index_displacement];
        v.set_o(obj);
      }
      break;
    case 200:
      {
        v.set_i(LOCAL_MEM->local_mem.ints[index - index_displacement]);
      }
      break;
    case 210:
      {
        v.set_f(LOCAL_MEM->local_mem.floats[index - index_displacement]);
      }
      break;
    case 220:
      {
        v.set_s(LOCAL_MEM->local_mem.strings[index - index_displacement]);
      }
      break;
    case 230:
      {
        v.set_b(LOCAL_MEM->local_mem.booleans[index - index_displacement]);
      }
      break;
		case 240:
      {
				Memory obj = LOCAL_MEM->local_mem.objects[index - index_displacement];
        v.set_o(obj);
      }
      break;
    case 201:
      {
        v.set_i(LOCAL_MEM->temp_mem.ints[index - index_displacement]);
      }
      break;
    case 211:
      {
        v.set_f(LOCAL_MEM->temp_mem.floats[index - index_displacement]);
      }
      break;
    case 221:
      {
        v.set_s(LOCAL_MEM->temp_mem.strings[index - index_displacement]);
      }
      break;
    case 231:
      {
        v.set_b(LOCAL_MEM->temp_mem.booleans[index - index_displacement]);
      }
      break;
		case 241:
      {
				Memory obj = LOCAL_MEM->temp_mem.objects[index - index_displacement];
        v.set_o(obj);
      }
      break;
    default:
    {
      // ERROR! Nothing was read
      cout << ">> Fatal Error: could not read "  << index << " from memory" << endl;
      exit(EXIT_FAILURE);
    }
  }
  return v;
}

Value read_from_memory(Memory* this_mem, int index){
  string mem_sign = mem_index_to_mem_sign(index);
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

	Value v;

  switch (int_mem_sign) {
		case 300:
      {
				v.set_i(this_mem->ints[index - index_displacement]);
      }
      break;
		case 310:
      {
				v.set_f(this_mem->floats[index - index_displacement]);
      }
      break;
		case 320:
      {
				v.set_s(this_mem->strings[index - index_displacement]);
      }
      break;
		case 330:
      {
				v.set_b(this_mem->booleans[index - index_displacement]);
      }
    	break;
		default:
    {
      // ERROR! Nothing was read
      cout << ">> Fatal Error: could not read from " << index << endl;
      exit(EXIT_FAILURE);
    }
	}

	return v;
}

void write_to_memory(int index, string value){
  string mem_sign = mem_index_to_mem_sign(index);

	if(mem_sign[0] == '2'){
    if (!LOCAL_MEM->active){
      cout << ">> Fatal Error: No local context to write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE); // ERROR! No context to write local variable to
    }
  }

	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
    case 0:
      {
        GLOBAL_MEM.const_mem.ints[index] = s_stoll(value);
      }
      break;
    case 10:
      {
        GLOBAL_MEM.const_mem.floats[index - index_displacement] = s_stold(value);
      }
      break;
    case 20:
      {
        GLOBAL_MEM.const_mem.strings[index - index_displacement] = value;
      }
      break;
    case 30:
      {
        GLOBAL_MEM.const_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
    case 100:
      {
        GLOBAL_MEM.local_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 110:
      {
        GLOBAL_MEM.local_mem.floats[index - index_displacement] = s_stold(value);
      }
      break;
    case 120:
      {
        GLOBAL_MEM.local_mem.strings[index - index_displacement] = value;
      }
      break;
    case 130:
      {
        GLOBAL_MEM.local_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 140:
      {
				GLOBAL_MEM.local_mem.objects[index - index_displacement] = Memory(OBJECT_MEMORY_CONTEXT_SIGN.at(s_stoi(value)), s_stoi(value));
      }
      break;
    case 101:
      {
        GLOBAL_MEM.temp_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 111:
      {
        GLOBAL_MEM.temp_mem.floats[index - index_displacement] = s_stold(value);
      }
      break;
    case 121:
      {
        GLOBAL_MEM.temp_mem.strings[index - index_displacement] = value;
      }
      break;
    case 131:
      {
        GLOBAL_MEM.temp_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 141:
      {
				GLOBAL_MEM.temp_mem.objects[index - index_displacement] = Memory(OBJECT_MEMORY_CONTEXT_SIGN.at(s_stoi(value)), s_stoi(value));
      }
      break;
    case 200:
      {
      	LOCAL_MEM->local_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 210:
      {
      	LOCAL_MEM->local_mem.floats[index - index_displacement] = s_stold(value);
      }
      break;
    case 220:
      {
      	LOCAL_MEM->local_mem.strings[index - index_displacement] = value;
      }
      break;
    case 230:
      {
      	LOCAL_MEM->local_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 240:
      {
				LOCAL_MEM->local_mem.objects[index - index_displacement] = Memory(OBJECT_MEMORY_CONTEXT_SIGN.at(s_stoi(value)), s_stoi(value));
      }
      break;
    case 201:
      {
      	LOCAL_MEM->temp_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 211:
      {
      	LOCAL_MEM->temp_mem.floats[index - index_displacement] = s_stold(value);
      }
      break;
    case 221:
      {
      	LOCAL_MEM->temp_mem.strings[index - index_displacement] = value;
      }
      break;
    case 231:
      {
      	LOCAL_MEM->temp_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		case 241:
      {
				LOCAL_MEM->temp_mem.objects[index - index_displacement] = Memory(OBJECT_MEMORY_CONTEXT_SIGN.at(s_stoi(value)), s_stoi(value));
      }
      break;
    default:
    {
      // ERROR! Nothing was written
      cout << ">> Fatal Error: could not write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE);
    }
  }
}

void write_to_memory(Memory* this_mem, int index, string value){
  string mem_sign = mem_index_to_mem_sign(index);
	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
		case 300:
      {
				this_mem->ints[index - index_displacement] = s_stoll(value);
      }
      break;
		case 310:
      {
				this_mem->floats[index - index_displacement] = s_stold(value);
      }
      break;
		case 320:
      {
				this_mem->strings[index - index_displacement] = value;
      }
      break;
		case 330:
      {
				this_mem->booleans[index - index_displacement] = s_stoll(value);
      }
    	break;
		default:
    {
      // ERROR! Nothing was written
      cout << ">> Fatal Error: could not write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE);
    }
	}
}

void write_to_param(int index, string value){
	string mem_sign = mem_index_to_mem_sign(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << ">> Fatal Error: No local context to write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE); // ERROR! No context to write local variable to
    }
  }

	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
		case 200:
      {
        MEMORY_STACK.top().local_mem.ints[index - index_displacement] = s_stoll(value);
      }
      break;
    case 210:
      {
        MEMORY_STACK.top().local_mem.floats[index - index_displacement] = s_stold(value);
      }
      break;
    case 220:
      {
        MEMORY_STACK.top().local_mem.strings[index - index_displacement] = value;
      }
      break;
    case 230:
      {
        MEMORY_STACK.top().local_mem.booleans[index - index_displacement] = s_stob(value);
      }
      break;
		default:
			{
				// ERROR! Nothing was written
	      cout << ">> Fatal Error: could not write "  << value << " to param at " << index << endl;
	      exit(EXIT_FAILURE);
			}
			break;
	}
}

void setup(){

	// Memory signature with highest value is always pointing to the start of the main() method (no function can syntactically come after the main)
  PROGRAM_START = FUNCTION_MEMORY_CONTEXT_SIGN.rbegin()->first;

  // Generates global memory context
  GLOBAL_MEM = MemoryContext(FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(0), FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(1), FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(2));

	// WRITE CONSTANTS TO MEMORY //

	for (auto const& pair : CONSTANTS){
		write_to_memory(pair.first, pair.second);
  }

	// SET INITIAL VALUES FOR GLOBAL VARS //

	RUNNING = true; // This will get the instruction pointer movin through the quads
  IP = 0; // Start execution at the first QUAD
	THIS_OPERATOR_COUNTER = 0; // No this.have been seen yet
	LOCAL_MEM = new MemoryContext(); // Initialize LOCAL_MEM without parameters so that LOCAL_MEM->active is set to false
	THIS_MEM = new Memory();
}

void run(){
  while(RUNNING){
    int op = QUADS[IP][0];

		if (!op){
			// =

			int  is_ptr = QUADS[IP][1];
			int result_dir;
			Value value;

			if (is_ptr == 1 || is_ptr == 3) value = read_from_memory(read_from_memory(QUADS[IP][2]).i);
			else value = read_from_memory(QUADS[IP][2]);

			if (is_ptr == 2 || is_ptr == 3) result_dir = read_from_memory(QUADS[IP][3]).i;
			else result_dir = QUADS[IP][3];

			write_to_memory(result_dir, value.to_str());

			IP++;
			continue;
		}

		else if (op <= 13){
			// Arithmetic Epxressions (unary and binary)

			int result_dir = QUADS[IP][3];

			Value left_value, right_value;

			// May be a unary expression
			if (QUADS[IP][1] >= 0){
				left_value = read_from_memory(QUADS[IP][1]);
			}

			right_value = read_from_memory(QUADS[IP][2]);

			switch (op) {
				case 1:				// +
					{
						// Sum!
						Value res_value = left_value + right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 2:				// -
					{
						Value res_value;
						if (left_value.has_value())
							// Subtract !
							res_value = left_value - right_value;
						else
							// Negate !
							res_value = -right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 3:				// *
					{
						// Mutiply!
						Value res_value = left_value * right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 4:				// /
					{
						// Divide!
						Value res_value = left_value / right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 5:				// ==
					{
						// Compare (equals to)!
						Value res_value = left_value == right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 6:				// >
					{
						// Compare (bigger than)!
						Value res_value = left_value > right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 7:				// <
					{
						// Compare (less than)!
						Value res_value = left_value < right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 8:				// >=
					{
						// Compare (bigger than or equal to)!
						Value res_value = left_value >= right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 9:				// <=
					{
						// Compare (less than or equal to)!
						Value res_value = left_value <= right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 10:			// &&
					{
						// Compare (and)!
						Value res_value = left_value && right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 11:			// ||
					{
						// Compare (or)!
						Value res_value = left_value || right_value;
						write_to_memory(result_dir, res_value.to_str());
					}
					break;

				case 12:			// !=
					{
						// Compare (not equal to)!
						Value res_value = !(left_value == right_value);
						write_to_memory(result_dir, res_value.to_str());
					}
					break;
				case 13:			// !
					{
						// Negate!
						Value res_value = !right_value;
						write_to_memory(result_dir, res_value.to_str());
						IP++;
					}
					break;
			}
			IP++;
			continue;
		}

    switch(op) {
			// Other operations

			case 14:			// ARR_ACCESS
        {
					int result_dir = QUADS[IP][3];

					int arr_dir = QUADS[IP][1];
					int access_value = read_from_memory(QUADS[IP][2]).i;

					int result = arr_dir + access_value;

					write_to_memory(result_dir, to_string(result));
					IP++;
        }
        break;

			case 15:			// ARR_BNDS
        {
					Value arr_access_value = read_from_memory(QUADS[IP][2]);
					int arr_dim_size = QUADS[IP][3];

					if (arr_access_value.i < 0 || arr_access_value.i >= arr_dim_size){
						// If this point is reached, an array index out of bounds error has ocurred
						cout << ">> Fatal Error: array index out of bounds!" << endl;
						exit(EXIT_FAILURE);
					}

					// Else, continue execution
					IP++;
        }
        break;

			case 16:			// TMP_RESET
        {

					int reset_value = QUADS[IP][2];
					int tmp_address = QUADS[IP][3];

					write_to_memory(tmp_address, to_string(reset_value));

					IP++;
        }
        break;

			case 17:			// OBJ_INST
        {
					int object_sign  = QUADS[IP][2];
					int obj_dir = QUADS[IP][3];

					// Here we check to see if the object we are instatiating is not currently referenced bu the "this." operator
					// This prevents weird behaviour, e.g. changing an object's type in the middle of its own type's function execution
					if (THIS_MEM->id != -1 && get_object_memory(obj_dir)->id == THIS_MEM->id){
							cout << ">> Fatal Error: Cannot re-instantiate object variable within it's own scope" << endl;
							exit(EXIT_FAILURE);
					}

					write_to_memory(obj_dir, to_string(object_sign));

					IP++;
        }
        break;

			case 18:			// OBJ_READ
        {

					Memory* this_mem;
					Value result;

					int obj_dir = QUADS[IP][1];
					int object_var_dir = QUADS[IP][2];
					int result_dir = QUADS[IP][3];

					int ptr_value = -1;

					if (QUADS[IP].size() == 5){
						ptr_value = QUADS[IP][4];
					}

					if (ptr_value == 1 || ptr_value == 3) object_var_dir = read_from_memory(object_var_dir).i;

					if (ptr_value == 2 || ptr_value == 3) result_dir = read_from_memory(result_dir).i;

					if (obj_dir != -1) this_mem = get_object_memory(obj_dir);
					else this_mem = THIS_MEM;

					result = read_from_memory(this_mem, object_var_dir);

					write_to_memory(result_dir, result.to_str());
					IP++;
        }
        break;

			case 19:			// OBJ_WRITE
        {

				 	Memory* this_mem;
					Value value;

					int obj_dir = QUADS[IP][1];
					int value_dir = QUADS[IP][2];
					int obj_var_dir = QUADS[IP][3];
					int ptr_value = -1;

					if (QUADS[IP].size() == 5){
						ptr_value = QUADS[IP][4];
					}

					if (ptr_value == 1 || ptr_value == 3) value = read_from_memory(read_from_memory(value_dir).i);
					else value = read_from_memory(value_dir);

					if (ptr_value == 2 || ptr_value == 3) obj_var_dir = read_from_memory(obj_var_dir).i;


					if (obj_dir != -1) this_mem = get_object_memory(obj_dir);
					else this_mem = THIS_MEM;

					write_to_memory(this_mem, obj_var_dir, value.to_str());

					IP++;
        }
        break;

			case 20:		// ERA
				{
					int func_start_addr = QUADS[IP][3];
					if (MEMORY_STACK.size() > MEMORY_STACK_LIMIT){
						// Too many functions on the stack!
						cout << ">> Fatal Error: Memory Stack Limit of " << MEMORY_STACK_LIMIT << " reached (infinite recursion?) Terminating..." << endl;
						exit(EXIT_FAILURE);
					}

					MemoryContext new_memory_context = MemoryContext(FUNCTION_MEMORY_CONTEXT_SIGN.at(func_start_addr).at(0), FUNCTION_MEMORY_CONTEXT_SIGN.at(func_start_addr).at(1));
					new_memory_context.return_scope = (LOCAL_MEM->active) ? LOCAL_MEM : &GLOBAL_MEM;

					MEMORY_STACK.push(new_memory_context);
					IP++;
				}
				break;

			case 21:		// PARAM
				{

					Value param_value;

					int parent_obj_dir = QUADS[IP][1];
					int param_addr = QUADS[IP][3];

					if (parent_obj_dir != -1) param_value = read_from_memory(get_object_memory(parent_obj_dir), QUADS[IP][2]);
					else param_value = read_from_memory(QUADS[IP][2]);

					write_to_param(param_addr, param_value.to_str());
					IP++;
				}
				break;

			case 22:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);

					IP = func_start_addr;
				}
				break;

			case 23:		// OBJ_GOSUB
				{

					int object_dir = QUADS[IP][2];
					int func_start_addr = QUADS[IP][3];

					if (object_dir != -1){
						if (!OBJECT_MEMORY_STACK.size()){
							OBJECT_MEMORY_STACK.push(get_object_memory(object_dir));
						}else{
							Memory* new_class_memory = get_object_memory(object_dir);
							new_class_memory->return_memory = OBJECT_MEMORY_STACK.top();
							OBJECT_MEMORY_STACK.push(new_class_memory);
						}
						THIS_MEM = OBJECT_MEMORY_STACK.top();
					} else{
						THIS_OPERATOR_COUNTER++;
					}

					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);

					IP = func_start_addr;
				}
				break;

			case 24:		// READ
				{

					int result_dir;
					int parent_obj_dir = QUADS[IP][1];
					int dir_is_ptr = QUADS[IP][2];

					if (dir_is_ptr == 1) result_dir = read_from_memory(QUADS[IP][3]).i;
					else result_dir = QUADS[IP][3];

					string user_input;
					getline(cin, user_input);

					if (parent_obj_dir != -1)  write_to_memory(get_object_memory(parent_obj_dir), result_dir, user_input);
					else write_to_memory(result_dir, user_input);

					IP++;
				}
				break;

			case 25:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (LOCAL_MEM->active) LOCAL_MEM->add_to_print_buffer(printable.to_str(true));
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str(true));
					IP++;
				}
				break;

      case 26:			// PRNT
        {
          string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 27:			// PRNTLN
        {
					string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
					cout << printable << endl;
					IP++;
        }
        break;

			case 28:			// STOX
        {

					Memory* this_mem;
					int parent_obj_dir = QUADS[IP][1];
					int result_dir = QUADS[IP][3];

					string stox_arg = read_from_memory(QUADS[IP][2]).s;

					if (parent_obj_dir > 0) this_mem = get_object_memory(parent_obj_dir);
					else if (parent_obj_dir == 0) this_mem = THIS_MEM;
					else this_mem = new Memory();

					if (this_mem->id != -1) write_to_memory(this_mem, result_dir, stox_arg);
					else write_to_memory(result_dir, stox_arg);

					IP++;
        }
        break;

			case 29:			// SUBSTR
        {

					Memory* this_mem;
					int parent_obj_dir = QUADS[IP][1];
					int start_index = s_stoi(read_from_memory(QUADS[IP][3]).to_str());
					int size = s_stoi(read_from_memory(QUADS[IP][4]).to_str());
					int result_dir = QUADS[IP][5];

					string substr_arg = read_from_memory(QUADS[IP][2]).s;

					if (parent_obj_dir > 0) this_mem = get_object_memory(parent_obj_dir);
					else if (parent_obj_dir == 0) this_mem = THIS_MEM;
					else this_mem = new Memory();

					if (this_mem->id != -1) write_to_memory(this_mem, result_dir, substr_arg.substr(start_index, size));
					else write_to_memory(result_dir, substr_arg.substr(start_index, size));

					IP++;
        }
        break;

			case 30:			// F_OPEN
        {
					Memory* this_mem;
					int parent_obj_dir = QUADS[IP][1];
					int buffer_dir = QUADS[IP][4];
					int buffer_size = QUADS[IP][5];

					string file_path = read_from_memory(QUADS[IP][2]).s;
					string separator = read_from_memory(QUADS[IP][3]).s;

					if (parent_obj_dir > 0) this_mem = get_object_memory(parent_obj_dir);
					else if (parent_obj_dir == 0) this_mem = THIS_MEM;
					else this_mem = new Memory();

					vector<string> file_data = FileIO::parse_file(file_path, separator, buffer_size);

					for(int i = 0; i < file_data.size(); i++){
						if (this_mem->id != -1) write_to_memory(this_mem, buffer_dir + i, file_data[i]);
						else write_to_memory(buffer_dir + i, file_data[i]);
						if (file_data[i] == "END_OF_STREAM") break;
					}

					IP++;
        }
        break;

			case 31:			// F_WRITE
        {
					Memory* this_mem;
					int parent_obj_dir = QUADS[IP][1];
					int buffer_dir = QUADS[IP][4];
					int buffer_size = QUADS[IP][5];

					string file_path = read_from_memory(QUADS[IP][2]).s;
					string separator = read_from_memory(QUADS[IP][3]).s;

					if (parent_obj_dir > 0) this_mem = get_object_memory(parent_obj_dir);
					else if (parent_obj_dir == 0) this_mem = THIS_MEM;
					else this_mem = new Memory();

					vector<string> buffer;
					string next_entry;

					for(int i = 0; i < buffer_size; i++){
						if (this_mem->id != -1) next_entry = read_from_memory(this_mem, buffer_dir + i).to_str();
						else next_entry = read_from_memory(buffer_dir + i).to_str();
						if (next_entry == "END_OF_STREAM") break;
						buffer.push_back(next_entry);
					}

					FileIO::write_to_file(buffer, file_path, separator);

					IP++;
        }
        break;

      case 32:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 33:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 34:			// ENDFNC
				{

					int was_class_func = QUADS[IP][3];
					int return_addr = LOCAL_MEM->return_addr;

					if (THIS_OPERATOR_COUNTER <= 0 && was_class_func){
						THIS_MEM = (OBJECT_MEMORY_STACK.size()) ? OBJECT_MEMORY_STACK.top()->return_memory : new Memory();
						if (OBJECT_MEMORY_STACK.size()) OBJECT_MEMORY_STACK.pop();
					}else if (was_class_func) {
						THIS_OPERATOR_COUNTER--;
					}


					LOCAL_MEM = (MEMORY_STACK.size()) ? MEMORY_STACK.top().return_scope : new MemoryContext();
					if (MEMORY_STACK.size()) MEMORY_STACK.pop();


					IP = return_addr;
				}
				break;

      case 35:			// END
        {
          RUNNING = false;
        }
        break;

      default:
        {
        cout << ">> Fatal Error: Unknown Op: " << op << endl;
        exit(EXIT_FAILURE);
        }
    }
  }
}

int main () {

  // Setup virtual machine to run the program
  setup();

  // Run program
  run();

  return 0;
}
