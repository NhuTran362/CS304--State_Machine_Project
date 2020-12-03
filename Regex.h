#ifndef _REGEX_H_
#define _REGEX_H_

#include "myString.h"
//TASK 41
class Regex {
public:
	virtual void print_regex() { cout << "regex\n"; }; // TASK 42
	virtual bool accept(myString r) { return 0; };
	
};
class RE_Empty : public Regex {
public:
	RE_Empty() {};
	void print_regex() { cout << "Empty"; }
	bool accept(myString r) { return false; }
};

class RE_Epsilon: public Regex {
public:
	RE_Epsilon() {};
	void print_regex() { cout << "E"; }
	bool accept(myString r) { return r == myString(r.getAlphabet(), reg); }
private:
	string reg = "EPSILON";
 };
class RE_Char : public Regex{
public:
	RE_Char(string init) : reg(init) {}
	void print_regex() { cout << reg; }
	bool accept(myString r) { if (r == myString(reg)) return true; return false; }
	myString getReg()const { return reg; }
private:
	string reg;
};

class RE_Union : public Regex {
public:
	RE_Union( Regex& a,  Regex& b) : lhs(&a), rhs(&b) {}
	~RE_Union() {
		delete lhs;
		delete rhs;
	}
	void print_regex() { lhs->print_regex(); cout << " U "; rhs->print_regex(); }
	bool accept(myString r) {
		
		return lhs->accept(r) || rhs->accept(r);
	}
	Regex& getLhs() const { return *lhs; }
	Regex& getrhs() const { return *rhs; }
private:
	Regex* lhs;
	Regex* rhs;

};

class RE_Start : public Regex {
public:
	RE_Start(Regex& arg) : reg(&arg) {}
	~RE_Start() {
		delete reg;
	}
	void print_regex() { cout << "( "; reg->print_regex(); cout << "*"; cout << ")"; }
	bool accept(myString r) {
		string a = "";
		for (int i = 0; i < r.getStringLen(); i++) {
			a += r.getCharacterAt(i);
			if (reg->accept(myString(a)))
				a = "";
		}	
		return (a == "");
	}
private:
	Regex* reg;
};

class RE_Circ : public Regex {
public:
	RE_Circ(Regex &a, Regex &b) : lhs(&a), rhs(&b) {}
	~RE_Circ() {
		delete lhs;
		delete rhs;
	}
	void print_regex() { lhs->print_regex(); cout << " o "; rhs->print_regex(); }
	bool accept(myString r) {
		string a = "";
		vector<int> marker;
		for (int i = 0; i < r.getStringLen(); i++) {
			a += r.getCharacterAt(i);
			if (lhs->accept(myString(a))) {
				marker.push_back(i + 1);
			}
		}

			for (auto & each : marker) {
				a = "";
				for (int i = each; i < r.getStringLen(); i++) {
					a += r.getCharacterAt(i);
					if (rhs->accept(a) && i == r.getStringLen() -1)
						return true;
				}
			}
			return false;
	}

private:
	Regex* lhs;
	Regex* rhs;
};

#endif // !_REGEX_H_
