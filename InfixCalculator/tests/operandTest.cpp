#include "./../src/operand.hpp"
#include "./../src/expressor.hpp"
#include <iostream>
#include <string>

using namespace std;

void testEvaluate(Operand opVal, int expecVal) {
	if (opVal.evaluate() == expecVal) {
		cout << "PASSED: " << expecVal << " was correctly assigned" << endl;
	}
	else {
		cout << "FAILED: " << expecVal << " was not correctly assigned" << endl;
	}
}

void testExpType(Operand op, int suffix) {
	if (op.getExpType() == "operand") {
		cout << "PASSED: op" << suffix << " is the right type" << endl;
	}
	else {
		cout << "FAILED: op" << suffix << " is the wrong type" << endl;
	}
}

void brokenConstructor(string invalidStr) {
	try {
		Operand opBroke(invalidStr);
		cout << "FAILED: Constructor didn't break as expected" << endl;
	}
	catch (exception& e) {
		cout << "PASSED: Constructor broke as expected" << endl;
	}
}

int main() {
	string initVal;
	Operand op1(initVal = "0");
	Operand op2(initVal = "10");

	cout << "Testing operand.evaluate" << endl;
	testEvaluate(op1, 0);
	testEvaluate(op2, 10);

	cout << "Testing operand.expType" << endl;
	testExpType(op1, 1);
	testExpType(op2, 2);

	cout << "Testing incorrect constructor assignment" << endl;
	brokenConstructor(initVal = "/");

	return 0;
}
