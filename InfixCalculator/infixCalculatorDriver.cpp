/*******************************************************************************
** File: infixCalculatorDriver.cpp
** Purpose: Provide a demo of the infix calculator
** Author: Conner Pappas
** Date: 10/07/20
*******************************************************************************/
#include "./include/ConnerPappasPlexsys/infixCalculator.hpp"
#include <string>
#include <iostream>

using namespace std;

void printHeading() {
	cout << "****************************************" << endl <<
			"Infix Calculator - By Conner Pappas" << endl <<
			"****************************************" << endl;
}

int main () {
	InfixCalculator infixCal;
	string demoExpr = "(4 * 5 * (5 - 7) + ((4 - 3) / (2) + 5)) * (4 * (3 - 1))";
	string userExpr;
	float result;
	string userChoice;
	printHeading();

	cout << endl << "Quick demo:" << endl << "Evaluating expression: " <<
			demoExpr << endl;
	infixCal.setExpression(demoExpr);
	cout << "Resulting calculation: " << infixCal.evaluateExpression() << endl;

	cout << endl << "Would you like to try?(Y/N): ";
	cin >> userChoice;

	if (userChoice == "Y") {
		while (userChoice == "Y") {
			cout << "Input expression following normal conventions: ";
			getline(cin, userExpr);
			getline(cin, userExpr);
			cout << "Your expression: " << userExpr << endl << "Result: ";
			try {
				infixCal.setExpression(userExpr);
				result = infixCal.evaluateExpression();
				cout << result << endl << endl;
			}
			catch (const char* e) {
				cout << e << endl << endl;
			}
			cout << "Try again?(Y/N): ";
			cin >> userChoice;
		}
	}

	cout << "Goodbye!" << endl;

	return 0;
}
