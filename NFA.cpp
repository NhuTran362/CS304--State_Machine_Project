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
