#ifndef _NFA_H_
#define _NFA_H_

#include "myString.h"
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
static NFA NFA_nonempty_string(vector<string>{"0", "1"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "EPSILON"), { "1" }}, { Pair("0", "0"), { "0" }}, { Pair("0", "1"), { "0" } }}, vector<string>{"0"});

//accep "10"
static NFA NFA_10(vector<string>{"0", "1", "2"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "1"), { "1" }}, { Pair("1", "0"), { "2" }}}, vector<string>{"2"});

//even length but not zero
static NFA NFA_non_empty_even_len(vector<string>{"0", "1", "2","3"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "1"), { "1" }}, {Pair("0", "0"), { "1" } }, { Pair("0", "EPSILON"), { "3" }}, { Pair("1", "0"), { "2"}}, { Pair("1", "1"), { "2" }}, { Pair("2", "0"), { "1"} }, { Pair("2", "1"), { "1" } }}, vector<string>{"2"});

//consecutive 0 and not empty
static NFA NFA_0s(vector<string>{"0", "1", "2"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "0"), { "1" }}, { Pair("0", "EPSILON"), {"2"} }, { Pair("1","0"),{"1"} }}, vector<string>{"0"});

//consecutive 0 or consecutive "01"
static NFA NFA_0s_or_01s(vector<string>{"0", "1", "2","3"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "0"), { "1","2"}}, { Pair("1", "0"), {"1"}}, { Pair("2", "1"), {"3"}}, { Pair("3", "0"), {"2"}}}, vector<string>{"1","3"});

//consecutive 1 or the last sympol is 0
static NFA NFA_1s_or_end_0(vector<string>{"0", "1", "2", "3"}, set<string>{"0", "1"}, "0", map<Pair, set<string>>{ {Pair("0", "EPSILON"), { "1","2" }}, { Pair("1", "1"), {"1"} }, { Pair("2", "1"), {"2"} }, { Pair("2", "0"), {"2","3"} }}, vector<string>{"1", "3"});

#endif // !_NFA_H_

