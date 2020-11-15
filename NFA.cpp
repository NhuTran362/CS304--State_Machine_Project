#include "NFA.h"
#include "myString.h"
//TASK 23

NFA::NFA(const NFA& initNFA) {
	state = initNFA.getState();
	alphabet = initNFA.getAlphabet();
	startState = initNFA.getStartState();
	acceptingState = initNFA.getAcceptingState();
	transition = initNFA.getTransition();

	stateNum = initNFA.getStateNum();
	alphabetSize = initNFA.getAlphabetSize();
	acceptingState_num = initNFA.getAcceptingState_num();
}
set<string> NFA::myTransition(string state, string character) {

	set<string> currentState = { state };
	if (transition.empty())
		return currentState;
	
	if (character == "")
		character = "EPSILON";

	map<Pair, set<string>>::iterator temp = transition.find(Pair(state, character));


	if (temp != transition.end())
	{
		return temp->second;
	}

	return currentState;
}

// TASK 24
void NFA::operator=(const DFA &dfa) {
	state = dfa.getState();
	alphabet = dfa.getAlphabet();
	startState = dfa.getStartState();
	acceptingState = dfa.getAcceptingState();
	stateNum = dfa.getStateNum();
	alphabetSize = dfa.getAlphabetSize();
	acceptingState_num = dfa.getAcceptingState_num();

	map<Pair, string> T = dfa.getTransition();
	for (auto each : T)
		transition[each.first] = set<string>{ each.second };
}
