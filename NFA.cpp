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

