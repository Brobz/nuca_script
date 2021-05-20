// NucaScript VM
// To compile: g++ main.cpp -o out_file_path


#include <iostream>
#include <fstream>
#include <stack>
#include <map>

#include "MemoryMap.h"
#include "Value.h"

using namespace std;


// MEMORY //
const int MAX_CONSTANTS = 1000, MAX_SYMBOLS = 3000, MAX_TMP_SYMBOLS = 3000, VAR_TYPES = 4, MEMORY_STACK_LIMIT = 100000;

const map<int, vector<vector<int>>> MEMORY_MAP_SIGN = {
										{11, {{138,0,0,0}, {175,0,0,114}, {11,0,2,0}}},
										{1, {{2,0,0,0}, {1,0,0,1}}},
										{8, {{1,0,0,0}, {1,0,0,0}}},
										};
// MEMORY //

// CONSTANTS //
const map<int, string> CONSTANTS = {
										{0, "100"},
										{1, "3"},
										{2, "0"},
										{3, "10"},
										{4, "1"},
										{5, "2"},
										{6, "25"},
										{7, "95"},
										{8, "20"},
										{9, "30"},
										{2000, "mult:"},
										{10, "28"},
										{2001, "------------------"},
										};
// CONSTANTS //

// QUADS //
const vector<vector<int>> QUADS = {
										{22, -1, -1, 11},
										{0, -1, 2, 28001},
										{7, 28001, 3, 49000},
										{23, -1, 49000, 7},
										{1, 28001, 4, 40000},
										{0, -1, 40000, 28001},
										{22, -1, -1, 2},
										{24, -1, -1, -1},
										{3, 28000, 5, 40000},
										{0, -1, 40000, 4137},
										{24, -1, -1, -1},
										{0, -1, 5, 4136},
										{19, -1, -1, 4136},
										{21, -1, -1, -1},
										{2, 4136, 4136, 16001},
										{7, 4136, 0, 25001},
										{8, 4136, 16001, 25000},
										{10, 25000, 25001, 25001},
										{23, -1, 25001, 20},
										{22, -1, -1, 21},
										{26, -1, -1, -1},
										{1, 16000, 4136, 16000},
										{14, 4000, 16000, 16002},
										{0, 2, 4, 16002},
										{2, 4136, 4136, 16004},
										{7, 4136, 0, 25003},
										{8, 4136, 16004, 25002},
										{10, 25002, 25003, 25003},
										{23, -1, 25003, 30},
										{22, -1, -1, 31},
										{26, -1, -1, -1},
										{1, 16003, 4136, 16003},
										{14, 4000, 16003, 16005},
										{0, 1, 16005, 16006},
										{19, -1, -1, 16006},
										{21, -1, -1, -1},
										{2, 5, 5, 16008},
										{7, 5, 1, 25005},
										{8, 5, 16008, 25004},
										{10, 25004, 25005, 25005},
										{23, -1, 25005, 42},
										{22, -1, -1, 43},
										{26, -1, -1, -1},
										{0, -1, 5, 16009},
										{3, 16009, 1, 16009},
										{1, 16007, 16009, 16007},
										{2, 5, 5, 16010},
										{7, 5, 1, 25007},
										{8, 5, 16010, 25006},
										{10, 25006, 25007, 25007},
										{23, -1, 25007, 52},
										{22, -1, -1, 53},
										{26, -1, -1, -1},
										{1, 16007, 5, 16007},
										{14, 4100, 16007, 16011},
										{0, 2, 3, 16011},
										{2, 2, 2, 16013},
										{7, 2, 1, 25009},
										{8, 2, 16013, 25008},
										{10, 25008, 25009, 25009},
										{23, -1, 25009, 62},
										{22, -1, -1, 63},
										{26, -1, -1, -1},
										{0, -1, 2, 16014},
										{3, 16014, 1, 16014},
										{1, 16012, 16014, 16012},
										{2, 5, 5, 16015},
										{7, 5, 1, 25011},
										{8, 5, 16015, 25010},
										{10, 25010, 25011, 25011},
										{23, -1, 25011, 72},
										{22, -1, -1, 73},
										{26, -1, -1, -1},
										{1, 16012, 5, 16012},
										{14, 4100, 16012, 16016},
										{15, -1, -1, 8},
										{16, -1, 4136, 28000},
										{17, -1, -1, 8},
										{0, -1, 4137, 16017},
										{0, 2, 16017, 16016},
										{2, 2, 2, 16019},
										{7, 2, 1, 25013},
										{8, 2, 16019, 25012},
										{10, 25012, 25013, 25013},
										{23, -1, 25013, 86},
										{22, -1, -1, 87},
										{26, -1, -1, -1},
										{0, -1, 2, 16020},
										{3, 16020, 1, 16020},
										{1, 16018, 16020, 16018},
										{2, 2, 2, 16021},
										{7, 2, 1, 25015},
										{8, 2, 16021, 25014},
										{10, 25014, 25015, 25015},
										{23, -1, 25015, 96},
										{22, -1, -1, 97},
										{26, -1, -1, -1},
										{1, 16018, 2, 16018},
										{14, 4100, 16018, 16022},
										{1, 6, 1, 16023},
										{0, 2, 16023, 16022},
										{2, 2, 2, 16025},
										{7, 2, 0, 25017},
										{8, 2, 16025, 25016},
										{10, 25016, 25017, 25017},
										{23, -1, 25017, 107},
										{22, -1, -1, 108},
										{26, -1, -1, -1},
										{1, 16024, 2, 16024},
										{14, 4000, 16024, 16026},
										{0, 1, 16026, 16027},
										{19, -1, -1, 16027},
										{2, 5, 5, 16029},
										{7, 5, 0, 25019},
										{8, 5, 16029, 25018},
										{10, 25018, 25019, 25019},
										{23, -1, 25019, 118},
										{22, -1, -1, 119},
										{26, -1, -1, -1},
										{1, 16028, 5, 16028},
										{14, 4000, 16028, 16030},
										{0, 1, 16030, 16031},
										{19, -1, -1, 16031},
										{2, 2, 2, 16033},
										{7, 2, 1, 25021},
										{8, 2, 16033, 25020},
										{10, 25020, 25021, 25021},
										{23, -1, 25021, 129},
										{22, -1, -1, 130},
										{26, -1, -1, -1},
										{0, -1, 2, 16034},
										{3, 16034, 1, 16034},
										{1, 16032, 16034, 16032},
										{2, 2, 2, 16035},
										{7, 2, 1, 25023},
										{8, 2, 16035, 25022},
										{10, 25022, 25023, 25023},
										{23, -1, 25023, 139},
										{22, -1, -1, 140},
										{26, -1, -1, -1},
										{1, 16032, 2, 16032},
										{14, 4100, 16032, 16036},
										{0, 1, 16036, 16037},
										{19, -1, -1, 16037},
										{2, 2, 2, 16039},
										{7, 2, 1, 25025},
										{8, 2, 16039, 25024},
										{10, 25024, 25025, 25025},
										{23, -1, 25025, 150},
										{22, -1, -1, 151},
										{26, -1, -1, -1},
										{0, -1, 2, 16040},
										{3, 16040, 1, 16040},
										{1, 16038, 16040, 16038},
										{2, 5, 5, 16041},
										{7, 5, 1, 25027},
										{8, 5, 16041, 25026},
										{10, 25026, 25027, 25027},
										{23, -1, 25027, 160},
										{22, -1, -1, 161},
										{26, -1, -1, -1},
										{1, 16038, 5, 16038},
										{14, 4100, 16038, 16042},
										{0, 1, 16042, 16043},
										{19, -1, -1, 16043},
										{2, 5, 5, 16045},
										{7, 5, 1, 25029},
										{8, 5, 16045, 25028},
										{10, 25028, 25029, 25029},
										{23, -1, 25029, 171},
										{22, -1, -1, 172},
										{26, -1, -1, -1},
										{0, -1, 5, 16046},
										{3, 16046, 1, 16046},
										{1, 16044, 16046, 16044},
										{2, 2, 2, 16047},
										{7, 2, 1, 25031},
										{8, 2, 16047, 25030},
										{10, 25030, 25031, 25031},
										{23, -1, 25031, 181},
										{22, -1, -1, 182},
										{26, -1, -1, -1},
										{1, 16044, 2, 16044},
										{14, 4100, 16044, 16048},
										{0, 1, 16048, 16049},
										{19, -1, -1, 16049},
										{2, 4, 4, 16051},
										{7, 4, 1, 25033},
										{8, 4, 16051, 25032},
										{10, 25032, 25033, 25033},
										{23, -1, 25033, 192},
										{22, -1, -1, 193},
										{26, -1, -1, -1},
										{0, -1, 4, 16052},
										{3, 16052, 1, 16052},
										{1, 16050, 16052, 16050},
										{2, 4, 4, 16053},
										{7, 4, 1, 25035},
										{8, 4, 16053, 25034},
										{10, 25034, 25035, 25035},
										{23, -1, 25035, 202},
										{22, -1, -1, 203},
										{26, -1, -1, -1},
										{1, 16050, 4, 16050},
										{14, 4100, 16050, 16054},
										{0, 1, 16054, 16055},
										{19, -1, -1, 16055},
										{2, 5, 5, 16057},
										{7, 5, 1, 25037},
										{8, 5, 16057, 25036},
										{10, 25036, 25037, 25037},
										{23, -1, 25037, 213},
										{22, -1, -1, 214},
										{26, -1, -1, -1},
										{0, -1, 5, 16058},
										{3, 16058, 1, 16058},
										{1, 16056, 16058, 16056},
										{2, 2, 2, 16059},
										{7, 2, 1, 25039},
										{8, 2, 16059, 25038},
										{10, 25038, 25039, 25039},
										{23, -1, 25039, 223},
										{22, -1, -1, 224},
										{26, -1, -1, -1},
										{1, 16056, 2, 16056},
										{14, 4100, 16056, 16060},
										{0, 1, 16060, 16061},
										{19, -1, -1, 16061},
										{2, 5, 5, 16063},
										{7, 5, 1, 25041},
										{8, 5, 16063, 25040},
										{10, 25040, 25041, 25041},
										{23, -1, 25041, 234},
										{22, -1, -1, 235},
										{26, -1, -1, -1},
										{0, -1, 5, 16064},
										{3, 16064, 1, 16064},
										{1, 16062, 16064, 16062},
										{2, 5, 5, 16065},
										{7, 5, 1, 25043},
										{8, 5, 16065, 25042},
										{10, 25042, 25043, 25043},
										{23, -1, 25043, 244},
										{22, -1, -1, 245},
										{26, -1, -1, -1},
										{1, 16062, 5, 16062},
										{14, 4100, 16062, 16066},
										{0, 1, 16066, 16067},
										{19, -1, -1, 16067},
										{21, -1, -1, -1},
										{2, 7, 7, 16069},
										{7, 7, 0, 25045},
										{8, 7, 16069, 25044},
										{10, 25044, 25045, 25045},
										{23, -1, 25045, 256},
										{22, -1, -1, 257},
										{26, -1, -1, -1},
										{1, 16068, 7, 16068},
										{14, 4000, 16068, 16070},
										{2, 2, 2, 16072},
										{7, 2, 1, 25047},
										{8, 2, 16072, 25046},
										{10, 25046, 25047, 25047},
										{23, -1, 25047, 265},
										{22, -1, -1, 266},
										{26, -1, -1, -1},
										{0, -1, 2, 16073},
										{3, 16073, 1, 16073},
										{1, 16071, 16073, 16071},
										{2, 2, 2, 16074},
										{7, 2, 1, 25049},
										{8, 2, 16074, 25048},
										{10, 25048, 25049, 25049},
										{23, -1, 25049, 275},
										{22, -1, -1, 276},
										{26, -1, -1, -1},
										{1, 16071, 2, 16071},
										{14, 4100, 16071, 16075},
										{0, 1, 16075, 16076},
										{0, 2, 16076, 16070},
										{2, 3, 3, 16078},
										{7, 3, 0, 25051},
										{8, 3, 16078, 25050},
										{10, 25050, 25051, 25051},
										{23, -1, 25051, 286},
										{22, -1, -1, 287},
										{26, -1, -1, -1},
										{1, 16077, 3, 16077},
										{14, 4000, 16077, 16079},
										{0, 2, 2, 16079},
										{2, 8, 8, 16081},
										{7, 8, 0, 25053},
										{8, 8, 16081, 25052},
										{10, 25052, 25053, 25053},
										{23, -1, 25053, 296},
										{22, -1, -1, 297},
										{26, -1, -1, -1},
										{1, 16080, 8, 16080},
										{14, 4000, 16080, 16082},
										{0, 2, 4, 16082},
										{2, 9, 9, 16084},
										{7, 9, 0, 25055},
										{8, 9, 16084, 25054},
										{10, 25054, 25055, 25055},
										{23, -1, 25055, 306},
										{22, -1, -1, 307},
										{26, -1, -1, -1},
										{1, 16083, 9, 16083},
										{14, 4000, 16083, 16085},
										{0, 2, 5, 16085},
										{19, -1, -1, 2000},
										{2, 9, 9, 16087},
										{7, 9, 0, 25057},
										{8, 9, 16087, 25056},
										{10, 25056, 25057, 25057},
										{23, -1, 25057, 317},
										{22, -1, -1, 318},
										{26, -1, -1, -1},
										{1, 16086, 9, 16086},
										{14, 4000, 16086, 16088},
										{0, 1, 16088, 16089},
										{2, 8, 8, 16091},
										{7, 8, 0, 25059},
										{8, 8, 16091, 25058},
										{10, 25058, 25059, 25059},
										{23, -1, 25059, 327},
										{22, -1, -1, 328},
										{26, -1, -1, -1},
										{1, 16090, 8, 16090},
										{14, 4000, 16090, 16092},
										{0, 1, 16092, 16093},
										{2, -1, 16093, 16094},
										{3, 16089, 16094, 16095},
										{19, -1, -1, 16095},
										{21, -1, -1, -1},
										{2, 2, 2, 16097},
										{7, 2, 1, 25061},
										{8, 2, 16097, 25060},
										{10, 25060, 25061, 25061},
										{23, -1, 25061, 341},
										{22, -1, -1, 342},
										{26, -1, -1, -1},
										{0, -1, 2, 16098},
										{3, 16098, 1, 16098},
										{1, 16096, 16098, 16096},
										{2, 2, 2, 16099},
										{7, 2, 1, 25063},
										{8, 2, 16099, 25062},
										{10, 25062, 25063, 25063},
										{23, -1, 25063, 351},
										{22, -1, -1, 352},
										{26, -1, -1, -1},
										{1, 16096, 2, 16096},
										{14, 4100, 16096, 16100},
										{0, 1, 16100, 16101},
										{2, 16101, 16101, 16103},
										{7, 16101, 0, 25065},
										{8, 16101, 16103, 25064},
										{10, 25064, 25065, 25065},
										{23, -1, 25065, 361},
										{22, -1, -1, 362},
										{26, -1, -1, -1},
										{1, 16102, 16101, 16102},
										{14, 4000, 16102, 16104},
										{2, 9, 9, 16106},
										{7, 9, 0, 25067},
										{8, 9, 16106, 25066},
										{10, 25066, 25067, 25067},
										{23, -1, 25067, 370},
										{22, -1, -1, 371},
										{26, -1, -1, -1},
										{1, 16105, 9, 16105},
										{14, 4000, 16105, 16107},
										{0, 1, 16107, 16108},
										{2, 8, 8, 16110},
										{7, 8, 0, 25069},
										{8, 8, 16110, 25068},
										{10, 25068, 25069, 25069},
										{23, -1, 25069, 380},
										{22, -1, -1, 381},
										{26, -1, -1, -1},
										{1, 16109, 8, 16109},
										{14, 4000, 16109, 16111},
										{0, 1, 16111, 16112},
										{3, 16108, 16112, 16113},
										{2, 2, 2, 16115},
										{7, 2, 1, 25071},
										{8, 2, 16115, 25070},
										{10, 25070, 25071, 25071},
										{23, -1, 25071, 391},
										{22, -1, -1, 392},
										{26, -1, -1, -1},
										{0, -1, 2, 16116},
										{3, 16116, 1, 16116},
										{1, 16114, 16116, 16114},
										{2, 16113, 16113, 16117},
										{7, 16113, 1, 25073},
										{8, 16113, 16117, 25072},
										{10, 25072, 25073, 25073},
										{23, -1, 25073, 401},
										{22, -1, -1, 402},
										{26, -1, -1, -1},
										{1, 16114, 16113, 16114},
										{14, 4100, 16114, 16118},
										{0, 1, 16118, 16119},
										{0, 2, 16119, 16104},
										{2, 10, 10, 16121},
										{7, 10, 0, 25075},
										{8, 10, 16121, 25074},
										{10, 25074, 25075, 25075},
										{23, -1, 25075, 412},
										{22, -1, -1, 413},
										{26, -1, -1, -1},
										{1, 16120, 10, 16120},
										{14, 4000, 16120, 16122},
										{0, 1, 16122, 16123},
										{19, -1, -1, 16123},
										{21, -1, -1, -1},
										{2, 7, 7, 16125},
										{7, 7, 0, 25077},
										{8, 7, 16125, 25076},
										{10, 25076, 25077, 25077},
										{23, -1, 25077, 424},
										{22, -1, -1, 425},
										{26, -1, -1, -1},
										{1, 16124, 7, 16124},
										{14, 4000, 16124, 16126},
										{0, 1, 16126, 16127},
										{19, -1, -1, 16127},
										{21, -1, -1, -1},
										{19, -1, -1, 2001},
										{21, -1, -1, -1},
										{2, 2, 2, 16129},
										{7, 2, 1, 25079},
										{8, 2, 16129, 25078},
										{10, 25078, 25079, 25079},
										{23, -1, 25079, 438},
										{22, -1, -1, 439},
										{26, -1, -1, -1},
										{0, -1, 2, 16130},
										{3, 16130, 1, 16130},
										{3, 16130, 1, 16130},
										{1, 16128, 16130, 16128},
										{2, 2, 2, 16131},
										{7, 2, 1, 25081},
										{8, 2, 16131, 25080},
										{10, 25080, 25081, 25081},
										{23, -1, 25081, 449},
										{22, -1, -1, 450},
										{26, -1, -1, -1},
										{0, -1, 2, 16132},
										{3, 16132, 1, 16132},
										{1, 16128, 16132, 16128},
										{2, 2, 2, 16133},
										{7, 2, 1, 25083},
										{8, 2, 16133, 25082},
										{10, 25082, 25083, 25083},
										{23, -1, 25083, 459},
										{22, -1, -1, 460},
										{26, -1, -1, -1},
										{1, 16128, 2, 16128},
										{14, 4109, 16128, 16134},
										{0, 2, 1, 16134},
										{2, 2, 2, 16136},
										{7, 2, 1, 25085},
										{8, 2, 16136, 25084},
										{10, 25084, 25085, 25085},
										{23, -1, 25085, 469},
										{22, -1, -1, 470},
										{26, -1, -1, -1},
										{0, -1, 2, 16137},
										{3, 16137, 1, 16137},
										{3, 16137, 1, 16137},
										{1, 16135, 16137, 16135},
										{2, 2, 2, 16138},
										{7, 2, 1, 25087},
										{8, 2, 16138, 25086},
										{10, 25086, 25087, 25087},
										{23, -1, 25087, 480},
										{22, -1, -1, 481},
										{26, -1, -1, -1},
										{0, -1, 2, 16139},
										{3, 16139, 1, 16139},
										{1, 16135, 16139, 16135},
										{2, 2, 2, 16140},
										{7, 2, 1, 25089},
										{8, 2, 16140, 25088},
										{10, 25088, 25089, 25089},
										{23, -1, 25089, 490},
										{22, -1, -1, 491},
										{26, -1, -1, -1},
										{1, 16135, 2, 16135},
										{14, 4109, 16135, 16141},
										{0, 1, 16141, 16142},
										{19, -1, -1, 16142},
										{2, 2, 2, 16144},
										{7, 2, 1, 25091},
										{8, 2, 16144, 25090},
										{10, 25090, 25091, 25091},
										{23, -1, 25091, 501},
										{22, -1, -1, 502},
										{26, -1, -1, -1},
										{0, -1, 2, 16145},
										{3, 16145, 1, 16145},
										{3, 16145, 1, 16145},
										{1, 16143, 16145, 16143},
										{2, 4, 4, 16146},
										{7, 4, 1, 25093},
										{8, 4, 16146, 25092},
										{10, 25092, 25093, 25093},
										{23, -1, 25093, 512},
										{22, -1, -1, 513},
										{26, -1, -1, -1},
										{0, -1, 4, 16147},
										{3, 16147, 1, 16147},
										{1, 16143, 16147, 16143},
										{2, 5, 5, 16148},
										{7, 5, 1, 25095},
										{8, 5, 16148, 25094},
										{10, 25094, 25095, 25095},
										{23, -1, 25095, 522},
										{22, -1, -1, 523},
										{26, -1, -1, -1},
										{1, 16143, 5, 16143},
										{14, 4109, 16143, 16149},
										{0, 1, 16149, 16150},
										{19, -1, -1, 16150},
										{2, 2, 2, 16152},
										{7, 2, 1, 25097},
										{8, 2, 16152, 25096},
										{10, 25096, 25097, 25097},
										{23, -1, 25097, 533},
										{22, -1, -1, 534},
										{26, -1, -1, -1},
										{0, -1, 2, 16153},
										{3, 16153, 1, 16153},
										{3, 16153, 1, 16153},
										{1, 16151, 16153, 16151},
										{2, 5, 5, 16154},
										{7, 5, 1, 25099},
										{8, 5, 16154, 25098},
										{10, 25098, 25099, 25099},
										{23, -1, 25099, 544},
										{22, -1, -1, 545},
										{26, -1, -1, -1},
										{0, -1, 5, 16155},
										{3, 16155, 1, 16155},
										{1, 16151, 16155, 16151},
										{2, 5, 5, 16156},
										{7, 5, 1, 25101},
										{8, 5, 16156, 25100},
										{10, 25100, 25101, 25101},
										{23, -1, 25101, 554},
										{22, -1, -1, 555},
										{26, -1, -1, -1},
										{1, 16151, 5, 16151},
										{14, 4109, 16151, 16157},
										{0, 1, 16157, 16158},
										{19, -1, -1, 16158},
										{2, 4, 4, 16160},
										{7, 4, 1, 25103},
										{8, 4, 16160, 25102},
										{10, 25102, 25103, 25103},
										{23, -1, 25103, 565},
										{22, -1, -1, 566},
										{26, -1, -1, -1},
										{0, -1, 4, 16161},
										{3, 16161, 1, 16161},
										{3, 16161, 1, 16161},
										{1, 16159, 16161, 16159},
										{2, 5, 5, 16162},
										{7, 5, 1, 25105},
										{8, 5, 16162, 25104},
										{10, 25104, 25105, 25105},
										{23, -1, 25105, 576},
										{22, -1, -1, 577},
										{26, -1, -1, -1},
										{0, -1, 5, 16163},
										{3, 16163, 1, 16163},
										{1, 16159, 16163, 16159},
										{2, 2, 2, 16164},
										{7, 2, 1, 25107},
										{8, 2, 16164, 25106},
										{10, 25106, 25107, 25107},
										{23, -1, 25107, 586},
										{22, -1, -1, 587},
										{26, -1, -1, -1},
										{1, 16159, 2, 16159},
										{14, 4109, 16159, 16165},
										{0, 1, 16165, 16166},
										{19, -1, -1, 16166},
										{2, 5, 5, 16168},
										{7, 5, 1, 25109},
										{8, 5, 16168, 25108},
										{10, 25108, 25109, 25109},
										{23, -1, 25109, 597},
										{22, -1, -1, 598},
										{26, -1, -1, -1},
										{0, -1, 5, 16169},
										{3, 16169, 1, 16169},
										{3, 16169, 1, 16169},
										{1, 16167, 16169, 16167},
										{2, 5, 5, 16170},
										{7, 5, 1, 25111},
										{8, 5, 16170, 25110},
										{10, 25110, 25111, 25111},
										{23, -1, 25111, 608},
										{22, -1, -1, 609},
										{26, -1, -1, -1},
										{0, -1, 5, 16171},
										{3, 16171, 1, 16171},
										{1, 16167, 16171, 16167},
										{2, 5, 5, 16172},
										{7, 5, 1, 25113},
										{8, 5, 16172, 25112},
										{10, 25112, 25113, 25113},
										{23, -1, 25113, 618},
										{22, -1, -1, 619},
										{26, -1, -1, -1},
										{1, 16167, 5, 16167},
										{14, 4109, 16167, 16173},
										{0, 1, 16173, 16174},
										{19, -1, -1, 16174},
										{21, -1, -1, -1},
										{25, -1, -1, -1},
										};
// QUADS //

// GLOBAL VARS //
int PROGRAM_START; // Quad index of the start of main()
bool RUNNING = false;
int IP; // Instruction Pointer
MemoryMap GLOBAL_MEM;
MemoryMap* LOCAL_MEM;
stack<MemoryMap> MEMORY_STACK;
// GLOBAL VARS //


// HELPER METHODS //
const map<string, bool> STOB_MAP = {
							{"true", 1},
							{"True", 1},
							{"false", 0},
							{"False", 0},
};

// Safe String to Int
int s_stoi(string s){
	try{
		return stoi(s);
	}catch(...){
			cout << ">> Error: Cannot resolve stoi(" << s << ")" << endl;
			exit(EXIT_FAILURE);
		}
}

// Safe String to Float
float s_stof(string s){
	try{
		return stof(s);
	}catch(...){
			cout << ">> Error: Cannot resolve stof(" << s << ")" << endl;
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
				cout << ">> Error: Cannot resolve stob(" << s << ")" << endl;
				exit(EXIT_FAILURE);
			}
	}
}

string mem_index_to_mem_sign(int index){
  if (index < MAX_CONSTANTS * VAR_TYPES){ // CONSTANTS
		string mem_sign = "0" + to_string(index / MAX_CONSTANTS) + "0";
		return mem_sign;
  }
  else if (index < MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES){ // GLOBALS
		string mem_sign = "1" + to_string(((index - MAX_CONSTANTS * VAR_TYPES) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - MAX_CONSTANTS * VAR_TYPES) >= MAX_SYMBOLS * VAR_TYPES) ? "1" : "0";
		return mem_sign;
  }
  else{ // LOCALS
		string mem_sign = "2" + to_string(((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES)) / MAX_SYMBOLS) % VAR_TYPES);
		mem_sign += ((index - (MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES) >= MAX_SYMBOLS * VAR_TYPES)) ? "1" : "0";
		return mem_sign;
  }

  // ERROR! Nothing was written
  cout << ">> Error: could not locate "  << index << " in memory" << endl;
  exit(EXIT_FAILURE);
}

int mem_sign_to_index_displacement(string mem_sign){
	int index_displacement = 0;
	int mem_class = mem_sign[0] - '0', var_type = mem_sign[1] - '0', is_temp = mem_sign[2] - '0';

	switch (mem_class) {
		case 1: // GLOBAL
		{
			index_displacement += MAX_CONSTANTS * VAR_TYPES;
		} break;
		case 2: // LOCAL
		{
			index_displacement += MAX_CONSTANTS * VAR_TYPES + (MAX_SYMBOLS + MAX_TMP_SYMBOLS) * VAR_TYPES;
		} break;
	}

	int type_displacement_mult = (mem_class) ? MAX_SYMBOLS : MAX_CONSTANTS;

	index_displacement += var_type * type_displacement_mult;
	index_displacement += (is_temp) ? MAX_SYMBOLS * VAR_TYPES : 0;

	return index_displacement;
}

// HELPER METHODS //

Value read_from_memory(int index){
  string mem_sign = mem_index_to_mem_sign(index);
  if(mem_sign[0] == '2'){
    if (!LOCAL_MEM->active){
      cout << ">> Error: No local context to read "  << index << " from memory" << endl;
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
    default:
    {
      // ERROR! Nothing was read
      cout << ">> Error: could not read "  << index << " from memory" << endl;
      exit(EXIT_FAILURE);
    }
  }

  return v;
}

int write_to_memory(int index, string value){
  string mem_sign = mem_index_to_mem_sign(index);

	if(mem_sign[0] == '2'){
    if (!LOCAL_MEM->active){
      cout << ">> Error: No local context to write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE); // ERROR! No context to write local variable to
    }
  }

	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
    case 0:
      {
        GLOBAL_MEM.const_mem.ints[index] = s_stoi(value);
      }
      break;
    case 10:
      {
        GLOBAL_MEM.const_mem.floats[index - index_displacement] = s_stof(value);
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
        GLOBAL_MEM.local_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 110:
      {
        GLOBAL_MEM.local_mem.floats[index - index_displacement] = s_stof(value);
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
    case 101:
      {
        GLOBAL_MEM.temp_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 111:
      {
        GLOBAL_MEM.temp_mem.floats[index - index_displacement] = s_stof(value);
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
    case 200:
      {
      	LOCAL_MEM->local_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 210:
      {
      	LOCAL_MEM->local_mem.floats[index - index_displacement] = s_stof(value);
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
    case 201:
      {
      	LOCAL_MEM->temp_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 211:
      {
      	LOCAL_MEM->temp_mem.floats[index - index_displacement] = s_stof(value);
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
    default:
    {
      // ERROR! Nothing was written
      return 1;
    }
  }

  return 0; // Success!
}

void write_to_param(int index, string value){
	string mem_sign = mem_index_to_mem_sign(index);
  if(mem_sign[0] == '2'){
    if (!MEMORY_STACK.size()){
      cout << ">> Error: No local context to write "  << value << " to " << index << endl;
      exit(EXIT_FAILURE); // ERROR! No context to write local variable to
    }
  }

	int int_mem_sign = stoi(mem_sign);
	int index_displacement = mem_sign_to_index_displacement(mem_sign);

  switch (int_mem_sign) {
		case 200:
      {
        MEMORY_STACK.top().local_mem.ints[index - index_displacement] = s_stoi(value);
      }
      break;
    case 210:
      {
        MEMORY_STACK.top().local_mem.floats[index - index_displacement] = s_stof(value);
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
	      cout << ">> Error: could not write "  << value << " to param at " << index << endl;
	      exit(EXIT_FAILURE);
			}
			break;
	}
}

void setup(){

	// WRITE CONSTANTS TO MEMORY //

	for (auto const& pair : CONSTANTS){
		if (write_to_memory(pair.first, pair.second)){
      cout << ">> Error writting " << pair.second << " to " << pair.first << endl;
      exit(EXIT_FAILURE);
    }
  }

	// SET INITIAL VALUES FOR GLOBAL VARS //

	RUNNING = true; // This will get the instruction pointer movin through the quads
  IP = 0; // Start execution at the first QUAD
	LOCAL_MEM = new MemoryMap(); // Initialize LOCAL_MEM without parameters so that LOCAL_MEM->active is set to false
}

void run(){
  while(RUNNING){
    int op = QUADS[IP][0];

		if (!op){
			// =

			int  is_ptr = QUADS[IP][1];
			int result_dir;
			Value value;

			if (is_ptr == 1 || is_ptr == 3) {
				value = read_from_memory(read_from_memory(QUADS[IP][2]).i);
			}else{
				value = read_from_memory(QUADS[IP][2]);
			}

			if (is_ptr == 2 || is_ptr == 3){
				result_dir = read_from_memory(QUADS[IP][3]).i;
			}else{
				result_dir = QUADS[IP][3];
			}

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

			case 14:			// ACCESS
        {
					int result_dir = QUADS[IP][3];

					Value arr_dir = QUADS[IP][1];
					Value access_value = read_from_memory(QUADS[IP][2]);

					Value result = arr_dir + access_value;

					write_to_memory(result_dir, result.to_str());
					IP++;
        }
        break;

			case 15:		// ERA
				{
					int func_start_addr = QUADS[IP][3];
					if (MEMORY_STACK.size() > MEMORY_STACK_LIMIT){
						// Too many functions on the stack!
						cout << ">> Error: Memory Stack Limit reached (infinite recursion?). Terminating..." << endl;
						exit(EXIT_FAILURE);
					}

					MEMORY_STACK.push(MemoryMap(MEMORY_MAP_SIGN.at(func_start_addr).at(0), MEMORY_MAP_SIGN.at(func_start_addr).at(1)));
					IP++;
				}
				break;

			case 16:		// PARAM
				{

					Value param_value = read_from_memory(QUADS[IP][2]);
					int param_addr = QUADS[IP][3];

					write_to_param(param_addr, param_value.to_str());
					IP++;
				}
				break;

			case 17:		// GOSUB
				{
					int func_start_addr = QUADS[IP][3];
					LOCAL_MEM = &(MEMORY_STACK.top());
					LOCAL_MEM->set_return_addr(IP + 1);
					IP = func_start_addr;
				}
				break;

			case 18:		// READ
				{

					int result_dir = QUADS[IP][3];

					string user_input;
					cin >> user_input;

					write_to_memory(result_dir, user_input);

					IP++;
				}
				break;

			case 19:			// PRNTBFFR
				{
					Value printable = read_from_memory(QUADS[IP][3]);
					if (LOCAL_MEM->active) LOCAL_MEM->add_to_print_buffer(printable.to_str());
					else GLOBAL_MEM.add_to_print_buffer(printable.to_str());
					IP++;
				}
				break;

      case 20:			// PRNT
        {
          string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable;
          IP++;
        }
        break;

			case 21:			// PRNTLN
        {
					string printable = (LOCAL_MEM->active) ? LOCAL_MEM->flush_print_buffer() : GLOBAL_MEM.flush_print_buffer();
          cout << printable << endl;
          IP++;
        }
        break;

      case 22:			// GOTO
        {
          int to_addr = QUADS[IP][3];
          IP = to_addr;
        }
        break;

			case 23:			// GOTOF
				{
					int to_addr = QUADS[IP][3];
					Value condition = read_from_memory(QUADS[IP][2]);
					Value false_value = Value(false);
					Value result = condition == false_value;
					if(result.b) IP = to_addr;
					else IP++;
				}
				break;

			case 24:			// ENDFNC
				{
					int return_addr = LOCAL_MEM->return_addr;
					MEMORY_STACK.pop();
					LOCAL_MEM = (MEMORY_STACK.size()) ? &(MEMORY_STACK.top()) : new MemoryMap();
					IP = return_addr;
				}
				break;

      case 25:			// END
        {
          RUNNING = false;
        }
        break;

			case 26:			// ERR_OOB
        {
					// If this point is reached, an array index out of bounds error has ocurred
					cout << ">> Error: array index out of bounds!" << endl;
					exit(EXIT_FAILURE);
        }
        break;

      default:
        {
        cout << ">> Error: Unknown Op: " << op << endl;
        exit(EXIT_FAILURE);
        }
    }
  }
}

int main () {

  // Memory signature with highest value is always pointing to the start of the main() method (no function can syntactically come after the main)
  PROGRAM_START = MEMORY_MAP_SIGN.rbegin()->first;

  // Generates global memory map
  GLOBAL_MEM = MemoryMap(MEMORY_MAP_SIGN.at(PROGRAM_START).at(0), MEMORY_MAP_SIGN.at(PROGRAM_START).at(1), MEMORY_MAP_SIGN.at(PROGRAM_START).at(2));

  // Setup virtual machine to run the program
  setup();

  // Run program
  run();

  return 0;
}
