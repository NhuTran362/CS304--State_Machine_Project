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
  
  DFA::DFA(const DFA& initDFA) {
	state = initDFA.getState();
	alphabet = initDFA.getAlphabet();
	startState = initDFA.getStartState();
	acceptingState = initDFA.getAcceptingState();
	transition = initDFA.getTransition();

	stateNum = initDFA.getStateNum();
	alphabetSize = initDFA.getAlphabetSize();
	acceptingState_num = initDFA.getAcceptingState_num();
}
string DFA::getFinalState(const myString& inputString) {


	if (!isSubSet(inputString.getAlphabet(), alphabet))
	{
		cout << "The input string does not used the same alphabet as this DFA\n" << endl;
		char c;
		cin >> c;
		exit(-1);
	}

	int i = 0;
	int len = inputString.getStringLen();
	string current_state = getStartState();
	while (i < len) {

		current_state = myTransition(current_state, inputString.getCharacterAt(i));

		i++;
	}

	return current_state;
}

string DFA::myTransition(string state, string character) {


	if (transition.empty() || character == "EPSILON")
	{
		return state;
	}
	map<Pair, string>::iterator temp = transition.find(Pair(state, character));


	if (temp != transition.end())
	{


		return temp->second;
	}

	return state;
}
