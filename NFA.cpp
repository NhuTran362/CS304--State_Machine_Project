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

// TASK 29
//trace tree for NFA_11_00
//tree 1: string "1100"
static trace_tree NFA_11_00_tree1_9(true, "4", { {"EPSILON",nullptr} });
static trace_tree NFA_11_00_tree1_8(true, "3", { {"0",&NFA_11_00_tree1_9} });
static trace_tree NFA_11_00_tree1_7(true, "2", { {"0",&NFA_11_00_tree1_8} });
static trace_tree NFA_11_00_tree1_6(false, "1", { {"0",nullptr} });
static trace_tree NFA_11_00_tree1_5(false, "0", { {"EPSILON",nullptr} });
static trace_tree NFA_11_00_tree1_4( false, "1",{{"0",&NFA_11_00_tree1_5}});
static trace_tree NFA_11_00_tree1_3(false, "0", { {"0",&NFA_11_00_tree1_4} });
static trace_tree NFA_11_00_tree1_2(true, "1", { {"1",&NFA_11_00_tree1_7} });
static trace_tree NFA_11_00_tree1_1(false, "0", { {"1",&NFA_11_00_tree1_3}, {"1",&NFA_11_00_tree1_6} });
static trace_tree NFA_11_00_tree1_0(true, "0", { {"1",&NFA_11_00_tree1_1}, {"1",&NFA_11_00_tree1_2} });

//tree2: string "1"
trace_tree NFA_11_00_tree2_2( false, "1", {{"EPSILON", nullptr}} );
trace_tree NFA_11_00_tree2_1(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_11_00_tree2_0( false, "0", {{"1",&NFA_11_00_tree2_1},{"1",&NFA_11_00_tree2_2} });



//tree3: string "0"
trace_tree NFA_11_00_tree3_1(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_11_00_tree3_0( false, "0", {{"1",&NFA_11_00_tree3_1}} );


//tree4: string "10"
trace_tree NFA_11_00_tree4_3(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_11_00_tree4_2(false, "1", { {"0", nullptr} });
trace_tree NFA_11_00_tree4_1(false, "0", { {"0", &NFA_11_00_tree4_3} });
trace_tree NFA_11_00_tree4_0(false, "0", { {"1",&NFA_11_00_tree4_1},{"1",&NFA_11_00_tree4_2} });

//tree5: string "11"
trace_tree NFA_11_00_tree5_5(false, "2", { {"EPSILON", nullptr} });
trace_tree NFA_11_00_tree5_4(false, "1", { {"EPSILON", nullptr} });
trace_tree NFA_11_00_tree5_3(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_11_00_tree5_2(false, "1", { {"1", &NFA_11_00_tree5_5} });
trace_tree NFA_11_00_tree5_1(false, "0", { {"1", &NFA_11_00_tree5_3}, {"1", &NFA_11_00_tree5_4} });
trace_tree NFA_11_00_tree5_0( false, "0", {{"1",&NFA_11_00_tree5_1},{"1",&NFA_11_00_tree5_2}} );
//tree6: string "EPSILON"
trace_tree NFA_11_00_tree6_0( false,"0",{{"EPSILON",nullptr}} );


//trace_tree for NFA_end_01

//tree1: "EPSILON"
trace_tree NFA_end_01_tree1_0( false,"0",{{"EPSILON",nullptr}} );

//tree2: "0"
trace_tree NFA_end_01_tree2_2(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_end_01_tree2_1(false, "0", { {"EPSILON",nullptr} });
trace_tree NFA_end_01_tree2_0( false,"0",{{"0",&NFA_end_01_tree2_1}, {"0",&NFA_end_01_tree2_2}} );


//tree3: "1"
trace_tree NFA_end_01_tree3_1(false, "0", { {"EPSILON",nullptr} });
trace_tree NFA_end_01_tree3_0( false,"0",{{"1",&NFA_end_01_tree3_1}} );

//tree4: "10"
trace_tree NFA_end_01_tree4_2(false, "0", { {"EPSILON",nullptr} });
trace_tree NFA_end_01_tree4_3(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_end_01_tree4_1(false, "0", { {"0",&NFA_end_01_tree4_2}, {"0",&NFA_end_01_tree4_3} });
trace_tree NFA_end_01_tree4_0( false,"0",{{"1",&NFA_end_01_tree4_1}} );


//tree5: "00"
trace_tree NFA_end_01_tree5_2(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_end_01_tree5_3(false, "0", { {"EPSILON",nullptr} });
trace_tree NFA_end_01_tree5_4(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_end_01_tree5_1(false, "0", { {"0",&NFA_end_01_tree5_3}, {"0",&NFA_end_01_tree5_4} });
trace_tree NFA_end_01_tree5_0( false,"0",{{"0",&NFA_end_01_tree5_1}, {"0",&NFA_end_01_tree5_2}} );


//tree6: "01"
trace_tree NFA_end_01_tree6_3( false,"0",{{"EPSILON",nullptr}} );
trace_tree NFA_end_01_tree6_4( true,"2",{{"EPSILON",nullptr}} );
trace_tree NFA_end_01_tree6_2( true,"1",{{"1",&NFA_end_01_tree6_4}} );
trace_tree NFA_end_01_tree6_1( false,"0",{{"1",&NFA_end_01_tree5_3}} );
trace_tree NFA_end_01_tree6_0( true,"0",{{"0",&NFA_end_01_tree6_1}, {"0",&NFA_end_01_tree6_2}} );

//trace_tree for NFA_third_0

//tree1: EPSILON
trace_tree NFA_third_0_tree1_0( false, "0", {{"EPSILON",nullptr}} );

// tree2: "0"
trace_tree NFA_third_0_tree2_1(false, "0", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree2_2(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree2_0( false,"0",{{"0",&NFA_third_0_tree2_1}, {"0",&NFA_third_0_tree2_2}} );


// tree3: "1"
trace_tree NFA_third_0_tree3_1( false,"0",{{"EPSILON",nullptr}} );
trace_tree NFA_third_0_tree3_0( false,"0",{{"1",&NFA_third_0_tree3_1}} );


// tree4: "00"
trace_tree NFA_third_0_tree4_3( false,"0",{{"EPSILON",nullptr}} );
trace_tree NFA_third_0_tree4_4( false,"1",{{"EPSILON",nullptr}} );
trace_tree NFA_third_0_tree4_5( false,"2",{{"EPSILON",nullptr}} );
trace_tree NFA_third_0_tree4_2( false,"0",{{"0",&NFA_third_0_tree4_5}} );
trace_tree NFA_third_0_tree4_1( false,"0",{{"0",&NFA_third_0_tree4_3}, {"0",&NFA_third_0_tree4_4}} );
trace_tree NFA_third_0_tree4_0( false,"0",{{"0",&NFA_third_0_tree4_1}, {"0",&NFA_third_0_tree4_2}} );


//tree5: "001"
trace_tree NFA_third_0_tree5_6(false, "0", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree5_7(false, "2", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree5_8(true, "3", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree5_5(true, "2", { {"1",&NFA_third_0_tree5_8} });
trace_tree NFA_third_0_tree5_4(false, "1", { {"1",&NFA_third_0_tree5_7} });
trace_tree NFA_third_0_tree5_3(false, "0", { {"1",&NFA_third_0_tree5_6} });
trace_tree NFA_third_0_tree5_2(true, "0", { {"0",&NFA_third_0_tree5_5} });
trace_tree NFA_third_0_tree5_1(false, "0", { {"0",&NFA_third_0_tree5_3}, {"0",&NFA_third_0_tree5_4} });
trace_tree NFA_third_0_tree5_0( true,"0",{{"0",&NFA_third_0_tree5_1}, {"0",&NFA_third_0_tree5_2}} );

//tree6: "000"
trace_tree NFA_third_0_tree6_6(false, "0", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree6_7(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree6_8(false, "2", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree6_9(true, "3", { {"EPSILON",nullptr} });
trace_tree NFA_third_0_tree6_5(true, "2", { {"0",&NFA_third_0_tree6_9} });
trace_tree NFA_third_0_tree6_4(false, "1", { {"0",&NFA_third_0_tree6_8} });
trace_tree NFA_third_0_tree6_3(false, "0", { {"0",&NFA_third_0_tree6_6}, {"0",&NFA_third_0_tree6_7} });
trace_tree NFA_third_0_tree6_2(true, "0", { {"0",&NFA_third_0_tree6_5} });
trace_tree NFA_third_0_tree6_1(false, "0", { {"0",&NFA_third_0_tree6_3}, {"0",&NFA_third_0_tree6_4} });
trace_tree NFA_third_0_tree6_0( true,"0",{{"0",&NFA_third_0_tree6_1}, {"0",&NFA_third_0_tree6_2}} );

// trace_tree for NFA_substring_1110
//tree1: EPSILON
trace_tree NFA_substring_1110_tree1_0( false,"0",{{"EPSILON",nullptr}} );

//tree2: "1"
trace_tree NFA_substring_1110_tree2_1(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree2_2(false, "1", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree2_0( false, "0", {{"1",&NFA_substring_1110_tree2_1},{"1",&NFA_substring_1110_tree2_2}} );


// tree3: "11"
trace_tree NFA_substring_1110_tree3_3(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree3_4(false, "1", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree3_5(false, "2", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree3_2(false, "1", { {"1", &NFA_substring_1110_tree3_5} });
trace_tree NFA_substring_1110_tree3_1(false, "0", { {"1",&NFA_substring_1110_tree3_3},{"1",&NFA_substring_1110_tree3_4} });
trace_tree NFA_substring_1110_tree3_0( false, "0", {{"1",&NFA_substring_1110_tree3_1},{"1",&NFA_substring_1110_tree3_2}} );



//tree4: "111"
trace_tree NFA_substring_1110_tree4_6(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree4_7(false, "1", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree4_8(false, "2", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree4_9(false, "3", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree4_5(false, "2", { {"1", &NFA_substring_1110_tree4_9} });
trace_tree NFA_substring_1110_tree4_4(false, "1", { {"1", &NFA_substring_1110_tree4_8} });
trace_tree NFA_substring_1110_tree4_3(false, "0", { {"1",&NFA_substring_1110_tree4_6},{"1",&NFA_substring_1110_tree4_7} });
trace_tree NFA_substring_1110_tree4_2(false, "1", { {"1", &NFA_substring_1110_tree4_5} });
trace_tree NFA_substring_1110_tree4_1(false, "0", { {"1",&NFA_substring_1110_tree4_3},{"1",&NFA_substring_1110_tree4_4} });
trace_tree NFA_substring_1110_tree4_0( false, "0", {{"1",&NFA_substring_1110_tree4_1},{"1",&NFA_substring_1110_tree4_2}} );



//tree5: "1110"
trace_tree NFA_substring_1110_tree5_10(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree5_11(true, "4", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree5_7(false, "1", { {"0", nullptr} });
trace_tree NFA_substring_1110_tree5_8(false, "2", { {"0", nullptr} });
trace_tree NFA_substring_1110_tree5_9(true, "3", { {"0", &NFA_substring_1110_tree5_11} });
trace_tree NFA_substring_1110_tree5_6(false, "0", { {"0", &NFA_substring_1110_tree5_10} });
trace_tree NFA_substring_1110_tree5_5(true, "2", { {"1", &NFA_substring_1110_tree5_9} });
trace_tree NFA_substring_1110_tree5_4(false, "1", { {"1", &NFA_substring_1110_tree5_8} });
trace_tree NFA_substring_1110_tree5_3(false, "0", { {"1",&NFA_substring_1110_tree5_6},{"1",&NFA_substring_1110_tree5_7} });
trace_tree NFA_substring_1110_tree5_2(true, "1", { {"1", &NFA_substring_1110_tree5_5} });
trace_tree NFA_substring_1110_tree5_1(false, "0", { {"1",&NFA_substring_1110_tree5_3},{"1",&NFA_substring_1110_tree5_4} });
trace_tree NFA_substring_1110_tree5_0( true, "0", {{"1",&NFA_substring_1110_tree5_1},{"1",&NFA_substring_1110_tree5_2}} );


//trace6: "0"
trace_tree NFA_substring_1110_tree6_1(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_substring_1110_tree6_0( false,"0",{{"0",&NFA_substring_1110_tree6_1}} );


//trace_tree for NFA_10s
//tree1: EPSILON
trace_tree NFA_10s_tree1_1(false, "2", { {"EPSILON", nullptr} });
trace_tree NFA_10s_tree1_0( false,"0",{  {"EPSILON", &NFA_10s_tree1_1}} );

//tree2: "0"
trace_tree NFA_10s_tree2_1(false, "2", { {"0", nullptr} });
trace_tree NFA_10s_tree2_0( false,"0",{{"0",nullptr}, {"EPSILON", &NFA_10s_tree2_1}} );

//tree3: "1"
trace_tree NFA_10s_tree3_1(false, "1", { {"EPSILON", nullptr} });
trace_tree NFA_10s_tree3_2(false, "2", { {"1", nullptr} });
trace_tree NFA_10s_tree3_0( false,"0",{{"1", &NFA_10s_tree3_1}, {"EPSILON", &NFA_10s_tree3_2}} );


//tree4: "10"
trace_tree NFA_10s_tree4_2(false, "2", { {"1", nullptr} });
trace_tree NFA_10s_tree4_3(false, "0", { {"EPSILON", nullptr} });
trace_tree NFA_10s_tree4_4( true,"2",{{"EPSILON", nullptr}} );
trace_tree NFA_10s_tree4_1(true, "1", { {"0", &NFA_10s_tree4_3}, {"0", &NFA_10s_tree4_4} });
trace_tree NFA_10s_tree4_0( true,"0",{{"1", &NFA_10s_tree4_1}, {"EPSILON", &NFA_10s_tree4_2}} );


//tree5: "11"
trace_tree NFA_10s_tree5_2(false, "2", { {"1", nullptr} });
trace_tree NFA_10s_tree5_3(false, "2", { {"EPSILON", nullptr} });
trace_tree NFA_10s_tree5_1(false, "1", { {"1", &NFA_10s_tree5_3} });
trace_tree NFA_10s_tree5_0( false,"0",{{"1", &NFA_10s_tree5_1}, {"EPSILON", &NFA_10s_tree5_2}} );


//tree6: "101"
trace_tree NFA_10s_tree6_4(false, "2", { {"1", nullptr} });
trace_tree NFA_10s_tree6_5(false, "1", { {"EPSILON", nullptr} });
trace_tree NFA_10s_tree6_6(false, "2", { {"1", nullptr} });
trace_tree NFA_10s_tree6_2(false, "2", { {"1", nullptr} });
trace_tree NFA_10s_tree6_3(false, "0", { {"EPSILON", &NFA_10s_tree6_6}, {"1", &NFA_10s_tree6_5} });
trace_tree NFA_10s_tree6_1(false, "1", { {"0", &NFA_10s_tree6_3}, {"0", &NFA_10s_tree6_4} });
trace_tree NFA_10s_tree6_0( false,"0",{{"1", &NFA_10s_tree6_1}, {"EPSILON", &NFA_10s_tree6_2}} );

//trace_tree for NFA_empty_string
//tree1: EPSILON
trace_tree NFA_empty_string_tree1_1(true, "1", { {"EPSILON",nullptr} });
trace_tree NFA_empty_string_tree1_0( true, "0",{ {"EPSILON",&NFA_empty_string_tree1_1}} );

//tree2: "0"
trace_tree NFA_empty_string_tree2_1(false, "1", { {"0",nullptr} });
trace_tree NFA_empty_string_tree2_0( false, "0",{{"0",nullptr}, {"EPSILON", &NFA_empty_string_tree2_1}} );

//tree3: "1"
trace_tree NFA_empty_string_tree3_1(false, "1", { {"1",nullptr} });
trace_tree NFA_empty_string_tree3_0( false, "0",{{"1",nullptr}, {"EPSILON", &NFA_empty_string_tree3_1}} );

//tree4: "10"
trace_tree NFA_empty_string_tree4_1(false, "1", { {"1",nullptr} });
trace_tree NFA_empty_string_tree4_0( false, "0",{{"1",nullptr}, {"EPSILON", &NFA_empty_string_tree4_1}} );

//tree5: "100"
trace_tree NFA_empty_string_tree5_1(false, "1", { {"1",nullptr} });
trace_tree NFA_empty_string_tree5_0( false, "0",{{"1",nullptr}, {"EPSILON", &NFA_empty_string_tree5_1}} );

//tree6: "00"
trace_tree NFA_empty_string_tree6_1(false, "1", { {"0",nullptr} });
trace_tree NFA_empty_string_tree6_0( false, "0",{{"0",nullptr}, {"EPSILON", &NFA_empty_string_tree6_1}} );

// trace_tree for NFA_non_empty_string
//tree1: EPSILON
trace_tree NFA_non_empty_string_tree1_1(false, "2", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_string_tree1_0( false, "0",{{"EPSILON",&NFA_non_empty_string_tree1_1}} );

//tree2: "0"
trace_tree NFA_non_empty_string_tree2_1(true, "1", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_string_tree2_2(false, "2", { {"0",nullptr} });
trace_tree NFA_non_empty_string_tree2_0( true, "0",{{"0",&NFA_non_empty_string_tree2_1},{"EPSILON",&NFA_non_empty_string_tree2_2}} );


// tree3: "1"
trace_tree NFA_non_empty_string_tree3_1(true, "1", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_string_tree3_2(false, "2", { {"1",nullptr} });
trace_tree NFA_non_empty_string_tree3_0( true, "0",{{"1",&NFA_non_empty_string_tree3_1},{"EPSILON",&NFA_non_empty_string_tree3_2}} );


// tree4: "00"
trace_tree NFA_non_empty_string_tree4_2(false, "2", { {"0",nullptr} });
trace_tree NFA_non_empty_string_tree4_3(true, "1", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_string_tree4_1(true, "1", { {"0",&NFA_non_empty_string_tree4_3} });
trace_tree NFA_non_empty_string_tree4_0( true, "0",{{"0",&NFA_non_empty_string_tree4_1},{"EPSILON",&NFA_non_empty_string_tree4_2}} );


//tree5: "11"
trace_tree NFA_non_empty_string_tree5_2(false, "2", { {"1",nullptr} });
trace_tree NFA_non_empty_string_tree5_3(true, "1", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_string_tree5_1(true, "1", { {"1",&NFA_non_empty_string_tree5_3} });
trace_tree NFA_non_empty_string_tree5_0( true, "0",{{"1",&NFA_non_empty_string_tree5_1},{"EPSILON",&NFA_non_empty_string_tree5_2}} );


//tree6: "10"
trace_tree NFA_non_empty_string_tree6_2(false, "2", { {"1",nullptr} });
trace_tree NFA_non_empty_string_tree6_3(true, "1", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_string_tree6_1(true, "1", { {"0",&NFA_non_empty_string_tree4_3} });
trace_tree NFA_non_empty_string_tree6_0( true, "0",{{"1",&NFA_non_empty_string_tree4_1},{"EPSILON",&NFA_non_empty_string_tree4_2}} );

//tree_trace for NFA_10
//tree1: EPSILON
trace_tree NFA_10_tree1_0( false,"0",{{"EPSILON",nullptr}} );

//tree2: "0"
trace_tree NFA_10_tree2_0( false,"0", {{"0",nullptr}} );

//tree3: "1"
trace_tree NFA_10_tree3_1(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_10_tree3_0( false, "0",{{"1",&NFA_10_tree3_1}} );


//tree4: "10"
trace_tree NFA_10_tree4_2(true, "2", { {"EPSILON",nullptr} });
trace_tree NFA_10_tree4_1(true, "1", { {"0",&NFA_10_tree4_2} });
trace_tree NFA_10_tree4_0( true, "0",{{"1",&NFA_10_tree4_1}} );

//tree5: "11"
trace_tree NFA_10_tree5_1(false, "1", { {"1",nullptr} });
trace_tree NFA_10_tree5_0( false, "0",{{"1",&NFA_10_tree5_1}} );

//tree6: "100"
trace_tree NFA_10_tree6_2(false, "2", { {"0",nullptr} });
trace_tree NFA_10_tree6_1(false, "1", { {"0",&NFA_10_tree6_2} });
trace_tree NFA_10_tree6_0( false, "0",{{"1",&NFA_10_tree6_1}} );

//trace_tree for NFA_non_empty_even_len
// tree1: EPSILON
trace_tree NFA_non_empty_even_len_tree1_1(false, "3", { {"EPSILOn",nullptr} });
trace_tree NFA_non_empty_even_len_tree1_0( false,"0", {{"EPSILON",&NFA_non_empty_even_len_tree1_1}} );

//tree2: "0"
trace_tree NFA_non_empty_even_len_tree2_1(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_even_len_tree2_2(false, "3", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_even_len_tree2_0( false, "0",{{"EPSILON",&NFA_non_empty_even_len_tree2_2}, {"0", &NFA_non_empty_even_len_tree2_1}} );

//tree3: "1"
trace_tree NFA_non_empty_even_len_tree3_1(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_even_len_tree3_2(false, "3", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_even_len_tree3_0( false, "0",{{"1", &NFA_non_empty_even_len_tree3_1}, {"1", &NFA_non_empty_even_len_tree3_1}} );

//tree4: "00"
trace_tree NFA_non_empty_even_len_tree4_2(false, "3", { {"0",nullptr} });
trace_tree NFA_non_empty_even_len_tree4_3(true, "2", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_even_len_tree4_1(true, "1", { {"0",&NFA_non_empty_even_len_tree4_3} });
trace_tree NFA_non_empty_even_len_tree4_0( true, "0",{{"EPSILON",&NFA_non_empty_even_len_tree4_2}, {"0", &NFA_non_empty_even_len_tree4_1}} );


//tree5: "11"
trace_tree NFA_non_empty_even_len_tree5_2(false, "3", { {"1",nullptr} });
trace_tree NFA_non_empty_even_len_tree5_3(true, "2", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_even_len_tree5_1(true, "1", { {"1",&NFA_non_empty_even_len_tree5_3} });
trace_tree NFA_non_empty_even_len_tree5_0( true, "0",{{"EPSILON",&NFA_non_empty_even_len_tree5_2}, {"1", &NFA_non_empty_even_len_tree5_1}} );

//tree6: "000"
trace_tree NFA_non_empty_even_len_tree6_4(false, "1", { {"EPSILON",nullptr} });
trace_tree NFA_non_empty_even_len_tree6_2(false, "3", { {"0",nullptr} });
trace_tree NFA_non_empty_even_len_tree6_3(false, "2", { {"0",&NFA_non_empty_even_len_tree6_4} });
trace_tree NFA_non_empty_even_len_tree6_1(false, "1", { {"0",&NFA_non_empty_even_len_tree6_3} });
trace_tree NFA_non_empty_even_len_tree6_0( false, "0",{{"EPSILON",&NFA_non_empty_even_len_tree6_2}, {"0", &NFA_non_empty_even_len_tree6_1}} );

// trace_tree for NFA_0s
//tree1: EPSILON
trace_tree NFA_0s_tree1_1(false, "2", { {"EPSILON", nullptr} });
trace_tree NFA_0s_tree1_0( false,"0",{{"EPSILON", &NFA_0s_tree1_1}} );

//tree2: "0"
trace_tree NFA_0s_tree2_2(false, "1", { {"0", nullptr} });
trace_tree NFA_0s_tree2_1(true, "1", { {"EPSILON", nullptr} });
trace_tree NFA_0s_tree2_0(true, "0", { {"0", &NFA_0s_tree2_1}, {"EPSILON",&NFA_0s_tree2_2} });


//tree3: "1"
trace_tree NFA_0s_tree3_1(false, "2", { {"1", nullptr} });
trace_tree NFA_0s_tree3_0(false, "0", { {"EPSILON",&NFA_0s_tree3_1}, {"1", nullptr} });

//tree4: "00"
trace_tree NFA_0s_tree4_3(false, "2", { {"0",nullptr } });
trace_tree NFA_0s_tree4_2(true, "1", { {"EPSILON",nullptr } });
trace_tree NFA_0s_tree4_1(true, "1", { {"0", &NFA_0s_tree4_2} });
trace_tree NFA_0s_tree4_0(true, "0", { {"0", &NFA_0s_tree4_1}, {"EPSILON", &NFA_0s_tree4_3 } });


//tree5: "01"
trace_tree NFA_0s_tree5_2(false, "2", { {"0", nullptr} });
trace_tree NFA_0s_tree5_1(true, "1", { {"1", nullptr} });
trace_tree NFA_0s_tree5_0(true, "0", { {"0", &NFA_0s_tree5_1}, {"EPSILON", &NFA_0s_tree5_2 } });


//tree6: "000"
trace_tree NFA_0s_tree6_4(true, "1", { {"EPSILON",nullptr } });
trace_tree NFA_0s_tree6_3(false, "2", { {"0",nullptr } });
trace_tree NFA_0s_tree6_2(true, "1", { {"0",&NFA_0s_tree6_4 } });
trace_tree NFA_0s_tree6_1(true, "1", { {"0", &NFA_0s_tree6_2} });
trace_tree NFA_0s_tree6_0(true, "0", { {"0", &NFA_0s_tree6_1}, {"EPSILON", &NFA_0s_tree6_3 } });



//trace_tree for NFA_0s_or_01s
//tree1: EPSILON
trace_tree NFA_0s_or_01s_tree1_0(false, "0", { {"EPSILON",nullptr} });

//tree2: "0"
trace_tree NFA_0s_or_01s_tree2_2(false, "2", { {"EPSILON",nullptr } });
trace_tree NFA_0s_or_01s_tree2_1(true, "1", { {"EPSILON",nullptr} });
trace_tree NFA_0s_or_01s_tree2_0(true, "0", { {"0",&NFA_0s_or_01s_tree2_1 }, { "0", &NFA_0s_or_01s_tree2_2 } });

// tree3: "1"
trace_tree NFA_0s_or_01s_tree3_0(false, "0", { {"1",nullptr} });

//tree4: "01"
trace_tree NFA_0s_or_01s_tree4_3(true, "3", { {"EPSILON",nullptr } });
trace_tree NFA_0s_or_01s_tree4_2(true, "2", { {"1",&NFA_0s_or_01s_tree4_3 } });
trace_tree NFA_0s_or_01s_tree4_1(false, "1", { {"1",nullptr} });
trace_tree NFA_0s_or_01s_tree4_0(true, "0", { {"0",&NFA_0s_or_01s_tree4_1 }, { "0", &NFA_0s_or_01s_tree4_2 } });

//tree5: "00"
trace_tree NFA_0s_or_01s_tree5_3(true, "1", { {"EPSILON",nullptr } });
trace_tree NFA_0s_or_01s_tree5_2(false, "2", { {"0",nullptr } });
trace_tree NFA_0s_or_01s_tree5_1(true, "1", { {"0",&NFA_0s_or_01s_tree5_3} });
trace_tree NFA_0s_or_01s_tree5_0(true, "0", { {"0",&NFA_0s_or_01s_tree5_1 }, { "0", &NFA_0s_or_01s_tree5_2 } });

//tree6: "010"
trace_tree NFA_0s_or_01s_tree6_4(false, "2", { {"EPSILON",nullptr } });
trace_tree NFA_0s_or_01s_tree6_3(false, "3", { {"0",&NFA_0s_or_01s_tree6_4 } });
trace_tree NFA_0s_or_01s_tree6_2(false, "2", { {"1",&NFA_0s_or_01s_tree6_3 } });
trace_tree NFA_0s_or_01s_tree6_1(false, "1", { {"1",nullptr} });
trace_tree NFA_0s_or_01s_tree6_0(false, "0", { {"0",&NFA_0s_or_01s_tree6_1 }, { "0", &NFA_0s_or_01s_tree6_2 } });

// tree_trace for NFA_1s_or_end_0
//tree1: EPSILON
trace_tree NFA_1s_or_end_0_tree1_2(false, "2", { {"EPSILON",nullptr } });
trace_tree NFA_1s_or_end_0_tree1_1(true, "1", { {"EPSILON",nullptr} });
trace_tree NFA_1s_or_end_0_tree1_0(true, "0", { {"EPSILON",&NFA_1s_or_end_0_tree1_1 }, { "EPSILON", &NFA_1s_or_end_0_tree1_2 }});

//tree2: "1"
trace_tree NFA_1s_or_end_0_tree2_4(false, "2", { {"EPSILON",nullptr } });
trace_tree NFA_1s_or_end_0_tree2_3(true, "1", { {"EPSILON",nullptr } });
trace_tree NFA_1s_or_end_0_tree2_2(false, "2", { {"1",&NFA_1s_or_end_0_tree2_4 } });
trace_tree NFA_1s_or_end_0_tree2_1(true, "1", { {"1",&NFA_1s_or_end_0_tree2_3} });
trace_tree NFA_1s_or_end_0_tree2_0(true, "0", { {"EPSILON",&NFA_1s_or_end_0_tree2_1 }, { "EPSILON", &NFA_1s_or_end_0_tree2_2 } });

//tree3: "0"
trace_tree NFA_1s_or_end_0_tree3_4(false, "2", { {"EPSILON",nullptr } });
trace_tree NFA_1s_or_end_0_tree3_3(true, "3", { {"EPSILON",nullptr } });
trace_tree NFA_1s_or_end_0_tree3_2(false, "2", { {"0",&NFA_1s_or_end_0_tree3_3 }, {"0",&NFA_1s_or_end_0_tree3_4 } });
trace_tree NFA_1s_or_end_0_tree3_1(true, "1", { {"0",nullptr} });
trace_tree NFA_1s_or_end_0_tree3_0(true, "0", { {"EPSILON",&NFA_1s_or_end_0_tree3_1 }, { "EPSILON", &NFA_1s_or_end_0_tree3_2 } });

//tree4: "01
trace_tree NFA_1s_or_end_0_tree4_5(false, "2", { {"EPSILON",nullptr } });
trace_tree NFA_1s_or_end_0_tree4_4(false, "2", { {"1",&NFA_1s_or_end_0_tree4_5 } });
trace_tree NFA_1s_or_end_0_tree4_3(false, "3", { {"1",nullptr } });
trace_tree NFA_1s_or_end_0_tree4_2(false, "2", { {"0",&NFA_1s_or_end_0_tree4_3 }, {"0",&NFA_1s_or_end_0_tree4_4 } });
trace_tree NFA_1s_or_end_0_tree4_1(false, "1", { {"0",nullptr} });
trace_tree NFA_1s_or_end_0_tree4_0(false, "0", { {"EPSILON",&NFA_1s_or_end_0_tree4_1 }, { "EPSILON", &NFA_1s_or_end_0_tree4_2 } });

//tree5: "10"
trace_tree NFA_1s_or_end_0_tree5_6(true, "3", { {"EPSILON",nullptr} });
trace_tree NFA_1s_or_end_0_tree5_5(false, "2", { {"EPSILON",nullptr}});
trace_tree NFA_1s_or_end_0_tree5_4(true, "2", { {"0",&NFA_1s_or_end_0_tree5_5 }, {"0",&NFA_1s_or_end_0_tree5_6 } });
trace_tree NFA_1s_or_end_0_tree5_3(false, "1", { {"0",nullptr } });
trace_tree NFA_1s_or_end_0_tree5_2(true, "2", { {"1",&NFA_1s_or_end_0_tree5_4 } });
trace_tree NFA_1s_or_end_0_tree5_1(false, "1", { {"1",&NFA_1s_or_end_0_tree5_3} });
trace_tree NFA_1s_or_end_0_tree5_0(true, "0", { {"EPSILON",&NFA_1s_or_end_0_tree5_1 }, { "EPSILON", &NFA_1s_or_end_0_tree5_2 } });

//tree6: "11"

trace_tree NFA_1s_or_end_0_tree6_5(false, "2", { {"EPSILON",nullptr} });
trace_tree NFA_1s_or_end_0_tree6_4(false, "2", { {"1",&NFA_1s_or_end_0_tree6_5 }});
trace_tree NFA_1s_or_end_0_tree6_3(false, "1", { {"0",nullptr } });
trace_tree NFA_1s_or_end_0_tree6_2(false, "2", { {"1",&NFA_1s_or_end_0_tree6_4 } });
trace_tree NFA_1s_or_end_0_tree6_1(false, "1", { {"1",&NFA_1s_or_end_0_tree6_3} });
trace_tree NFA_1s_or_end_0_tree6_0(false, "0", { {"EPSILON",&NFA_1s_or_end_0_tree6_1 }, { "EPSILON", &NFA_1s_or_end_0_tree6_2 } });

//TASK 30 
trace_tree NFA_Forking(const NFA& n, myString w) {
	return explore(n, w, n.getStartState());
}

trace_tree explore(const NFA& n, myString w, string q) {
	
	map<Pair, set<string>> T = n.getTransition();
	vector<string> F = n.getAcceptingState();
	string a = w.getCharacterAt(0);
	map<Pair, set<string>>::iterator p = T.find({ q, a });
	list <pair<string, trace_tree*>> branch;
	bool v = false;
	
	if (w == myString(set<string>{"0", "1"}, vector<string> {"EPSILON"})) {
		
		if (find(F.begin(), F.end(), q) != F.end())
		{
			return trace_tree(true, q, { {"EPSILON",nullptr} });
		}
		else
		{
			return trace_tree(false, q, { {"EPSILON",nullptr} });
		}
	}
	if (p == T.end()) {
		return trace_tree{ false, q, {{a, nullptr}} };
	}
	
	w.pop_front();
	set<string> states = p->second;
	
	for (auto p1 = states.begin();p1 != states.end(); p1++)
		branch.push_front(pair<string, trace_tree*>{a, &explore(n, w, *p1)});

	for (auto each : branch) 	
		v = v || each.second->accepted;
	trace_tree tree(v, q, branch);
	return tree;
	
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


