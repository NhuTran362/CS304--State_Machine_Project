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
};
#endif // !_NFA_H_

