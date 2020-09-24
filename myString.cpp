#include "myString.h"

myString::myString(set<string> initAlphabet, vector<string> initString) {
	if (!check_alpha_string(initAlphabet, initString)) {
		cout << "The give alphabet and string are not comprehensive\n Fail to create new myString object\n";
		char c;
		cin >> c;
		exit(-1);
	}

	alphabet = initAlphabet;
	_string = initString;
	alphabetSize = initAlphabet.size();
	_stringLen = initString.size();
}
myString::myString(string initString) {
	if (initString == "EPSILON" || initString == "")
	{
		alphabet = set<string>{ "EPSILON" };
		_string = vector<string>{ "EPSILON" };
		alphabetSize = 0;
		_stringLen = 0;

	}
	else
		for (unsigned i = 0; i < initString.length();i++)
		{
			string a = "";
			a = a + initString[i];
			_string.push_back(a);
			alphabet.insert(a);
			_stringLen = _string.size();
			alphabetSize = alphabet.size();
		}
}
myString::myString(set<string> initAlphabet, string initString) {
	if (initString == "EPSILON")
	{
		alphabet = initAlphabet;
		_string = vector<string>{ "EPSILON" };
		alphabetSize = initAlphabet.size();
		_stringLen = 0;

	}
	else {
		vector<string> my_string = convert_standard_string_to_vector_based_string(initAlphabet, initString);

		alphabet = initAlphabet;
		_string = my_string;
		alphabetSize = initAlphabet.size();
		_stringLen = my_string.size();
	}
}

ostream& operator<<(ostream& OutStream, const myString& myObject) {

	if (myObject._stringLen == 0)
		cout << "EPSILON";

	for (int i = 0; i < myObject._stringLen;i++)
	{
		OutStream << myObject._string[i];
	}
	return OutStream;
}

vector<string> myString::convert_standard_string_to_vector_based_string(set<string> alphabet, string standard_string) {

	vector<string> newString;
	unsigned i = 0;
	string a = "";
	while (i < standard_string.length()) {

		a += standard_string[i];
		if (find(alphabet.begin(), alphabet.end(), a) != alphabet.end())
		{
			cout << "push " << a << " to the newString at i = " << i << endl;
			newString.push_back(a);
			a = "";
			i++;
		}
		else
		{
			i++;
			if (i == standard_string.length())
			{
				cout << "Fail to convert\n";
				char c;
				cin >> c;
				exit(-1);
			}
		}

	}
	return newString;
}

bool myString::check_alpha_string(set<string> myAlphabet, vector<string> _string) {

	if (_string[0] == "EPSILON")
		return true;
	for (unsigned i = 0; i < _string.size(); i++)
		if (find(myAlphabet.begin(), myAlphabet.end(), _string[i]) == myAlphabet.end())
			return false;
	return true;

}
