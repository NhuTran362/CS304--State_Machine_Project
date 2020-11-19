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

void test_DFA_string_that_does_not_contain_consecutive_1() {
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
	
	if (find(acceptingStates.begin(), acceptingStates.end(), current) != acceptingStates.end())
		return result;
	
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
				return search(alphabet, transition, newVisited, totalStates, p1->second, newResult, acceptingStates);
			}
		}
	}
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

//TASK 14
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
				
				string nextState;

				if (p1 != transA.end() && p2 != transB.end())
					nextState = transA[Pair(each1, each3)] + "," + transB[Pair(each2, each3)];
			
				else if (p1 == transA.end() && p2 != transB.end())
					nextState = each1 + "," + transB[Pair(each2, each3)];
				
				else if (p1 != transA.end() && p2 == transB.end())
					nextState = transA[Pair(each1, each3)] + "," + each2;
				if (nextState.size() > 0)
				transC[Pair(each1 + "," + each2, each3)] = nextState;			
			}
	return DFA(statesC, AlphabetA, startC, transC, acceptC);

}

//TASK 15
void test_even_len_OR_strings_of_0s() {
	cout << "********** TESTING EVEN_LEN_OR_STRINGS_OF_0s ************\n" << endl;
	DFA myDFA = DFA_Union(even_len, string_of_0s);
	if (myDFA.isAccepted(myString("00000000")) && myDFA.isAccepted(myString("01010101101100"))
		&& myDFA.isAccepted(myString("0000000")) && !myDFA.isAccepted(myString("1001001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

}

void test_string_end_with_0_OR_string_of_even_number_of_0() {
	cout << "********** TESTING STRING_END_WITH_ZERO_OR_STRING_OF_EVEN_NUMBER_OF_ZERO ************\n" << endl;
	DFA myDFA = DFA_Union(string_end_with_0, string_of_even_number_of_0);
	if (myDFA.isAccepted(myString("00000000")) && myDFA.isAccepted(myString("001001101010"))
		&& myDFA.isAccepted(myString("001001001001")) && !myDFA.isAccepted(myString("10010001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_three_consecutive_zero_OR_strings_of_110s() {
	cout << "********** TESTING STRING_OF_THREE_CONSECUTIVE_ZERO_OR_STRINGS_OF_110s ************\n" << endl;
	DFA myDFA = DFA_Union(string_of_three_consecutive_zero, strings_of_110s);
	if (myDFA.isAccepted(myString("110110000")) && myDFA.isAccepted(myString("110110110"))
		&& myDFA.isAccepted(myString("000")) && !myDFA.isAccepted(myString("1001001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_len_2_OR_string_that_does_not_contain_consecutive_1() {
	cout << "********** TESTING STRING_OF_LEN_2_OR_STRING_THAT_DOES_NOT_CONTAIN_CONSECUTIVE_1 ************\n" << endl;
	DFA myDFA = DFA_Union(string_of_len_2, string_that_does_not_contain_consecutive_1);
	if (myDFA.isAccepted(myString("10")) && myDFA.isAccepted(myString("11"))
		&& myDFA.isAccepted(myString("0010")) && !myDFA.isAccepted(myString("1111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_even_0_and_1_OR_string_of_three_consecutive_zero() {
	cout << "********** TESTING STRING_OF_EVEN_0_AND_1_OR_STRING_OF_THREE_CONSECUTIVE_ZERO ************\n" << endl;
	DFA myDFA = DFA_Union(string_of_even_0_and_1, string_of_three_consecutive_zero);
	if (myDFA.isAccepted(myString("000011")) && myDFA.isAccepted(myString("0011"))
		&& myDFA.isAccepted(myString("000")) && !myDFA.isAccepted(myString("1110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_even_len_OR_strings_of_110s() {
	cout << "********** TESTING EVEN_LEN_OR_STRINGS_OF_110s ************\n" << endl;
	DFA myDFA = DFA_Union(even_len, strings_of_110s);
	if (myDFA.isAccepted(myString("110110")) && myDFA.isAccepted(myString("10"))
		&& myDFA.isAccepted(myString("110110110")) && !myDFA.isAccepted(myString("1001010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_end_with_0_OR_string_of_even_0_and_1() {
	cout << "********** TESTING STRING_END_WITH_0_OR_STRING_OF_EVEN_0_AND_1 ************\n" << endl;
	DFA myDFA = DFA_Union(string_end_with_0, string_of_even_0_and_1);
	if (myDFA.isAccepted(myString("001100")) && myDFA.isAccepted(myString("0010"))
		&& myDFA.isAccepted(myString("0101")) && !myDFA.isAccepted(myString("10001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_that_only_accept_101_OR_string_end_with_0() {
	cout << "********** TESTING STRING_THAT_ONLY_ACCEPT_101_OR_STRING_END_WITH_0 ************\n" << endl;
	DFA myDFA = DFA_Union(string_that_accept_only_101, string_end_with_0);
	if (myDFA.isAccepted(myString("101")) && myDFA.isAccepted(myString("1010100"))
		&& !myDFA.isAccepted(myString("1101001101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_0s_start_and_end_with_1_OR_string_of_0s() {
	cout << "********** TESTING STRING_OF_0s_START_AND_END_WITH_1_OR_STRING_OF_0s ************\n" << endl;
	DFA myDFA = DFA_Union(string_of_0s_start_and_end_with_1, string_of_0s);
	if (myDFA.isAccepted(myString("100000001")) && myDFA.isAccepted(myString("11"))
		&& myDFA.isAccepted(myString("0000")) && !myDFA.isAccepted(myString("01001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_110s_OR_string_of_len_2() {
	cout << "********** TESTING STRINGS_OF_110s_OR_STRING_OF_LEN_2 ************\n" << endl;
	DFA myDFA = DFA_Union(strings_of_110s, string_of_len_2);
	if (myDFA.isAccepted(myString("11")) && myDFA.isAccepted(myString("110110"))
		&& !myDFA.isAccepted(myString("11101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_string_of_even_number_of_0_OR_string_of_0s_start_and_end_with_1() {
	cout << "********** TESTING STRINGS_OF_EVEN_NUMBER_OF_0_OR_STRING_OF_0s_START_AND_END_WITH_1 ************\n" << endl;
	DFA myDFA = DFA_Union(string_of_even_number_of_0, string_of_0s_start_and_end_with_1);
	if (myDFA.isAccepted(myString("100001")) && myDFA.isAccepted(myString("00100010"))
		&& myDFA.isAccepted(myString("1000001")) && !myDFA.isAccepted(myString("1110100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_that_does_not_contain_consecutive_1_OR_even_len() {
	cout << "********** TESTING STRINGS_THAT_DOES_NOT_CONTAIN_CONSECUTIVE_1_OR_EVEN_LEN ************\n" << endl;
	DFA myDFA = DFA_Union(string_that_does_not_contain_consecutive_1, even_len);
	if (myDFA.isAccepted(myString("00101000")) && myDFA.isAccepted(myString("110110"))
		&& myDFA.isAccepted(myString("0001010")) && !myDFA.isAccepted(myString("110010110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//TASK 16
DFA DFA_Intersection(const DFA& A, const DFA& B) {
	vector<string> statesA = A.getState();
	set<string> AlphabetA = A.getAlphabet();
	string startA = A.getStartState();
	vector<string> acceptA = A.getAcceptingState();
	map<Pair, string> transA = A.getTransition();

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
	for (auto &each1 : statesA)
		for (auto &each2 : statesB)
		{
			string newState = each1 + "," + each2;
			statesC.push_back(newState);
		}

	//start
	startC = startA + "," + startB;

	//accept 
	for (auto &each1 : acceptA)
		for (auto &each2 : acceptB)
		{
			string newState = each1 + "," + each2;
			acceptC.push_back(newState);
		}
	

	//trans

	for (auto &each1 : statesA)

		for (auto &each2 : statesB)
			for (auto &each3 : AlphabetA)
			{
				auto p1 = transA.find(Pair(each1, each3));
				auto p2 = transB.find(Pair(each2, each3));

				string nextState;

				if (p1 != transA.end() && p2 != transB.end())
					nextState = transA[Pair(each1, each3)] + "," + transB[Pair(each2, each3)];

				else if (p1 == transA.end() && p2 != transB.end())
					nextState = each1 + "," + transB[Pair(each2, each3)];

				else if (p1 != transA.end() && p2 == transB.end())
					nextState = transA[Pair(each1, each3)] + "," + each2;
				if (nextState.size() > 0)
					transC[Pair(each1 + "," + each2, each3)] = nextState;
			}

	return DFA(statesC, AlphabetA, startC, transC, acceptC);
}

//TASK 17
void test_even_len_AND_strings_of_0s() {
	cout << "********** TESTING EVEN_LEN_AND_STRINGS_OF_0s ************\n" << endl;
	DFA myDFA = DFA_Intersection(even_len, string_of_0s);
	if (myDFA.isAccepted(myString("00000000")) && !myDFA.isAccepted(myString("01010101101100"))
		&& !myDFA.isAccepted(myString("0000000")) && !myDFA.isAccepted(myString("1001001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

}

void test_string_end_with_0_AND_string_of_even_number_of_0() {
	cout << "********** TESTING STRING_END_WITH_ZERO_AND_STRING_OF_EVEN_NUMBER_OF_ZERO ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_end_with_0, string_of_even_number_of_0);
	if (myDFA.isAccepted(myString("00000000")) && !myDFA.isAccepted(myString("001001101010"))
		&& !myDFA.isAccepted(myString("001001001001")) && !myDFA.isAccepted(myString("10010001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_three_consecutive_zero_AND_strings_of_110s() {
	cout << "********** TESTING STRING_OF_THREE_CONSECUTIVE_ZERO_AND_STRINGS_OF_110s ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_of_three_consecutive_zero, strings_of_110s);
	if (!myDFA.isAccepted(myString("110110000")) && !myDFA.isAccepted(myString("110110110"))
		&& !myDFA.isAccepted(myString("000")) && !myDFA.isAccepted(myString("1001001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_len_2_AND_string_that_does_not_contain_consecutive_1() {
	cout << "********** TESTING STRING_OF_LEN_2_AND_STRING_THAT_DOES_NOT_CONTAIN_CONSECUTIVE_1 ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_of_len_2, string_that_does_not_contain_consecutive_1);
	if (myDFA.isAccepted(myString("10")) && !myDFA.isAccepted(myString("11"))
		&& !myDFA.isAccepted(myString("0010")) && !myDFA.isAccepted(myString("1111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_even_0_and_1_AND_string_of_three_consecutive_zero() {
	cout << "********** TESTING STRING_OF_EVEN_0_AND_1_AND_STRING_OF_THREE_CONSECUTIVE_ZERO ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_of_even_0_and_1, string_of_three_consecutive_zero);
	if (myDFA.isAccepted(myString("000011")) && !myDFA.isAccepted(myString("0011"))
		&& !myDFA.isAccepted(myString("000")) && !myDFA.isAccepted(myString("1110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_even_len_AND_strings_of_110s() {
	cout << "********** TESTING EVEN_LEN_AND_STRINGS_OF_110s ************\n" << endl;
	DFA myDFA = DFA_Intersection(even_len, strings_of_110s);
	if (myDFA.isAccepted(myString("110110")) && !myDFA.isAccepted(myString("10"))
		&& !myDFA.isAccepted(myString("110110110")) && !myDFA.isAccepted(myString("1001010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_end_with_0_AND_string_of_even_0_and_1() {
	cout << "********** TESTING STRING_END_WITH_0_AND_STRING_OF_EVEN_0_AND_1 ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_end_with_0, string_of_even_0_and_1);
	if (myDFA.isAccepted(myString("001100")) && !myDFA.isAccepted(myString("0010"))
		&& !myDFA.isAccepted(myString("0101")) && !myDFA.isAccepted(myString("10001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_that_only_accept_101_AND_string_end_with_0() {
	cout << "********** TESTING STRING_THAT_ONLY_ACCEPT_101_AND_STRING_END_WITH_0 ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_that_accept_only_101, string_end_with_0);
	if (!myDFA.isAccepted(myString("101")) && !myDFA.isAccepted(myString("1010100"))
		&& !myDFA.isAccepted(myString("1101001101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_0s_start_and_end_with_1_AND_string_of_0s() {
	cout << "********** TESTING STRING_OF_0s_START_AND_END_WITH_1_OR_STRING_OF_0s ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_of_0s_start_and_end_with_1, string_of_0s);
	
	if (!myDFA.isAccepted(myString("100000001")) && !myDFA.isAccepted(myString("11"))
		&& !myDFA.isAccepted(myString("0000")) && !myDFA.isAccepted(myString("01001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_110s_AND_string_of_len_2() {
	cout << "********** TESTING STRINGS_OF_110s_AND_STRING_OF_LEN_2 ************\n" << endl;
	DFA myDFA = DFA_Intersection(strings_of_110s, string_of_len_2);
	if (!myDFA.isAccepted(myString("11")) && !myDFA.isAccepted(myString("110110"))
		&& !myDFA.isAccepted(myString("11101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_string_of_even_number_of_0_AND_string_of_0s_start_and_end_with_1() {
	cout << "********** TESTING STRINGS_OF_EVEN_NUMBER_OF_0_AND_STRING_OF_0s_START_AND_END_WITH_1 ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_of_even_number_of_0, string_of_0s_start_and_end_with_1);
	if (myDFA.isAccepted(myString("100001")) && !myDFA.isAccepted(myString("00100010"))
		&& !myDFA.isAccepted(myString("1000001")) && !myDFA.isAccepted(myString("1110100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_that_does_not_contain_consecutive_1_AND_even_len() {
	cout << "********** TESTING STRINGS_THAT_DOES_NOT_CONTAIN_CONSECUTIVE_1_AND_EVEN_LEN ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_that_does_not_contain_consecutive_1, even_len);
	if (myDFA.isAccepted(myString("00101000")) && !myDFA.isAccepted(myString("110110"))
		&& !myDFA.isAccepted(myString("0001010")) && !myDFA.isAccepted(myString("110010110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//TASK 18
bool DFA_Subset(const DFA& A, const DFA& B) {

	if ( returnAcceptedString(DFA_Intersection(DFA_Complement(B), A)) == myString("false"))
		return true;
	else 
		return false;
}

//TASK 19
void test_even_len_SUBSET_strings_of_0s() {
	cout << "********** TESTING EVEN_LEN_SUBSET_STRINGS_OF_0s ************\n" << endl;
	if (!DFA_Subset(even_len,string_end_with_0))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_end_with_0_SUBSET_string_of_even_number_of_0() {
	cout << "********** TESTING STRING_END_WITH_ZERO_SUBSET_STRING_OF_EVEN_NUMBER_OF_ZERO ************\n" << endl;

	if (!DFA_Subset(string_end_with_0, string_of_even_number_of_0))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_three_consecutive_zero_SUBSET_strings_of_110s() {
	cout << "********** TESTING STRING_OF_THREE_CONSECUTIVE_ZERO_SUBSET_STRINGS_OF_110s ************\n" << endl;
	if (!DFA_Subset(string_of_three_consecutive_zero, strings_of_110s ))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_len_2_SUBSET_even_len() {
	cout << "********** TESTING STRING_OF_LEN_2_SUBSET_EVEN_LEN ************\n" << endl;
	if (DFA_Subset(string_of_len_2, even_len))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_even_0_and_1_SUBSET_string_of_even_number_of_0() {
	cout << "********** TESTING STRING_OF_EVEN__NUMBER_OF_0_SUBSET_STRING_OF_EVEN_0_AND_1 ************\n" << endl;
	if (DFA_Subset(string_of_even_0_and_1, string_of_even_number_of_0))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_strings_of_110s_SUBSET_string_end_with_zero() {
	cout << "********** TESTING STRING_OF_110s_SUBSET_STRING_END_WITH_ZERO ************\n" << endl;
	if (DFA_Subset(strings_of_110s,string_end_with_0))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_end_with_0_SUBSET_string_of_0s() {
	cout << "********** TESTING STRING_END_WITH_0_SUBSET_STRING_OF_0s ************\n" << endl;
	if (!DFA_Subset(string_end_with_0, string_of_0s))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_0s_SUBSET_string_end_with_0() {
	cout << "********** TESTING STRING_OF_0s_SUBSET_STRING_END_WITH_0 ************\n" << endl;
	if (DFA_Subset(string_of_0s, string_end_with_0))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_that_accept_only_101_SUBSET_string_that_does_not_contain_consecutive_1() {
	cout << "********** TESTING STRING_THAT_ACCEPT_ONLY_101_SUBSET_STRING_THAT_DOES_NOT_CONTAIN_CONSECUTIVE_1 ************\n" << endl;
	if (DFA_Subset(string_that_accept_only_101, string_that_does_not_contain_consecutive_1))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_0s_SUBSET_string_that_does_not_contain_consecutive_1() {
	cout << "********** TESTING STRINGS_OF_0s_SUBSET_STRING_THAT_DOES_NOT_CONTAIN_CONSECUTIVE_1 ************\n" << endl;
	if (DFA_Subset(string_of_0s,string_that_does_not_contain_consecutive_1))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_that_accept_only_101_SUBSET_string_of_0s_start_and_end_with_1() {
	cout << "********** TESTING STRINGS_THAT_ACCEPT_ONLY_101_SUBSET_STRING_OF_0s_START_AND_END_WITH_1 ************\n" << endl;
	if (DFA_Subset(string_that_accept_only_101,string_of_0s_start_and_end_with_1))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_that_does_not_contain_consecutive_1_SUBSET_even_len() {
	cout << "********** TESTING STRINGS_THAT_DOES_NOT_CONTAIN_CONSECUTIVE_1_SUBSET_EVEN_LEN ************\n" << endl;
	DFA myDFA = DFA_Intersection(string_that_does_not_contain_consecutive_1, even_len);
	if (!DFA_Subset(string_that_does_not_contain_consecutive_1, even_len))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
//TASK 20
bool DFA_Equality(const DFA& A, const DFA& B) {
	return DFA_Subset(A, B) && DFA_Subset(B, A);
}

//TASK 21
void test_even_len_EQUAL_strings_of_0s() {
	if (!DFA_Equality(even_len, string_of_0s))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_end_with_0_EQUAL_string_of_even_number_of_0() {
	if (!DFA_Equality(string_end_with_0, string_of_even_number_of_0))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_three_consecutive_zero_EQUAL_strings_of_110s() {
	if (!DFA_Equality(string_of_three_consecutive_zero, strings_of_110s))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_len_2_EQUAL_even_len() {
	if (!DFA_Equality(string_of_len_2, even_len))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_even_0_and_1_EQUAL_string_of_even_number_of_0() {
	if (!DFA_Equality(string_of_even_0_and_1, string_of_even_number_of_0))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_strings_of_110s_EQUAL_string_end_with_zero() {
	if (!DFA_Equality(strings_of_110s, string_end_with_0))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_end_with_0_EQUAL_string_of_0s() {
	if (!DFA_Equality(string_end_with_0, string_of_0s))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_0s_EQUAL_string_of_0s() {
	if (DFA_Equality(string_of_0s, string_of_0s))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_even_0_and_1_EQUAL_even_len() {
	if (!DFA_Equality(string_of_even_0_and_1, even_len))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void string_that_does_not_contain_consecutive_1_EQUAL_string_that_does_not_contain_consecutive_1() {
	if (DFA_Equality(string_that_does_not_contain_consecutive_1, string_that_does_not_contain_consecutive_1))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_that_accept_only_101_EQUAL_string_that_accept_only_101() {
	if (DFA_Equality(string_that_accept_only_101, string_that_accept_only_101))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_string_of_len_2_EQUAL_Intersection_of_len_2_and_even_len() {
	if (DFA_Equality(string_of_len_2, DFA_Intersection(string_of_len_2, even_len)))
		cout << "PASSED\n";
	else
		cout << "NOT PASSED\n";
}

//TASK 31
//test for NFA_11_00
void test_NFA_11_00_1() {
	cout << "\n\nNFA_11_00 TEST 1: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("101100"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_2() {
	cout << "NFA_11_00 TEST 2: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("0110011"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

}
void test_NFA_11_00_3() {
	cout << "NFA_11_00 TEST 3: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("0111101"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_4() {
	cout << "NFA_11_00 TEST 4: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("0101"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_5() {
	cout << "NFA_11_00 TEST 5: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n ";
}
void test_NFA_11_00_6() {
	cout << "NFA_11_00 TEST 6: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("1000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_7() {
	cout << "NFA_11_00 TEST 7: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("0111100"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n ";
}
void test_NFA_11_00_8() {
	cout << "NFA_11_00 TEST 8: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("1100"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_9() {
	cout << "NFA_11_00 TEST 9: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("0011"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_10() {
	cout << "NFA_11_00 TEST 10: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("0"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_11() {
	cout << "NFA_11_00 TEST 11: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("EPSILON"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_12() {
	cout << "NFA_11_00 TEST 12: ";
	trace_tree test = NFA_Forking(NFA_11_00, myString("10000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_end_01_1() {
	cout << "\n\nNFA_end_01 TEST 1: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("01"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_2() {
	cout << "NFA_end_01 TEST 2: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("001"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_3() {
	cout << "NFA_end_01 TEST 3: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("0"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_4() {
	cout << "NFA_end_01 TEST 4: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("1"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_5() {
	cout << "NFA_end_01 TEST 5: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("EPSILON"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_6() {
	cout << "NFA_end_01 TEST 6: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("101"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_7() {
	cout << "NFA_end_01 TEST 7: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("1101"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_8() {
	cout << "NFA_end_01 TEST 8: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("10"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_9() {
	cout << "NFA_end_01 TEST 9: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("010"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_10() {
	cout << "NFA_end_01 TEST 10: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("1110"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_11() {
	cout << "NFA_end_01 TEST 11: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("0101"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_12() {
	cout << "NFA_end_01 TEST 12: ";
	trace_tree test = NFA_Forking(NFA_end_01, myString("11"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_third_0
void test_NFA_third_0_1() {
	cout << "\n\nNFA_third_0_11 TEST 1: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("11"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_2() {
	cout << "NFA_third_0_11 TEST 2: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("011"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_third_0_3() {
	cout << "NFA_third_0_11 TEST 3: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("1011"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_4() {
	cout << "NFA_third_0_11 TEST 4: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("111"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_5() {
	cout << "NFA_third_0_11 TEST 5: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("10011"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_third_0_6() {
	cout << "NFA_third_0_11 TEST 6: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("EPSILON"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_7() {
	cout << "NFA_third_0_11 TEST 7: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("1100"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_8() {
	cout << "NFA_third_0_11 TEST 8: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("0000"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_third_0_9() {
	cout << "NFA_third_0_11 TEST 9: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("1"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_10() {
	cout << "NFA_third_0_11 TEST 10: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("0"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_third_0_11() {
	cout << "NFA_third_0_11 TEST 11: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("01001"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_12() {
	cout << "NFA_third_0_11 TEST 12: ";
	trace_tree test = NFA_Forking(NFA_third_0, myString("01110"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}


//test for NFA_substring_1110
void test_NFA_substring_1110_1() {
	{
		cout << "\n\nNFA_substring_1110 TEST 1: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("1110"));
		if (test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

void test_NFA_substring_1110_2() {
	{
		cout << "NFA_substring_1110 TEST 2: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("11100"));
		if (test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

void test_NFA_substring_1110_3() {
	{
		cout << "NFA_substring_1110 TEST 3: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("01110"));
		if (test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_4() {
	{
		cout << "NFA_substring_1110 TEST 4: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("11110"));
		if (test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

void test_NFA_substring_1110_5() {
	{
		cout << "NFA_substring_1110 TEST 5: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("11101"));
		if (test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

void test_NFA_substring_1110_6() {
	{
		cout << "NFA_substring_1110 TEST 6: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("1111101"));
		if (test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

void test_NFA_substring_1110_7() {
	{
		cout << "NFA_substring_1110 TEST 7: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("1"));
		if (!test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

void test_NFA_substring_1110_8() {
	{
		cout << "NFA_substring_1110 TEST 8: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("0"));
		if (!test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

void test_NFA_substring_1110_9() {
	{
		cout << "NFA_substring_1110 TEST 9: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("EPSILON"));
		if (!test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_10() {
	{
		cout << "NFA_substring_1110 TEST 10: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("11"));
		if (!test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_11() {
	{
		cout << "NFA_substring_1110 TEST 11: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("111"));
		if (!test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

void test_NFA_substring_1110_12() {
	{
		cout << "NFA_substring_1110 TEST 12: ";
		trace_tree test = NFA_Forking(NFA_substring_1110, myString("1010"));
		if (!test.accepted)
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

//test for NFA_10s
void test_NFA_10s_1() {
	cout << "\n\nNFA_10s TEST 1: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("10"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10s_2() {
	cout << "NFA_10s TEST 2: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("1010"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10s_3() {
	cout << "NFA_10s TEST 3: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("101010"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10s_4() {
	cout << "NFA_10s TEST 4: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("0"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10s_5() {
	cout << "NFA_10s TEST 5: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("1"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10s_6() {
	cout << "NFA_10s TEST 6: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("00"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10s_7() {
	cout << "NFA_10s TEST 7: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("01"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_8() {
	cout << "NFA_10s TEST 8: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("11"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10s_9() {
	cout << "NFA_10s TEST 9: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_10() {
	cout << "NFA_10s TEST 10: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("010"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_11() {
	cout << "NFA_10s TEST 11: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("1000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10s_12() {
	cout << "NFA_10s TEST 12: ";
	trace_tree test = NFA_Forking(NFA_10s, myString("10010"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_empty_string
void test_NFA_empty_string_1() {
	cout << "\n\nNFA_empty_string TEST 1: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("EPSILON"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_2() {
	cout << "NFA_empty_string TEST 2: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("0"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_3() {
	cout << "NFA_empty_string TEST 3: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("1"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_4() {
	cout << "NFA_empty_string TEST 4: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("00"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_5() {
	cout << "NFA_empty_string TEST 5: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("01"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_empty_string_6() {
	cout << "NFA_empty_string TEST 6: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_empty_string_7() {
	cout << "NFA_empty_string TEST 7: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("010"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_8() {
	cout << "NFA_empty_string TEST 8: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("110"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_empty_string_9() {
	cout << "NFA_empty_string TEST 9: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("0000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_10() {
	cout << "NFA_empty_string TEST 10: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("01000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_11() {
	cout << "NFA_empty_string TEST 11: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("11110"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_12() {
	cout << "NFA_empty_string TEST 12: ";
	trace_tree test = NFA_Forking(NFA_empty_string, myString("100101"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_nonempty_string
void test_NFA_nonempty_string_1() {
	cout << "\n\nNFA_nonempty_string TEST 1: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("EPSILON"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_2() {
	cout << "NFA_nonempty_string TEST 2: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("0"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_3() {
	cout << "NFA_nonempty_string TEST 3: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("1"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_4() {
	cout << "NFA_nonempty_string TEST 5: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("10"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_5() {
	cout << "NFA_nonempty_string TEST 5: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("11"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_6() {
	cout << "NFA_nonempty_string TEST 6: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("100"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_7() {
	cout << "NFA_nonempty_string TEST 7: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("101"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_8() {
	cout << "NFA_nonempty_string TEST 8: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("110"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_9() {
	cout << "NFA_nonempty_string TEST 9: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("111"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_10() {
	cout << "NFA_nonempty_string TEST 10: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("1000"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_11() {
	cout << "NFA_nonempty_string TEST 11: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("1001"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_nonempty_string_12() {
	cout << "NFA_nonempty_string TEST 12: ";
	trace_tree test = NFA_Forking(NFA_nonempty_string, myString("1111"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_10
void test_NFA_10_1() {
	cout << "\n\nNFA_10 TEST 1: ";
	trace_tree test = NFA_Forking(NFA_10, myString("10"));
	if (test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_10_2() {
	cout << "NFA_10 TEST 2: ";
	trace_tree test = NFA_Forking(NFA_10, myString("1011"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_3() {
	cout << "NFA_10 TEST 3: ";
	trace_tree test = NFA_Forking(NFA_10, myString("011"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_4() {
	cout << "NFA_10 TEST 4: ";
	trace_tree test = NFA_Forking(NFA_10, myString("1010"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_5() {
	cout << "NFA_10 TEST 5: ";
	trace_tree test = NFA_Forking(NFA_10, myString("101"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_6() {
	cout << "NFA_10 TEST 6: ";
	trace_tree test = NFA_Forking(NFA_10, myString("000"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_7() {
	cout << "NFA_10 TEST 7: ";
	trace_tree test = NFA_Forking(NFA_10, myString("100"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_8() {
	cout << "NFA_10 TEST 8: ";
	trace_tree test = NFA_Forking(NFA_10, myString("11"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_9() {
	cout << "NFA_10 TEST 9: ";
	trace_tree test = NFA_Forking(NFA_10, myString("01"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_10() {
	cout << "NFA_10 TEST 10: ";
	trace_tree test = NFA_Forking(NFA_10, myString("00"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_11() {
	cout << "NFA_10 TEST 11: ";
	trace_tree test = NFA_Forking(NFA_10, myString("EPSILON"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_12() {
	cout << "NFA_10 TEST 12: ";
	trace_tree test = NFA_Forking(NFA_10, myString("1"));
	if (!test.accepted)
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_non_empty_even_len
void test_NFA_non_empty_even_len_1() {
	cout << "\n\nNFA_non_empty_even_len TEST 1: ";
	if(NFA_Backtracking(NFA_non_empty_even_len, myString("10")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_2() {
	cout << "NFA_non_empty_even_len TEST 2: ";
	if (NFA_Backtracking(NFA_non_empty_even_len, myString("1000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_3() {
	cout << "NFA_non_empty_even_len TEST 3: ";
	if (NFA_Backtracking(NFA_non_empty_even_len, myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_4() {
	cout << "NFA_non_empty_even_len TEST 4: ";
	if (NFA_Backtracking(NFA_non_empty_even_len, myString("00")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_5() {
	cout << "NFA_non_empty_even_len TEST 5: ";
	if (NFA_Backtracking(NFA_non_empty_even_len, myString("1000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_6() {
	cout << "NFA_non_empty_even_len TEST 6: ";
	if (NFA_Backtracking(NFA_non_empty_even_len, myString("1001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_7() {
	cout << "NFA_non_empty_even_len TEST 7: ";
	if (!NFA_Backtracking(NFA_non_empty_even_len, myString("EPSILON")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_8() {
	cout << "NFA_non_empty_even_len TEST 8: ";
	if (!NFA_Backtracking(NFA_non_empty_even_len, myString("100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_9() {
	cout << "NFA_non_empty_even_len TEST 9: ";
	if (!NFA_Backtracking(NFA_non_empty_even_len, myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_10() {
	cout << "NFA_non_empty_even_len TEST 10: ";
	if (!NFA_Backtracking(NFA_non_empty_even_len, myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_11() {
	cout << "NFA_non_empty_even_len TEST 11: ";
	if (!NFA_Backtracking(NFA_non_empty_even_len, myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_12() {
	cout << "NFA_non_empty_even_len TEST 12: ";
	if (!NFA_Backtracking(NFA_non_empty_even_len, myString("01011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}


//test for NFA_0s
void test_NFA_0s_1() {
	cout << "\n\nNFA_0s TEST 1: ";
	if (NFA_Backtracking(NFA_0s, myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_2() {
	cout << "NFA_0s TEST 2: ";
	if (NFA_Backtracking(NFA_0s, myString("00000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_3() {
	cout << "NFA_0s TEST 3: ";
	if (NFA_Backtracking(NFA_0s, myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_4() {
	cout << "NFA_0s TEST 4: ";
	if (NFA_Backtracking(NFA_0s, myString("0000000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_5() {
	cout << "NFA_0s TEST 5: ";
	if (!NFA_Backtracking(NFA_0s, myString("01")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_6() {
	cout << "NFA_0s TEST 6: ";
	if (!NFA_Backtracking(NFA_0s, myString("010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_7() {
	cout << "NFA_0s TEST 7: ";
	if (!NFA_Backtracking(NFA_0s, myString("01110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_8(){
	cout << "NFA_0s TEST 8: ";
	if (!NFA_Backtracking(NFA_0s, myString("111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_9() {
	cout << "NFA_0s TEST 9: ";
	if (!NFA_Backtracking(NFA_0s, myString("1111111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_10() {
	cout << "NFA_0s TEST 10: ";
	if (!NFA_Backtracking(NFA_0s, myString("01010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_11() {
	cout << "NFA_0s TEST 11: ";
	if (!NFA_Backtracking(NFA_0s, myString("000111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_12() {
	
		cout << "NFA_0s TEST 12: ";
		if (!NFA_Backtracking(NFA_0s, myString("1111111")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	
}

//test for NFA_0s_or_01s
void test_NFA_0s_or_01s_1() {
	cout << "\n\nNFA_0s_or_01s TEST 1: ";
	if (NFA_Backtracking(NFA_0s_or_01s, myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_0s_or_01s_2() {
	cout << "NFA_0s_or_01s TEST 2: ";
	if (NFA_Backtracking(NFA_0s_or_01s, myString("0101010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_3() {
	cout << "NFA_0s_or_01s TEST 3: ";
	if (NFA_Backtracking(NFA_0s_or_01s, myString("00000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_4() {
	cout << "\n\nNFA_0s_or_01s TEST 4: ";
	if (NFA_Backtracking(NFA_0s_or_01s, myString("0101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_5() {
	cout << "NFA_0s_or_01s TEST 5: ";
	if (NFA_Backtracking(NFA_0s_or_01s, myString("00000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_6() {
	cout << "NFA_0s_or_01s TEST 6: ";
	if (NFA_Backtracking(NFA_0s_or_01s, myString("101010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_0s_or_01s_7() {
	cout << "NFA_0s_or_01s TEST 7: ";
	if (!NFA_Backtracking(NFA_0s_or_01s, myString("10000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_0s_or_01s_8() {
	cout << "NFA_0s_or_01s TEST 8: ";
	if (!NFA_Backtracking(NFA_0s_or_01s, myString("10100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_0s_or_01s_9() {
	cout << "NFA_0s_or_01s TEST 9: ";
	if (!NFA_Backtracking(NFA_0s_or_01s, myString("10000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_0s_or_01s_10() {
	cout << "NFA_0s_or_01s TEST 10: ";
	if (!NFA_Backtracking(NFA_0s_or_01s, myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_0s_or_01s_11() {
	cout << "NFA_0s_or_01s TEST 11: ";
	if (!NFA_Backtracking(NFA_0s_or_01s, myString("11000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_12() {
	cout << "NFA_0s_or_01s TEST 12: ";
	if (!NFA_Backtracking(NFA_0s_or_01s, myString("100001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}


//test for NFA_1s_or_end_0
void test_NFA_1s_or_end_0_1() {
	cout << "\n\nNFA_1s_or_end_0 TEST 1: ";
	if (NFA_Backtracking(NFA_1s_or_end_0, myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_2() {
	cout << "NFA_1s_or_end_0 TEST 2: ";
	if (NFA_Backtracking(NFA_1s_or_end_0, myString("110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_3() {
	cout << "NFA_1s_or_end_0 TEST 2: ";
	if (NFA_Backtracking(NFA_1s_or_end_0, myString("11000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_4() {
	cout << "NFA_1s_or_end_0 TEST 4: ";
	if (NFA_Backtracking(NFA_1s_or_end_0, myString("111111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_5() {
	cout << "NFA_1s_or_end_0 TEST 5: ";
	if (NFA_Backtracking(NFA_1s_or_end_0, myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

void test_NFA_1s_or_end_0_6() {
	cout << "NFA_1s_or_end_0 TEST 6: ";
	if (NFA_Backtracking(NFA_1s_or_end_0, myString("10")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_7() {
	cout << "NFA_1s_or_end_0 TEST 7: ";
	if (!NFA_Backtracking(NFA_1s_or_end_0, myString("0101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_8() {
	cout << "NFA_1s_or_end_0 TEST 8: ";
	if (!NFA_Backtracking(NFA_1s_or_end_0, myString("100001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_9() {
	cout << "NFA_1s_or_end_0 TEST 9: ";
	if (!NFA_Backtracking(NFA_1s_or_end_0, myString("0101001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_10() {
	cout << "NFA_1s_or_end_0 TEST 10: ";
	if (!NFA_Backtracking(NFA_1s_or_end_0, myString("11101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_11() {
	cout << "NFA_1s_or_end_0 TEST 11: ";
	if (!NFA_Backtracking(NFA_1s_or_end_0, myString("0001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_12() {
	cout << "NFA_1s_or_end_0 TEST 12: ";
	if (!NFA_Backtracking(NFA_1s_or_end_0, myString("1101001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
//TASK 32
bool NFA_Backtracking(NFA obj, myString s) {

	return NFA_search(obj, obj.getAcceptingState(), s, obj.getStartState());
}
bool NFA_search(NFA obj, vector<string> acceptedStates, myString w, string currentState)
{
	map<Pair, set<string>> T = obj.getTransition();
	string a = w.getCharacterAt(0);
	set<string> nextState = obj.myTransition(currentState, a);
	list <pair<string, trace_tree*>> branch;
	bool v = false;
	if (nextState.empty())
		return false;
	if (w.getStringLen() == 0) {
		for (auto &each : nextState) {
			if (find(acceptedStates.begin(), acceptedStates.end(), each) != acceptedStates.end())
				return true;
			return false;
		}
		w.pop_front();
		for (auto &p1 : nextState)
			if (NFA_search(obj, acceptedStates, w, p1))
				return NFA_search(obj, acceptedStates, w, p1);
	}
}

