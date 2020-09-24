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
  
  }
