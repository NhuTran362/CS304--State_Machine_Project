#include "DFA.h"


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
		return "false";
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

ostream& operator<<(ostream& OStream, const DFA& obj) {
	OStream << "States:";
	for (auto& each: obj.state)
		OStream << "     " << each ;
	OStream << endl;
	OStream << "Alphabet:";
	for (auto& each : obj.alphabet)
		OStream << "     " <<each;
	OStream << endl;
	OStream << "Start State:" << obj.startState << endl;
	OStream << "Transition:"<<endl;
	for (auto& each : obj.transition)
		OStream << each.first.first << "x" << each.first.second << "-> " << each.second << endl;
	OStream << "Accepting State:";
	for (auto &each : obj.acceptingState)
		OStream << "   " << each;
	OStream << endl;
	return OStream;
}

// Completed TASK 7 - A function returning a DFA that accep only the string of one given character
DFA AcceptingStringofOneCharacter(const string& oneCharacter, set<string> initAlphabet) {

	if (!isSubSet(set<string>{oneCharacter}, initAlphabet))
	{
		cout << "The given character does not belong to the alphabet\n";
		exit(-1);
	}
	map<pair<string, string>, string> initTransition;
	if (initAlphabet.begin() != initAlphabet.end())

		for (auto p = initAlphabet.begin(); p != initAlphabet.end(); p++)
		{

			if (*p != oneCharacter)
				initTransition[pair<string, string>("0", *p)] = "2";
			initTransition[pair<string, string>("1", *p)] = "2";
			initTransition[pair<string, string>("2", *p)] = "2";
			initTransition[pair<string, string>("0", oneCharacter)] = "1";

		}
	DFA newDFA(vector<string>{"0", "1", "3"}, initAlphabet, "0", initTransition, vector<string>{"1"});
	return newDFA;
}



void test_DFA_even_len() {

	cout << "********** TESTING DFA EVEN_LEN ************\n" << endl;

	myString a("1001010100000");
	if (!even_len.isAccepted(a) && even_len.isAccepted(myString("100010001000")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}


	cout << "NOT PASSED\n\n" << endl;
	return;

}

void test_DFA_string_of_0s() {

	cout << "********** TESTING DFA STRING_OF_0s ************\n" << endl;

	if (string_of_0s.isAccepted(myString("0000000000000")) && !string_of_0s.isAccepted(myString("00000010000")) && string_of_0s.isAccepted(myString("")))

	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;

}

void test_DFA_recognize_nano() {
	cout << "********** TESTING DFA RECOGNIZE_NANO ************\n" << endl;


	if (!recognize_nano.isAccepted(myString("nnnaaon")) && recognize_nano.isAccepted(myString("naaanonananooo")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;
}

void test_DFA_string_end_with_0() {
	cout << "********** TESTING DFA STRING_END_WITH_ZERO ************\n" << endl;

	if (!string_end_with_0.isAccepted(myString("0111001")) && string_end_with_0.isAccepted(myString("00111101010010")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;
}

void test_DFA_string_of_even_number_of_0() {

	cout << "********** TESTING DFA STRING_OF_EVEN_NUMBER_OF_0 ************\n" << endl;

	if (!string_of_even_number_of_0.isAccepted(myString("0001001")) && string_of_even_number_of_0.isAccepted(myString("1111110001011")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;

}

void test_DFA_string_of_three_consecutive_zero() {
	cout << "********** TESTING DFA STRING_OF_EVEN_NUMBER_OF_0 ************\n" << endl;

	if (!string_of_three_consecutive_zero.isAccepted(myString("001010010111010")) && string_of_three_consecutive_zero.isAccepted(myString("100000010001")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;
}

void test_DFA_string_of_even_0_and_1() {
	cout << "********** TESTING DFA STRING_OF_EVEN_0_AND_1 ************\n" << endl;

	if (!string_of_even_0_and_1.isAccepted(myString("0010010")) && !string_of_even_0_and_1.isAccepted(myString("001001100")) && !string_of_even_0_and_1.isAccepted(myString("101001")) && string_of_even_0_and_1.isAccepted(myString("1000010000100010")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;
}

void test_DFA_string_of_0s_start_and_end_with_1() {
	cout << "********** TESTING DFA STRING_OF_0s_START_AND_END_WITH_1 ************\n" << endl;

	if (!string_of_0s_start_and_end_with_1.isAccepted(myString("0001")) && !string_of_0s_start_and_end_with_1.isAccepted(myString("1000000000")) && !string_of_0s_start_and_end_with_1.isAccepted(myString("1000000010")) && string_of_0s_start_and_end_with_1.isAccepted(myString("10000000000001")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;
}

void test_DFA_string_that_accept_only_101() {
	cout << "********** TESTING DFA STRING_THAT_ACCEPT_ONLY_101 ************\n" << endl;

	if (!string_that_accept_only_101.isAccepted(myString("101001100")) && !string_that_accept_only_101.isAccepted(myString("01010001010")) && string_that_accept_only_101.isAccepted(myString("101")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;
}

void test_string_that_does_not_contain_consecutive_1() {
	cout << "********** TESTING DFA STRING_THAT_DOES_NOT_CONTAIN_CONSECUTIVE_1 ************\n" << endl;

	if (!string_that_does_not_contain_consecutive_1.isAccepted(myString("0001100010")) && !string_that_does_not_contain_consecutive_1.isAccepted(myString("010011100")) && string_that_does_not_contain_consecutive_1.isAccepted(myString("1010001001")) && string_that_does_not_contain_consecutive_1.isAccepted(myString("10101010")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;
}

void test_DFA_string_of_len_2() {
	cout << "********** TESTING DFA STRING_OF_LEN_2 ************\n" << endl;


	if (!string_of_len_2.isAccepted(myString("0001100010")) && !string_of_len_2.isAccepted(myString("0")) && string_of_len_2.isAccepted(myString("10")) && string_of_len_2.isAccepted(myString("11")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;
}
void test_DFA_strings_of_110s() {
	cout << "********** TESTING DFA STRING_OF_110s ************\n" << endl;

	if (!strings_of_110s.isAccepted(myString("0001100010")) && !strings_of_110s.isAccepted(myString("11011010")) && strings_of_110s.isAccepted(myString("110110110110")))
	{
		cout << "PASSED\n\n" << endl;
		return;
	}

	cout << "NOT PASSED\n\n" << endl;
	return;

}

list<config> trace(DFA inputDFA, myString inputString) {

	list<config> myTrace;
	string _state = inputDFA.getStartState();
	
	int i = 0, len = inputString.getStringLen();
	config temp;

	for (i; i <= len; i++) {
	
		temp.q = _state;
		temp.w = inputString;
		myTrace.push_back(temp);
		_state = inputDFA.myTransition(temp.q,inputString.getCharacterAt(0));
		inputString.pop_front();
	
	
	}

	return myTrace;
}

myString  returnAcceptedString(const DFA& inputDFA) {
	
	vector<string> states = inputDFA.getState();
	set<string> alphabet = inputDFA.getAlphabet();
	string start = inputDFA.getStartState();
	vector<string> acceptingStates = inputDFA.getAcceptingState();
	map<Pair, string> transition = inputDFA.getTransition();
	
	set<string> visited = {start };
	myString result(alphabet, "EPSILON");
	if (acceptingStates.empty())
		return myString("false");

	return  search (alphabet, transition, visited,states.size(), start, result, acceptingStates);


}

myString search(set<string> alphabet, map<Pair, string> transition, set<string> visited, int totalStates, string current, myString result, vector<string> acceptingStates) {
	//cout << "\nSEARCH CALL: \n";
	//cout << result << endl;
	//cout << "current state: " << current << endl;
	//cout << "visit.size: "<< visited.size() << " totalStates: " << totalStates << endl;
	
	if (find(acceptingStates.begin(), acceptingStates.end(), current) != acceptingStates.end())
	{
		///cout << "Return result at the begining\n";
		return result;
	}
	for (auto p = alphabet.begin(); p != alphabet.end(); p++)
	{
		auto p1 = transition.find(Pair(current, *p));
		if (p1 != transition.end() && visited.find(p1->second) == visited.end())
		{
			set<string>newVisited = visited;
			newVisited.insert(p1->second);
			myString newResult(result);
			//cout << "before push: " << newResult << endl;
			newResult.push_back(*p);
			//cout << "pushed " << *p << " to the string\n";
			//cout << "after push: " << newResult << endl;
			

			if (search(alphabet, transition, newVisited, totalStates, p1->second, newResult, acceptingStates) != myString("false"))
			{
				//cout << "return newresult\n";
				return search(alphabet, transition, newVisited, totalStates, p1->second, newResult, acceptingStates);
			}
		}
	}
	//cout << "return false when out of loop\n";
	return myString("false");

}

//TASK 13
DFA DFA_Complement(const DFA& myDFA) {
	vector<string> newAcceptingstates;
	vector<string> states = myDFA.getState();
	vector<string> acceptingState = myDFA.getAcceptingState();
	
	for (unsigned i = 0; i < states.size(); i++) {
		if (find(acceptingState.begin(), acceptingState.end(), states[i]) == acceptingState.end())
			newAcceptingstates.push_back(states[i]);
	}

	return DFA(myDFA.getState(), myDFA.getAlphabet(), myDFA.getStartState(), myDFA.getTransition(), newAcceptingstates);
}

/TASK 14
DFA DFA_Union(const DFA& A, const DFA& B) {

	vector<string> statesA = A.getState();
	set<string> AlphabetA= A.getAlphabet();
	string startA = A.getStartState();
	vector<string> acceptA = A.getAcceptingState();
	map<Pair, string> transA =A.getTransition();

	vector<string> statesB = B.getState();
	set<string> AlphabetB = B.getAlphabet();
	string startB = B.getStartState();
	vector<string> acceptB = B.getAcceptingState();
	map<Pair, string> transB = B.getTransition();

	if (AlphabetA != AlphabetB)
	{
		cout << "DFA_Union: The Two DFAs must have the same alphabet\n\n";
		exit(-1);
	}
	
	
	vector<string> statesC;
	set<string> AlphabetC;
	string startC;
	vector<string> acceptC;
	map<Pair, string> transC;

	//states
	for(auto &each1: statesA)
		for (auto &each2 : statesB)
		{
			string newState = each1 + "," + each2;
			statesC.push_back(newState);
		}

	//start
	startC = startA + "," + startB;

	//accept 
	for (auto &each1 : acceptA)
		for (auto &each2 : statesB)
		{
			string newState = each1 + "," + each2;
			acceptC.push_back(newState);
		}
	for (auto &each1 : acceptB)
		for (auto &each2 : statesA)
		{
			string newState = each2 + "," + each1;
			if (find(acceptC.begin(), acceptC.end(), newState) == acceptC.end())
			   acceptC.push_back(newState);
		}

	//trans

	for (auto &each1 : statesA)
		for (auto &each2 : statesB)
			for (auto &each3 : AlphabetA)
			{
				auto p1 = transA.find(Pair(each1, each3));
				auto p2 = transB.find(Pair(each2, each3));
				
				if (p1 == transA.end() && p2 == transB.end())
					break;
				
				string nextState;

				if (p1 != transA.end() && p2 != transB.end())
					nextState = transA[Pair(each1, each3)] + "," + transB[Pair(each2, each3)];
			
				else if (p1 == transA.end() && p2 != transB.end())
					nextState = each1 + "," + transB[Pair(each2, each3)];
				
				else if (p1 != transA.end() && p2 == transB.end())
					nextState = transA[Pair(each1, each3)] + "," + each2;

				transC[Pair(each1 + "," + each2, each3)] = nextState;			
			}
	return DFA(statesC, AlphabetA, startC, transC, acceptC);

}
