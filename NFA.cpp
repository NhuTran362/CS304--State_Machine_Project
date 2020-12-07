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
	map<Pair, set<string>>::iterator p = T.find(Pair{ q, a });
	list <pair<string, trace_tree*>> branch;
	bool v = false;
	
	if (w == myString(w.getAlphabet(), vector<string> {"EPSILON"})) {
		
		if (find(F.begin(), F.end(), q) != F.end())
		{
			//cout << "here1 " << w << " " << q << endl;
			return trace_tree(true, q, { {"EPSILON",nullptr} });
		}
		else if (p == T.end())
		{
			//cout << "here2 " << w << " " << q << endl;
			return trace_tree(false, q, { {"EPSILON",nullptr} });
		}
	}
	if (p == T.end()) {
		return trace_tree{ false, q, {{a, nullptr}} };
	}
	
	w.pop_front();
	auto states = p->second;
	vector<trace_tree> tt;
	for (auto p1 = states.begin();p1 != states.end(); ++p1) 
		tt.push_back(explore(n, w, *p1));

	for(unsigned i = 0; i < tt.size(); i++)
		branch.push_front(pair<string, trace_tree*>{a, &tt[i]});

	for (auto& each : branch) 
		v = v || each.second->accepted;
	trace_tree tree(v, q, branch);
	//cout << "here3 " << w << " " <<q << endl;

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
	if (NFA_Backtracking(NFA_0s_or_01s, myString("01010101")))
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
	cout << "NFA_0s_or_01s TEST 4: ";
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
	if (NFA_Backtracking(NFA_0s_or_01s, myString("1010101")))
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
bool NFA_search(const NFA& obj, const vector<string>& acceptedStates, myString w, const string& currentState, vector<string> visited, int loop_detected)
{
	map<Pair, set<string>> T = obj.getTransition();
	string a = w.getCharacterAt(0);
	map<Pair, set<string>>::iterator nextState;
	nextState = T.find({ currentState, a });
	auto emptyT = T.find({ currentState,"EPSILON" });
	list <pair<string, trace_tree*>> branch;
	
	if (loop_detected == visited.size() && loop_detected != 0)
		return false;
	if (w.getStringLen() == 0) {
		if (find(acceptedStates.begin(), acceptedStates.end(), currentState) != acceptedStates.end())
			return true;
		
		else if (nextState == T.end())
			return false;
		}
	if (find(visited.begin(), visited.end(), currentState) != visited.end() && nextState == T.end() && emptyT != T.end())
		++loop_detected;
	else
		visited.push_back(currentState);
	if (emptyT != T.end()) {
		for (auto &p1 : emptyT->second) {
			if (NFA_search(obj, acceptedStates, w, p1, visited,loop_detected))
				return true;
		}
	}
	if (nextState != T.end()) {
		w.pop_front();
		for (auto &p1 : nextState->second) {
			if (NFA_search(obj, acceptedStates, w, p1,visited))
				return true;	
		}
	}
	
	return false;
}

//TASK 33
NFA NFA_Union(const NFA& A, const NFA& B) {
	if (A.getAlphabet() != B.getAlphabet())
		throw invalid_argument("NFA_Union: Alphabet error");
	//state
	vector<string> stateA = A.getState();
	vector<string> stateB = B.getState();
	vector<string> stateC;

	for (auto &each : stateA)
		stateC.push_back("0" + each);
	for (auto &each : stateB)
		stateC.push_back("1" + each);
	stateC.push_back("finalState");
	string startC = "Start";
	stateC.push_back(startC);
	map<Pair, set<string>> T_A = A.getTransition();
	map<Pair, set<string>> T_B = B.getTransition();
	map<Pair, set<string>> T_C;
	T_C[{startC, "EPSILON"}] = { "0" + A.getStartState(), "1" + B.getStartState() };

	for (auto &each : T_A)
	{
		for (auto &each1 : each.second) {
			T_C[{"0" + each.first.first, each.first.second}].insert("0" + each1);
		}
	}

	for (auto &each : T_B)
	{
		for (auto &each1 : each.second) {
			T_C[{"1" + each.first.first, each.first.second}].insert("1" + each1);
		}
	}

	vector<string> F_A = A.getAcceptingState();
	vector<string> F_B = B.getAcceptingState();
	vector<string> F_C = { "finalState" };
	for (auto &each : F_A) {
		T_C[{"0" + each, "EPSILON"}].insert("finalState");
		F_C.push_back("0" + each);
	}
	for (auto &each : F_B) {
		F_C.push_back("1" + each);
		T_C[{"1" + each, "EPSILON"}].insert("finalState");
	}
	return NFA(stateC, A.getAlphabet(), startC, T_C, F_C);
}


//TASK 34
NFA NFA_Concat(const NFA& A, const NFA&B) {
	vector<string> stateA = A.getState();
	vector<string> stateB = B.getState();
	vector<string> stateC;

	for (auto &each : stateA)
		stateC.push_back("0" + each);
	for (auto &each : stateB)
		stateC.push_back("1" + each);

	string startC = "0" + A.getStartState();
	

	map<Pair, set<string>> T_A = A.getTransition();
	map<Pair, set<string>> T_B = B.getTransition();
	map<Pair, set<string>> T_C;

	for (auto &each : T_A)
	{
		for (auto &each1 : each.second) {
			T_C[{"0" + each.first.first, each.first.second}].insert("0" + each1);
		}
	}

	for (auto &each : T_B)
	{
		for (auto &each1 : each.second) {
			T_C[{"1" + each.first.first, each.first.second}].insert("1" + each1);
		}
	}

	vector<string> F_A = A.getAcceptingState();
	vector<string> F_B = B.getAcceptingState();
	vector<string> F_C;
	for (auto&each : F_A)
		T_C[{"0" + each, "EPSILON" }].insert( "1" + B.getStartState());
	for (auto&each : F_B)
		F_C.push_back("1" + each);

	return NFA(stateC, A.getAlphabet(), startC, T_C, F_C);
}

//TASK 36
NFA NFA_KStart(const NFA& A) {
	vector<string> State = A.getState();
	map<Pair, set<string>> T = A.getTransition();
	vector<string> accept = A.getAcceptingState();
	State.push_back("StartK");
	T[{"StartK", "EPSILON"}].insert({ A.getStartState() });
	for (auto &each : accept)
		T[{each, "EPSILON"}].insert("StartK");
	return NFA(State, A.getAlphabet(), "StartK", T, A.getAcceptingState());
}
//TASK 37
void test_NFA_KStart_01() {
	cout << "\n\ntest_NFA_KStart_01: ";
	NFA test = NFA_KStart(NFA_0s_or_01s);
	if (NFA_Backtracking(test, myString("0010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_02() {
	cout << "test_NFA_KStart_02: ";
	NFA test = NFA_KStart(NFA_1s_or_end_0);
	if (NFA_Backtracking(test, myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_03() {
	cout << "test_NFA_KStart_03: ";
	NFA test = NFA_KStart(NFA_10);
	if (NFA_Backtracking(test, myString("1010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_04() {
	cout << "test_NFA_KStart_04: ";
	NFA test = NFA_KStart(NFA_Union(NFA_third_0, NFA_end_01));
	if (NFA_Backtracking(test, myString("01101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_05() {
	cout << "test_NFA_KStart_05: ";
	NFA test = NFA_KStart(NFA_Union(NFA_third_0, NFA_end_01));
	if (NFA_Backtracking(test, myString("01101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_06() {
	cout << "test_NFA_KStart_06: ";
	NFA test = NFA_KStart(NFA_Union(NFA_10s, NFA_0s));
	if (NFA_Backtracking(test, myString("100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_07() {
	cout << "test_NFA_KStart_07: ";
	NFA test = NFA_KStart(NFA_Union(NFA_0s, NFA_non_empty_even_len));
	if (NFA_Backtracking(test, myString("110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_08() {
	cout << "test_NFA_KStart_08: ";
	NFA test = NFA_KStart(NFA_Union(NFA_0s_or_01s, NFA_non_empty_even_len));
	if (NFA_Backtracking(test, myString("010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_09() {
	cout << "test_NFA_KStart_09: ";
	NFA test = NFA_KStart(NFA_1s_or_end_0);
	if (NFA_Backtracking(test, myString("101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_10() {
	cout << "test_NFA_KStart_10: ";
	NFA test = NFA_KStart(NFA_Union(NFA_0s_or_01s, NFA_1s_or_end_0));
	if (NFA_Backtracking(test, myString("0110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_11(){
	cout << "test_NFA_KStart_11: ";
	NFA test = NFA_KStart(NFA_Union(NFA_0s, NFA_1s_or_end_0));
	if (NFA_Backtracking(test, myString("001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_KStart_12() {
	cout << "test_NFA_KStart_12: ";
	NFA test = NFA_KStart(NFA_Union(NFA_third_0, NFA_10));
	if (NFA_Backtracking(test, myString("00010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//TASK 38
DFA NFA_to_DFA(NFA& obj) {
	vector<string> nState = obj.getState();
	vector<string> dState;
	set<string> dAlphabet = obj.getAlphabet();
	string dStartState = obj.getStartState();
	map<Pair, set<string>> nT = obj.getTransition();
	map<Pair, string> dT;
	vector<string> nF = obj.getAcceptingState();
	vector<string> dF;
	map<string, vector<string>> E_closure = closure(nState, nT);

	auto e = nT.find({ dStartState, "EPSILON" });
	if ( e != nT.end()) {
		auto e1 = E_closure.find(dStartState)->second;
		for (unsigned i = 0; i < e1.size(); i++) {
			if(dStartState.find(e1[i]) == std::string::npos)
				dStartState += e1[i];
		}
	}
	if (find(nF.begin(), nF.end(), obj.getStartState()) != nF.end())
		dF.push_back(dStartState);
	
	string current = dStartState;
	dState.push_back(current);

	for (unsigned i = 0; i < dState.size(); i++) {
		current = dState[i];
		if (current != "dead") {
			for (auto &symbol : dAlphabet) {
				vector<string> nS;
				for (unsigned j = 0; j < current.length(); j++) {
					vector<string> temp = newState(string(1, current[j]), nT, symbol, E_closure);
					vector_add(nS, temp);
				}
				string newS = "";
				for (unsigned j = 0; j < nS.size(); ++j) 
				
						newS += nS[j];
				if (newS.length() == 0)
					newS = "dead";
				//cout << "newS: " << newS << endl << endl;
				dT[{current, symbol}] = newS;
				if (find(dState.begin(), dState.end(), newS) == dState.end()) {
					dState.push_back(newS);
					for (unsigned k = 0; k < newS.length(); k++)
						if (find(nF.begin(), nF.end(), string(1, newS[k])) != nF.end()) {
							dF.push_back(newS);
							break;
						}
				}
			}
		}

	}
	return DFA(dState, dAlphabet, dStartState, dT, dF);
}
map<string, vector<string>> closure(vector<string>nstate, map<Pair, set<string>> nT) {
	map<string, vector<string>> result;
	for (unsigned i = 0; i < nstate.size();i++) {
		E_move(nstate[i], nT, result[nstate[i]]);
	}
	return result;
}
void E_move(string state, map<Pair, set<string>> nT, vector<string>& result){
	result.push_back(state);
	sort(result.begin(), result.end());
	auto p = nT.find({ state, "EPSILON" });
	if (p == nT.end())
		return;
	for (auto & each : p->second) 
		if (find(result.begin(), result.end(), each) == result.end())
			E_move(each, nT, result);
	
	return;
} 
vector<string> newState(string state, map<Pair, set<string>> nT, string character, map<string,vector<string>> closure) {
	vector<string> result;
	auto p = closure.find(state);
	for (auto &each : p->second) {

		auto p2 = nT.find({ each, character });
		if (p2 != nT.end()) {
			for (auto & each2 : p2->second) {
				auto cl = closure.find(each2);
				vector_add(result, cl->second);
				
			}
		}

	}
	sort(result.begin(), result.end());
	unique(result.begin(), result.end());
	return result;

	/*auto p = nT.find({ state,character });
	
	if (p != nT.end())
		for (auto &each : p->second) {
			cout << state << " " << character << ": " << each << endl;
			result.push_back(each);
		}
		
	//if (nT.find({ state,"EPSILON" }) != nT.end()) {
		auto p2 = closure.find(state);
		for (auto &each : p2->second) {
			if (nT.find({ each,character }) != nT.end()) {
				auto p3 = closure.find(each);
				vector_add(result, p3->second);
			}
		}
	//}	
		if (result.size() == 0)
			result.push_back("dead");
	sort(result.begin(), result.end());
	unique(result.begin(), result.end());
	return result;*/
}
void vector_add(vector<string>& a, const vector<string>& b){
	for (auto &each : b)
		if (find(a.begin(), a.end(), each) == a.end())
			a.push_back(each);
	sort(a.begin(), a.end());
	return;
}

//TASK 39
//test for NFA_11_00 to DFA
void test_NFA_11_00_1_DFA() {
	cout << "\n\nNFA_11_00_DFA TEST 1: ";
	if (NFA_to_DFA(NFA_11_00).isAccepted(myString("101100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_2_DFA() {
	cout << "NFA_11_00_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_11_00).isAccepted(myString("0110011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

}
void test_NFA_11_00_3_DFA() {
	cout << "NFA_11_00_DFA TEST 3: ";
	if (!NFA_to_DFA(NFA_11_00).isAccepted(myString("0111101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_4_DFA() {
	cout << "NFA_11_00_DFA TEST 4: ";
	if (!NFA_to_DFA(NFA_11_00).isAccepted(myString("0101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_5_DFA() {
	cout << "NFA_11_00 TEST_DFA 5: ";
	if (!NFA_to_DFA(NFA_11_00).isAccepted(myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_6_DFA() {
	cout << "NFA_11_00 TEST_DFA 6: ";
	if (!NFA_to_DFA(NFA_11_00).isAccepted(myString("1000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_7_DFA() {
	cout << "NFA_11_00_DFA TEST 7: ";
	if (NFA_to_DFA(NFA_11_00).isAccepted(myString("0111100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n ";
}
void test_NFA_11_00_8_DFA() {
	cout << "NFA_11_00_DFA TEST 8: ";
	if (NFA_to_DFA(NFA_11_00).isAccepted(myString("1100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_9_DFA() {
	cout << "NFA_11_00_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_11_00).isAccepted(myString("0011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_10_DFA() {
	cout << "NFA_11_00_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_11_00).isAccepted(myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_11_DFA() {
	cout << "NFA_11_00_DFA TEST 11: ";
	if (!NFA_to_DFA(NFA_11_00).isAccepted(myString("EPSILON")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_11_00_12_DFA() {
	cout << "NFA_11_00_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_11_00).isAccepted(myString("10000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_end_01 to DFA
void test_NFA_end_01_1_DFA() {
	cout << "\n\nNFA_end_01_DFA TEST 1: ";
	if (NFA_to_DFA(NFA_end_01).isAccepted(myString("01")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_2_DFA() {
	cout << "NFA_end_01_DFA TEST 2: ";
	
	if (NFA_to_DFA(NFA_end_01).isAccepted(myString("001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_3_DFA() {
	cout << "NFA_end_01_DFA TEST 3: ";
	if (!NFA_to_DFA(NFA_end_01).isAccepted(myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_4_DFA() {
	cout << "NFA_end_01_DFA TEST 4: ";
	if (!NFA_to_DFA(NFA_end_01).isAccepted(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_5_DFA() {
	cout << "NFA_end_01_DFA TEST 5: ";
	if (!NFA_to_DFA(NFA_end_01).isAccepted(myString("EPSILON")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_6_DFA() {
	cout << "NFA_end_01 TEST_DFA 6: ";
	if (NFA_to_DFA(NFA_end_01).isAccepted(myString("101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_7_DFA() {
	cout << "NFA_end_01_DFA TEST 7: ";
	if (NFA_to_DFA(NFA_end_01).isAccepted(myString("1101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_8_DFA() {
	cout << "NFA_end_01_DFA TEST 8: ";
	if (!NFA_to_DFA(NFA_end_01).isAccepted(myString("10")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_9_DFA() {
	cout << "NFA_end_01_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_end_01).isAccepted(myString("010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_10_DFA() {
	cout << "NFA_end_01_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_end_01).isAccepted(myString("1110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_11_DFA() {
	cout << "NFA_end_01_DFA TEST 11: ";
	if (NFA_to_DFA(NFA_end_01).isAccepted(myString("0101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_end_01_12_DFA() {
	cout << "NFA_end_01_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_end_01).isAccepted(myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_third_0 to DFA
void test_NFA_third_0_1_DFA() {
	cout << "\n\nNFA_third_0_11_DFA TEST 1: ";
	if (!NFA_to_DFA(NFA_third_0).isAccepted(myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_2_DFA() {
	cout << "NFA_third_0_11_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_third_0).isAccepted(myString("011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_3_DFA() {
	cout << "NFA_third_0_11_DFA TEST 3: ";
	if (NFA_to_DFA(NFA_third_0).isAccepted(myString("1011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_4_DFA() {
	cout << "NFA_third_0_11_DFA TEST 4: ";
	if (!NFA_to_DFA(NFA_third_0).isAccepted(myString("111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_5_DFA() {
	cout << "NFA_third_0_11_DFA TEST 5: ";
	if (NFA_to_DFA(NFA_third_0).isAccepted(myString("10011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_6_DFA() {
	cout << "NFA_third_0_11_DFA TEST 6: ";
	if (!NFA_to_DFA(NFA_third_0).isAccepted(myString("EPSILON")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_7_DFA() {
	cout << "NFA_third_0_11_DFA TEST 7: ";
	if (!NFA_to_DFA(NFA_third_0).isAccepted(myString("1100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_8_DFA() {
	cout << "NFA_third_0_11_DFA TEST 8: ";
	if (NFA_to_DFA(NFA_third_0).isAccepted(myString("0000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_9_DFA() {
	cout << "NFA_third_0_11_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_third_0).isAccepted(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_10_DFA() {
	cout << "NFA_third_0_11_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_third_0).isAccepted(myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_11_DFA() {
	cout << "NFA_third_0_11_DFA TEST 11: ";
	if (NFA_to_DFA(NFA_third_0).isAccepted(myString("01001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_third_0_12_DFA() {
	cout << "NFA_third_0_11_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_third_0).isAccepted(myString("01110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}


//test for NFA_substring_1110 to DFA
void test_NFA_substring_1110_1_DFA() {
	{
		cout << "\n\nNFA_substring_1110_DFA TEST 1: ";
		if (NFA_to_DFA(NFA_substring_1110).isAccepted(myString("1110")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_2_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 2: ";
		if (NFA_to_DFA(NFA_substring_1110).isAccepted(myString("11100")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_3_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 3: ";
		if (NFA_to_DFA(NFA_substring_1110).isAccepted(myString("01110")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_4_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 4: ";
		if (NFA_to_DFA(NFA_substring_1110).isAccepted(myString("11110")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_5_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 5: ";
		if (NFA_to_DFA(NFA_substring_1110).isAccepted(myString("11101")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_6_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 6: ";
		if (NFA_to_DFA(NFA_substring_1110).isAccepted(myString("1111101")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_7_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 7: ";
		if (!NFA_to_DFA(NFA_substring_1110).isAccepted(myString("1")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_8_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 8: ";
		if (!NFA_to_DFA(NFA_substring_1110).isAccepted(myString("0")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_9_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 9: ";
		if (!NFA_to_DFA(NFA_substring_1110).isAccepted(myString("EPSILON")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_10_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 10: ";
		if (!NFA_to_DFA(NFA_substring_1110).isAccepted(myString("11")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_11_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 11: ";
		if (!NFA_to_DFA(NFA_substring_1110).isAccepted(myString("111")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}
void test_NFA_substring_1110_12_DFA() {
	{
		cout << "NFA_substring_1110_DFA TEST 12: ";
		if (!NFA_to_DFA(NFA_substring_1110).isAccepted(myString("1010")))
			cout << "PASSED\n\n";
		else
			cout << "NOT PASSED\n\n";
	}
}

//test for NFA_10s to DFA
void test_NFA_10s_1_DFA() {
	cout << "\n\nNFA_10s_DFA TEST 1: ";

	if (NFA_to_DFA(NFA_10s).isAccepted(myString("10")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_2_DFA() {
	cout << "NFA_10s_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_10s).isAccepted(myString("1010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_3_DFA() {
	cout << "NFA_10s_DFA TEST 3: ";
	if (NFA_to_DFA(NFA_10s).isAccepted(myString("101010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_4_DFA() {	cout << "NFA_10s_DFA TEST 4: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_5_DFA() {
	cout << "NFA_10s_DFA TEST 5: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_6_DFA() {
	cout << "NFA_10s_DFA TEST 6: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("00")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_7_DFA() {
	cout << "NFA_10s_DFA TEST 7: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("01")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_8_DFA() {
	cout << "NFA_10s_DFA TEST 8: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_9_DFA() {
	cout << "NFA_10s_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_10_DFA() {
	cout << "NFA_10s_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_11_DFA() {
	cout << "NFA_10s_DFA TEST 11: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("1000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10s_12_DFA() {
	cout << "NFA_10s_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_10s).isAccepted(myString("10010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_empty_string to DFA
void test_NFA_empty_string_1_DFA() {
	cout << "\n\nNFA_empty_string_DFA TEST 1: ";
	if (NFA_to_DFA(NFA_empty_string).isAccepted(myString("EPSILON")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_2_DFA() {
	cout << "NFA_empty_string_DFA TEST 2: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_3_DFA() {
	cout << "NFA_empty_string_DFA TEST 3: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_4_DFA() {
	cout << "NFA_empty_string_DFA TEST 4: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("00")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_5_DFA() {
	cout << "NFA_empty_string_DFA TEST 5: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("01")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_6_DFA() {
	cout << "NFA_empty_string_DFA TEST 6: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_7_DFA() {
	cout << "NFA_empty_string_DFA TEST 7: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_8_DFA() {
	cout << "NFA_empty_string_DFA TEST 8: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_9_DFA() {
	cout << "NFA_empty_string_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("0000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_10_DFA() {
	cout << "NFA_empty_string_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("01000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_11_DFA() {
	cout << "NFA_empty_string_DFA TEST 11: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("11110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_empty_string_12_DFA() {
	cout << "NFA_empty_string_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_empty_string).isAccepted(myString("100101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_nonempty_string to DFA
void test_NFA_nonempty_string_1_DFA() {
	cout << "\n\nNFA_nonempty_string_DFA TEST 1: ";
	if (!NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("EPSILON")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_2_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_3_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 3: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_4_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 5: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("10")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_5_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 5: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_6_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 6: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_7_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 7: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_8_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 8: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_9_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 9: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_10_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 10: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("1000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_11_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 11: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("1001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_nonempty_string_12_DFA() {
	cout << "NFA_nonempty_string_DFA TEST 12: ";
	if (NFA_to_DFA(NFA_nonempty_string).isAccepted(myString("1111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_10 to DFA
void test_NFA_10_1_DFA() {
	cout << "\n\nNFA_10_DFA TEST 1: ";
	if (NFA_to_DFA(NFA_10).isAccepted(myString("10")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_2_DFA() {
	cout << "NFA_10_DFA TEST 2: ";
	trace_tree test = NFA_Forking(NFA_10, myString("1011"));
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("1011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_3_DFA() {
	cout << "NFA_10_DFA TEST 3: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_4_DFA() {
	cout << "NFA_10_DFA TEST 4: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("1010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_5_DFA() {
	cout << "NFA_10_DFA TEST 5: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_6_DFA() {
	cout << "NFA_10_DFA TEST 6: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_7_DFA() {
	cout << "NFA_10_DFA TEST 7: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_8_DFA() {
	cout << "NFA_10_DFA TEST 8: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_9_DFA() {
	cout << "NFA_10_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("01")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_10_DFA() {
	cout << "NFA_10_DFA TEST 10: ";
	trace_tree test = NFA_Forking(NFA_10, myString("00"));
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("00")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_11_DFA() {
	cout << "NFA_10_DFA TEST 11: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("EPSILON")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_10_12_DFA() {
	cout << "NFA_10_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_10).isAccepted(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//test for NFA_non_empty_even_len to DFA
void test_NFA_non_empty_even_len_1_DFA() {
	cout << "\n\nNFA_non_empty_even_len_DFA TEST 1: ";
	if (NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("10")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_2_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("1000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_3_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 3: ";
	if (NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_4_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 4: ";
	if (NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("00")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_5_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 5: ";
	if (NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("1000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_6_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 6: ";
	if (NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("1001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_7_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 7: ";
	if (!NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("EPSILON")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_8_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 8: ";
	if (!NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_9_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_10_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_11_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 11: ";
	if (!NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_non_empty_even_len_12_DFA() {
	cout << "NFA_non_empty_even_len_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_non_empty_even_len).isAccepted(myString("01011")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}


//test for NFA_0s to DFA
void test_NFA_0s_1_DFA() {
	cout << "\n\nNFA_0s_DFA TEST 1: ";
	if (NFA_to_DFA(NFA_0s).isAccepted(myString("0")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_2_DFA() {
	cout << "NFA_0s_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_0s).isAccepted(myString("00000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_3_DFA() {
	cout << "NFA_0s_DFA TEST 3: ";
	if (NFA_to_DFA(NFA_0s).isAccepted(myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_4_DFA() {
	cout << "NFA_0s_DFA TEST 4: ";
	if (NFA_to_DFA(NFA_0s).isAccepted(myString("0000000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_5_DFA() {
	cout << "NFA_0s_DFA TEST 5: ";
	if (!NFA_to_DFA(NFA_0s).isAccepted(myString("01")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_6_DFA() {
	cout << "NFA_0s_DFA TEST 6: ";
	if (!NFA_to_DFA(NFA_0s).isAccepted(myString("010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_7_DFA() {
	cout << "NFA_0s_DFA TEST 7: ";
	if (!NFA_to_DFA(NFA_0s).isAccepted(myString("01110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_8_DFA() {
	cout << "NFA_0s_DFA TEST 8: ";
	if (!NFA_to_DFA(NFA_0s).isAccepted(myString("111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_9_DFA() {
	cout << "NFA_0s_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_0s).isAccepted(myString("1111111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_10_DFA() {
	cout << "NFA_0s_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_0s).isAccepted(myString("01010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_11_DFA() {
	cout << "NFA_0s_DFA TEST 11: ";
	if (!NFA_to_DFA(NFA_0s).isAccepted(myString("000111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_12_DFA() {

	cout << "NFA_0s_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_0s).isAccepted(myString("1111111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

}

//test for NFA_0s_or_01s to DFA
void test_NFA_0s_or_01s_1_DFA() {
	cout << "\n\nNFA_0s_or_01s_DFA TEST 1: ";
	if (NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_2_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("010101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_3_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 3: ";
	if (NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("00000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_4_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 4: ";
	if (NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("0101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_5_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 5: ";
	if (NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("00000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_6_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 6: ";
	if (NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("01010101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_7_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 7: ";
	if (!NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("10000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_8_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 8: ";
	if (!NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("10100")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_9_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("10000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_10_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_11_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 11: ";
	if (!NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("11000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_0s_or_01s_12_DFA() {
	cout << "NFA_0s_or_01s_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_0s_or_01s).isAccepted(myString("100001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}


//test for NFA_1s_or_end_0 to DFA
void test_NFA_1s_or_end_0_1_DFA() {
	cout << "\n\nNFA_1s_or_end_0_DFA TEST 1: ";
	if (NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("11")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_2_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_3_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 2: ";
	if (NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("11000")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_4_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 4: ";
	if (NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("111111")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_5_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 5: ";
	if (NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("00")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_6_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 6: ";
	if (NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("10")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_7_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 7: ";
	if (!NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("0101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_8_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 8: ";
	if (!NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("100001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_9_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 9: ";
	if (!NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("0101001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_10_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 10: ";
	if (!NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("11101")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_11_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 11: ";
	if (!NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("0001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_NFA_1s_or_end_0_12_DFA() {
	cout << "NFA_1s_or_end_0_DFA TEST 12: ";
	if (!NFA_to_DFA(NFA_1s_or_end_0).isAccepted(myString("1101001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}


