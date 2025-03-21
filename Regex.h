#ifndef _REGEX_H_
#define _REGEX_H_
#include "myString.h"

//TASK 41
class Regex {
public:
	virtual void print_regex() { cout << "regex\n"; }; // TASK 42
	virtual bool accept(myString r) { return 0; };
	string type;
	
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
	Regex& getRhs() const { return *rhs; }
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
		if (r == myString("EPSILON"))
			return true;
		string a = "";
		vector<int> marker;
		for (int i = 0; i < r.getStringLen(); i++) {
			a += r.getCharacterAt(i);
			if (reg->accept(myString(a))) {
				marker.push_back(i);
				if (i == r.getStringLen() - 1)
					return true;
			}
		}
		int k = 0;
		while (k < marker.size()) {
			a = "";
			for (int i = marker[k] + 1; i < r.getStringLen(); i++) {
				a += r.getCharacterAt(i);			
				if (reg->accept(myString(a))) {
					cout << r.getStringLen() - 1 << endl;
					if (i == r.getStringLen() - 1)
						return true;
					marker.push_back(i);
				}
			}
			k++;
		}
		return false;
	}
	Regex* getReg() const { return reg; }
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
	Regex& getLhs() const { return *lhs; }
	Regex& getRhs() const { return *rhs; }
private:
	Regex* lhs;
	Regex* rhs;
};

//TASK 43
static  RE_Empty re_empty;
static  RE_Epsilon re_epsilon;
static  RE_Char r0("0");
static  RE_Char r1("1");
static  RE_Union r_0U1(r0, r1);
static  RE_Start r0_start(r0);
static  RE_Circ r_01(r0, r1);
static  RE_Circ r_10(r1,r0);
static  RE_Start r_10_Start(r_10);
static  RE_Circ r_01_10_Start(r_01, r_10_Start);
static  RE_Circ r_00(r0, r0);
static  RE_Union r_00U01_10_Start(r_00, r_01_10_Start);

//TASK 44
void test_r1();
void test_r2();
void test_r3();
void test_r4();
void test_r5();
void test_r6();
void test_r7();
void test_r8();
void test_r9();
void test_r10();
void test_r11();
void test_r12();

//TASK 45
myString Regex_Generator(Regex* obj);
#endif // !_REGEX_H_
