#include "./../src/expressor.hpp"
#include "./../src/operand.hpp"
#include "./../src/operator.hpp"
#include "./expressionHelpers.hpp"
#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

template <class T, class U, class V>
void checkExpected(T input, U func (T), V expected) {
	string expectedString;
	if (func(input) == expected) {
		expectedString = " passed ";
	}
	else {
		expectedString = " failed ";
	}
		if (func(input) == expected) {
			cout << "PASSED: " << input << expectedString << "as expected" << endl << endl;
		}
		else {
			cout << "FAILED: " << input << " unexpectedly failed" << endl << endl;
		}
}

void checkEqualityE (float calculated, float actual) {
	if (calculated == actual) {
		cout << "PASSED: Calculated val: " << calculated << " Actual: " << actual << endl;
	}
	else {
		cout << "FAILED: Calcualted val: " << calculated << " Actual: " << actual << endl;
	}
}

int main() {
	string withSpaces = "L o o k ma, no s p a c es";
	string noSpace = "Lookma,nospaces";
	checkExpected(withSpaces, removeSpaces, noSpace);


	vector<string> expressions;
	vector<float> solutions;

	expressions.push_back("(3*5+2)*(8*(1+1))+1*5)");
	expressions.push_back("(4*5*(5-7)+((4-3)/(2)+5))*(4*(3-1))");
	expressions.push_back("((36-2))-(4*(2+1))+5*2");
	expressions.push_back("2-((2+3*2+5)/(13)+1)");
	expressions.push_back("5");
	expressions.push_back("(5)");

	solutions.push_back(277);
	solutions.push_back(-276);
	solutions.push_back(32);
	solutions.push_back(0);
	solutions.push_back(5);
	solutions.push_back(5);

	cout << "Testing super complicated calculator" << endl;
	for (unsigned int i = 0; i < expressions.size(); i++) {
		checkEqualityE(evaluateExpression(expressions[i]), solutions[i]);
	}

	cout << "End of driver" << endl;
	return 0;
}
