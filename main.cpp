#include "myString.cpp"

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
	
	char c;
	cin >> c;

	return 0;
}
	
	char c;
	cin >> c;

	return 0;
  
  }
