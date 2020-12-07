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

myString::myString(const myString& obj) {
	alphabet = obj.alphabet;
	_string = obj._string;
	alphabetSize = obj.alphabetSize;
	_stringLen = obj._stringLen;

};

ostream& operator<<(ostream& OutStream, const myString& myObject) {

	if (myObject._stringLen == 0)
		cout << "EPSILON";

	for (int i = 0; i < myObject._stringLen;i++)
	{
		OutStream << myObject._string[i];
	}
	return OutStream;
}

void myString::operator=(const myString& copiedOjb) {
	alphabet = copiedOjb.alphabet;
	_string = copiedOjb._string;
	alphabetSize = copiedOjb.alphabetSize;
	_stringLen = copiedOjb._stringLen;

}

bool myString::operator==(const myString& obj) {
	if ((isSubSet(alphabet,obj.alphabet)|| isSubSet(obj.alphabet, alphabet)) && _string == obj._string)
		return true;
	return false;

}

bool myString::operator!=(const myString& obj) {
	if (!(isSubSet(alphabet, obj.alphabet) || isSubSet(obj.alphabet, alphabet)) || _string != obj._string ||_stringLen != obj._stringLen)
		return true;
	return false;

}

vector<string> myString::convert_standard_string_to_vector_based_string(set<string> alphabet, string standard_string) {

	vector<string> newString;
	unsigned i = 0;
	string a = "";
	while (i < standard_string.length()) {

		a += standard_string[i];
		if (find(alphabet.begin(), alphabet.end(), a) != alphabet.end())
		{
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

bool isSubSet(set<string> alphabetA, set<string> alphabetB) {

	if (alphabetA == set<string>{"EPSILON"})
		return true;
	
	for (auto &each:alphabetA)
		if (find(alphabetB.begin(), alphabetB.end(), each) == alphabetB.end())
			return false;
		
		return true;
}


int calculate_the_number_of_string_of_a_given_len_or_shorter_can_be_generated(int alphabetSize, int len) {
	int result = 0, i = 0;
	while (i < len)
	{
		result += (int) pow(alphabetSize, i);
		i++;
	}
	return result;
}



// Completed TASK 3 - write a function that generates the Nth string of a given alphabet’s lexicographic order.


myString generate_Nth_string_lexi(set<string> alphabet, int n) {
	vector<string> result;
	
	if (n <= 1)
	{
		myString newString(alphabet, vector<string> {"EPSILON"});
		return newString;
	}
	int len = (int) floor(log(n) / log(alphabet.size()));
	
	for (len; len > 0; len--)
	{
		int number_of_string_with_shorter_len = calculate_the_number_of_string_of_a_given_len_or_shorter_can_be_generated(alphabet.size(), len);
	
		int next_sympol_position_in_alphabet = (int) floor( ( n - number_of_string_with_shorter_len- 1) /  ( pow(alphabet.size(),len) / alphabet.size() ) );

		n = (n - number_of_string_with_shorter_len - 1) % (int) pow(alphabet.size(), len - 1)  + calculate_the_number_of_string_of_a_given_len_or_shorter_can_be_generated(alphabet.size(), len-1) + 1;
		
		auto p = alphabet.begin();

		for (int i = 0; i < next_sympol_position_in_alphabet; i++)
			p++;
		result.push_back(*p);
	}
	myString newString(alphabet, result);
	return newString;
}
/*******************************************/

void myString::pop_front() {
	if (!_string.empty() && _string[0] != "EPSILON")
	{
		_string.erase(_string.begin());

		_stringLen--;
	
	if (_stringLen == 0)
		_string.push_back("EPSILON");
	}
}

void myString::push_back(string newCharacter) {

	if (alphabet.find(newCharacter) != alphabet.end())
	{
		if (_string[0] != "EPSILON")
		
			_string.push_back(newCharacter);
			
		else
			_string[0] = newCharacter;

		_stringLen++;
	}
}

myString operator+(const myString & obj1, const myString& obj2) {
	myString obj = obj1;
	for (auto &each : obj2.getAlphabet())
		if (find(obj.alphabet.begin(), obj.alphabet.end(), each) == obj.alphabet.end()) {
			obj.alphabetSize++;
			obj.alphabet.insert(each);
		}
	for (auto &each : obj2._string) {
		obj._string.push_back(each);
		obj._stringLen++;
	}
	return obj;
}


