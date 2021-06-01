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
										{220, {{53,0,4,0,113}, {128,0,20,11,3}, {17,1,25,2,0}}},
										{1, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{4, {{0,0,1,0,3}, {91,0,4,0,1}}},
										{206, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{210, {{1,0,0,0,0}, {0,0,1,0,0}}},
										{213, {{0,0,0,0,0}, {0,0,2,0,0}}},
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
										{3, "3"},
										{4, "0"},
										{5, "101"},
										{6, "1"},
										{7, "5"},
										{20001, "cc_obj.n = "},
										{8, "2"},
										{20002, "objs[1].n = "},
										{20003, "lol!"},
										{20004, "n:"},
										{20005, "hehehe"},
										{9, "44"},
										{10, "33"},
										{11, "22"},
										{20006, "05"},
										{20007, " "},
										{20008, "\n"},
										{20009, "--------"},
										{20010, "here we go"},
										{20011, "ok"},
										{10000, "2.33"},
										{20012, "lol"},
										{20013, "lolo"},
										{20014, "HI!"},
										{20015, "hilo"},
										{12, "20"},
										{13, "49"},
										{14, "45"},
										{15, "93"},
										{20016, "100"},
										{20017, ">> Enter file path:\n-- "},
										{20018, ">> Parsing file..."},
										{16, "1499"},
										{20019, "END_OF_STREAM"},
										{20020, "Entry "},
										{20021, ": "},
										{20022, "file.txt"},
										{20023, " // An extra funny comment to confirm this works : ) "},
										{20024, " //"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{33, -1, -1, 220},
										{3, 20000, 340000, 550000},
										{0, -1, 550000, 100000},
										{35, -1, -1, 1},
										{17, -1, 3, 160000},
										{17, -1, 3, 160001},
										{17, 10, 3, 160003},
										{17, 3, 3, 460000},
										{16, -1, 0, 490000},
										{15, -1, 4, 3},
										{0, -1, 4, 490000},
										{16, -1, 0, 490001},
										{14, 460000, 490000, 490001},
										{18, 1, 3, 490001},
										{16, -1, 0, 490002},
										{15, -1, 4, 3},
										{0, -1, 4, 490002},
										{16, -1, 0, 490003},
										{14, 460000, 490002, 490003},
										{20, 490003, 5, 640050, -1, 1},
										{16, -1, 0, 490004},
										{15, -1, 6, 3},
										{0, -1, 6, 490004},
										{16, -1, 0, 490005},
										{14, 460000, 490004, 490005},
										{19, 490005, 640050, 490006, -1, 1},
										{16, -1, 0, 490007},
										{15, -1, 4, 3},
										{0, -1, 4, 490007},
										{16, -1, 0, 490008},
										{14, 460000, 490007, 490008},
										{19, 490008, 640050, 490009, -1, 1},
										{1, 490006, 490009, 490010},
										{1, 490010, 7, 490011},
										{20, 490005, 490011, 640050, -1, 1},
										{16, -1, 0, 490012},
										{15, -1, 4, 3},
										{0, -1, 4, 490012},
										{16, -1, 0, 490013},
										{14, 460000, 490012, 490013},
										{19, 490013, 640050, 490014, -1, 1},
										{26, -1, -1, 490014},
										{16, -1, 0, 490015},
										{15, -1, 6, 3},
										{0, -1, 6, 490015},
										{16, -1, 0, 490016},
										{14, 460000, 490015, 490016},
										{19, 490016, 640050, 490017, -1, 1},
										{26, -1, -1, 490017},
										{28, -1, -1, -1},
										{16, -1, 0, 490018},
										{15, -1, 6, 3},
										{0, -1, 6, 490018},
										{16, -1, 0, 490019},
										{14, 460000, 490018, 490019},
										{19, 490019, 640050, 490020, -1, 1},
										{0, -1, 490020, 40000},
										{16, -1, 0, 490021},
										{15, -1, 6, 3},
										{0, -1, 6, 490021},
										{16, -1, 0, 490022},
										{14, 460000, 490021, 490022},
										{19, 490022, 640050, 490023, -1, 1},
										{1, 40000, 490023, 490024},
										{0, -1, 490024, 40000},
										{26, -1, -1, 40000},
										{28, -1, -1, -1},
										{19, 160001, 640050, 490025, -1, -1},
										{1, 20001, 490025, 550000},
										{26, -1, -1, 550000},
										{28, -1, -1, -1},
										{16, -1, 0, 490026},
										{15, -1, 6, 10},
										{0, -1, 6, 490026},
										{16, -1, 0, 490027},
										{14, 160003, 490026, 490027},
										{19, 490027, 640050, 490028, -1, 1},
										{16, -1, 0, 490029},
										{15, -1, 4, 10},
										{0, -1, 4, 490029},
										{16, -1, 0, 490030},
										{14, 160003, 490029, 490030},
										{19, 490030, 640050, 490031, -1, 1},
										{3, 490028, 490031, 490032},
										{16, -1, 0, 490033},
										{15, -1, 8, 10},
										{0, -1, 8, 490033},
										{16, -1, 0, 490034},
										{14, 160003, 490033, 490034},
										{19, 490034, 640050, 490035, -1, 1},
										{3, 490032, 490035, 490036},
										{20, 490027, 490036, 640050, -1, 1},
										{16, -1, 0, 490037},
										{15, -1, 6, 10},
										{0, -1, 6, 490037},
										{16, -1, 0, 490038},
										{14, 160003, 490037, 490038},
										{19, 490038, 640050, 490039, -1, 1},
										{1, 20002, 490039, 550001},
										{26, -1, -1, 550001},
										{28, -1, -1, -1},
										{19, -1, 640050, 490040},
										{16, -1, 1, 490041},
										{1, 490040, 490041, 490042},
										{20, -1, 490042, 640050, -1},
										{19, -1, 640050, 490043},
										{16, -1, 1, 490044},
										{2, 490043, 490044, 490045},
										{20, -1, 490045, 640050, -1},
										{1, 400000, 20003, 550002},
										{0, -1, 550002, 400000},
										{26, -1, -1, 20004},
										{19, -1, 640050, 490046},
										{26, -1, -1, 490046},
										{16, -1, 0, 490047},
										{15, -1, 7, 10},
										{0, -1, 7, 490047},
										{16, -1, 0, 490048},
										{14, 160003, 490047, 490048},
										{21, -1, -1, 1},
										{22, -1, 8, 340000},
										{24, 1, 490048, 1},
										{0, -1, 100000, 550003},
										{26, -1, -1, 550003},
										{26, -1, -1, 20005},
										{28, -1, -1, -1},
										{19, -1, 640050, 490049},
										{3, 490049, 8, 490050},
										{20, -1, 490050, 640050, -1},
										{16, -1, 0, 490051},
										{15, -1, 0, 50},
										{0, -1, 0, 490051},
										{16, -1, 0, 490052},
										{14, 640000, 490051, 490052},
										{19, 160001, 490052, 490053, 1},
										{16, -1, 0, 490054},
										{15, -1, 0, 50},
										{0, -1, 0, 490054},
										{16, -1, 0, 490055},
										{14, 640000, 490054, 490055},
										{16, -1, 0, 490056},
										{19, -1, 490055, 490056, 1},
										{3, 490056, 3, 490057},
										{1, 490053, 490057, 490058},
										{20, 160001, 490058, 490052, 2, -1},
										{16, -1, 0, 490059},
										{15, -1, 9, 50},
										{0, -1, 9, 490059},
										{16, -1, 0, 490060},
										{14, 640000, 490059, 490060},
										{19, -1, 490060, 490061, 1},
										{2, -1, 10, 490062},
										{2, 490061, 490062, 490063},
										{20, -1, 490063, 490060, 2},
										{16, -1, 0, 490064},
										{15, -1, 0, 50},
										{0, -1, 0, 490064},
										{16, -1, 0, 490065},
										{14, 640000, 490064, 490065},
										{19, 160001, 490065, 490066, 1},
										{3, 11, 8, 490067},
										{16, -1, 0, 490068},
										{15, -1, 490067, 50},
										{0, -1, 490067, 490068},
										{16, -1, 0, 490069},
										{14, 640000, 490068, 490069},
										{16, -1, 0, 490070},
										{19, -1, 490069, 490070, 1},
										{1, 490066, 490070, 490071},
										{20, 160001, 490071, 490065, 2, -1},
										{16, -1, 0, 490072},
										{15, -1, 0, 50},
										{0, -1, 0, 490072},
										{16, -1, 0, 490073},
										{14, 640000, 490072, 490073},
										{16, -1, 0, 490074},
										{19, 160001, 490073, 490074, 1},
										{26, -1, -1, 490074},
										{28, -1, -1, -1},
										{19, -1, 640050, 490075},
										{29, -1, 400000, 490076},
										{1, 490075, 490076, 490077},
										{19, -1, 640050, 490078},
										{1, 490077, 490078, 490079},
										{16, -1, 0, 490080},
										{15, -1, 0, 50},
										{0, -1, 0, 490080},
										{16, -1, 0, 490081},
										{14, 640000, 490080, 490081},
										{16, -1, 0, 490082},
										{19, -1, 490081, 490082, 1},
										{1, 490079, 490082, 490083},
										{20, -1, 490083, 640050, -1},
										{29, -1, 20006, 490084},
										{16, -1, 0, 490085},
										{15, -1, 0, 50},
										{0, -1, 0, 490085},
										{16, -1, 0, 490086},
										{14, 640000, 490085, 490086},
										{16, -1, 0, 490087},
										{19, -1, 490086, 490087, 1},
										{1, 490084, 490087, 490088},
										{19, -1, 640050, 490089},
										{1, 490088, 490089, 490090},
										{0, -1, 490090, 40001},
										{35, -1, -1, 1},
										{20, -1, 340000, 640050, -1},
										{3, 20007, 340000, 550000},
										{0, -1, 550000, 100001},
										{35, -1, -1, 1},
										{3, 20008, 340000, 550000},
										{0, -1, 550000, 100002},
										{35, -1, -1, 1},
										{19, -1, 700000, 550000},
										{21, -1, -1, 210},
										{22, -1, 6, 340000},
										{24, -1, -1, 210},
										{0, -1, 100002, 550001},
										{31, 0, 550000, 550001, 700001, 1500},
										{35, -1, -1, 1},
										{17, 10, 3, 160003},
										{17, 100, 3, 160013},
										{16, -1, 0, 190000},
										{15, -1, 4, 10},
										{16, -1, 0, 190001},
										{0, -1, 4, 190001},
										{3, 190001, 0, 190001},
										{1, 190000, 190001, 190000},
										{15, -1, 4, 10},
										{1, 190000, 4, 190000},
										{16, -1, 0, 190002},
										{14, 160013, 190000, 190002},
										{20, 190002, 0, 640050, -1, 1},
										{16, -1, 0, 190003},
										{15, -1, 4, 10},
										{16, -1, 0, 190004},
										{0, -1, 4, 190004},
										{3, 190004, 0, 190004},
										{1, 190003, 190004, 190003},
										{15, -1, 4, 10},
										{1, 190003, 4, 190003},
										{16, -1, 0, 190005},
										{14, 160013, 190003, 190005},
										{19, 190005, 640050, 190006, -1, 1},
										{16, -1, 1, 190007},
										{1, 190006, 190007, 190008},
										{20, 190005, 190008, 640050, -1, 1},
										{16, -1, 0, 190009},
										{15, -1, 6, 10},
										{16, -1, 0, 190010},
										{0, -1, 6, 190010},
										{3, 190010, 0, 190010},
										{1, 190009, 190010, 190009},
										{15, -1, 4, 10},
										{1, 190009, 4, 190009},
										{16, -1, 0, 190011},
										{14, 160013, 190009, 190011},
										{18, 1, 3, 190011},
										{26, -1, -1, 20009},
										{28, -1, -1, -1},
										{16, -1, 0, 190012},
										{15, -1, 4, 10},
										{16, -1, 0, 190013},
										{0, -1, 4, 190013},
										{3, 190013, 0, 190013},
										{1, 190012, 190013, 190012},
										{15, -1, 4, 10},
										{1, 190012, 4, 190012},
										{16, -1, 0, 190014},
										{14, 160013, 190012, 190014},
										{19, 190014, 640050, 190015, -1, 1},
										{26, -1, -1, 190015},
										{28, -1, -1, -1},
										{26, -1, -1, 20009},
										{28, -1, -1, -1},
										{0, -1, 4, 40000},
										{7, 40000, 0, 280000},
										{34, -1, 280000, 329},
										{0, -1, 4, 40002},
										{7, 40002, 0, 280001},
										{34, -1, 280001, 325},
										{16, -1, 0, 190020},
										{15, -1, 40000, 10},
										{16, -1, 0, 190021},
										{0, -1, 40000, 190021},
										{3, 190021, 0, 190021},
										{1, 190020, 190021, 190020},
										{15, -1, 40002, 10},
										{1, 190020, 40002, 190020},
										{16, -1, 0, 190022},
										{14, 160013, 190020, 190022},
										{19, 190022, 640050, 190023, -1, 1},
										{1, 190023, 0, 190024},
										{12, 40002, 4, 280002},
										{2, 40002, 280002, 190025},
										{16, -1, 0, 190026},
										{15, -1, 40000, 10},
										{16, -1, 0, 190027},
										{0, -1, 40000, 190027},
										{3, 190027, 0, 190027},
										{1, 190026, 190027, 190026},
										{15, -1, 190025, 10},
										{1, 190026, 190025, 190026},
										{16, -1, 0, 190028},
										{14, 160013, 190026, 190028},
										{19, 190028, 640050, 190029, -1, 1},
										{1, 190024, 190029, 190030},
										{20, 190022, 190030, 640050, -1, 1},
										{16, -1, 0, 190031},
										{15, -1, 40000, 10},
										{16, -1, 0, 190032},
										{0, -1, 40000, 190032},
										{3, 190032, 0, 190032},
										{1, 190031, 190032, 190031},
										{15, -1, 40002, 10},
										{1, 190031, 40002, 190031},
										{16, -1, 0, 190033},
										{14, 160013, 190031, 190033},
										{19, 190033, 640050, 190034, -1, 1},
										{26, -1, -1, 190034},
										{28, -1, -1, -1},
										{16, -1, 1, 190018},
										{1, 40002, 190018, 190019},
										{0, -1, 190019, 40002},
										{33, -1, -1, 279},
										{16, -1, 1, 190016},
										{1, 40000, 190016, 190017},
										{0, -1, 190017, 40000},
										{33, -1, -1, 276},
										{26, -1, -1, 20010},
										{28, -1, -1, -1},
										{16, -1, 0, 190035},
										{15, -1, 4, 10},
										{0, -1, 4, 190035},
										{16, -1, 0, 190036},
										{14, 160003, 190035, 190036},
										{19, 190036, 640050, 190037, -1, 1},
										{26, -1, -1, 190037},
										{16, -1, 0, 190038},
										{15, -1, 7, 10},
										{0, -1, 7, 190038},
										{16, -1, 0, 190039},
										{14, 160003, 190038, 190039},
										{19, 190039, 640050, 190040, -1, 1},
										{26, -1, -1, 190040},
										{16, -1, 0, 190041},
										{15, -1, 7, 10},
										{0, -1, 7, 190041},
										{16, -1, 0, 190042},
										{14, 160003, 190041, 190042},
										{21, -1, -1, 206},
										{22, -1, 7, 340000},
										{24, 1, 190042, 206},
										{0, -1, 100001, 250000},
										{1, 250000, 20011, 250001},
										{26, -1, -1, 250001},
										{28, -1, -1, -1},
										{16, -1, 0, 190043},
										{15, -1, 7, 10},
										{0, -1, 7, 190043},
										{16, -1, 0, 190044},
										{14, 160003, 190043, 190044},
										{19, 190044, 640050, 190045, -1, 1},
										{26, -1, -1, 190045},
										{28, -1, -1, -1},
										{13, -1, 30000, 280003},
										{11, 30000, 30001, 280004},
										{11, 280003, 280004, 280005},
										{0, -1, 280005, 40000},
										{26, -1, -1, 40000},
										{28, -1, -1, -1},
										{34, -1, 30000, 375},
										{26, -1, -1, 30000},
										{28, -1, -1, -1},
										{33, -1, -1, 379},
										{34, -1, 30001, 379},
										{5, 10000, 10000, 280006},
										{26, -1, -1, 280006},
										{28, -1, -1, -1},
										{34, -1, 30000, 381},
										{33, -1, -1, 384},
										{5, 20012, 20013, 280007},
										{26, -1, -1, 280007},
										{28, -1, -1, -1},
										{18, -1, 3, 160000},
										{18, -1, 3, 160001},
										{20, 160001, 0, 640050, -1, -1},
										{1, 100003, 20014, 250002},
										{0, -1, 250002, 100003},
										{3, 100003, 3, 250003},
										{0, -1, 250003, 100003},
										{20, 160000, 20015, 700000, -1, -1},
										{19, 160000, 700000, 250004, -1, -1},
										{26, -1, -1, 250004},
										{19, 160000, 700000, 250005, -1, -1},
										{19, 160000, 640050, 190046, -1, -1},
										{30, -1, 250005, 190046, 3, 250006},
										{26, -1, -1, 250006},
										{28, -1, -1, -1},
										{16, -1, 0, 190047},
										{15, -1, 0, 50},
										{0, -1, 0, 190047},
										{16, -1, 0, 190048},
										{14, 640000, 190047, 190048},
										{20, 160000, 12, 190048, 2, -1},
										{19, 160000, 640050, 190049, -1, -1},
										{16, -1, 0, 190050},
										{15, -1, 0, 50},
										{0, -1, 0, 190050},
										{16, -1, 0, 190051},
										{14, 640000, 190050, 190051},
										{16, -1, 0, 190052},
										{19, 160000, 190051, 190052, 1},
										{2, 190049, 190052, 190053},
										{20, 160000, 190053, 640050, -1, -1},
										{16, -1, 0, 190054},
										{15, -1, 13, 50},
										{0, -1, 13, 190054},
										{16, -1, 0, 190055},
										{14, 40003, 190054, 190055},
										{0, 1, 190055, 190056},
										{19, 160000, 640050, 190057, -1, -1},
										{2, 190056, 190057, 190058},
										{0, 2, 190058, 190055},
										{16, -1, 0, 190059},
										{15, -1, 14, 50},
										{0, -1, 14, 190059},
										{16, -1, 0, 190060},
										{14, 640000, 190059, 190060},
										{19, 160000, 190060, 190061, 1},
										{16, -1, 0, 190062},
										{15, -1, 13, 50},
										{0, -1, 13, 190062},
										{16, -1, 0, 190063},
										{14, 40003, 190062, 190063},
										{16, -1, 0, 190064},
										{0, 1, 190063, 190064},
										{1, 190061, 190064, 190065},
										{20, 160000, 190065, 190060, 2, -1},
										{16, -1, 0, 190066},
										{15, -1, 14, 50},
										{0, -1, 14, 190066},
										{16, -1, 0, 190067},
										{14, 640000, 190066, 190067},
										{19, 160000, 190067, 190068, 1},
										{16, -1, 0, 190069},
										{15, -1, 13, 50},
										{0, -1, 13, 190069},
										{16, -1, 0, 190070},
										{14, 40003, 190069, 190070},
										{16, -1, 0, 190071},
										{0, 1, 190070, 190071},
										{3, 190068, 190071, 190072},
										{20, 160000, 190072, 190067, 2, -1},
										{16, -1, 0, 190073},
										{15, -1, 13, 50},
										{0, -1, 13, 190073},
										{16, -1, 0, 190074},
										{14, 40003, 190073, 190074},
										{16, -1, 0, 190075},
										{0, 1, 190074, 190075},
										{26, -1, -1, 190075},
										{16, -1, 0, 190076},
										{15, -1, 14, 50},
										{0, -1, 14, 190076},
										{16, -1, 0, 190077},
										{14, 640000, 190076, 190077},
										{16, -1, 0, 190078},
										{19, 160000, 190077, 190078, 1},
										{26, -1, -1, 190078},
										{28, -1, -1, -1},
										{3, 7, 3, 190079},
										{1, 40000, 190079, 190080},
										{0, -1, 190080, 40000},
										{26, -1, -1, 40000},
										{28, -1, -1, -1},
										{16, -1, 0, 190081},
										{15, -1, 0, 50},
										{0, -1, 0, 190081},
										{16, -1, 0, 190082},
										{14, 640000, 190081, 190082},
										{16, -1, 0, 190083},
										{19, 160000, 190082, 190083, 1},
										{2, 40000, 190083, 190084},
										{0, -1, 190084, 40000},
										{26, -1, -1, 40000},
										{28, -1, -1, -1},
										{16, -1, 0, 190085},
										{15, -1, 7, 50},
										{0, -1, 7, 190085},
										{16, -1, 0, 190086},
										{14, 640000, 190085, 190086},
										{19, 160000, 190086, 190087, 1},
										{16, -1, 0, 190088},
										{15, -1, 0, 50},
										{0, -1, 0, 190088},
										{16, -1, 0, 190089},
										{14, 640000, 190088, 190089},
										{16, -1, 0, 190090},
										{19, 160000, 190089, 190090, 1},
										{1, 190087, 190090, 190091},
										{20, 160000, 190091, 190086, 2, -1},
										{19, 160000, 640050, 190092, -1, -1},
										{16, -1, 0, 190093},
										{15, -1, 0, 50},
										{0, -1, 0, 190093},
										{16, -1, 0, 190094},
										{14, 640000, 190093, 190094},
										{16, -1, 0, 190095},
										{19, 160000, 190094, 190095, 1},
										{4, 190092, 190095, 190096},
										{20, 160000, 190096, 640050, -1, -1},
										{16, -1, 0, 190097},
										{15, -1, 7, 50},
										{0, -1, 7, 190097},
										{16, -1, 0, 190098},
										{14, 640000, 190097, 190098},
										{19, 160000, 190098, 190099, 1},
										{16, -1, 1, 190100},
										{1, 190099, 190100, 190101},
										{20, 160000, 190101, 190098, 2, -1},
										{16, -1, 0, 190102},
										{15, -1, 3, 50},
										{0, -1, 3, 190102},
										{16, -1, 0, 190103},
										{14, 40003, 190102, 190103},
										{16, -1, 0, 190104},
										{0, 1, 190103, 190104},
										{1, 190104, 15, 190105},
										{26, -1, -1, 190105},
										{16, -1, 0, 190106},
										{15, -1, 8, 50},
										{0, -1, 8, 190106},
										{16, -1, 0, 190107},
										{14, 40003, 190106, 190107},
										{16, -1, 0, 190108},
										{0, 1, 190107, 190108},
										{1, 190108, 15, 190109},
										{26, -1, -1, 190109},
										{28, -1, -1, -1},
										{16, -1, 0, 190110},
										{15, -1, 7, 50},
										{0, -1, 7, 190110},
										{16, -1, 0, 190111},
										{14, 640000, 190110, 190111},
										{16, -1, 0, 190112},
										{19, 160000, 190111, 190112, 1},
										{26, -1, -1, 190112},
										{19, 160000, 640050, 190113, -1, -1},
										{26, -1, -1, 190113},
										{28, -1, -1, -1},
										{21, -1, -1, 4},
										{22, -1, 20016, 400000},
										{24, -1, 160000, 4},
										{0, -1, 40001, 190114},
										{26, -1, -1, 190114},
										{28, -1, -1, -1},
										{26, -1, -1, 20017},
										{27, -1, -1, -1},
										{25, 160000, -1, 700000},
										{26, -1, -1, 20018},
										{28, -1, -1, -1},
										{21, -1, -1, 213},
										{24, -1, 160000, 213},
										{0, -1, 4, 40000},
										{7, 40000, 16, 280008},
										{16, -1, 0, 190115},
										{15, -1, 40000, 1500},
										{0, -1, 40000, 190115},
										{16, -1, 0, 190116},
										{14, 700001, 190115, 190116},
										{16, -1, 0, 250007},
										{19, 160000, 190116, 250007, 1},
										{12, 250007, 20019, 280009},
										{10, 280008, 280009, 280010},
										{34, -1, 280010, 606},
										{1, 20020, 40000, 250008},
										{1, 250008, 20021, 250009},
										{16, -1, 0, 190119},
										{15, -1, 40000, 1500},
										{0, -1, 40000, 190119},
										{16, -1, 0, 190120},
										{14, 700001, 190119, 190120},
										{16, -1, 0, 250010},
										{19, 160000, 190120, 250010, 1},
										{1, 250009, 250010, 250011},
										{26, -1, -1, 250011},
										{28, -1, -1, -1},
										{16, -1, 0, 190121},
										{15, -1, 40000, 1500},
										{0, -1, 40000, 190121},
										{16, -1, 0, 190122},
										{14, 700001, 190121, 190122},
										{16, -1, 0, 190123},
										{15, -1, 40000, 1500},
										{0, -1, 40000, 190123},
										{16, -1, 0, 190124},
										{14, 700001, 190123, 190124},
										{16, -1, 0, 250012},
										{19, 160000, 190124, 250012, 1},
										{30, -1, 250012, 4, 0, 250013},
										{20, 160000, 250013, 190122, 2, -1},
										{16, -1, 1, 190117},
										{1, 40000, 190117, 190118},
										{0, -1, 190118, 40000},
										{33, -1, -1, 565},
										{21, -1, -1, 1},
										{22, -1, 0, 340000},
										{24, -1, 160000, 1},
										{0, -1, 100000, 250014},
										{1, 250014, 20023, 250015},
										{16, -1, 0, 190125},
										{15, -1, 0, 50},
										{0, -1, 0, 190125},
										{16, -1, 0, 190126},
										{14, 640000, 190125, 190126},
										{16, -1, 0, 190127},
										{19, 160001, 190126, 190127, 1},
										{1, 250015, 190127, 250016},
										{1, 250016, 20024, 250017},
										{21, -1, -1, 210},
										{22, -1, 6, 340000},
										{24, -1, 160000, 210},
										{0, -1, 100002, 250018},
										{1, 250017, 250018, 250019},
										{32, 160000, 20022, 250019, 700001, 1500},
										{36, -1, -1, -1},
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

// Gien a variable's memory index, calculates its signature
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
