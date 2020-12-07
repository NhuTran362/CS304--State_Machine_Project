#include "myString.h"
#include "Regex.h"

//TASK 44
void test_r1() {
	cout << "\n\ntest_r1: ";
	if (!(re_empty.accept(myString("0"))))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r2() {
	cout << "test_r2: ";
	if (!(r1.accept(myString("0"))) &&  r1.accept(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r3() {
	cout << "test_r3: ";
	if (r0.accept(myString("0")) && !(r0.accept(myString("1"))) )
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r4() {
	cout << "test_r4: ";
	if (r_0U1.accept(myString("0")) && r_0U1.accept(myString("1")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r5() {
	cout << "test_r5: ";
	if (r0_start.accept(myString("0000")) && !r0_start.accept(myString("001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r6() {
	cout << "test_r6: ";
	if (r_01.accept(myString("01")) && !r_01.accept(myString("010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r7() {
	cout << "test_r7: ";
	if (r_10.accept(myString("10")) && !r_10.accept(myString("1001")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r8() {
	cout << "test_r8: ";
	if (r_10_Start.accept(myString("101010")) && !r_10_Start.accept(myString("10100010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r9() {
	cout << "test_r9: ";
	if (r_01_10_Start.accept(myString("011010")) && !r_01_10_Start.accept(myString("01")) && !r_01_10_Start.accept(myString("101010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r10() {
	cout << "test_r10: ";
	if (r_00.accept(myString("00")) && !r_00.accept(myString("01")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r11() {
	cout << "test_r11: ";
	if (r_00U01_10_Start.accept(myString("00"))  && r_00U01_10_Start.accept(myString("011010"))  && !r_00U01_10_Start.accept(myString("010")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}
void test_r12() {
	cout << "test_r12: ";
	if (r1.accept(myString("1")) && !r1.accept(myString("11")) && !r1.accept(myString("01")))
		cout << "PASSED\n\n";
	else
		cout << "NOT PASSED\n\n";
}

//TASK 45
myString Regex_Generator(Regex* obj) {
	if (obj->type == "Empty")
		return myString("false");
	else if (obj->type == "Epsilon")
		return myString("EPSILON");
	else if (obj->type == "Character") {
		RE_Char * temp = (RE_Char*)obj;
		return myString(temp->getReg());
	}
	else if (obj->type == "Union") {
		RE_Union * temp = (RE_Union *)obj;
		myString t1 = Regex_Generator(&temp->getLhs());
		if (t1 != myString("false"))
			return t1;
		else {
			t1 = Regex_Generator(&temp->getrhs());
			if (t1 != myString("false"))
				return t1;
		}
		return myString("false");
	}
	else if (obj->type == "Start") {
		return myString("EPSILON");
	}
	else if (obj->type == "Circ") {
		RE_Circ* temp = (RE_Circ*)obj;
		myString s1 = Regex_Generator(&temp->getLhs());
		myString s2 = Regex_Generator(&temp->getRhs());
		if (s1 != myString("false") && s2 != myString("false")){
			return s1 + s2;
		}
		return myString("false");
	}
	return myString("false");

}
