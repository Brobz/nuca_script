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
										{160, {{52,0,4,0,13}, {107,0,20,9,2}, {15,1,24,2,0}}},
										{1, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{4, {{0,0,1,0,0}, {66,0,4,0,0}}},
										{146, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{150, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{153, {{0,0,0,0,0}, {0,0,2,0,0}}},
										};
// FUNCTION_MEMORY //


// OBJECT_MEMORY //
const map<int, vector<int>> OBJECT_MEMORY_CONTEXT_SIGN = {
										{2, {0,0,0,0,0}},
										{3, {51,0,1501,0,0}},
										};
// OBJECT_MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{30000, "0"},
										{30001, "1"},
										{0, "10"},
										{1, "1500"},
										{2, "50"},
										{20000, "\t"},
										{20001, "cc_obj.n = "},
										{3, "1"},
										{4, "0"},
										{5, "2"},
										{20002, "objs[1].n = "},
										{20003, "lol!"},
										{20004, "n:"},
										{6, "5"},
										{20005, "hehehe"},
										{7, "3"},
										{8, "44"},
										{9, "33"},
										{10, "22"},
										{20006, "05"},
										{20007, " "},
										{20008, "\n"},
										{20009, "here we go"},
										{20010, "ok"},
										{10000, "2.33"},
										{20011, "lol"},
										{20012, "lolo"},
										{20013, "HI!"},
										{20014, "hilo"},
										{11, "20"},
										{12, "49"},
										{13, "45"},
										{20015, "100"},
										{20016, ">> Enter file path:\n-- "},
										{20017, ">> Parsing file..."},
										{14, "1499"},
										{20018, "END_OF_STREAM"},
										{20019, "Entry "},
										{20020, ": "},
										{20021, "file.txt"},
										{20022, " // An extra funny comment to confirm this works : ) "},
										{20023, " //"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{33, -1, -1, 160},
										{3, 20000, 340000, 550000},
										{0, -1, 550000, 100000},
										{35, -1, -1, 1},
										{17, -1, 3, 160000},
										{17, -1, 3, 160001},
										{17, 10, 3, 160003},
										{19, 160001, 640050, 490000, -1, -1},
										{1, 20001, 490000, 550000},
										{26, -1, -1, 550000},
										{28, -1, -1, -1},
										{16, -1, 0, 490001},
										{15, -1, 3, 10},
										{0, -1, 3, 490001},
										{16, -1, 0, 490002},
										{14, 160003, 490001, 490002},
										{19, 490002, 640050, 490003, -1, 1},
										{16, -1, 0, 490004},
										{15, -1, 4, 10},
										{0, -1, 4, 490004},
										{16, -1, 0, 490005},
										{14, 160003, 490004, 490005},
										{19, 490005, 640050, 490006, -1, 1},
										{3, 490003, 490006, 490007},
										{16, -1, 0, 490008},
										{15, -1, 5, 10},
										{0, -1, 5, 490008},
										{16, -1, 0, 490009},
										{14, 160003, 490008, 490009},
										{19, 490009, 640050, 490010, -1, 1},
										{3, 490007, 490010, 490011},
										{20, 490002, 490011, 640050, -1, 1},
										{16, -1, 0, 490012},
										{15, -1, 3, 10},
										{0, -1, 3, 490012},
										{16, -1, 0, 490013},
										{14, 160003, 490012, 490013},
										{19, 490013, 640050, 490014, -1, 1},
										{1, 20002, 490014, 550001},
										{26, -1, -1, 550001},
										{28, -1, -1, -1},
										{19, -1, 640050, 490015},
										{16, -1, 1, 490016},
										{1, 490015, 490016, 490017},
										{20, -1, 490017, 640050, -1},
										{19, -1, 640050, 490018},
										{16, -1, 1, 490019},
										{2, 490018, 490019, 490020},
										{20, -1, 490020, 640050, -1},
										{1, 400000, 20003, 550002},
										{0, -1, 550002, 400000},
										{26, -1, -1, 20004},
										{19, -1, 640050, 490021},
										{26, -1, -1, 490021},
										{16, -1, 0, 490022},
										{15, -1, 6, 10},
										{0, -1, 6, 490022},
										{16, -1, 0, 490023},
										{14, 160003, 490022, 490023},
										{21, -1, -1, 1},
										{22, -1, 5, 340000},
										{24, 1, 490023, 1},
										{0, -1, 100000, 550003},
										{26, -1, -1, 550003},
										{26, -1, -1, 20005},
										{28, -1, -1, -1},
										{19, -1, 640050, 490024},
										{3, 490024, 5, 490025},
										{20, -1, 490025, 640050, -1},
										{16, -1, 0, 490026},
										{15, -1, 0, 50},
										{0, -1, 0, 490026},
										{16, -1, 0, 490027},
										{14, 640000, 490026, 490027},
										{19, 160001, 490027, 490028, 1},
										{16, -1, 0, 490029},
										{15, -1, 0, 50},
										{0, -1, 0, 490029},
										{16, -1, 0, 490030},
										{14, 640000, 490029, 490030},
										{16, -1, 0, 490031},
										{19, -1, 490030, 490031, 1},
										{3, 490031, 7, 490032},
										{1, 490028, 490032, 490033},
										{20, 160001, 490033, 490027, 2, -1},
										{16, -1, 0, 490034},
										{15, -1, 8, 50},
										{0, -1, 8, 490034},
										{16, -1, 0, 490035},
										{14, 640000, 490034, 490035},
										{19, -1, 490035, 490036, 1},
										{2, -1, 9, 490037},
										{2, 490036, 490037, 490038},
										{20, -1, 490038, 490035, 2},
										{16, -1, 0, 490039},
										{15, -1, 0, 50},
										{0, -1, 0, 490039},
										{16, -1, 0, 490040},
										{14, 640000, 490039, 490040},
										{19, 160001, 490040, 490041, 1},
										{3, 10, 5, 490042},
										{16, -1, 0, 490043},
										{15, -1, 490042, 50},
										{0, -1, 490042, 490043},
										{16, -1, 0, 490044},
										{14, 640000, 490043, 490044},
										{16, -1, 0, 490045},
										{19, -1, 490044, 490045, 1},
										{1, 490041, 490045, 490046},
										{20, 160001, 490046, 490040, 2, -1},
										{16, -1, 0, 490047},
										{15, -1, 0, 50},
										{0, -1, 0, 490047},
										{16, -1, 0, 490048},
										{14, 640000, 490047, 490048},
										{16, -1, 0, 490049},
										{19, 160001, 490048, 490049, 1},
										{26, -1, -1, 490049},
										{28, -1, -1, -1},
										{19, -1, 640050, 490050},
										{29, -1, 400000, 490051},
										{1, 490050, 490051, 490052},
										{19, -1, 640050, 490053},
										{1, 490052, 490053, 490054},
										{16, -1, 0, 490055},
										{15, -1, 0, 50},
										{0, -1, 0, 490055},
										{16, -1, 0, 490056},
										{14, 640000, 490055, 490056},
										{16, -1, 0, 490057},
										{19, -1, 490056, 490057, 1},
										{1, 490054, 490057, 490058},
										{20, -1, 490058, 640050, -1},
										{29, -1, 20006, 490059},
										{16, -1, 0, 490060},
										{15, -1, 0, 50},
										{0, -1, 0, 490060},
										{16, -1, 0, 490061},
										{14, 640000, 490060, 490061},
										{16, -1, 0, 490062},
										{19, -1, 490061, 490062, 1},
										{1, 490059, 490062, 490063},
										{19, -1, 640050, 490064},
										{1, 490063, 490064, 490065},
										{0, -1, 490065, 40000},
										{35, -1, -1, 1},
										{20, -1, 340000, 640050, -1},
										{3, 20007, 340000, 550000},
										{0, -1, 550000, 100001},
										{35, -1, -1, 1},
										{3, 20008, 340000, 550000},
										{0, -1, 550000, 100002},
										{35, -1, -1, 1},
										{19, -1, 700000, 550000},
										{21, -1, -1, 150},
										{22, -1, 3, 340000},
										{24, -1, -1, 150},
										{0, -1, 100002, 550001},
										{31, 0, 550000, 550001, 700001, 1500},
										{35, -1, -1, 1},
										{17, 10, 3, 160003},
										{16, -1, 0, 190000},
										{15, -1, 4, 10},
										{0, -1, 4, 190000},
										{16, -1, 0, 190001},
										{14, 160003, 190000, 190001},
										{20, 190001, 0, 640050, -1, 1},
										{0, -1, 3, 40001},
										{7, 40001, 0, 280000},
										{34, -1, 280000, 198},
										{16, -1, 0, 190004},
										{15, -1, 40001, 10},
										{0, -1, 40001, 190004},
										{16, -1, 0, 190005},
										{14, 160003, 190004, 190005},
										{19, 190005, 640050, 190006, -1, 1},
										{1, 190006, 0, 190007},
										{2, 40001, 3, 190008},
										{16, -1, 0, 190009},
										{15, -1, 190008, 10},
										{0, -1, 190008, 190009},
										{16, -1, 0, 190010},
										{14, 160003, 190009, 190010},
										{19, 190010, 640050, 190011, -1, 1},
										{1, 190007, 190011, 190012},
										{20, 190005, 190012, 640050, -1, 1},
										{16, -1, 0, 190013},
										{15, -1, 40001, 10},
										{0, -1, 40001, 190013},
										{16, -1, 0, 190014},
										{14, 160003, 190013, 190014},
										{19, 190014, 640050, 190015, -1, 1},
										{26, -1, -1, 190015},
										{28, -1, -1, -1},
										{16, -1, 1, 190002},
										{1, 40001, 190002, 190003},
										{0, -1, 190003, 40001},
										{33, -1, -1, 168},
										{26, -1, -1, 20009},
										{28, -1, -1, -1},
										{16, -1, 0, 190016},
										{15, -1, 4, 10},
										{0, -1, 4, 190016},
										{16, -1, 0, 190017},
										{14, 160003, 190016, 190017},
										{19, 190017, 640050, 190018, -1, 1},
										{26, -1, -1, 190018},
										{16, -1, 0, 190019},
										{15, -1, 6, 10},
										{0, -1, 6, 190019},
										{16, -1, 0, 190020},
										{14, 160003, 190019, 190020},
										{19, 190020, 640050, 190021, -1, 1},
										{26, -1, -1, 190021},
										{16, -1, 0, 190022},
										{15, -1, 6, 10},
										{0, -1, 6, 190022},
										{16, -1, 0, 190023},
										{14, 160003, 190022, 190023},
										{21, -1, -1, 146},
										{22, -1, 6, 340000},
										{24, 1, 190023, 146},
										{0, -1, 100001, 250000},
										{1, 250000, 20010, 250001},
										{26, -1, -1, 250001},
										{28, -1, -1, -1},
										{16, -1, 0, 190024},
										{15, -1, 6, 10},
										{0, -1, 6, 190024},
										{16, -1, 0, 190025},
										{14, 160003, 190024, 190025},
										{19, 190025, 640050, 190026, -1, 1},
										{26, -1, -1, 190026},
										{28, -1, -1, -1},
										{13, -1, 30000, 280001},
										{11, 30000, 30001, 280002},
										{11, 280001, 280002, 280003},
										{0, -1, 280003, 40001},
										{26, -1, -1, 40001},
										{28, -1, -1, -1},
										{34, -1, 30000, 244},
										{26, -1, -1, 30000},
										{28, -1, -1, -1},
										{33, -1, -1, 248},
										{34, -1, 30001, 248},
										{5, 10000, 10000, 280004},
										{26, -1, -1, 280004},
										{28, -1, -1, -1},
										{34, -1, 30000, 250},
										{33, -1, -1, 253},
										{5, 20011, 20012, 280005},
										{26, -1, -1, 280005},
										{28, -1, -1, -1},
										{18, -1, 3, 160000},
										{18, -1, 3, 160001},
										{20, 160001, 0, 640050, -1, -1},
										{1, 100003, 20013, 250002},
										{0, -1, 250002, 100003},
										{3, 100003, 7, 250003},
										{0, -1, 250003, 100003},
										{20, 160000, 20014, 700000, -1, -1},
										{19, 160000, 700000, 250004, -1, -1},
										{26, -1, -1, 250004},
										{19, 160000, 700000, 250005, -1, -1},
										{19, 160000, 640050, 190027, -1, -1},
										{30, -1, 250005, 190027, 7, 250006},
										{26, -1, -1, 250006},
										{28, -1, -1, -1},
										{16, -1, 0, 190028},
										{15, -1, 0, 50},
										{0, -1, 0, 190028},
										{16, -1, 0, 190029},
										{14, 640000, 190028, 190029},
										{20, 160000, 11, 190029, 2, -1},
										{19, 160000, 640050, 190030, -1, -1},
										{16, -1, 0, 190031},
										{15, -1, 0, 50},
										{0, -1, 0, 190031},
										{16, -1, 0, 190032},
										{14, 640000, 190031, 190032},
										{16, -1, 0, 190033},
										{19, 160000, 190032, 190033, 1},
										{2, 190030, 190033, 190034},
										{20, 160000, 190034, 640050, -1, -1},
										{16, -1, 0, 190035},
										{15, -1, 12, 50},
										{0, -1, 12, 190035},
										{16, -1, 0, 190036},
										{14, 40002, 190035, 190036},
										{0, 1, 190036, 190037},
										{19, 160000, 640050, 190038, -1, -1},
										{2, 190037, 190038, 190039},
										{0, 2, 190039, 190036},
										{16, -1, 0, 190040},
										{15, -1, 13, 50},
										{0, -1, 13, 190040},
										{16, -1, 0, 190041},
										{14, 640000, 190040, 190041},
										{19, 160000, 190041, 190042, 1},
										{16, -1, 0, 190043},
										{15, -1, 12, 50},
										{0, -1, 12, 190043},
										{16, -1, 0, 190044},
										{14, 40002, 190043, 190044},
										{16, -1, 0, 190045},
										{0, 1, 190044, 190045},
										{1, 190042, 190045, 190046},
										{20, 160000, 190046, 190041, 2, -1},
										{16, -1, 0, 190047},
										{15, -1, 13, 50},
										{0, -1, 13, 190047},
										{16, -1, 0, 190048},
										{14, 640000, 190047, 190048},
										{19, 160000, 190048, 190049, 1},
										{16, -1, 0, 190050},
										{15, -1, 12, 50},
										{0, -1, 12, 190050},
										{16, -1, 0, 190051},
										{14, 40002, 190050, 190051},
										{16, -1, 0, 190052},
										{0, 1, 190051, 190052},
										{3, 190049, 190052, 190053},
										{20, 160000, 190053, 190048, 2, -1},
										{16, -1, 0, 190054},
										{15, -1, 12, 50},
										{0, -1, 12, 190054},
										{16, -1, 0, 190055},
										{14, 40002, 190054, 190055},
										{16, -1, 0, 190056},
										{0, 1, 190055, 190056},
										{26, -1, -1, 190056},
										{16, -1, 0, 190057},
										{15, -1, 13, 50},
										{0, -1, 13, 190057},
										{16, -1, 0, 190058},
										{14, 640000, 190057, 190058},
										{16, -1, 0, 190059},
										{19, 160000, 190058, 190059, 1},
										{26, -1, -1, 190059},
										{28, -1, -1, -1},
										{3, 6, 7, 190060},
										{1, 40001, 190060, 190061},
										{0, -1, 190061, 40001},
										{26, -1, -1, 40001},
										{28, -1, -1, -1},
										{16, -1, 0, 190062},
										{15, -1, 0, 50},
										{0, -1, 0, 190062},
										{16, -1, 0, 190063},
										{14, 640000, 190062, 190063},
										{16, -1, 0, 190064},
										{19, 160000, 190063, 190064, 1},
										{2, 40001, 190064, 190065},
										{0, -1, 190065, 40001},
										{26, -1, -1, 40001},
										{28, -1, -1, -1},
										{16, -1, 0, 190066},
										{15, -1, 6, 50},
										{0, -1, 6, 190066},
										{16, -1, 0, 190067},
										{14, 640000, 190066, 190067},
										{19, 160000, 190067, 190068, 1},
										{16, -1, 0, 190069},
										{15, -1, 0, 50},
										{0, -1, 0, 190069},
										{16, -1, 0, 190070},
										{14, 640000, 190069, 190070},
										{16, -1, 0, 190071},
										{19, 160000, 190070, 190071, 1},
										{1, 190068, 190071, 190072},
										{20, 160000, 190072, 190067, 2, -1},
										{19, 160000, 640050, 190073, -1, -1},
										{16, -1, 0, 190074},
										{15, -1, 0, 50},
										{0, -1, 0, 190074},
										{16, -1, 0, 190075},
										{14, 640000, 190074, 190075},
										{16, -1, 0, 190076},
										{19, 160000, 190075, 190076, 1},
										{4, 190073, 190076, 190077},
										{20, 160000, 190077, 640050, -1, -1},
										{16, -1, 0, 190078},
										{15, -1, 6, 50},
										{0, -1, 6, 190078},
										{16, -1, 0, 190079},
										{14, 640000, 190078, 190079},
										{19, 160000, 190079, 190080, 1},
										{16, -1, 1, 190081},
										{1, 190080, 190081, 190082},
										{20, 160000, 190082, 190079, 2, -1},
										{16, -1, 0, 190083},
										{15, -1, 7, 50},
										{0, -1, 7, 190083},
										{16, -1, 0, 190084},
										{14, 40002, 190083, 190084},
										{16, -1, 0, 190085},
										{0, 1, 190084, 190085},
										{26, -1, -1, 190085},
										{16, -1, 0, 190086},
										{15, -1, 5, 50},
										{0, -1, 5, 190086},
										{16, -1, 0, 190087},
										{14, 40002, 190086, 190087},
										{16, -1, 0, 190088},
										{0, 1, 190087, 190088},
										{26, -1, -1, 190088},
										{28, -1, -1, -1},
										{16, -1, 0, 190089},
										{15, -1, 6, 50},
										{0, -1, 6, 190089},
										{16, -1, 0, 190090},
										{14, 640000, 190089, 190090},
										{16, -1, 0, 190091},
										{19, 160000, 190090, 190091, 1},
										{26, -1, -1, 190091},
										{19, 160000, 640050, 190092, -1, -1},
										{26, -1, -1, 190092},
										{28, -1, -1, -1},
										{21, -1, -1, 4},
										{22, -1, 20015, 400000},
										{24, -1, 160000, 4},
										{0, -1, 40000, 190093},
										{26, -1, -1, 190093},
										{28, -1, -1, -1},
										{26, -1, -1, 20016},
										{27, -1, -1, -1},
										{25, 160000, -1, 700000},
										{26, -1, -1, 20017},
										{28, -1, -1, -1},
										{21, -1, -1, 153},
										{24, -1, 160000, 153},
										{0, -1, 4, 40001},
										{7, 40001, 14, 280006},
										{16, -1, 0, 190094},
										{15, -1, 40001, 1500},
										{0, -1, 40001, 190094},
										{16, -1, 0, 190095},
										{14, 700001, 190094, 190095},
										{16, -1, 0, 250007},
										{19, 160000, 190095, 250007, 1},
										{12, 250007, 20018, 280007},
										{10, 280006, 280007, 280008},
										{34, -1, 280008, 473},
										{1, 20019, 40001, 250008},
										{1, 250008, 20020, 250009},
										{16, -1, 0, 190098},
										{15, -1, 40001, 1500},
										{0, -1, 40001, 190098},
										{16, -1, 0, 190099},
										{14, 700001, 190098, 190099},
										{16, -1, 0, 250010},
										{19, 160000, 190099, 250010, 1},
										{1, 250009, 250010, 250011},
										{26, -1, -1, 250011},
										{28, -1, -1, -1},
										{16, -1, 0, 190100},
										{15, -1, 40001, 1500},
										{0, -1, 40001, 190100},
										{16, -1, 0, 190101},
										{14, 700001, 190100, 190101},
										{16, -1, 0, 190102},
										{15, -1, 40001, 1500},
										{0, -1, 40001, 190102},
										{16, -1, 0, 190103},
										{14, 700001, 190102, 190103},
										{16, -1, 0, 250012},
										{19, 160000, 190103, 250012, 1},
										{30, -1, 250012, 4, 0, 250013},
										{20, 160000, 250013, 190101, 2, -1},
										{16, -1, 1, 190096},
										{1, 40001, 190096, 190097},
										{0, -1, 190097, 40001},
										{33, -1, -1, 432},
										{21, -1, -1, 1},
										{22, -1, 0, 340000},
										{24, -1, 160000, 1},
										{0, -1, 100000, 250014},
										{1, 250014, 20022, 250015},
										{16, -1, 0, 190104},
										{15, -1, 0, 50},
										{0, -1, 0, 190104},
										{16, -1, 0, 190105},
										{14, 640000, 190104, 190105},
										{16, -1, 0, 190106},
										{19, 160001, 190105, 190106, 1},
										{1, 250015, 190106, 250016},
										{1, 250016, 20023, 250017},
										{21, -1, -1, 150},
										{22, -1, 3, 340000},
										{24, -1, 160000, 150},
										{0, -1, 100002, 250018},
										{1, 250017, 250018, 250019},
										{32, 160000, 20021, 250019, 700001, 1500},
										{36, -1, -1, -1},
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

			case 30:			// SUBSTR
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

			case 31:			// F_OPEN
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

			case 32:			// F_WRITE
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

      case 33:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 34:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 35:			// ENDFNC
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

      case 36:			// END
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
