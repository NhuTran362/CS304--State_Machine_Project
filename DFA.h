#ifndef DFA_H
#define DFA_H

#include "myString.h"
#include <map>
using namespace std;

typedef pair<string, string> Pair;

/***** DEFINE A DATA TYPE TO REPRESENT DFA **************/
/******************** TASK 4 ***********************/
class DFA {

private:
	vector<string> state;
	set <string> alphabet;
	string startState;
	vector<string> acceptingState;
	map<Pair, string> transition;


	int stateNum = 0; 
	int alphabetSize = 0;
	int acceptingState_num = 0;

	string getFinalState(const myString& inputString);
	
	string myTransition(string state, string character);


public:
	DFA():state(vector<string> {"0"}), alphabet(set<string>{"0", "1"}), startState("0"), transition(), acceptingState(vector<string>{"0"}), stateNum(1), alphabetSize(2), acceptingState_num(1)  {};
	DFA(vector<string> initStates, set<string> initAlphabet, string initStartState, map<Pair, string> initTransition, vector<string> initAcceptingState) : state(initStates), alphabet(initAlphabet), startState(initStartState), transition(initTransition), acceptingState(initAcceptingState) {
		stateNum = state.size();
		alphabetSize = alphabet.size();
		acceptingState_num = acceptingState.size();
	}
	DFA(const DFA& initDFA);

	vector<string> getState() const { return state; }
	set<string> getAlphabet() const { return alphabet; }
	string getStartState() const { return startState; }
	vector<string> getAcceptingState() const { return acceptingState; }


	int getStateNum() const { return stateNum; }
	int getAlphabetSize() const { return alphabetSize; }
	int getAcceptingState_num() const { return acceptingState_num; }
	map<Pair, string> getTransition()const { return transition; }

	void operator=(const DFA& initDFA) {
		state = initDFA.getState();
		alphabet = initDFA.getAlphabet();
		startState = initDFA.getStartState();
		acceptingState = initDFA.getAcceptingState();
		transition = initDFA.getTransition();


		int stateNum = initDFA.getStateNum();
		int alphabetSize = initDFA.getAlphabetSize();
		int acceptingState_num = initDFA.getAcceptingState_num();
	}

	void setState(vector<string> initState) { state = initState; stateNum = initState.size(); }
	void setalphabet(set<string> initAlphabet) { alphabet = initAlphabet; alphabetSize = initAlphabet.size(); }
	void setStartState(string initStartState) { startState = initStartState; }
	void setAcceptingState(vector<string> initAcceptingState) { acceptingState = initAcceptingState; acceptingState_num = initAcceptingState.size(); }
	void setTransition(map<Pair, string> initTranistion) { transition = initTranistion; }
	
	/****** A FUNCTIION TO CHECK IF A STRING IS ACCEPTED ***********/
	/******************** TASK 10 ********************/
	bool isAccepted(myString inputString) {

		string finalState = getFinalState(inputString);
		vector<string> acceptingState = getAcceptingState();
		return (find(acceptingState.begin(), acceptingState.end(), finalState) != acceptingState.end());
	}
	/*******************************************************************/
  
  }
  
DFA AcceptingStringofOneCharacter(const string& oneCharacter, set<string> initAlphabet);
// Completed TASK 5 - DFA Accepting no String
static DFA AcceptingNoString(vector<string> {"0"}, set<string> {"0", "1"}, "0", map<pair<string, string>, string> {}, vector<string> {});

// Completed TASK 6 - DFA Accepting Empty String - EPSILON
static DFA AcceptingEmptyString(vector<string> {"0", "1"}, set<string> {"0", "1"}, "0", map<pair<string, string>, string> { {pair<string, string>("0", "0"), "1"}, { pair<string, string>("0", "1"), "1" }}, vector<string> {"0"});


// Completed TASK 8 - A DOZEN EXAMPLE OF DFA
//accept string that have even length
static DFA even_len(vector<string> { "0", "1" }, set<string> {"0", "1"}, "0", map<Pair, string> { {Pair("0", "0"), "1"}, { Pair("0", "1"), "1" }, { Pair("1", "0"), "0" }, { Pair("1", "1"), "0" }}, { "0" });

// accept strings that only consists of 0
static DFA string_of_0s(vector<string> { "0", "1" }, set<string> {"0", "1"}, "0", map<Pair, string> { { Pair("0", "1"), "1" }}, vector<string> {"0"});

// accept strings that consit the word "nano" in it
static DFA recognize_nano(vector<string> {"0", "1", "2", "3"}, set<string>{"n", "a", "o"}, "0", map<Pair, string> { {Pair("0", "n"), "1"}, { Pair("1", "a"), "2" }, { Pair("1","o"),"0" }, { Pair("2", "n"), "3" }, { Pair("2", "o"), "0" }, { Pair("2", "a"), "0" }, { pair<string,string>("3", "o"), "4" }, { pair<string,string>("3", "a"), "2" }, { pair<string,string>("3", "n"), "1" }, { pair<string,string>("3", "a"), "2" }}, vector<string> {"4"});

// accept string that end with zero
static DFA string_end_with_0(vector<string>{"0", "1"}, set<string>{"0", "1"}, "0", map<Pair, string>{ {Pair("0", "1"), "1"}, { Pair("1", "0"), "0" }}, vector<string> {"0"});

// accept strings that have even number of 0
static DFA string_of_even_number_of_0(vector<string>{"0", "1"}, set<string>{"0", "1"}, "0", map<Pair, string>{ {Pair("0", "0"), "1"}, { Pair("1", "0"), "0" }}, vector<string> {"0"});

//accept strings that have at least three consecutive zero e.g 1000, 10000101, 000
static DFA string_of_three_consecutive_zero(vector<string>{"0", "1"}, set<string>{"0", "1", "2", "3"}, "0", map<Pair, string>{ {Pair("0", "0"), "1"}, { Pair("1", "0"), "2" }, { Pair("1","1"), "0" }, { Pair("2","0"), "3" }, { Pair("2","1"), "0" }}, vector<string> {"3"});

//accept string that have even number of 0 and 1
static DFA string_of_even_0_and_1(vector<string>{"0", "1", "2", "3"}, set<string>{"0", "1", "2"}, "0", map<Pair, string>{ {Pair("0", "0"), "1"}, { Pair("0", "1"), "2" }, { Pair("1","0"), "0" }, { Pair("1","1"), "3" }, { Pair("2","0"), "3" }, { Pair("2","1"), "0" }, { Pair("3","0"), "2" }, { Pair("3","1"), "1" }}, vector<string> {"0"});

// accept string that strat and end with 1 and have a bunch of 0 in betwen e.g 100001,11,101,10000001
static DFA string_of_0s_start_and_end_with_1(vector<string>{"0", "1", "2", "3"}, set<string>{"0", "1"}, "0", map<Pair, string>{ {Pair("0", "0"), "3"}, { Pair("0", "1"), "1" }, { Pair("1","1"), "2" }, { Pair("2","0"), "3" }, { Pair("2","1"), "3" }, }, vector<string> {"2"});

// accept only "101"
static DFA string_that_accept_only_101(vector<string>{"0", "1", "2", "3", "4"}, set<string>{"0", "1"}, "0", map<Pair, string>{ {Pair("0", "0"), "4"}, { Pair("0", "1"), "1" }, { Pair("1","0"), "2" }, { Pair("1","1"), "4" }, { Pair("2","1"), "3" }, { Pair("2","0"), "4" }, { Pair("3","0"), "4" }, { Pair("3","1"), "4" }}, vector<string> {"3"});

//accept only string that does not contain consecutive 1
static DFA string_that_does_not_contain_consecutive_1(vector<string>{"0", "1", "2"}, set<string>{"0", "1"}, "0", map<Pair, string>{ {Pair("0", "1"), "1"}, { Pair("1","1"), "2" }, { Pair("1","0"), "0" }}, vector<string> {"0", "1"});

//accept only strings of length 2
static DFA string_of_len_2(vector<string> {"0", "1", "2", "3"}, set<string>{"0", "1"}, "0", map<Pair, string>{ {Pair("0", "0"), "1"}, { Pair("0","1"),"1" }, { Pair("1","0"),"2" }, { Pair("1","1"),"2" }, { Pair("2","0"),"3" }, { Pair("2","1"),"3" }}, vector<string>{"2"});

//acceps strings that have two 1 follow by 1 zero e.g 110, 110110, 110110110
static DFA strings_of_110s(vector<string> {"0", "1", "2", "3", "4"}, set<string>{"0", "1"}, "0", map<Pair, string>{ {Pair("0", "1"), "1"}, { Pair("0", "0"), "4" }, { Pair("1", "1"), "2" }, { Pair("1", "0"), "4" }, { Pair("2", "0"), "3" }, { Pair("2", "1"), "4" }, { Pair("3", "1"), "1" }, { Pair("3", "0"), "4" }}, vector<string> {"3"});
/************************************/




//Completed TASK 9 - A DOZEN DFA TEST
void test_DFA_even_len();
void test_DFA_string_of_0s();
void test_DFA_recognize_nano();
void test_DFA_string_end_with_0();
void test_DFA_string_of_even_number_of_0();
void test_DFA_string_of_three_consecutive_zero();
void test_DFA_string_of_even_0_and_1();
void test_DFA_string_of_0s_start_and_end_with_1();
void test_DFA_string_that_accept_only_101();
void test_DFA_string_that_does_not_contain_consecutive_1();
void test_DFA_string_of_len_2();
void test_DFA_strings_of_110s();



#endif // !DFA_H
