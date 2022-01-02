// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>
#include <ctime>

#include "MemoryContext.h"
#include "Value.h"
#include "FileIO.h"

using namespace std;

/*/

		VM execution file for NucaScript

		!!! ATENTION !!!
		The next few code segments are automatically generated during compilation time,
		and should not be tampered with!
		Doing so migh mess up the following compilation cycle!
		!!! ATENTION !!!


/*/

// MEMORY_CONSTRAINTS //
const int MAX_CONSTANTS = 10000, MAX_SYMBOLS = 30000, MAX_TMP_SYMBOLS = 30000, MAX_OBJ_SYMBOLS = 30000, VAR_TYPES = 5, MEMORY_STACK_LIMIT = 100000;
// MEMORY_CONSTRAINTS //

// FUNCTION_MEMORY //
const map<int, vector<vector<int>>> FUNCTION_MEMORY_CONTEXT_SIGN = {
										{424, {{6,0,0,0,7}, {27,0,8,1,2}, {10,0,28,2,0}}},
										{420, {{0,0,0,0,0}, {0,0,1,0,0}}},
										{1, {{1,0,0,0,0}, {3,0,0,1,0}}},
										{13, {{2,0,0,0,0}, {4,0,0,1,0}}},
										{25, {{1,0,0,0,0}, {5,0,0,1,0}}},
										{42, {{5,0,0,0,0}, {3,0,0,1,0}}},
										{58, {{1,0,0,0,0}, {5,0,3,1,0}}},
										{78, {{1,0,0,1,0}, {7,0,0,1,0}}},
										{101, {{3,0,0,1,0}, {33,0,0,8,0}}},
										{185, {{1,0,0,0,0}, {0,0,0,0,0}}},
										{195, {{2,0,0,0,0}, {21,3,15,6,0}}},
										{301, {{2,0,52,0,0}, {19,2,2,2,0}}},
										{360, {{2,0,0,0,0}, {13,3,0,2,0}}},
										{411, {{0,0,0,0,0}, {0,0,0,0,0}}},
										{413, {{0,0,0,0,0}, {0,0,5,0,0}}},
										};
// FUNCTION_MEMORY //


// OBJECT_MEMORY //
const map<int, vector<int>> OBJECT_MEMORY_CONTEXT_SIGN = {
										{2, {25,75,1001,0,0}},
										{3, {51,0,0,0,0}},
										};
// OBJECT_MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{30000, "0"},
										{30001, "1"},
										{0, "25"},
										{1, "5"},
										{2, "1000"},
										{3, "1"},
										{4, "2"},
										{5, "0"},
										{20000, "int_array["},
										{20001, "] = "},
										{6, "24"},
										{20002, "--- FLOAT MATRIX A ---"},
										{20003, "float_matrix_a["},
										{20004, "]["},
										{20005, "--- FLOAT MATRIX B ---"},
										{20006, "float_matrix_b["},
										{20007, "--- FLOAT MATRIX C ---"},
										{20008, "float_matrix_c["},
										{7, "50"},
										{20009, "Examples/example_nuca.nuca"},
										{20010, "\n"},
										{20011, "output_file.txt"},
										{20012, "\t"},
										{8, "15"},
										{20013, "/*/ "},
										{20014, " /*/\n"},
										{160000, "2"},
										{160001, "2"},
										{160006, "3"},
										{20015, "---!---"},
										{20016, "!!!!"},
										{310000, "3"},
										{310001, "2"},
										{20017, "hi "},
										{20018, " : "},
										{9, "10"},
										{20019, ", "},
										{20020, ">> Before Sort:"},
										{20021, ">> After sort:"},
										{20022, "Examples/matrix_input.txt"},
										{20023, ","},
										{20024, ">> Before multiplication:"},
										{20025, ">> After multiplication:"},
										{20026, ">> Enter a funny string:\n-- "},
										{20027, ">> All done : )"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{35, -1, -1, 424},
										{5, 340000, 3, 580000},
										{36, -1, 580000, 5},
										{0, -1, 340000, 40000},
										{37, -1, -1, 1},
										{21, -1, -1, 1},
										{2, 340000, 3, 490000},
										{22, -1, 490000, 340000},
										{24, -1, -1, 1},
										{0, -1, 40000, 490001},
										{3, 340000, 490001, 490002},
										{0, -1, 490002, 40000},
										{37, -1, -1, 1},
										{0, -1, 340000, 340001},
										{6, 340001, 3, 580000},
										{36, -1, 580000, 23},
										{2, 340001, 3, 490000},
										{3, 340000, 490000, 490001},
										{0, -1, 490001, 340000},
										{16, -1, 1, 490002},
										{2, 340001, 490002, 490003},
										{0, -1, 490003, 340001},
										{35, -1, -1, 14},
										{0, -1, 340000, 40001},
										{37, -1, -1, 1},
										{9, 340000, 3, 580000},
										{36, -1, 580000, 29},
										{0, -1, 340000, 40002},
										{37, -1, -1, 1},
										{21, -1, -1, 25},
										{2, 340000, 3, 490000},
										{22, -1, 490000, 340000},
										{24, -1, -1, 25},
										{0, -1, 40002, 490001},
										{21, -1, -1, 25},
										{2, 340000, 4, 490002},
										{22, -1, 490002, 340000},
										{24, -1, -1, 25},
										{0, -1, 40002, 490003},
										{1, 490001, 490003, 490004},
										{0, -1, 490004, 40002},
										{37, -1, -1, 1},
										{0, -1, 3, 340001},
										{0, -1, 3, 340002},
										{0, -1, 3, 340003},
										{0, -1, 4, 340004},
										{7, 340004, 340000, 580000},
										{36, -1, 580000, 56},
										{1, 340002, 340003, 490002},
										{0, -1, 490002, 340001},
										{0, -1, 340002, 340003},
										{0, -1, 340001, 340002},
										{16, -1, 1, 490000},
										{1, 340004, 490000, 490001},
										{0, -1, 490001, 340004},
										{35, -1, -1, 46},
										{0, -1, 340001, 40003},
										{37, -1, -1, 1},
										{0, -1, 5, 340000},
										{7, 340000, 0, 580000},
										{36, -1, 580000, 77},
										{1, 20000, 340000, 550000},
										{1, 550000, 20001, 550001},
										{16, -1, 0, 490002},
										{15, -1, 340000, 25},
										{0, -1, 340000, 490002},
										{16, -1, 0, 490003},
										{14, 640000, 490002, 490003},
										{16, -1, 0, 490004},
										{19, -1, 490003, 490004, 1},
										{1, 550001, 490004, 550002},
										{26, -1, -1, 550002},
										{28, -1, -1, -1},
										{16, -1, 1, 490000},
										{1, 340000, 490000, 490001},
										{0, -1, 490001, 340000},
										{35, -1, -1, 59},
										{37, -1, -1, 1},
										{0, -1, 5, 340000},
										{7, 340000, 0, 580000},
										{36, -1, 580000, 100},
										{36, -1, 430000, 89},
										{16, -1, 0, 490002},
										{15, -1, 340000, 25},
										{0, -1, 340000, 490002},
										{16, -1, 0, 490003},
										{14, 640000, 490002, 490003},
										{20, -1, 340000, 490003, 2},
										{35, -1, -1, 96},
										{2, 6, 340000, 490004},
										{16, -1, 0, 490005},
										{15, -1, 490004, 25},
										{0, -1, 490004, 490005},
										{16, -1, 0, 490006},
										{14, 640000, 490005, 490006},
										{20, -1, 340000, 490006, 2},
										{16, -1, 1, 490000},
										{1, 340000, 490000, 490001},
										{0, -1, 490001, 340000},
										{35, -1, -1, 79},
										{37, -1, -1, 1},
										{0, -1, 5, 340000},
										{2, 0, 3, 490000},
										{7, 340000, 490000, 580000},
										{36, -1, 580000, 184},
										{0, -1, 5, 340001},
										{2, 0, 340000, 490003},
										{2, 490003, 3, 490004},
										{7, 340001, 490004, 580001},
										{36, -1, 580001, 180},
										{16, -1, 0, 490007},
										{15, -1, 340001, 25},
										{0, -1, 340001, 490007},
										{16, -1, 0, 490008},
										{14, 640000, 490007, 490008},
										{16, -1, 0, 490009},
										{19, -1, 490008, 490009, 1},
										{1, 340001, 3, 490010},
										{16, -1, 0, 490011},
										{15, -1, 490010, 25},
										{0, -1, 490010, 490011},
										{16, -1, 0, 490012},
										{14, 640000, 490011, 490012},
										{16, -1, 0, 490013},
										{19, -1, 490012, 490013, 1},
										{6, 490009, 490013, 580002},
										{10, 430000, 580002, 580003},
										{13, -1, 430000, 580004},
										{16, -1, 0, 490014},
										{15, -1, 340001, 25},
										{0, -1, 340001, 490014},
										{16, -1, 0, 490015},
										{14, 640000, 490014, 490015},
										{16, -1, 0, 490016},
										{19, -1, 490015, 490016, 1},
										{1, 340001, 3, 490017},
										{16, -1, 0, 490018},
										{15, -1, 490017, 25},
										{0, -1, 490017, 490018},
										{16, -1, 0, 490019},
										{14, 640000, 490018, 490019},
										{16, -1, 0, 490020},
										{19, -1, 490019, 490020, 1},
										{7, 490016, 490020, 580005},
										{10, 580004, 580005, 580006},
										{11, 580003, 580006, 580007},
										{36, -1, 580007, 176},
										{16, -1, 0, 490021},
										{15, -1, 340001, 25},
										{0, -1, 340001, 490021},
										{16, -1, 0, 490022},
										{14, 640000, 490021, 490022},
										{16, -1, 0, 490023},
										{19, -1, 490022, 490023, 1},
										{0, -1, 490023, 340002},
										{16, -1, 0, 490024},
										{15, -1, 340001, 25},
										{0, -1, 340001, 490024},
										{16, -1, 0, 490025},
										{14, 640000, 490024, 490025},
										{1, 340001, 3, 490026},
										{16, -1, 0, 490027},
										{15, -1, 490026, 25},
										{0, -1, 490026, 490027},
										{16, -1, 0, 490028},
										{14, 640000, 490027, 490028},
										{16, -1, 0, 490029},
										{19, -1, 490028, 490029, 1},
										{20, -1, 490029, 490025, 2},
										{1, 340001, 3, 490030},
										{16, -1, 0, 490031},
										{15, -1, 490030, 25},
										{0, -1, 490030, 490031},
										{16, -1, 0, 490032},
										{14, 640000, 490031, 490032},
										{20, -1, 340002, 490032, 2},
										{16, -1, 1, 490005},
										{1, 340001, 490005, 490006},
										{0, -1, 490006, 340001},
										{35, -1, -1, 106},
										{16, -1, 1, 490001},
										{1, 340000, 490001, 490002},
										{0, -1, 490002, 340000},
										{35, -1, -1, 102},
										{37, -1, -1, 1},
										{36, -1, 5, 193},
										{36, -1, 5, 190},
										{0, -1, 5, 40004},
										{37, -1, -1, 1},
										{35, -1, -1, 192},
										{0, -1, 3, 40004},
										{37, -1, -1, 1},
										{35, -1, -1, 195},
										{0, -1, 3, 40004},
										{37, -1, -1, 1},
										{26, -1, -1, 20002},
										{28, -1, -1, -1},
										{0, -1, 5, 340000},
										{7, 340000, 1, 580000},
										{36, -1, 580000, 230},
										{0, -1, 5, 340001},
										{7, 340001, 1, 580001},
										{36, -1, 580001, 226},
										{1, 20003, 340000, 550000},
										{1, 550000, 20004, 550001},
										{1, 550001, 340001, 550002},
										{1, 550002, 20001, 550003},
										{16, -1, 0, 490004},
										{15, -1, 340000, 5},
										{16, -1, 0, 490005},
										{0, -1, 340000, 490005},
										{3, 490005, 1, 490005},
										{1, 490004, 490005, 490004},
										{15, -1, 340001, 5},
										{1, 490004, 340001, 490004},
										{16, -1, 0, 490006},
										{14, 670000, 490004, 490006},
										{16, -1, 0, 520000},
										{19, -1, 490006, 520000, 1},
										{1, 550003, 520000, 550004},
										{26, -1, -1, 550004},
										{28, -1, -1, -1},
										{16, -1, 1, 490002},
										{1, 340001, 490002, 490003},
										{0, -1, 490003, 340001},
										{35, -1, -1, 201},
										{16, -1, 1, 490000},
										{1, 340000, 490000, 490001},
										{0, -1, 490001, 340000},
										{35, -1, -1, 198},
										{26, -1, -1, 20005},
										{28, -1, -1, -1},
										{0, -1, 5, 340000},
										{7, 340000, 1, 580002},
										{36, -1, 580002, 265},
										{0, -1, 5, 340001},
										{7, 340001, 1, 580003},
										{36, -1, 580003, 261},
										{1, 20006, 340000, 550005},
										{1, 550005, 20004, 550006},
										{1, 550006, 340001, 550007},
										{1, 550007, 20001, 550008},
										{16, -1, 0, 490011},
										{15, -1, 340000, 5},
										{16, -1, 0, 490012},
										{0, -1, 340000, 490012},
										{3, 490012, 1, 490012},
										{1, 490011, 490012, 490011},
										{15, -1, 340001, 5},
										{1, 490011, 340001, 490011},
										{16, -1, 0, 490013},
										{14, 670025, 490011, 490013},
										{16, -1, 0, 520001},
										{19, -1, 490013, 520001, 1},
										{1, 550008, 520001, 550009},
										{26, -1, -1, 550009},
										{28, -1, -1, -1},
										{16, -1, 1, 490009},
										{1, 340001, 490009, 490010},
										{0, -1, 490010, 340001},
										{35, -1, -1, 236},
										{16, -1, 1, 490007},
										{1, 340000, 490007, 490008},
										{0, -1, 490008, 340000},
										{35, -1, -1, 233},
										{26, -1, -1, 20007},
										{28, -1, -1, -1},
										{0, -1, 5, 340000},
										{7, 340000, 1, 580004},
										{36, -1, 580004, 300},
										{0, -1, 5, 340001},
										{7, 340001, 1, 580005},
										{36, -1, 580005, 296},
										{1, 20008, 340000, 550010},
										{1, 550010, 20004, 550011},
										{1, 550011, 340001, 550012},
										{1, 550012, 20001, 550013},
										{16, -1, 0, 490018},
										{15, -1, 340000, 5},
										{16, -1, 0, 490019},
										{0, -1, 340000, 490019},
										{3, 490019, 1, 490019},
										{1, 490018, 490019, 490018},
										{15, -1, 340001, 5},
										{1, 490018, 340001, 490018},
										{16, -1, 0, 490020},
										{14, 670050, 490018, 490020},
										{16, -1, 0, 520002},
										{19, -1, 490020, 520002, 1},
										{1, 550013, 520002, 550014},
										{26, -1, -1, 550014},
										{28, -1, -1, -1},
										{16, -1, 1, 490016},
										{1, 340001, 490016, 490017},
										{0, -1, 490017, 340001},
										{35, -1, -1, 271},
										{16, -1, 1, 490014},
										{1, 340000, 490014, 490015},
										{0, -1, 490015, 340000},
										{35, -1, -1, 268},
										{37, -1, -1, 1},
										{33, -1, 400000, 400001, 400002, 50},
										{0, -1, 5, 340000},
										{7, 340000, 1, 580000},
										{36, -1, 580000, 359},
										{0, -1, 5, 340001},
										{7, 340001, 1, 580001},
										{36, -1, 580001, 355},
										{16, -1, 0, 490004},
										{15, -1, 340000, 5},
										{16, -1, 0, 490005},
										{0, -1, 340000, 490005},
										{3, 490005, 1, 490005},
										{1, 490004, 490005, 490004},
										{15, -1, 340001, 5},
										{1, 490004, 340001, 490004},
										{16, -1, 0, 490006},
										{14, 670000, 490004, 490006},
										{3, 340000, 1, 490007},
										{1, 490007, 340001, 490008},
										{16, -1, 0, 490009},
										{15, -1, 490008, 50},
										{0, -1, 490008, 490009},
										{16, -1, 0, 490010},
										{14, 400002, 490009, 490010},
										{16, -1, 0, 550000},
										{0, 1, 490010, 550000},
										{29, -1, 550000, 520000},
										{20, -1, 520000, 490006, 2},
										{16, -1, 0, 490011},
										{15, -1, 340000, 5},
										{16, -1, 0, 490012},
										{0, -1, 340000, 490012},
										{3, 490012, 1, 490012},
										{1, 490011, 490012, 490011},
										{15, -1, 340001, 5},
										{1, 490011, 340001, 490011},
										{16, -1, 0, 490013},
										{14, 670025, 490011, 490013},
										{3, 340000, 1, 490014},
										{1, 490014, 340001, 490015},
										{1, 490015, 0, 490016},
										{16, -1, 0, 490017},
										{15, -1, 490016, 50},
										{0, -1, 490016, 490017},
										{16, -1, 0, 490018},
										{14, 400002, 490017, 490018},
										{16, -1, 0, 550001},
										{0, 1, 490018, 550001},
										{29, -1, 550001, 520001},
										{20, -1, 520001, 490013, 2},
										{16, -1, 1, 490002},
										{1, 340001, 490002, 490003},
										{0, -1, 490003, 340001},
										{35, -1, -1, 306},
										{16, -1, 1, 490000},
										{1, 340000, 490000, 490001},
										{0, -1, 490001, 340000},
										{35, -1, -1, 303},
										{37, -1, -1, 1},
										{0, -1, 5, 340000},
										{7, 340000, 1, 580000},
										{36, -1, 580000, 410},
										{0, -1, 5, 340001},
										{7, 340001, 1, 580001},
										{36, -1, 580001, 406},
										{16, -1, 0, 490004},
										{15, -1, 340000, 5},
										{16, -1, 0, 490005},
										{0, -1, 340000, 490005},
										{3, 490005, 1, 490005},
										{1, 490004, 490005, 490004},
										{15, -1, 340001, 5},
										{1, 490004, 340001, 490004},
										{16, -1, 0, 490006},
										{14, 670050, 490004, 490006},
										{16, -1, 0, 490007},
										{15, -1, 340000, 5},
										{16, -1, 0, 490008},
										{0, -1, 340000, 490008},
										{3, 490008, 1, 490008},
										{1, 490007, 490008, 490007},
										{15, -1, 340001, 5},
										{1, 490007, 340001, 490007},
										{16, -1, 0, 490009},
										{14, 670000, 490007, 490009},
										{16, -1, 0, 520000},
										{19, -1, 490009, 520000, 1},
										{16, -1, 0, 490010},
										{15, -1, 340000, 5},
										{16, -1, 0, 490011},
										{0, -1, 340000, 490011},
										{3, 490011, 1, 490011},
										{1, 490010, 490011, 490010},
										{15, -1, 340001, 5},
										{1, 490010, 340001, 490010},
										{16, -1, 0, 490012},
										{14, 670025, 490010, 490012},
										{16, -1, 0, 520001},
										{19, -1, 490012, 520001, 1},
										{3, 520000, 520001, 520002},
										{20, -1, 520002, 490006, 2},
										{16, -1, 1, 490002},
										{1, 340001, 490002, 490003},
										{0, -1, 490003, 340001},
										{35, -1, -1, 364},
										{16, -1, 1, 490000},
										{1, 340000, 490000, 490001},
										{0, -1, 490001, 340000},
										{35, -1, -1, 361},
										{37, -1, -1, 1},
										{33, 0, 20009, 20010, 700000, 1000},
										{37, -1, -1, 1},
										{3, 20012, 8, 550000},
										{1, 550000, 20013, 550001},
										{19, -1, 701000, 550002},
										{1, 550001, 550002, 550003},
										{1, 550003, 20014, 550004},
										{34, 0, 20011, 550004, 700000, 1000},
										{37, -1, -1, 1},
										{19, 160000, 701000, 550000, -1, -1},
										{26, -1, -1, 550000},
										{28, -1, -1, -1},
										{37, -1, -1, 0},
										{17, 5, 2, 160001},
										{16, -1, 0, 190000},
										{15, -1, 5, 5},
										{0, -1, 5, 190000},
										{16, -1, 0, 190001},
										{14, 160001, 190000, 190001},
										{21, -1, -1, 185},
										{24, 1, 190001, 185},
										{0, -1, 40004, 190002},
										{0, -1, 190002, 40005},
										{16, -1, 0, 190003},
										{15, -1, 5, 5},
										{0, -1, 5, 190003},
										{16, -1, 0, 190004},
										{14, 160001, 190003, 190004},
										{21, -1, -1, 185},
										{24, 1, 190004, 185},
										{0, -1, 40004, 190005},
										{16, -1, 0, 190006},
										{15, -1, 5, 5},
										{0, -1, 5, 190006},
										{16, -1, 0, 190007},
										{14, 160001, 190006, 190007},
										{21, -1, -1, 185},
										{24, 1, 190007, 185},
										{0, -1, 40004, 190008},
										{1, 3, 190008, 190009},
										{0, -1, 190009, 40005},
										{20, 160000, 20015, 701000, -1, -1},
										{16, -1, 0, 190010},
										{15, -1, 3, 5},
										{0, -1, 3, 190010},
										{16, -1, 0, 190011},
										{14, 160001, 190010, 190011},
										{20, 190011, 20016, 701000, -1, 1},
										{18, -1, 3, 160006},
										{16, -1, 0, 190012},
										{15, -1, 5, 5},
										{0, -1, 5, 190012},
										{16, -1, 0, 190013},
										{14, 160001, 190012, 190013},
										{18, 1, 2, 190013},
										{16, -1, 0, 190014},
										{15, -1, 3, 5},
										{0, -1, 3, 190014},
										{16, -1, 0, 190015},
										{14, 160001, 190014, 190015},
										{19, 190015, 701000, 250000, -1, 1},
										{26, -1, -1, 250000},
										{19, 160000, 701000, 250001, -1, -1},
										{26, -1, -1, 250001},
										{28, -1, -1, -1},
										{0, -1, 5, 40005},
										{7, 40005, 1, 280000},
										{36, -1, 280000, 505},
										{1, 20017, 40005, 250002},
										{1, 250002, 20018, 250003},
										{16, -1, 0, 190018},
										{15, -1, 40005, 5},
										{0, -1, 40005, 190018},
										{16, -1, 0, 190019},
										{14, 160001, 190018, 190019},
										{21, -1, -1, 13},
										{22, -1, 9, 340000},
										{24, 1, 190019, 13},
										{0, -1, 40001, 190020},
										{1, 250003, 190020, 250004},
										{1, 250004, 20019, 250005},
										{16, -1, 0, 190021},
										{15, -1, 40005, 5},
										{0, -1, 40005, 190021},
										{16, -1, 0, 190022},
										{14, 160001, 190021, 190022},
										{19, 190022, 701000, 250006, -1, 1},
										{1, 250005, 250006, 250007},
										{26, -1, -1, 250007},
										{28, -1, -1, -1},
										{16, -1, 1, 190016},
										{1, 40005, 190016, 190017},
										{0, -1, 190017, 40005},
										{35, -1, -1, 477},
										{21, -1, -1, 13},
										{22, -1, 9, 340000},
										{24, -1, 160000, 13},
										{0, -1, 40001, 190023},
										{26, -1, -1, 190023},
										{21, -1, -1, 1},
										{22, -1, 9, 340000},
										{24, -1, 160000, 1},
										{0, -1, 40000, 190024},
										{26, -1, -1, 190024},
										{28, -1, -1, -1},
										{21, -1, -1, 42},
										{22, -1, 8, 340000},
										{24, -1, 160000, 42},
										{0, -1, 40003, 190025},
										{26, -1, -1, 190025},
										{21, -1, -1, 25},
										{22, -1, 8, 340000},
										{24, -1, 160000, 25},
										{0, -1, 40002, 190026},
										{26, -1, -1, 190026},
										{28, -1, -1, -1},
										{21, -1, -1, 78},
										{22, -1, 30000, 430000},
										{24, -1, 160000, 78},
										{26, -1, -1, 20020},
										{28, -1, -1, -1},
										{21, -1, -1, 58},
										{24, -1, 160000, 58},
										{21, -1, -1, 101},
										{22, -1, 30001, 430000},
										{24, -1, 160000, 101},
										{26, -1, -1, 20021},
										{28, -1, -1, -1},
										{21, -1, -1, 58},
										{24, -1, 160000, 58},
										{21, -1, -1, 301},
										{22, -1, 20022, 400000},
										{22, -1, 20023, 400001},
										{24, -1, 160000, 301},
										{26, -1, -1, 20024},
										{28, -1, -1, -1},
										{21, -1, -1, 195},
										{24, -1, 160000, 195},
										{21, -1, -1, 360},
										{24, -1, 160000, 360},
										{26, -1, -1, 20025},
										{28, -1, -1, -1},
										{21, -1, -1, 195},
										{24, -1, 160000, 195},
										{21, -1, -1, 411},
										{24, -1, 160000, 411},
										{26, -1, -1, 20026},
										{27, -1, -1, -1},
										{25, 160000, -1, 701000},
										{21, -1, -1, 413},
										{24, -1, 160000, 413},
										{26, -1, -1, 20027},
										{28, -1, -1, -1},
										{38, -1, -1, -1},
										};
// QUADS //


/*/

		Auto-generated Section ends here!
		Fell free to tamper with the rest of the code!
		Break something, learn something!

/*/

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

// Given a variable's memory index, calculates its signature
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

  // ERROR!
  cout << ">> Fatal Error: could not locate "  << index << " in memory" << endl;
  exit(EXIT_FAILURE);
}

// Given a variable's memory signature, calculates the displacement needed to convert from virtual memory to real memory
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

// Given a memory index, retrieves a pointer to the Object Memory instance located in it, if there is one
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

// Reads and returns the value of a memory index
// Responsible for figuring out which memory to read from (local / global, constant / var / temp, and type)
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

// Reads and returns the value of a memory index, in the given object memory
// Responsible for figuring out which memory to read from (types)
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

// Writes the given value into the given memory index
// Responsible for figuring out which memory to write into (local / global, constant / var / temp, and type)
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


// Writes the given value into the given memory index of the given object memory
// Responsible for figuring out which memory to write into (types)
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


// Writes the given value into the given memory index, but into the top of the memory stack instead of LOCAL_MEM
// Responsible for figuring out which memory to write into (types)
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


// Does all of the needed initializations so that the program can be run
void setup(){

	// Memory signature with highest value is always pointing to the start of the main() method (no function can syntactically come after the main)
  PROGRAM_START = FUNCTION_MEMORY_CONTEXT_SIGN.rbegin()->first;

  // Generates global memory context
  GLOBAL_MEM = MemoryContext(FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(0), FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(1), FUNCTION_MEMORY_CONTEXT_SIGN.at(PROGRAM_START).at(2));

	// WRITE CONSTANTS TO MEMORY //

	for (auto const& pair : CONSTANTS){
		write_to_memory(pair.first, pair.second);
  }

	// SEED THE PSEUDORANDOM GENERATOR //

	srand(time(NULL));

	// SET INITIAL VALUES FOR GLOBAL VARS //

	RUNNING = true; // This will get the instruction pointer movin through the quads
  IP = 0; // Start execution at the first QUAD
	THIS_OPERATOR_COUNTER = 0; // No this.have been seen yet
	LOCAL_MEM = new MemoryContext(); // Initialize LOCAL_MEM without parameters so that LOCAL_MEM->active is set to false
	THIS_MEM = new Memory();
}

// Runs the program, starting from QUAD 0
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

			case 17:			// USNG_AS
        {

					int arr_size = QUADS[IP][1];
					int class_sign = QUADS[IP][2];
					int obj_address = QUADS[IP][3];

					int obj_mem_sign = get_object_memory(obj_address)->signature;

					if (obj_mem_sign == -1 && arr_size == -1){
						cout << ">> Fatal Error: 'using as' employement exception; symbol is not instantiated" << endl;
						exit(EXIT_FAILURE);
					}

					if (obj_mem_sign != -1 && obj_mem_sign != class_sign){
						cout << ">> Fatal Error: 'using as' employement exception; symbol is instantiated as a different class type" << endl;
						exit(EXIT_FAILURE);
					}

					if (arr_size != -1){
						Memory* obj_mem;
						for (int i = 0; i < arr_size; i++){
							obj_mem = get_object_memory(obj_address + i);
							if (obj_mem->id == -1){
								// Here we must instantiate these array entrie with the appropriate class type
								write_to_memory(obj_address + i, to_string(class_sign));
							}
						}
					}

					IP++;
        }
        break;

			case 18:			// OBJ_INST
        {

					Memory* obj_mem;
					int obj_dir_is_ptr = QUADS[IP][1];
					int object_sign  = QUADS[IP][2];
					int obj_dir = QUADS[IP][3];

					if (obj_dir_is_ptr != -1) obj_dir = read_from_memory(obj_dir).i;

					obj_mem = get_object_memory(obj_dir);

					// Here we check to see if the object we are instatiating is not currently referenced bu the "this." operator
					// This prevents weird behaviour, e.g. changing an object's type in the middle of its own type's function execution
					if (THIS_MEM->id != -1 && obj_mem->id == THIS_MEM->id){
							cout << ">> Fatal Error: Cannot re-instantiate object variable within it's own scope" << endl;
							exit(EXIT_FAILURE);
					}

					write_to_memory(obj_dir, to_string(object_sign));

					IP++;
        }
        break;

			case 19:			// OBJ_READ
        {

					Memory* this_mem;
					Value result;

					int obj_dir = QUADS[IP][1];
					int object_var_dir = QUADS[IP][2];
					int result_dir = QUADS[IP][3];
					int ptr_value = -1;
					int obj_dir_is_ptr = -1;


					if (QUADS[IP].size() >= 5){
						ptr_value = QUADS[IP][4];
					}

					if (QUADS[IP].size() >= 6){
						obj_dir_is_ptr = QUADS[IP][5];
					}

					if (ptr_value == 1 || ptr_value == 3) object_var_dir = read_from_memory(object_var_dir).i;

					if (ptr_value == 2 || ptr_value == 3) result_dir = read_from_memory(result_dir).i;

					if (obj_dir != -1){
						if (obj_dir_is_ptr == -1) this_mem = get_object_memory(obj_dir);
						else this_mem = get_object_memory(read_from_memory(obj_dir).i);
					}
					else this_mem = THIS_MEM;

					result = read_from_memory(this_mem, object_var_dir);

					write_to_memory(result_dir, result.to_str());
					IP++;
        }
        break;

			case 20:			// OBJ_WRITE
        {

				 	Memory* this_mem;
					Value value;

					int obj_dir = QUADS[IP][1];
					int value_dir = QUADS[IP][2];
					int obj_var_dir = QUADS[IP][3];
					int ptr_value = -1;
					int obj_dir_is_ptr = -1;

					if (QUADS[IP].size() >= 5){
						ptr_value = QUADS[IP][4];
					}
					if (QUADS[IP].size() >= 6){
						obj_dir_is_ptr = QUADS[IP][5];
					}

					if (ptr_value == 1 || ptr_value == 3) value = read_from_memory(read_from_memory(value_dir).i);
					else value = read_from_memory(value_dir);

					if (ptr_value == 2 || ptr_value == 3) obj_var_dir = read_from_memory(obj_var_dir).i;

					if (obj_dir != -1){
						if (obj_dir_is_ptr == -1) this_mem = get_object_memory(obj_dir);
						else this_mem = get_object_memory(read_from_memory(obj_dir).i);
					}
					else this_mem = THIS_MEM;

					write_to_memory(this_mem, obj_var_dir, value.to_str());

					IP++;
        }
        break;

			case 21:		// ERA
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

			case 22:		// PARAM
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

			case 23:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);

					IP = func_start_addr;
				}
				break;

			case 24:		// OBJ_GOSUB
				{

					int obj_dir_is_ptr = QUADS[IP][1];
					int object_dir = QUADS[IP][2];
					int func_start_addr = QUADS[IP][3];

					if (object_dir != -1){
						if (!OBJECT_MEMORY_STACK.size()){

							if (obj_dir_is_ptr == -1) OBJECT_MEMORY_STACK.push(get_object_memory(object_dir));
							else OBJECT_MEMORY_STACK.push(get_object_memory(read_from_memory(object_dir).i));

						}else{

							Memory* new_class_memory;

							if (obj_dir_is_ptr == -1) new_class_memory = get_object_memory(object_dir);
							else new_class_memory = get_object_memory(read_from_memory(object_dir).i);

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

			case 25:		// READ
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

			case 26:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (LOCAL_MEM->active) LOCAL_MEM->add_to_print_buffer(printable.to_str(true));
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str(true));
					IP++;
				}
				break;

      case 27:			// PRNT
        {
          string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 28:			// PRNTLN
        {
					string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
					cout << printable << endl;
					IP++;
        }
        break;

			case 29:			// STOX
        {
					int parent_obj_dir = QUADS[IP][1];
					int result_dir = QUADS[IP][3];

					string stox_arg = read_from_memory(QUADS[IP][2]).s;

					write_to_memory(result_dir, stox_arg);

					IP++;
        }
        break;

			case 30:			// SUBSTR
        {
					int start_index = s_stoi(read_from_memory(QUADS[IP][2]).to_str());
					int size = s_stoi(read_from_memory(QUADS[IP][3]).to_str());
					int result_dir = QUADS[IP][4];

					string substr_arg = read_from_memory(QUADS[IP][1]).s;

					write_to_memory(result_dir, substr_arg.substr(start_index, size));

					IP++;
        }
        break;

			case 31:			// STRLEN
        {
					string string_arg = read_from_memory(QUADS[IP][2]).s;
					int result_dir = QUADS[IP][3];

					write_to_memory(result_dir, to_string(string_arg.length()));

					IP++;
        }
        break;

			case 32:			// RANDINT
        {
					int lower_bound = read_from_memory(QUADS[IP][1]).i;
					int upper_bound = read_from_memory(QUADS[IP][2]).i;
					int result_dir = QUADS[IP][3];

					int rand_num = rand() % (upper_bound - lower_bound + 1) + lower_bound; // Generate the number, assign to variable.

					write_to_memory(result_dir, to_string(rand_num));

					IP++;
        }
        break;

			case 33:			// F_OPEN
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

			case 34:			// F_WRITE
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

      case 35:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 36:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 37:			// ENDFNC
				{

					int was_class_func = QUADS[IP][3];
					int return_addr = LOCAL_MEM->return_addr;

					if (THIS_OPERATOR_COUNTER <= 0 && was_class_func){
						THIS_MEM = (OBJECT_MEMORY_STACK.size() > 1) ? OBJECT_MEMORY_STACK.top()->return_memory : new Memory();
						if (OBJECT_MEMORY_STACK.size()) OBJECT_MEMORY_STACK.pop();
					}else if (was_class_func) {
						THIS_OPERATOR_COUNTER--;
					}

					LOCAL_MEM = (MEMORY_STACK.size()) ? MEMORY_STACK.top().return_scope : new MemoryContext();
					if (MEMORY_STACK.size()) MEMORY_STACK.pop();

					IP = return_addr;
				}
				break;

      case 38:			// END
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
