#include "./../src/infixValidator.hpp"
#include <string>
#include <iostream>

using namespace std;

void checkExpected(string input, infixValidator valObj, bool expected, bool exceptionExpected) {
	string expectedString;
	try {
		(expected) ? expectedString = " passed " : expectedString = " failed ";
		if (valObj.fullValidation(input) == expected) {
			cout << "PASSED: " << input << expectedString << "as expected" << endl;
		}
		else {
			cout << "FAILED: " << input << " unexpectedly failed" << endl;
		}
	}
	catch (const char* e) {
		(exceptionExpected) ? expectedString = "PASSED: EXCEPTION EXPECTED: " : expectedString = "FAILED: EXCEPTION NOT EXPECTED: ";
		cout << expectedString << input << " " << e << endl;;
	}
}

int main () {
	string testExp;
	infixValidator inVal;

	cout << "Testing infixValidator.fullValidation" << endl;
	checkExpected(testExp = "", inVal, false, true);
	checkExpected(testExp = "()", inVal, false, false);
	checkExpected(testExp = "(4", inVal, false, false);
	checkExpected(testExp = ")", inVal, false, false);
	checkExpected(testExp = "(", inVal, false, false);
	checkExpected(testExp = "( )", inVal, false, false);
	checkExpected(testExp = "(4)", inVal, true, false);
	checkExpected(testExp = "4", inVal, true, false);
	checkExpected(testExp = "40", inVal, true, false);
	checkExpected(testExp = "040", inVal, false, false);
	checkExpected(testExp = "0", inVal, true, false);
	checkExpected(testExp = "(0)", inVal, true, false);
	checkExpected(testExp = "(4+3)", inVal, false, false);
	checkExpected(testExp = "4+3", inVal, false, false);
	checkExpected(testExp = "( 4+3", inVal, false, false);
	checkExpected(testExp = "+ (4 + 3)", inVal, false, false);
	checkExpected(testExp = "(4 + 3 -", inVal, false, false);
	checkExpected(testExp = " ( 4+3", inVal, false, true);
	checkExpected(testExp = "( ))", inVal, false, false);
	checkExpected(testExp = "(( )", inVal, false, false);
	checkExpected(testExp = "(( / ))", inVal, false, false);
	checkExpected(testExp = "(( / 4))", inVal, false, false);
	checkExpected(testExp = "((3 / 4))", inVal, true, false);
	checkExpected(testExp = "(( 4 / ))", inVal, false, false);
	checkExpected(testExp = "() + ()", inVal, false, false);
	checkExpected(testExp = "() * (", inVal, false, false);
	checkExpected(testExp = "(9 + 8) - (8 * 7)", inVal, true, false);
	checkExpected(testExp = "(9  + 8) - (8 * 7)", inVal, false, false);
	checkExpected(testExp = "(9 +  8) - (8 * 7)", inVal, false, false);
	checkExpected(testExp = "(90 + 8) - (80 * 7)", inVal, true, false);
	checkExpected(testExp = "(909 + 8) - (808 * 7)", inVal, true, false);
	checkExpected(testExp = "(09 + 8) - (8 * 7)", inVal, false, false);
	checkExpected(testExp = "(9+8) - (8*7)", inVal, false, false);
	checkExpected(testExp = "(9+8)- (8*7)", inVal, false, false);
	checkExpected(testExp = "(9+8) -(8*7)", inVal, false, false);
	checkExpected(testExp = "((9 + 8) - (8 * 7))", inVal, true, false);
	checkExpected(testExp = "(9 + (8) - (80) * 7)", inVal, true, false);
	cout << endl;

	return 0;
}
