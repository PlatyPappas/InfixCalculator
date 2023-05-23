#include "./../include/ConnerPappasPlexsys/infixCalculator.hpp"
#include <string>
#include <iostream>

using namespace std;

void checkEquality (float calculated, float actual) {
	if (calculated == actual) {
		cout << "PASSED: Calculated val: " << calculated << " Actual: " << actual << endl;
	}
	else {
		cout << "FAILED: Calcualted val: " << calculated << " Actual: " << actual << endl;
	}
}

int main () {
	InfixCalculator infixCal;

	vector<string> expressions;
	vector<float> solutions;
	vector<bool> expectedExceptions;
	string setString;
	InfixCalculator infix2(setString = "(50) + (3 * 9)");

	expressions.push_back(setString = "((3 * 5 + 2) * (8 * (1 + 1)) + 1 * 5)");
	expressions.push_back(setString = "(4 * 5 * (5 - 7) + ((4 - 3) / (2) + 5)) * (4 * (3 - 1))");
	expressions.push_back(setString = "((36 - 2)) - (4 * (2 + 1)) + 5 * 2");
	expressions.push_back(setString = "(9 + 8) - (8 * 7)");
	expressions.push_back(setString = "5");
	expressions.push_back(setString = "(5)");
	expressions.push_back(setString = "( 5)");

	solutions.push_back(277);
	solutions.push_back(-276);
	solutions.push_back(32);
	solutions.push_back(-39);
	solutions.push_back(5);
	solutions.push_back(5);
	solutions.push_back(0);

	expectedExceptions.push_back(false);
	expectedExceptions.push_back(false);
	expectedExceptions.push_back(false);
	expectedExceptions.push_back(false);
	expectedExceptions.push_back(false);
	expectedExceptions.push_back(false);
	expectedExceptions.push_back(true);

	cout << "Testing super complicated calculator" << endl;
	for (unsigned int i = 0; i < expressions.size(); i++) {
		try {
			infixCal.setExpression(expressions[i]);
			checkEquality(infixCal.evaluateExpression(), solutions[i]);
		}
		catch (const char* e){
			if (expectedExceptions[i]){
				cout << "PASSED: Exception expected for: " << expressions[i] << endl;
			}
			else {
				cout << "FAILED: Exception unexpected for: " << expressions[i] << endl;
			}
		}
	}

	try {
		checkEquality(infix2.evaluateExpression(), 77);
	}
	catch (const char* e){
		cout << e << endl;
	}

	return 0;
}
