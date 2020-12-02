#include "myString.h"
#include "DFA.h"
#include "NFA.h"

int main(int argc, char * argv[]) {

	set<string> initAlphabet = { "0","1" };
	vector<string> initString = { "0","1","1","0","0","0","1" };
	string a_String = "10100011";
	set<string> alpha_for_string_4 = { "01","10","00","11" };


	//test constructors
	cout << "\n\n TEST CONSTRUCTORS\n\n";

	myString string_1;
	myString string_2(initAlphabet, initString);
	myString string_3(a_String);
	myString string_4(alpha_for_string_4, a_String);


	cout << "string_1: " << string_1 << endl;
	cout << "string_2: " << string_2 << endl;
	cout << "string_3: " << string_3 << endl;
	cout << "string_4: " << string_4 << endl;

	cout << "\n\nTESTING THE generate_Nth_string_lexi function \n\n";
	cout << "Print out the 1th to 31th string of {0,1}\n\n";
	for (int i = 1; i < 32; i++)
	cout << generate_Nth_string_lexi(set<string> {"0", "1"}, i) << endl;
	
	
	cout << "********************ACCEPTING NO STRING*************" << endl;
	if (!AcceptingNoString.isAccepted(myString("10010")))
	cout << "PASSED\n\n";
	else
	cout << "NOT PASSED\n\n";

	cout << "********************ACCEPTING EMPTY STRING*************" << endl;
	if (AcceptingEmptyString.isAccepted(myString("")))
	cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
	
	cout << "********************ACCEPTING ONE CHARACTER*************" << endl;
	DFA myDFA = AcceptingStringofOneCharacter("a", set<string> {"a", "b", "c"});
	if (myDFA.isAccepted(myString("a")))
		cout << "PASSED\n\n";
	else cout << "PASSED\n\n";
	test_DFA_even_len();
	test_DFA_string_of_0s();
	test_DFA_recognize_nano();
	test_DFA_string_end_with_0();
	test_DFA_string_of_even_number_of_0();
	test_DFA_string_of_three_consecutive_zero(); 
	test_DFA_string_of_even_0_and_1();
	test_DFA_string_of_0s_start_and_end_with_1();
	test_DFA_string_that_accept_only_101();
	test_DFA_string_that_does_not_contain_consecutive_1();
	test_DFA_string_of_len_2();
	test_DFA_strings_of_110s();
	
	//Testing task 11
	list<config> test = trace(string_of_even_0_and_1, myString("100111010"));
	list<config> test2 = trace(strings_of_110s, myString("1101101101101000"));
	
	for (auto p = test.begin(); p != test.end(); p++)
	{
		
		cout << "(" << p->q << ", " << p->w << " )";
	}
	cout << endl;

	for (auto p = test2.begin(); p != test2.end(); p++)
	{

		cout << "(" << p->q << ", " << p->w << " )";
	}
	cout << endl;
	
	
	//test task 12
	cout << returnAcceptedString(AcceptingNoString) << endl;
	if (!AcceptingNoString.isAccepted(returnAcceptedString(AcceptingNoString)))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

	cout << returnAcceptedString(AcceptingEmptyString) << endl;
	if (AcceptingEmptyString.isAccepted(returnAcceptedString(AcceptingEmptyString)))
		cout << "PASSED\n\n";

	cout << returnAcceptedString(even_len) << endl;
	if (even_len.isAccepted(returnAcceptedString(even_len)))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

	cout << returnAcceptedString(string_that_accept_only_101) << endl;
	if (string_that_accept_only_101.isAccepted(returnAcceptedString(string_that_accept_only_101)))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

	cout << returnAcceptedString(strings_of_110s) << endl;
	if (strings_of_110s.isAccepted(returnAcceptedString(strings_of_110s)))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";

	cout << returnAcceptedString(recognize_nano) << endl;
	if (recognize_nano.isAccepted(returnAcceptedString(recognize_nano)))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
	
	
	//test TASK 13
	myDFA = DFA_Complement(even_len);
	if (myDFA.isAccepted(myString("1011100")) && !myDFA.isAccepted(myString("00110011001110")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
	
	//TASK 15
	test_even_len_OR_strings_of_0s();
	test_string_end_with_0_OR_string_of_even_number_of_0();
	test_string_of_three_consecutive_zero_OR_strings_of_110s();
	test_string_of_len_2_OR_string_that_does_not_contain_consecutive_1();
	test_string_of_even_0_and_1_OR_string_of_three_consecutive_zero();
	test_even_len_OR_strings_of_110s();
	test_string_end_with_0_OR_string_of_even_0_and_1();
	test_string_that_only_accept_101_OR_string_end_with_0();
	test_string_of_0s_start_and_end_with_1_OR_string_of_0s();
	test_string_of_110s_OR_string_of_len_2();
	
	//TASK 17
	test_even_len_AND_strings_of_0s();
	test_string_end_with_0_AND_string_of_even_number_of_0();
	test_string_of_three_consecutive_zero_AND_strings_of_110s();
	test_string_of_len_2_AND_string_that_does_not_contain_consecutive_1();
	test_string_of_even_0_and_1_AND_string_of_three_consecutive_zero();
	test_even_len_AND_strings_of_110s();
	test_string_end_with_0_AND_string_of_even_0_and_1();
	test_string_that_only_accept_101_AND_string_end_with_0();
	test_string_of_0s_start_and_end_with_1_AND_string_of_0s();
	test_string_of_110s_AND_string_of_len_2();
	test_string_of_even_number_of_0_AND_string_of_0s_start_and_end_with_1();
	test_string_that_does_not_contain_consecutive_1_AND_even_len();
	
	//TASK 19
	test_even_len_SUBSET_strings_of_0s();
	test_string_end_with_0_SUBSET_string_of_even_number_of_0();
	test_string_of_three_consecutive_zero_SUBSET_strings_of_110s();
	test_string_of_len_2_SUBSET_even_len();
	test_string_of_even_0_and_1_SUBSET_string_of_even_number_of_0();
	test_strings_of_110s_SUBSET_string_end_with_zero();
	test_string_end_with_0_SUBSET_string_of_0s();
	test_string_of_0s_SUBSET_string_end_with_0();
	test_string_that_accept_only_101_SUBSET_string_that_does_not_contain_consecutive_1();
	test_string_of_0s_SUBSET_string_that_does_not_contain_consecutive_1();
	test_string_that_accept_only_101_SUBSET_string_of_0s_start_and_end_with_1();
	test_string_that_does_not_contain_consecutive_1_SUBSET_even_len();

	test_even_len_EQUAL_strings_of_0s();
	test_string_end_with_0_EQUAL_string_of_even_number_of_0();
	test_string_of_three_consecutive_zero_EQUAL_strings_of_110s();
	test_string_of_len_2_EQUAL_even_len();
	test_string_of_even_0_and_1_EQUAL_string_of_even_number_of_0();
	test_strings_of_110s_EQUAL_string_end_with_zero();
	test_string_end_with_0_EQUAL_string_of_0s();
	test_string_of_0s_EQUAL_string_of_0s();
	test_string_of_even_0_and_1_EQUAL_even_len();
	string_that_does_not_contain_consecutive_1_EQUAL_string_that_does_not_contain_consecutive_1();
	test_string_that_accept_only_101_EQUAL_string_that_accept_only_101();
	test_string_of_len_2_EQUAL_Intersection_of_len_2_and_even_len();
	
	/TASK 22
	static DFA odd_len(vector<string> { "0", "1" }, set<string> {"0", "1"}, "0", map<Pair, string> { {Pair("0", "0"), "1"}, { Pair("0", "1"), "1" }, { Pair("1", "0"), "0" }, { Pair("1", "1"), "0" }}, { "1" });
	if(DFA_Equality(odd_len, DFA_Complement(even_len)))
		cout <<"DFA_Complement works!"<<endl;
	else 
		cout << "DFA_Complement does not work!" << endl;
	
	if (DFA_Equality(string_end_with_0, DFA_Union(strings_of_110s,string_end_with_0)))
		cout << "DFA_Union works!" << endl;
	else
		cout << "DFA_Union does not work!" << endl;
	if (DFA_Equality(DFA_Intersection(string_of_0s, string_of_even_number_of_0), DFA_Intersection(DFA_Intersection(string_of_0s, string_of_even_number_of_0), string_of_even_0_and_1)))
		cout << "DFA_Intersection works!" << endl;
	else
		cout << "DFA_Intersection does not work!" << endl;
	
	
	//TASK 31
	test_NFA_11_00_1();
	test_NFA_11_00_2();
	test_NFA_11_00_3();
	test_NFA_11_00_4();
	test_NFA_11_00_5();
	test_NFA_11_00_6();
	test_NFA_11_00_7();
	test_NFA_11_00_8();
	test_NFA_11_00_9();
	test_NFA_11_00_10();
	test_NFA_11_00_11();
	test_NFA_11_00_12();

	test_NFA_end_01_1();
	test_NFA_end_01_2();
	test_NFA_end_01_3();
	test_NFA_end_01_4();
	test_NFA_end_01_5();
	test_NFA_end_01_6();
	test_NFA_end_01_7();
	test_NFA_end_01_8();
	test_NFA_end_01_9();
	test_NFA_end_01_10();
	test_NFA_end_01_11();
	test_NFA_end_01_12();
	
	//test for NFA_third_0
	test_NFA_third_0_1();
	test_NFA_third_0_2();
	test_NFA_third_0_3();
	test_NFA_third_0_4();
	test_NFA_third_0_5();
	test_NFA_third_0_6();
	test_NFA_third_0_7();
	test_NFA_third_0_8();
	test_NFA_third_0_9();
	test_NFA_third_0_10();
	test_NFA_third_0_11();
	test_NFA_third_0_12();


	//test for NFA_substring_1110
	test_NFA_substring_1110_1();
	test_NFA_substring_1110_2();
	test_NFA_substring_1110_3();
	test_NFA_substring_1110_4();
	test_NFA_substring_1110_5();
	test_NFA_substring_1110_6();
	test_NFA_substring_1110_7();
	test_NFA_substring_1110_8();
	test_NFA_substring_1110_9();
	test_NFA_substring_1110_10();
	test_NFA_substring_1110_11();
	test_NFA_substring_1110_12();

	//test for NFA_10s
	test_NFA_10s_1();
	test_NFA_10s_2();
	 test_NFA_10s_3();
	 test_NFA_10s_4();
	 test_NFA_10s_5();
	 test_NFA_10s_6();
	 test_NFA_10s_7();
	 test_NFA_10s_8();
	 test_NFA_10s_9();
	 test_NFA_10s_10();
	 test_NFA_10s_11();
	 test_NFA_10s_12();


	 //test for NFA_empty_string
	  test_NFA_empty_string_1();
	  test_NFA_empty_string_2();
	  test_NFA_empty_string_3();
	  test_NFA_empty_string_4();
	  test_NFA_empty_string_5();
	  test_NFA_empty_string_6();
	  test_NFA_empty_string_7();
	  test_NFA_empty_string_8();
	  test_NFA_empty_string_9();
	  test_NFA_empty_string_10();
	  test_NFA_empty_string_11();
	  test_NFA_empty_string_12();

	  //test for NFA_nonempty_string
	   test_NFA_nonempty_string_1();
	   test_NFA_nonempty_string_2();
	   test_NFA_nonempty_string_3();
	   test_NFA_nonempty_string_4();
	   test_NFA_nonempty_string_5();
	   test_NFA_nonempty_string_6();
	   test_NFA_nonempty_string_7();
	   test_NFA_nonempty_string_8();
	   test_NFA_nonempty_string_9();
	   test_NFA_nonempty_string_10();
	   test_NFA_nonempty_string_11();
	   test_NFA_nonempty_string_12();

	   //test for NFA_10
	    test_NFA_10_1();
	    test_NFA_10_2();
	    test_NFA_10_3();
	    test_NFA_10_4();
	    test_NFA_10_5();
	    test_NFA_10_6();
	    test_NFA_10_7();
	    test_NFA_10_8();
	    test_NFA_10_9();
	    test_NFA_10_10();
	    test_NFA_10_11();
	    test_NFA_10_12();

		//test for NFA_non_empty_even_len
		 \test_NFA_non_empty_even_len_1();
		 test_NFA_non_empty_even_len_2();
		 test_NFA_non_empty_even_len_3();
		 test_NFA_non_empty_even_len_4();
		 test_NFA_non_empty_even_len_5();
		 test_NFA_non_empty_even_len_6();
		 test_NFA_non_empty_even_len_7();
		 test_NFA_non_empty_even_len_8();
		 test_NFA_non_empty_even_len_9();
		 test_NFA_non_empty_even_len_10();
		 test_NFA_non_empty_even_len_11();
		 test_NFA_non_empty_even_len_12();


		 //test for NFA_0s
		 test_NFA_0s_1();
		 test_NFA_0s_2();
		 test_NFA_0s_3();
		 test_NFA_0s_4();
		 test_NFA_0s_5();
		 test_NFA_0s_6();
		 test_NFA_0s_7();
		 test_NFA_0s_8();
		 test_NFA_0s_9();
		 test_NFA_0s_10();
		 test_NFA_0s_11();
		 test_NFA_0s_12();

		 //test for NFA_0s_or_01s
		  test_NFA_0s_or_01s_1();
		  test_NFA_0s_or_01s_2();
		  test_NFA_0s_or_01s_3();
		  test_NFA_0s_or_01s_4();
		  test_NFA_0s_or_01s_5();
		  test_NFA_0s_or_01s_6();
		  test_NFA_0s_or_01s_7();
		  test_NFA_0s_or_01s_8();
		  test_NFA_0s_or_01s_9();
		  test_NFA_0s_or_01s_10();
		  test_NFA_0s_or_01s_11();
		  test_NFA_0s_or_01s_12();

		  //test for NFA_1s_or_end_0
		   test_NFA_1s_or_end_0_1();
		   test_NFA_1s_or_end_0_2();
		   test_NFA_1s_or_end_0_3();
		   test_NFA_1s_or_end_0_4();
		   test_NFA_1s_or_end_0_5();
		   test_NFA_1s_or_end_0_6();
		   test_NFA_1s_or_end_0_7();
		   test_NFA_1s_or_end_0_8();
		   test_NFA_1s_or_end_0_9();
		   test_NFA_1s_or_end_0_10();
		   test_NFA_1s_or_end_0_11();
		   test_NFA_1s_or_end_0_12();


	//TASK 32
		cout << "TESTS FOR TASK 32: \n\n";
		if (NFA_Backtracking(NFA_11_00, myString("10101100")))
			cout << "TEST 1 PASSED\n\n";
		else
			cout << "TEST 1 NOT PASSED\n\n";
		if (!NFA_Backtracking(NFA_0s, myString("10101100")))
			cout << "TEST 2 PASSED\n\n";
		else
			cout << "TEST 2 NOT PASSED\n\n";
		if (NFA_Backtracking(NFA_0s, myString("0000")))
			cout << "TEST 3 PASSED\n\n";
		else
			cout << "TEST 3 NOT PASSED\n\n";
		if (NFA_Backtracking(NFA_0s_or_01s, myString("01010101")))
			cout << "TEST 4 PASSED\n\n";
		else
			cout << "TEST 4 NOT PASSED\n\n";
	
	//TASK 35
		cout << "TEST FOR TASKS 35: \n";
		if (NFA_Backtracking(NFA_Concat(NFA_10s,NFA_0s), myString("10101000000")))
			cout << "TEST 1 PASSED\n\n";
		else
			cout << "TEST 1 NOT PASSED\n\n";
		if (NFA_Backtracking(NFA_Concat(NFA_substring_1110, NFA_10s), myString("011101010")))
			cout << "TEST 2 PASSED\n\n";
		else
			cout << "TEST 2 NOT PASSED\n\n";

		if (NFA_Backtracking(NFA_Concat(NFA_10, NFA_1s_or_end_0), myString("1011111")))
			cout << "TEST 3 PASSED\n\n";
		else
			cout << "TEST 3 NOT PASSED\n\n";

		if (NFA_Backtracking(NFA_Concat(NFA_11_00, NFA_non_empty_even_len), myString("110011")))
			cout << "TEST 4 PASSED\n\n";
		else
			cout << "TEST 4 NOT PASSED\n\n";

		if (NFA_Backtracking(NFA_Concat(NFA_11_00, NFA_non_empty_even_len), myString("110011")))
			cout << "TEST 4 PASSED\n\n";
		else
			cout << "TEST 4 NOT PASSED\n\n";

		if (!NFA_Backtracking(NFA_Concat(NFA_11_00, NFA_non_empty_even_len), myString("EPSILON")))
			cout << "TEST 5 PASSED\n\n";
		else
			cout << "TEST 5 NOT PASSED\n\n";

		if (NFA_Backtracking(NFA_Concat(NFA_11_00, NFA_non_empty_even_len), myString("110000")))
			cout << "TEST 6 PASSED\n\n";
		else
			cout << "TEST 6 NOT PASSED\n\n";

		if (NFA_Backtracking(NFA_Concat(NFA_third_0, NFA_end_01), myString("000001")))
			cout << "TEST 7 PASSED\n\n";
		else
			cout << "TEST 7 NOT PASSED\n\n";

		if (NFA_Backtracking(NFA_Concat(NFA_0s, NFA_end_01), myString("000001")))
			cout << "TEST 8 PASSED\n\n";
		else
			cout << "TEST 8 NOT PASSED\n\n";
		if (NFA_Backtracking(NFA_Concat(NFA_end_01, NFA_0s), myString("000001000")))
			cout << "TEST 9 PASSED\n\n";
		else
			cout << "TEST 9 NOT PASSED\n\n";
		if (NFA_Backtracking(NFA_Concat(NFA_10, NFA_empty_string), myString("10")))
			cout << "TEST 10 PASSED\n\n";
		else
			cout << "TEST 10 NOT PASSED\n\n";
		if (NFA_Backtracking(NFA_Concat(NFA_0s, NFA_10), myString("00000010")))
			cout << "TEST 11 PASSED\n\n";
		else
			cout << "TEST 11 NOT PASSED\n\n";

		if (NFA_Backtracking(NFA_Concat(NFA_end_01, NFA_10), myString("0110")))
			cout << "TEST 12 PASSED\n\n";
		else
			cout << "TEST 12 NOT PASSED\n\n";

	
	char c;
	cin >> c;

	return 0;
  
  }
