#include<iostream>
#include<string>
#include<set>
#include <vector>


using namespace std;


// Completed TASK 1 and 2 - REPRESENTING ALPHABET AND STRING

class myString {

private:
	set<string> alphabet;
	vector<string> _string;

	int alphabetSize;
	int _stringLen;

	// this function will break down each characters in a standard string and put it in _string provided the alphabet
	//e.g. Alphabet = {ab, c}   standar_string = "abcab"   =>  _stringSize = {ab,c,ab}    
	vector<string> convert_standard_string_to_vector_based_string(set<string> alphabet, string standard_string);

	//this function will check if a vector-based string contain any symbol does not belong to the given alphabet.
	bool check_alpha_string(set<string> myAlphabet, vector<string> _string);

public:

	myString() : alphabet(set<string> {"EPISILON"}), _string({ "EPSILON" }), alphabetSize(0), _stringLen(0) {};
	myString(set<string> initAlphabet, vector<string> initString);
	myString(string initString);
	myString(set<string> initAlphabet, string initString);
	myString(const myString& obj);


	set<string> getAlphabet() const { return alphabet; }
	vector<string> getString() const { return _string; }
	int getAlphabetSize() const { return alphabetSize; }
	int getStringLen() const { return _stringLen; }

	void print_discrete_character() {
		for (int i = 0; i < _stringLen;i++)
			cout << _string[i] << " ";
	}
	string getCharacterAt(int i) const {
	if (!_string.empty())
		return _string[i];
	else
		return "EPSILON";
	}
	
	void pop_front();
	void push_back(string);

	friend ostream&  operator<<(ostream& OutStream, const myString& myObject);
	void operator=(const myString& copiedOjb);
	bool operator==(const myString& obj);
	bool operator!=(const myString& obj);

};

bool isSubSet(set<string> alphabetA, set<string> alphabetB); // check if alphabetA a subset of alphabetB

int calculate_the_number_of_string_of_a_given_len_or_shorter_can_be_generated(int alphabetSize, int len);//helper function of generate_Nth_string_lexi


// **** TASK 3 ****/ 
myString generate_Nth_string_lexi(set<string> alphabet, int n); 



#endif // !MYSTRING_H

