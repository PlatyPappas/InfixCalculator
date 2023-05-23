#include <string>
#include <iostream>
#include "helperFunctions.hpp"

using namespace std;

template <class T, class U, class V>
void checkExpected(T input, U func (T), V expected, bool exceptionExpected) {
	string expectedString;
	try {
		(expected) ? expectedString = " passed " : expectedString = " failed ";
		if (func(input) == expected) {
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

template <class S, class T, class U, class V>
void checkExpectedTwoArgs(S input1, T input2, U func (S, T), V expected, bool exceptionExpected) {
	string expectedString;
	try {
		(expected) ? expectedString = " passed " : expectedString = " failed ";
		if (func(input1, input2) == expected) {
			cout << "PASSED: " << " " << input2 << " " << expectedString << "as expected" << endl;
		}
		else {
			cout << "FAILED: " << " " << input2 << " " << " unexpectedly failed" << endl;
		}
	}
	catch (const char* e) {
		(exceptionExpected) ? expectedString = "PASSED: EXCEPTION EXPECTED: " : expectedString = "FAILED: EXCEPTION NOT EXPECTED: ";
		cout << expectedString << " " << input2 << " " << " " << e << endl;;
	}
}

int main () {
	string testExp;
	vector<unsigned int> testVec;

	cout << "Testing isValid" << endl;
	checkExpected('0', isValid, true, false);
	checkExpected('9', isValid, true, false);
	checkExpected('+', isValid, true, false);
	checkExpected('-', isValid, true, false);
	checkExpected('/', isValid, true, false);
	checkExpected('*', isValid, true, false);
	checkExpected('(', isValid, true, false);
	checkExpected(')', isValid, true, false);
	checkExpected(' ', isValid, true, false);
	checkExpected('a', isValid, false, false);
	checkExpected('z', isValid, false, false);
	checkExpected(';', isValid, false, false);
	checkExpected('>', isValid, false, false);
	cout << endl;

	cout << "Testing invalidCharCheck" << endl;
	checkExpected(testExp = "0", invalidCharCheck, true, false);
	checkExpected(testExp = "10", invalidCharCheck, true, false);
	checkExpected(testExp = " 2+ )", invalidCharCheck, true, false);
	checkExpected(testExp = "a", invalidCharCheck, false, false);
	checkExpected(testExp = "7z", invalidCharCheck, false, false);
	checkExpected(testExp = "        ", invalidCharCheck, true, false);
	checkExpected(testExp = "<>", invalidCharCheck, false, false);
	cout << endl;

	cout << "Testing checkParenthesesPairs" << endl;
	checkExpected(testExp = "()", checkParenthesesPairs, true, false);
	checkExpected(testExp = "(", checkParenthesesPairs, false, false);
	checkExpected(testExp = ")", checkParenthesesPairs, false, false);
	checkExpected(testExp = "( )", checkParenthesesPairs, true, false);
	checkExpected(testExp = "(4)", checkParenthesesPairs, true, false);
	checkExpected(testExp = "(4+3)", checkParenthesesPairs, true, false);
	checkExpected(testExp = "( ))", checkParenthesesPairs, false, false);
	checkExpected(testExp = "(( )", checkParenthesesPairs, false, false);
	checkExpected(testExp = "", checkParenthesesPairs, true, false);
	checkExpected(testExp = "(())", checkParenthesesPairs, true, false);
	checkExpected(testExp = "()()", checkParenthesesPairs, true, false);
	checkExpected(testExp = "()(", checkParenthesesPairs, false, false);
	checkExpected(testExp = "(9 + 8) - (8 * 7)", checkParenthesesPairs, true, false);
	checkExpected(testExp = "((9 + 8) - (8 * 7))", checkParenthesesPairs, true, false);
	checkExpected(testExp = "(9 + (8) - (8) * 7)", checkParenthesesPairs, true, false);
	cout << endl;

	cout << "Testing checkOpenParentheses" << endl;
	checkExpected(testExp = "()", checkOpenParentheses, false, false);
	checkExpected(testExp = "", checkOpenParentheses, false, true);
	checkExpected(testExp = "(4", checkOpenParentheses, true, false);
	checkExpected(testExp = ")", checkOpenParentheses, true, false);
	checkExpected(testExp = "(", checkOpenParentheses, false, true);
	checkExpected(testExp = "( )", checkOpenParentheses, false, false);
	checkExpected(testExp = "(4)", checkOpenParentheses, true, false);
	checkExpected(testExp = "(4+3)", checkOpenParentheses, true, false);
	checkExpected(testExp = "4+3", checkOpenParentheses, true, false);
	checkExpected(testExp = "( 4+3", checkOpenParentheses, false, false);
	checkExpected(testExp = " ( 4+3", checkOpenParentheses, false, true);
	checkExpected(testExp = "( ))", checkOpenParentheses, false, false);
	checkExpected(testExp = "(( )", checkOpenParentheses, false, false);
	checkExpected(testExp = "(())", checkOpenParentheses, false, false);
	checkExpected(testExp = "()()", checkOpenParentheses, false, false);
	checkExpected(testExp = "()(", checkOpenParentheses, false, false);
	checkExpected(testExp = "(9 + 8) - (8 * 7)", checkOpenParentheses, true, false);
	checkExpected(testExp = "((9 + 8) - (8 * 7))", checkOpenParentheses, true, false);
	checkExpected(testExp = "(9 + (8) - (8) * 7)", checkOpenParentheses, true, false);
	cout << endl;

	cout << "Testing checkCloseParentheses" << endl;
	checkExpected(testExp = "()", checkCloseParentheses, false, false);
	checkExpected(testExp = "(4)", checkCloseParentheses, true, false);
	checkExpected(testExp = "", checkCloseParentheses, false, true);
	checkExpected(testExp = " ( 4+3", checkCloseParentheses, false, true);
	checkExpected(testExp = ")", checkCloseParentheses, false, true);
	checkExpected(testExp = "( )", checkCloseParentheses, false, false);
	checkExpected(testExp = "(4)", checkCloseParentheses, true, false);
	checkExpected(testExp = "(4+3)", checkCloseParentheses, true, false);
	checkExpected(testExp = "( ))", checkCloseParentheses, false, false);
	checkExpected(testExp = "(( )", checkCloseParentheses, false, false);
	checkExpected(testExp = "(())", checkCloseParentheses, false, false);
	checkExpected(testExp = "()()", checkCloseParentheses, false, false);
	checkExpected(testExp = "()(", checkCloseParentheses, false, false);
	checkExpected(testExp = "(9 + 8) - (8 * 7)", checkCloseParentheses, true, false);
	checkExpected(testExp = "((9 + 8) - (8 * 7))", checkCloseParentheses, true, false);
	checkExpected(testExp = "(9 + (8) - (8) * 7)", checkCloseParentheses, true, false);
	cout << endl;

	cout << "Testing parenthesesCheck" << endl;
	checkExpected(testExp = "()", parenthesesCheck, false, false);
	checkExpected(testExp = "", parenthesesCheck, false, true);
	checkExpected(testExp = "(4", parenthesesCheck, false, false);
	checkExpected(testExp = ")", parenthesesCheck, false, false);
	checkExpected(testExp = "(", parenthesesCheck, false, true);
	checkExpected(testExp = "( )", parenthesesCheck, false, false);
	checkExpected(testExp = "(4)", parenthesesCheck, true, false);
	checkExpected(testExp = "(4+3)", parenthesesCheck, true, false);
	checkExpected(testExp = "4+3", parenthesesCheck, true, false);
	checkExpected(testExp = "( 4+3", parenthesesCheck, false, false);
	checkExpected(testExp = " ( 4+3", parenthesesCheck, false, true);
	checkExpected(testExp = "( ))", parenthesesCheck, false, false);
	checkExpected(testExp = "(( )", parenthesesCheck, false, false);
	checkExpected(testExp = "(())", parenthesesCheck, false, false);
	checkExpected(testExp = "()()", parenthesesCheck, false, false);
	checkExpected(testExp = "()(", parenthesesCheck, false, false);
	checkExpected(testExp = "(9 + 8) - (8 * 7)", parenthesesCheck, true, false);
	checkExpected(testExp = "(9+8) - (8*7)", parenthesesCheck, true, false);
	checkExpected(testExp = "(9+8)- (8*7)", parenthesesCheck, false, false);
	checkExpected(testExp = "(9+8) -(8*7)", parenthesesCheck, false, false);
	checkExpected(testExp = "((9 + 8) - (8 * 7))", parenthesesCheck, true, false);
	checkExpected(testExp = "(9 + (8) - (8) * 7)", parenthesesCheck, true, false);
	cout << endl;

	cout << "Testing operatorPreSpaceCheck" << endl;
	checkExpectedTwoArgs(testVec = {1}, testExp = "3 + 4", operatorPreSpaceCheck, true, false);
	cout << endl;

	cout << "Testing operatorPostSpaceCheck" << endl;
	checkExpectedTwoArgs(testVec = {3}, testExp = "3 + 4", operatorPostSpaceCheck, true, false);
	cout << endl;

	cout << "Testing operatorCheck" << endl;
	checkExpected(testExp = "()", operatorCheck, true, false);
	checkExpected(testExp = "", operatorCheck, false, true);
	checkExpected(testExp = "(4", operatorCheck, true, false);
	checkExpected(testExp = ")", operatorCheck, true, false);
	checkExpected(testExp = "(", operatorCheck, true, true);
	checkExpected(testExp = "( )", operatorCheck, true, false);
	checkExpected(testExp = "(4)", operatorCheck, true, false);
	checkExpected(testExp = "(4+3)", operatorCheck, false, false);
	checkExpected(testExp = "4+3", operatorCheck, false, false);
	checkExpected(testExp = "( 4+3", operatorCheck, false, false);
	checkExpected(testExp = "+ (4 + 3)", operatorCheck, false, false);
	checkExpected(testExp = "(4 + 3 -", operatorCheck, false, false);
	checkExpected(testExp = " ( 4+3", operatorCheck, false, true);
	checkExpected(testExp = "( ))", operatorCheck, true, false);
	checkExpected(testExp = "(( )", operatorCheck, true, false);
	checkExpected(testExp = "(( / ))", operatorCheck, false, false);
	checkExpected(testExp = "(( / 4))", operatorCheck, false, false);
	checkExpected(testExp = "((3 / 4))", operatorCheck, true, false);
	checkExpected(testExp = "(( 4 / ))", operatorCheck, false, false);
	checkExpected(testExp = "() + ()", operatorCheck, true, false);
	checkExpected(testExp = "() * (", operatorCheck, true, false);
	checkExpected(testExp = "(9 + 8) - (8 * 7)", operatorCheck, true, false);
	checkExpected(testExp = "(9+8) - (8*7)", operatorCheck, false, false);
	checkExpected(testExp = "(9+8)- (8*7)", operatorCheck, false, false);
	checkExpected(testExp = "(9+8) -(8*7)", operatorCheck, false, false);
	checkExpected(testExp = "((9 + 8) - (8 * 7))", operatorCheck, true, false);
	checkExpected(testExp = "(9 + (8) - (8) * 7)", operatorCheck, true, false);
	cout << endl;

	cout << "Testing validateZeroes" << endl;
	checkExpectedTwoArgs(testVec = {1}, testExp = "0", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {1}, testExp = "(0)", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {2}, testExp = " 0 ", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {1, 2}, testExp = "00", validateZeroes, false, false);
	checkExpectedTwoArgs(testVec = {1, 5}, testExp = "0 + 0", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {1, 2, 6}, testExp = "00 + 0", validateZeroes, false, false);
	checkExpectedTwoArgs(testVec = {2, 3}, testExp = "900", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {2}, testExp = "909", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {2, 7}, testExp = "909 + 0", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {1, 6}, testExp = "(0 + 909)", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {2, 3, 8}, testExp = "(900 + 909)", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {2, 8}, testExp = "901 + 909", validateZeroes, true, false);
	checkExpectedTwoArgs(testVec = {1, 5}, testExp = "0 + 09)", validateZeroes, false, false);
	cout << endl;

	cout << "Testing numberPreSpaceCheck" << endl;
	checkExpectedTwoArgs(testVec = {4}, testExp = "(3 + 4)", numberPreSpaceCheck, true, false);
	cout << endl;

	cout << "Testing numberPostSpaceCheck" << endl;
	checkExpectedTwoArgs(testVec = {2}, testExp = "(3 + 4)", numberPostSpaceCheck, true, false);
	cout << endl;

	cout << "Testing numbersCheck" << endl;
	checkExpected(testExp = "()", numbersCheck, true, false);
	checkExpected(testExp = "", numbersCheck, false, true);
	checkExpected(testExp = "(4", numbersCheck, true, false);
	checkExpected(testExp = ")", numbersCheck, true, false);
	checkExpected(testExp = "(", numbersCheck, true, true);
	checkExpected(testExp = "( )", numbersCheck, true, false);
	checkExpected(testExp = "(4)", numbersCheck, true, false);
	checkExpected(testExp = "4", numbersCheck, true, false);
	checkExpected(testExp = "40", numbersCheck, true, false);
	checkExpected(testExp = "040", numbersCheck, false, false);
	checkExpected(testExp = "0", numbersCheck, true, false);
	checkExpected(testExp = "(0)", numbersCheck, true, false);
	checkExpected(testExp = "(4+3)", numbersCheck, false, false);
	checkExpected(testExp = "4+3", numbersCheck, false, false);
	checkExpected(testExp = "( 4+3", numbersCheck, false, false);
	checkExpected(testExp = "+ (4 + 3)", numbersCheck, true, false);
	checkExpected(testExp = "(4 + 3 -", numbersCheck, true, false);
	checkExpected(testExp = " ( 4+3", numbersCheck, false, true);
	checkExpected(testExp = "( ))", numbersCheck, true, false);
	checkExpected(testExp = "(( )", numbersCheck, true, false);
	checkExpected(testExp = "(( / ))", numbersCheck, true, false);
	checkExpected(testExp = "(( / 4))", numbersCheck, true, false);
	checkExpected(testExp = "((3 / 4))", numbersCheck, true, false);
	checkExpected(testExp = "(( 4 / ))", numbersCheck, false, false);
	checkExpected(testExp = "() + ()", numbersCheck, true, false);
	checkExpected(testExp = "() * (", numbersCheck, true, false);
	checkExpected(testExp = "(9 + 8) - (8 * 7)", numbersCheck, true, false);
	checkExpected(testExp = "(9  + 8) - (8 * 7)", numbersCheck, false, false);
	checkExpected(testExp = "(9 +  8) - (8 * 7)", numbersCheck, false, false);
	checkExpected(testExp = "(90 + 8) - (80 * 7)", numbersCheck, true, false);
	checkExpected(testExp = "(909 + 8) - (808 * 7)", numbersCheck, true, false);
	checkExpected(testExp = "(09 + 8) - (8 * 7)", numbersCheck, false, false);
	checkExpected(testExp = "(9+8) - (8*7)", numbersCheck, false, false);
	checkExpected(testExp = "(9+8)- (8*7)", numbersCheck, false, false);
	checkExpected(testExp = "(9+8) -(8*7)", numbersCheck, false, false);
	checkExpected(testExp = "((9 + 8) - (8 * 7))", numbersCheck, true, false);
	checkExpected(testExp = "(9 + (8) - (8) * 7)", numbersCheck, true, false);
	cout << endl;

	cout << "Testing spacesCheck" << endl;
	checkExpected(testExp = "", spacesCheck, false, true);
	checkExpected(testExp = "()", spacesCheck, true, false);
	checkExpected(testExp = "4", spacesCheck, true, false);
	checkExpected(testExp = " )", spacesCheck, false, false);
	checkExpected(testExp = "( ", spacesCheck, false, false);
	checkExpected(testExp = " ( ) ", spacesCheck, false, false);
	cout << endl;

	cout << "Testing fullValidation" << endl;
	checkExpected(testExp = "", fullValidation, false, true);
	checkExpected(testExp = "()", fullValidation, false, false);
	checkExpected(testExp = "(4", fullValidation, false, false);
	checkExpected(testExp = ")", fullValidation, false, false);
	checkExpected(testExp = "(", fullValidation, false, false);
	checkExpected(testExp = "( )", fullValidation, false, false);
	checkExpected(testExp = "(4)", fullValidation, true, false);
	checkExpected(testExp = "4", fullValidation, true, false);
	checkExpected(testExp = "40", fullValidation, true, false);
	checkExpected(testExp = "040", fullValidation, false, false);
	checkExpected(testExp = "0", fullValidation, true, false);
	checkExpected(testExp = "(0)", fullValidation, true, false);
	checkExpected(testExp = "(4+3)", fullValidation, false, false);
	checkExpected(testExp = "4+3", fullValidation, false, false);
	checkExpected(testExp = "( 4+3", fullValidation, false, false);
	checkExpected(testExp = "+ (4 + 3)", fullValidation, false, false);
	checkExpected(testExp = "(4 + 3 -", fullValidation, false, false);
	checkExpected(testExp = " ( 4+3", fullValidation, false, true);
	checkExpected(testExp = "( ))", fullValidation, false, false);
	checkExpected(testExp = "(( )", fullValidation, false, false);
	checkExpected(testExp = "(( / ))", fullValidation, false, false);
	checkExpected(testExp = "(( / 4))", fullValidation, false, false);
	checkExpected(testExp = "((3 / 4))", fullValidation, true, false);
	checkExpected(testExp = "(( 4 / ))", fullValidation, false, false);
	checkExpected(testExp = "() + ()", fullValidation, false, false);
	checkExpected(testExp = "() * (", fullValidation, false, false);
	checkExpected(testExp = "(9 + 8) - (8 * 7)", fullValidation, true, false);
	checkExpected(testExp = "(9  + 8) - (8 * 7)", fullValidation, false, false);
	checkExpected(testExp = "(9 +  8) - (8 * 7)", fullValidation, false, false);
	checkExpected(testExp = "(90 + 8) - (80 * 7)", fullValidation, true, false);
	checkExpected(testExp = "(909 + 8) - (808 * 7)", fullValidation, true, false);
	checkExpected(testExp = "(09 + 8) - (8 * 7)", fullValidation, false, false);
	checkExpected(testExp = "(9+8) - (8*7)", fullValidation, false, false);
	checkExpected(testExp = "(9+8)- (8*7)", fullValidation, false, false);
	checkExpected(testExp = "(9+8) -(8*7)", fullValidation, false, false);
	checkExpected(testExp = "((9 + 8) - (8 * 7))", fullValidation, true, false);
	checkExpected(testExp = "(9 + (8) - (80) * 7)", fullValidation, true, false);
	cout << endl;

	return 0;
}
