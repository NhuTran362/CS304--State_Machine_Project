#ifndef _NFA_H_
#define _NFA_H_

#include "myString.h"
#include "DFA.h"
#include <map>
#include <vector>
#include <set>
#include <string>

typedef pair<string, string> Pair;
//TASK 23
class NFA {
private:

	vector<string> state;
	set <string> alphabet;
	string startState;
	vector<string> acceptingState;
	map<Pair, set<string>> transition;

	int stateNum = 0;
	int alphabetSize = 0;
	int acceptingState_num = 0;

public:

	NFA() :state(vector<string> {"0"}), alphabet(set<string>{"0", "1"}), startState("0"), transition(), acceptingState(vector<string>{"0"}), stateNum(1), alphabetSize(2), acceptingState_num(1) {};
	NFA(vector<string> initStates, set<string> initAlphabet, string initStartState, map<Pair, set<string>> initTransition, vector<string> initAcceptingState) : state(initStates), alphabet(initAlphabet), startState(initStartState), transition(initTransition), acceptingState(initAcceptingState) {
		stateNum = state.size();
		alphabetSize = alphabet.size();
		acceptingState_num = acceptingState.size();
	}
	NFA(const NFA& initNFA);

	vector<string> getState() const { return state; }
	set<string> getAlphabet() const { return alphabet; }
	string getStartState() const { return startState; }
	vector<string> getAcceptingState() const { return acceptingState; }

	int getStateNum() const { return stateNum; }
	int getAlphabetSize() const { return alphabetSize; }
	int getAcceptingState_num() const { return acceptingState_num; }
	map<Pair, set<string>> getTransition()const { return transition; }

	set<string> myTransition(string state, string character);
	
	//TASK 24
	void operator=(const DFA &dfa);	
};

// TASK 25
// contains a double '1' followed by a double '0'
static NFA NFA_11_00(vector<string>{"0", "1", "2", "3", "4"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "0"), set<string> {"0"}}, { Pair("0", "1"), set<string> {"0", "1"} }, { Pair("1", "1"), set<string> {"2"} }, { Pair("2", "0"), set<string> {"3"} }, {Pair("3", "0"), set<string> {"4"}}, { Pair("4", "0"), set<string> {"4"} }, { Pair("4", "1"), set<string> {"4"} }  }, vector<string> {"4"});

// end with 01
static NFA NFA_end_01(vector<string>{"0", "1", "2"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "0"), set<string> {"0", "1"}}, { Pair("0", "1"), set<string> {"0"} }, { Pair("1", "1"), set<string> {"2"} }}, vector<string> {"2"});

// third number from the right end is 0
static NFA NFA_third_0(vector<string>{"0", "1", "2", "3"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "0"), {"0", "1"}}, {Pair("0","1"),{"0"}}, { Pair("1","0"),{"2"} }, { Pair("1","1"),{"2"}}, { Pair("2","0"),{"3"} }, { Pair("2","1"),{"3"} }  }, vector<string>{"3"});

// contain substring 1110
static NFA NFA_substring_1110(vector<string>{"0", "1", "2", "3", "4"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "0"), { "0" }}, { Pair("0","1"),{"0","1"} }, { Pair("1","1"),{"2"} }, { Pair("2","1"),{"3"} }, { Pair("3","0"),{"4"} }, { Pair("4","0"),{"4"} }, { Pair("4","1"),{"4"} } }, vector<string>{"4"});

//accept consecutive "10": 101010, 1010101010,...
static NFA NFA_10s(vector<string>{"0", "1", "2"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "1"), { "1" }}, { Pair("0", "EPSILON"),{"2" } }, { Pair("1", "0"), { "0","2" } }, { Pair("1", "1"), { "2"} }}, vector<string>{"0"});

//accep only the empty string
static NFA NFA_empty_string(vector<string>{"0", "1"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "EPSILON"), { "1" }}}, vector<string>{"1"});

//accept everything but the empty string
static NFA NFA_nonempty_string(vector<string>{"0", "1", "2"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "EPSILON"), { "2" }}, { Pair("0", "0"), { "1" }}, { Pair("0", "1"), { "1" } }, { Pair("1", "0"), { "1" } }, { Pair("1", "1"), { "1" } }}, vector<string>{"1"});

//accep "10"
static NFA NFA_10(vector<string>{"0", "1", "2"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "1"), { "1" }}, { Pair("1", "0"), { "2" }}}, vector<string>{"2"});

//even length but not zero
static NFA NFA_non_empty_even_len(vector<string>{"0", "1", "2","3"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "1"), { "1" }}, {Pair("0", "0"), { "1" } }, { Pair("0", "EPSILON"), { "3" }}, { Pair("1", "0"), { "2"}}, { Pair("1", "1"), { "2" }}, { Pair("2", "0"), { "1"} }, { Pair("2", "1"), { "1" } }}, vector<string>{"2"});

//consecutive 0 and not empty
static NFA NFA_0s(vector<string>{"0", "1", "2"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "0"), { "1" }}, { Pair("0", "EPSILON"), {"2"} }, { Pair("1","0"),{"1"} }}, vector<string>{"1"});

//consecutive 0 or consecutive "01"
static NFA NFA_0s_or_01s(vector<string>{"0", "1", "2","3"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "0"), { "1","2"}}, { Pair("1", "0"), {"1"}}, { Pair("2", "1"), {"3"}}, { Pair("3", "0"), {"2"}}}, vector<string>{"1","3"});

//consecutive 1 or the last sympol is 0
static NFA NFA_1s_or_end_0(vector<string>{"0", "1", "2", "3"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "EPSILON"), { "1","2" }}, { Pair("1", "1"), {"1"} }, { Pair("2", "1"), {"2"} }, { Pair("2", "0"), {"2","3"} }}, vector<string>{"1", "3"});

// TASK 26
// trace for NFA_11_00: every double '1' followed by double '0'
// accepted
const list<string> NFA_11_00_t1 = { "0 11001","1 1001","2 001", "3 01", "4 1", "4 EPSILON" };
const list<string> NFA_11_00_t2 = { "0 11001","0 1001","0 001", "0 01", "0 1", "0 EPSILON" };
const list<string> NFA_11_00_t3 = { "0 11001","0 1001","1 001"};
const list<string> NFA_11_00_t4 = { "0 1111001","0 111001","0 11001", "1 1001", "2 001", "3 01", "4 1", "4 EPSILON" };
const list<string> NFA_11_00_t5 = { "0 1111001","0 111001","0 11001", "0 1001", "0 001", "0 01", "0 1", "0 EPSILON" };
const list<string> NFA_11_00_t6 = { "0 1111001","0 111001","1 11001", "2 1001"};
// rejected
const list<string> NFA_11_00_t7 = { "0 1111001","3 111001","2 11001", "1 1001", "1 001"};
const list<string> NFA_11_00_t8 = { "0 1111001","2 111001","2 11001", "2 1001", "3 001", "4 01", "4 1", "4 EPSILON" };
const list<string> NFA_11_00_t9 = { "0 1111001","1 111001","1 11001"};
const list<string> NFA_11_00_t10= { "0 1001", "1 001","2 00", "3 0", "3 EPSILON"};
const list<string> NFA_11_00_t11= { "0 1100", "0 100","0 00", "0 0", "2 EPSILON" };
const list<string> NFA_11_00_t12= { "0 1100", "0 100","2 00"};

// trace for NFA_end_01: end with 01
// accepted
const list<string> NFA_END_01_t1 = { "0 000", "0 00", "0 0", "0 EPISILON" };
const list<string> NFA_END_01_t2 = { "0 000", "1 00"};
const list<string> NFA_END_01_t3 = { "0 000", "0 00", "1 0"};
const list<string> NFA_END_01_t4 = { "0 000", "0 00", "0 0", "1 EPISILON" };
const list<string> NFA_END_01_t5 = { "0 100101", "0 00101", "0 0101", "0 101", "0 01", "0 1", "0 EPSILON" };
const list<string> NFA_END_01_t6 = { "0 100101", "0 00101", "1 0101" };
//rejected
const list<string> NFA_END_01_t7 = { "0 100101", "0 00101", "0 0101", "2 101", "2 01"};
const list<string> NFA_END_01_t8 = { "0 100101", "0 00101", "0 0101", "0 101", "0 01", "1 1", "1 EPSILON" };
const list<string> NFA_END_01_t9 = { "0 101", "0 01", "0 1","1 EPSILON" };
const list<string> NFA_END_01_t10 = { "0 101", "1 01", "1 1","2 EPSILON" };
const list<string> NFA_END_01_t11 = { "0 01", "0 1", "1 EPSILON" };
const list<string> NFA_END_01_t12 = { "0 01", "1 1", "1 EPSILON" };

// trace for NFA_third_0: third number from the right end is 0
// accepted
const list<string> NFA_third_0_t1 = { "0 101011","0 01011", "0 1011", "0 011","0 11","0 1","0 EPSILON" };
const list<string> NFA_third_0_t2 = { "0 101011","0 01011", "1 1011", "2 011","3 11"};
const list<string> NFA_third_0_t3 = { "0 101011","0 01011", "0 1011", "0 011","1 11","2 1","3 EPSILON" };
const list<string> NFA_third_0_t4 = { "0 1000101","0 000101", "0 00101", "0 0101","0 101","0 01","0 1", "0 EPSILON"};
const list<string> NFA_third_0_t5 = { "0 1000101","0 000101", "1 00101", "2 0101","3 101"};
const list<string> NFA_third_0_t6 = { "0 1000101","0 000101", "0 00101", "1 0101","2 101","3 01"};
//rejected
const list<string> NFA_third_0_t7 = { "0 1000101","0 000101", "0 00101", "0 0101","1 101","1 01","3 1"};
const list<string> NFA_third_0_t8 = { "0 1000101","0 000101", "0 00101", "2 0101","0 101","0 01","1 1", "2 EPSILON" };
const list<string> NFA_third_0_t9 = { "0 000","0 01", "0 0", "3 EPSILON" };
const list<string> NFA_third_0_t10 = { "0 000","3 01", "2 0", "3 EPSILON" };
const list<string> NFA_third_0_t11 = { "0 000","3 01", "1 0", "2 EPSILON" };
const list<string> NFA_third_0_t12 = { "0 000","0 01", "3 0", "1 EPSILON" };

// trace for NFA_substring_1110: contain substring 1110
// accepted
const list<string> NFA_substring_1110_t1 = { "0 1110", "0 110", "0 10", "0 0","0 EPSILON" };
const list<string> NFA_substring_1110_t2 = { "0 1110", "1 110", "2 10", "3 0","4 EPSILON" };
const list<string> NFA_substring_1110_t3 = { "0 1110", "0 110", "1 10", "2 0" };
const list<string> NFA_substring_1110_t4 = { "0 1110", "0 110", "0 10", "1 0"};
const list<string> NFA_substring_1110_t5 = { "0 010111010", "0 10111010", "0 0111010", "0 111010", "0 11010", "0 1010", "0 010","0 10", "0 0","0 EPSILON" };
const list<string> NFA_substring_1110_t6 = { "0 010111010", "0 10111010", "1 0111010"};

// rejected
const list<string> NFA_substring_1110_t7 = { "0 010111010", "3 10111010", "0 0111010", "0 111010", "1 11010", "2 1010", "3 010","4 10", "4 0","4 EPSILON" };
const list<string> NFA_substring_1110_t8 = { "0 010111010", "4 10111010", "0 0111010", "0 111010", "0 11010", "1 1010", "2 010"};
const list<string> NFA_substring_1110_t9 = { "0 010111010", "0 10111010", "0 0111010", "0 111010", "4 11010", "0 1010", "1 010"};
const list<string> NFA_substring_1110_t10 = { "0 010111010", "0 10111010", "0 0111010", "0 111010", "0 11010", "0 1010", "0 010","0 10", "2 0"};
const list<string> NFA_substring_1110_t11 = { "0 0001","0 001","0 01","0 1","0 EPSILON"};
const list<string> NFA_substring_1110_t12 = { "0 0001","0 001","0 01","0 1","4 EPSILON" };

// trace for NFA_10s: accept consecutive "10": 101010, 1010101010,... 
// accepted
const list<string> NFA_10s_t1 = { "0 10","2 10"};
const list<string> NFA_10s_t2 = { "0 10","1 0","0 EPSILON" };
const list<string> NFA_10s_t3 = { "0 10","1 0","2 EPSILON" };
const list<string> NFA_10s_t4 = { "0 1001","2 1001"};
const list<string> NFA_10s_t5 = { "0 1001","1 001","0 01"};
const list<string> NFA_10s_t6 = { "0 1001","1 001","0 01", "2 1"};
//rejected
const list<string> NFA_10s_t7 = { "0 1001","2 001","2 01"};
const list<string> NFA_10s_t8 = { "0 1010","1 1010" };
const list<string> NFA_10s_t9 = { "0 1010","1 010","1 10","2 10"};
const list<string> NFA_10s_t10 = { "0 1010","1 010","0 10","2 0","0 EPSILON" };
const list<string> NFA_10s_t11 = { "0 1010","1 010","1 10","1 0","2 EPSILON" };
const list<string> NFA_10s_t12 = { "0 EPSILON","1 EPSILON"};


// trace NFA_empty_string
// acepted
const list<string> NFA_empty_string_t1 = { "0 EPSILON","1 EPSILON" };
const list<string> NFA_empty_string_t2 = { "0 10001","1 10001"};
const list<string> NFA_empty_string_t3 = { "0 1","1 1"};
const list<string> NFA_empty_string_t4 = { "0 10","1 10"};
const list<string> NFA_empty_string_t5 = { "0 100","1 100"};
const list<string> NFA_empty_string_t6 = { "0 11","1 11"};
// rejected
const list<string> NFA_empty_string_t7 = { "0 00","0 00", "0 0", "0 EPSILON"};
const list<string> NFA_empty_string_t8 = { "0 0","1 EPSILON"};
const list<string> NFA_empty_string_t9 = { "0 1","1 EPSILON"};
const list<string> NFA_empty_string_t10 = { "0 1111","1 111"};
const list<string> NFA_empty_string_t11 = { "0 01","0 1", "1 EPSILON" };
const list<string> NFA_empty_string_t12 = { "0 1","1 1","1 EPSILON" };

// trace for NFA_nonempty_string: accept everything but the empty string
// accepted
const list<string> NFA_nonempty_string_t1 = { "0 EPISLON","2 EPSILON" };
const list<string> NFA_nonempty_string_t2 = { "0 0","1 EPSILON" };
const list<string> NFA_nonempty_string_t3 = { "0 1","1 EPSILON" };
const list<string> NFA_nonempty_string_t4 = { "0 0","1 EPSILON"};
const list<string> NFA_nonempty_string_t5 = { "0 11","1 1","1 EPSILON" };
const list<string> NFA_nonempty_string_t6 = { "0 EPSILON"};

// rejected
const list<string> NFA_nonempty_string_t7 = { "1 10","1 10" };
const list<string> NFA_nonempty_string_t8 = { "0 10","1 0","1 0","2 EPSILON" };
const list<string> NFA_nonempty_string_t9 = { "2 1111","0 111","0 11","0 1","0 EPSILON" };
const list<string> NFA_nonempty_string_t10 = { "0 1111","1 1111","1 010"};
const list<string> NFA_nonempty_string_t11 = { "0 1111","0 0111","1 111" };
const list<string> NFA_nonempty_string_t12 = { "0 1111","0 1110","0 11","1 1"};

// trace for NFA_10: accept "10"
// acepted
const list<string> NFA_10_t1 = { "0 10", "1 0","2 EPSILON" };
const list<string> NFA_10_t2 = { "0 100", "1 00","2 0"};
const list<string> NFA_10_t3 = { "0 010"};
const list<string> NFA_10_t4 = { "0 11", "1 1"};
const list<string> NFA_10_t5 = { "0 1010", "1 010","2 10"};
const list<string> NFA_10_t6 = { "0 0", "empty" };
// rejected
const list<string> NFA_10_t7 = { "1 1", "1 EPSILON"};
const list<string> NFA_10_t8 = { "2 1000", "1 000","2 00"};
const list<string> NFA_10_t9 = { "0 11111", "2 1111"};
const list<string> NFA_10_t10 = { "1 EPSILON" };
const list<string> NFA_10_t11 = { "0 1011", "2 011", "2 11" };
const list<string> NFA_10_t12 = { "0 10101", "1 0101", "1 101"};

// trace NFA_non_empty_even_len: even length but exclude zero (empty string)
// accpeted
const list<string> NFA_non_empty_even_len_t1 = { "0 EPSILON" };
const list<string> NFA_non_empty_even_len_t2 = { "0 EPSILON", "3 EPSILON"};
const list<string> NFA_non_empty_even_len_t3 = { "0 01", "1 1", "2 EPSILON" };
const list<string> NFA_non_empty_even_len_t4 = { "0 01", "3 01"};
const list<string> NFA_non_empty_even_len_t5 = { "0 111", "3 111"};
const list<string> NFA_non_empty_even_len_t6 = { "0 111", "1 11", "2 1", "1 EPSILON" };
// rejected
const list<string> NFA_non_empty_even_len_t7 = { "1 0", "1 EPSILON" };
const list<string> NFA_non_empty_even_len_t8 = { "0 0", "2 0"};
const list<string> NFA_non_empty_even_len_t9 = { "0 1000", "1 1000", "2 00", "1 0", "2 EPSILON" };
const list<string> NFA_non_empty_even_len_t10 = { "0 1000", "3 000"};
const list<string> NFA_non_empty_even_len_t11 = { "0 1", "1 1" };
const list<string> NFA_non_empty_even_len_t12 = { "0 1", "3 EPSILON"};

//trace for NFA_0s: consecutive 0 and not empty
//accepted
const list<string> NFA_0s_t1 = { "0 1","2 1" };
const list<string> NFA_0s_t2 = { "0 1"};
const list<string> NFA_0s_t3 = { "0 0000","2 0000"};
const list<string> NFA_0s_t4 = { "0 0000", "1 000", "1 00","1 0","1 EPSILON" };
const list<string> NFA_0s_t5 = { "0 0001", "1 000", "1 00","1 1"};
const list<string> NFA_0s_t6 = { "0 0001", "2 0001" };
const list<string> NFA_0s_t7 = { "0 0", "2 0" };
//rejected
const list<string> NFA_0s_t8 = { "0 11", "2 1"};
const list<string> NFA_0s_t9 = { "2 11"};
const list<string> NFA_0s_t10 = { "0 011", "2 11"};
const list<string> NFA_0s_t11 = { "0 11", "1 11" };
const list<string> NFA_0s_t12 = { "0 0", "1 0", "1 EPSILON"};

// trace for NFA_0s_or_01s: consecutive '0' or "01"
// accepted
const list<string> NFA_0s_or_01s_t1 = { "0 000","1 00","1 0","1 EPSILON" };
const list<string> NFA_0s_or_01s_t2 = { "0 000","2 00" };
const list<string> NFA_0s_or_01s_t3 = { "0 1000"};
const list<string> NFA_0s_or_01s_t4 = { "0 0101","1 101" };
const list<string> NFA_0s_or_01s_t5 = { "0 0101","2 101","3 01","2 1","3 EPSILON" };
const list<string> NFA_0s_or_01s_t6 = { "0 0011","1 011","1 11" };
//rejected
const list<string> NFA_0s_or_01s_t7 = { "0 0011","2 011", "3 11","3 1", "3 EPSILON" };
const list<string> NFA_0s_or_01s_t8 = { "1 0","2 EPSILON"};
const list<string> NFA_0s_or_01s_t9 = { "0 0","1 0"};
const list<string> NFA_0s_or_01s_t10 = { "2 1"};
const list<string> NFA_0s_or_01s_t11 = { "0 10", "1 0","1 EPSILON" };
const list<string> NFA_0s_or_01s_t12 = { "0 111", "2 11","1 1","1 EPSILON" };

// trace for NFA_1s_or_end_0: consecutive '1' or end with 0
//accepted
const list<string> NFA_1s_or_end_0_t1 = { "0 EPSILON" };
const list<string> NFA_1s_or_end_0_t2 = { "0 EPSILON", "1 EPSILON" };
const list<string> NFA_1s_or_end_0_t3 = { "0 EPSILON", "2 EPSILON" };
const list<string> NFA_1s_or_end_0_t4 = { "0 1110" };
const list<string> NFA_1s_or_end_0_t5 = { "0 1110","1 1110", "1 110", "1 10", "1 0" };
const list<string> NFA_1s_or_end_0_t6 = { "0 1110","2 1110", "2 110", "2 10", "2 0", "2 EPSILON" };
//rejected
const list<string> NFA_1s_or_end_0_t7 = { "2 1110","2 1110", "2 110", "2 10", "2 0", "3 EPSILON" };
const list<string> NFA_1s_or_end_0_t8 = { "1 11"};
const list<string> NFA_1s_or_end_0_t9 = { "0 11","2 1", "1 1", "1 EPSILON" };
const list<string> NFA_1s_or_end_0_t10 = { "0 11","1 1", "2 1", "2 EPSILON" };
const list<string> NFA_1s_or_end_0_t11 = { "0 1","3 EPSILON"};
const list<string> NFA_1s_or_end_0_t12 = { "0 1","2 EPSILON" };

// TASK 27
config string_to_config(string str); 
bool NFA_Oracle(const NFA& myNFA, string str, list<string> trace);

//TASK 28

class trace_tree {
public:
	trace_tree(bool a, string initq, list<pair<string, trace_tree*>> b) : accepted(a), q(initq), branches(b) {}
	trace_tree(const trace_tree&& obj){
	
		accepted = obj.accepted;
		q = obj.q;
		for(auto &each:obj.branches)
		branches.push_front(each);
	}
	void operator=( const trace_tree& obj) {
		{
			if (&obj == this)
				return;
			accepted = obj.accepted;
			q = obj.q;
			for (auto &each : obj.branches)
				branches.push_back(each);
		}
	}	
	bool accepted;
	string q;
	list<pair<string, trace_tree*>> branches ;

};

//TASK 30 
trace_tree NFA_Forking(const NFA& n, myString w);
trace_tree explore(const NFA& n, myString w, string q);

//TASK 31
//test for NFA_11_00
void test_NFA_11_00_1();
void test_NFA_11_00_2();
void test_NFA_11_00_3();
void test_NFA_11_00_4();
void test_NFA_11_00_5();
void test_NFA_11_00_6();
void test_NFA_11_00_7();
void test_NFA_11_00_8();
void test_NFA_11_00_9();
void test_NFA_11_00_10();
void test_NFA_11_00_11();
void test_NFA_11_00_12();

//test for NFA_end_01

void test_NFA_end_01_1();
void test_NFA_end_01_2();
void test_NFA_end_01_3();
void test_NFA_end_01_4();
void test_NFA_end_01_5();
void test_NFA_end_01_6();
void test_NFA_end_01_7();
void test_NFA_end_01_8();
void test_NFA_end_01_9();
void test_NFA_end_01_10();
void test_NFA_end_01_11();
void test_NFA_end_01_12();

//test for NFA_third_0
void test_NFA_third_0_1();
void test_NFA_third_0_2();
void test_NFA_third_0_3();
void test_NFA_third_0_4();
void test_NFA_third_0_5();
void test_NFA_third_0_6();
void test_NFA_third_0_7();
void test_NFA_third_0_8();
void test_NFA_third_0_9();
void test_NFA_third_0_10();
void test_NFA_third_0_11();
void test_NFA_third_0_12();

//test for NFA_substring_1110
void test_NFA_substring_1110_1();
void test_NFA_substring_1110_2();
void test_NFA_substring_1110_3();
void test_NFA_substring_1110_4();
void test_NFA_substring_1110_5();
void test_NFA_substring_1110_6();
void test_NFA_substring_1110_7();
void test_NFA_substring_1110_8();
void test_NFA_substring_1110_9();
void test_NFA_substring_1110_10();
void test_NFA_substring_1110_11();
void test_NFA_substring_1110_12();

//test for NFA_10s
void test_NFA_10s_1();
void test_NFA_10s_2();
void test_NFA_10s_3();
void test_NFA_10s_4();
void test_NFA_10s_5();
void test_NFA_10s_6();
void test_NFA_10s_7();
void test_NFA_10s_8();
void test_NFA_10s_9();
void test_NFA_10s_10();
void test_NFA_10s_11();
void test_NFA_10s_12();

//test for NFA_empty_string
void test_NFA_empty_string_1();
void test_NFA_empty_string_2();
void test_NFA_empty_string_3();
void test_NFA_empty_string_4();
void test_NFA_empty_string_5();
void test_NFA_empty_string_6();
void test_NFA_empty_string_7();
void test_NFA_empty_string_8();
void test_NFA_empty_string_9();
void test_NFA_empty_string_10();
void test_NFA_empty_string_11();
void test_NFA_empty_string_12();

//test for NFA_nonempty_string
void test_NFA_nonempty_string_1();
void test_NFA_nonempty_string_2();
void test_NFA_nonempty_string_3();
void test_NFA_nonempty_string_4();
void test_NFA_nonempty_string_5();
void test_NFA_nonempty_string_6();
void test_NFA_nonempty_string_7();
void test_NFA_nonempty_string_8();
void test_NFA_nonempty_string_9();
void test_NFA_nonempty_string_10();
void test_NFA_nonempty_string_11();
void test_NFA_nonempty_string_12();

//test for NFA_10
void test_NFA_10_1();
void test_NFA_10_2();
void test_NFA_10_3();
void test_NFA_10_4();
void test_NFA_10_5();
void test_NFA_10_6();
void test_NFA_10_7();
void test_NFA_10_8();
void test_NFA_10_9();
void test_NFA_10_10();
void test_NFA_10_11();
void test_NFA_10_12();

//test for NFA_non_empty_even_len
void test_NFA_non_empty_even_len_1();
void test_NFA_non_empty_even_len_2();
void test_NFA_non_empty_even_len_3();
void test_NFA_non_empty_even_len_4();
void test_NFA_non_empty_even_len_5();
void test_NFA_non_empty_even_len_6();
void test_NFA_non_empty_even_len_7();
void test_NFA_non_empty_even_len_8();
void test_NFA_non_empty_even_len_9();
void test_NFA_non_empty_even_len_10();
void test_NFA_non_empty_even_len_11();
void test_NFA_non_empty_even_len_12();

//test for NFA_0s
void test_NFA_0s_1();
void test_NFA_0s_2();
void test_NFA_0s_3();
void test_NFA_0s_4();
void test_NFA_0s_5();
void test_NFA_0s_6();
void test_NFA_0s_7();
void test_NFA_0s_8();
void test_NFA_0s_9();
void test_NFA_0s_10();
void test_NFA_0s_11();
void test_NFA_0s_12();

//test for NFA_0s_or_01s
void test_NFA_0s_or_01s_1();
void test_NFA_0s_or_01s_2();
void test_NFA_0s_or_01s_3();
void test_NFA_0s_or_01s_4();
void test_NFA_0s_or_01s_5();
void test_NFA_0s_or_01s_6();
void test_NFA_0s_or_01s_7();
void test_NFA_0s_or_01s_8();
void test_NFA_0s_or_01s_9();
void test_NFA_0s_or_01s_10();
void test_NFA_0s_or_01s_11();
void test_NFA_0s_or_01s_12();

//test for NFA_1s_or_end_0
void test_NFA_1s_or_end_0_1();
void test_NFA_1s_or_end_0_2();
void test_NFA_1s_or_end_0_3();
void test_NFA_1s_or_end_0_4();
void test_NFA_1s_or_end_0_5();
void test_NFA_1s_or_end_0_6();
void test_NFA_1s_or_end_0_7();
void test_NFA_1s_or_end_0_8();
void test_NFA_1s_or_end_0_9();
void test_NFA_1s_or_end_0_10();
void test_NFA_1s_or_end_0_11();
void test_NFA_1s_or_end_0_12();


//TASK 32
bool NFA_Backtracking( NFA obj, myString s);
bool NFA_search(const NFA& obj, const vector<string>& acceptedStates, myString w, const string& currentState, vector<string> visited, int loop_detect = 0);

//TASK 33
NFA NFA_Union(const NFA& A, const NFA& B);

//TASK 34
NFA NFA_Concat(const NFA& A, const NFA&B);

//TASK 36
NFA  NFA_KStart(const NFA& A);

//TASK 37
void test_NFA_KStart_01();
void test_NFA_KStart_02();
void test_NFA_KStart_03();
void test_NFA_KStart_04();
void test_NFA_KStart_05();
void test_NFA_KStart_06();
void test_NFA_KStart_07();
void test_NFA_KStart_08();
void test_NFA_KStart_09();
void test_NFA_KStart_10();
void test_NFA_KStart_11();
void test_NFA_KStart_12();

//TASK 38
DFA NFA_to_DFA(NFA& obj);
vector<string> newState(string state, map<Pair, set<string>> nT, string character, map<string, vector<string>> closure);
map<string, vector<string>> closure(vector<string>nstate, map<Pair, set<string>> nT);
void E_move(string state, map<Pair, set<string>> nT, vector<string>& result);
void vector_add(vector<string>& a, const vector<string>& b);

//TASK 39
//test for NFA_11_00 to DFA
void test_NFA_11_00_1_DFA();
void test_NFA_11_00_2_DFA();
void test_NFA_11_00_3_DFA();
void test_NFA_11_00_4_DFA();
void test_NFA_11_00_5_DFA();
void test_NFA_11_00_6_DFA();
void test_NFA_11_00_7_DFA();
void test_NFA_11_00_8_DFA();
void test_NFA_11_00_9_DFA();
void test_NFA_11_00_10_DFA();
void test_NFA_11_00_11_DFA();
void test_NFA_11_00_12_DFA();

//test for NFA_end_01 to DFA

void test_NFA_end_01_1_DFA();
void test_NFA_end_01_2_DFA();
void test_NFA_end_01_3_DFA();
void test_NFA_end_01_4_DFA();
void test_NFA_end_01_5_DFA();
void test_NFA_end_01_6_DFA();
void test_NFA_end_01_7_DFA();
void test_NFA_end_01_8_DFA();
void test_NFA_end_01_9_DFA();
void test_NFA_end_01_10_DFA();
void test_NFA_end_01_11_DFA();
void test_NFA_end_01_12_DFA();

//test for NFA_third_0 to DFA
void test_NFA_third_0_1_DFA();
void test_NFA_third_0_2_DFA();
void test_NFA_third_0_3_DFA();
void test_NFA_third_0_4_DFA();
void test_NFA_third_0_5_DFA();
void test_NFA_third_0_6_DFA();
void test_NFA_third_0_7_DFA();
void test_NFA_third_0_8_DFA();
void test_NFA_third_0_9_DFA();
void test_NFA_third_0_10_DFA();
void test_NFA_third_0_11_DFA();
void test_NFA_third_0_12_DFA();

//test for NFA_substring_1110 to DFA
void test_NFA_substring_1110_1_DFA();
void test_NFA_substring_1110_2_DFA();
void test_NFA_substring_1110_3_DFA();
void test_NFA_substring_1110_4_DFA();
void test_NFA_substring_1110_5_DFA();
void test_NFA_substring_1110_6_DFA();
void test_NFA_substring_1110_7_DFA();
void test_NFA_substring_1110_8_DFA();
void test_NFA_substring_1110_9_DFA();
void test_NFA_substring_1110_10_DFA();
void test_NFA_substring_1110_11_DFA();
void test_NFA_substring_1110_12_DFA();

//test for NFA_10s to DFA
void test_NFA_10s_1_DFA();
void test_NFA_10s_2_DFA();
void test_NFA_10s_3_DFA();
void test_NFA_10s_4_DFA();
void test_NFA_10s_5_DFA();
void test_NFA_10s_6_DFA();
void test_NFA_10s_7_DFA();
void test_NFA_10s_8_DFA();
void test_NFA_10s_9_DFA();
void test_NFA_10s_10_DFA();
void test_NFA_10s_11_DFA();
void test_NFA_10s_12_DFA();

//test for NFA_empty_string to DFA
void test_NFA_empty_string_1_DFA();
void test_NFA_empty_string_2_DFA();
void test_NFA_empty_string_3_DFA();
void test_NFA_empty_string_4_DFA();
void test_NFA_empty_string_5_DFA();
void test_NFA_empty_string_6_DFA();
void test_NFA_empty_string_7_DFA();
void test_NFA_empty_string_8_DFA();
void test_NFA_empty_string_9_DFA();
void test_NFA_empty_string_10_DFA();
void test_NFA_empty_string_11_DFA();
void test_NFA_empty_string_12_DFA();

//test for NFA_nonempty_string to DFA
void test_NFA_nonempty_string_1_DFA();
void test_NFA_nonempty_string_2_DFA();
void test_NFA_nonempty_string_3_DFA();
void test_NFA_nonempty_string_4_DFA();
void test_NFA_nonempty_string_5_DFA();
void test_NFA_nonempty_string_6_DFA();
void test_NFA_nonempty_string_7_DFA();
void test_NFA_nonempty_string_8_DFA();
void test_NFA_nonempty_string_9_DFA();
void test_NFA_nonempty_string_10_DFA();
void test_NFA_nonempty_string_11_DFA();
void test_NFA_nonempty_string_12_DFA();

//test for NFA_10 to DFA
void test_NFA_10_1_DFA();
void test_NFA_10_2_DFA();
void test_NFA_10_3_DFA();
void test_NFA_10_4_DFA();
void test_NFA_10_5_DFA();
void test_NFA_10_6_DFA();
void test_NFA_10_7_DFA();
void test_NFA_10_8_DFA();
void test_NFA_10_9_DFA();
void test_NFA_10_10_DFA();
void test_NFA_10_11_DFA();
void test_NFA_10_12_DFA();

//test for NFA_non_empty_even_len to DFA
void test_NFA_non_empty_even_len_1_DFA();
void test_NFA_non_empty_even_len_2_DFA();
void test_NFA_non_empty_even_len_3_DFA();
void test_NFA_non_empty_even_len_4_DFA();
void test_NFA_non_empty_even_len_5_DFA();
void test_NFA_non_empty_even_len_6_DFA();
void test_NFA_non_empty_even_len_7_DFA();
void test_NFA_non_empty_even_len_8_DFA();
void test_NFA_non_empty_even_len_9_DFA();
void test_NFA_non_empty_even_len_10_DFA();
void test_NFA_non_empty_even_len_11_DFA();
void test_NFA_non_empty_even_len_12_DFA();

//test for NFA_0s to DFA
void test_NFA_0s_1_DFA();
void test_NFA_0s_2_DFA();
void test_NFA_0s_3_DFA();
void test_NFA_0s_4_DFA();
void test_NFA_0s_5_DFA();
void test_NFA_0s_6_DFA();
void test_NFA_0s_7_DFA();
void test_NFA_0s_8_DFA();
void test_NFA_0s_9_DFA();
void test_NFA_0s_10_DFA();
void test_NFA_0s_11_DFA();
void test_NFA_0s_12_DFA();

//test for NFA_0s_or_01s to DFA
void test_NFA_0s_or_01s_1_DFA();
void test_NFA_0s_or_01s_2_DFA();
void test_NFA_0s_or_01s_3_DFA();
void test_NFA_0s_or_01s_4_DFA();
void test_NFA_0s_or_01s_5_DFA();
void test_NFA_0s_or_01s_6_DFA();
void test_NFA_0s_or_01s_7_DFA();
void test_NFA_0s_or_01s_8_DFA();
void test_NFA_0s_or_01s_9_DFA();
void test_NFA_0s_or_01s_10_DFA();
void test_NFA_0s_or_01s_11_DFA();
void test_NFA_0s_or_01s_12_DFA();

//test for NFA_1s_or_end_0 to DFA
void test_NFA_1s_or_end_0_1_DFA();
void test_NFA_1s_or_end_0_2_DFA();
void test_NFA_1s_or_end_0_3_DFA();
void test_NFA_1s_or_end_0_4_DFA();
void test_NFA_1s_or_end_0_5_DFA();
void test_NFA_1s_or_end_0_6_DFA();
void test_NFA_1s_or_end_0_7_DFA();
void test_NFA_1s_or_end_0_8_DFA();
void test_NFA_1s_or_end_0_9_DFA();
void test_NFA_1s_or_end_0_10_DFA();
void test_NFA_1s_or_end_0_11_DFA();
void test_NFA_1s_or_end_0_12_DFA();

//TASK 40
void test_NFA_DFA_Equal_11_00();
void test_NFA_DFA_Equal_10s();
void test_NFA_DFA_Equal_10();
void test_NFA_DFA_Equal_0s();


#endif // !_NFA_H_

