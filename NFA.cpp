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

	set<string> empty = {};
	if (transition.empty())
		return empty;
	
	if (character == "")
		character = "EPSILON";

	map<Pair, set<string>>::iterator temp = transition.find(Pair(state, character));


	if (temp != transition.end())
	{
		return temp->second;
	}

	return empty;
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

//TASK 27
config string_to_config(string str) {
	config rslt;
	rslt.q = str[0];
	str.erase(0,2);
	if (str == "EPSILON")
		rslt.w = myString(set<string>{"0", "1"}, vector<string> {str});
	else
		rslt.w = myString(str);
	return rslt;
}
bool NFA_Oracle(const NFA& myNFA, string str, list<string> trace){
if (trace.size() == 0)
		return true;
	map<Pair, set<string>> T = myNFA.getTransition();
	auto p1 = trace.begin();
	map<Pair,set<string>>::iterator p2;
	config c1, c2;
	int i = 0;
	while (p1 != (--trace.end())) {
		cout << i << endl;
		i++;
		c1 = string_to_config(*p1);
		p1++;
		c2 = string_to_config(*p1);
		
		if (p1 == trace.begin() && (c1.q != myNFA.getStartState() || c1.w != str))	
			return false;
		
		if (c1.w == c2.w) {
			p2 = T.find(Pair(c1.q, "EPSILON"));
			if (p2 == T.end() || p2->second.find(c2.q) == p2->second.end())
				return false;
		}
		else
		{
			
			string a = c1.w.getCharacterAt(0);
			c1.w.pop_front();
			if (c1.w == c2.w) {
				p2 = T.find(Pair(c1.q, a));
				if (p2 == T.end() || p2->second.find(c2.q) == p2->second.end())
					return false;
			}
			else {
				return false;
			}
		}
	}
	return true;
}

