/*******************************************************************************
** File: infixValidator.hpp
** Purpose: Define infixValidator class
** Author: Conner Pappas
** Date: 10/04/20
*******************************************************************************/

#ifndef INFIXVALIDATOR_H
#define INFIXVALIDATOR_H

#include <string>
#include <vector>

using namespace std;

class infixValidator {
	private:
		bool checkIn(char, string);
		bool isValid (char);
		bool invalidCharCheck(string);
		bool checkParenthesesPairs(string);
		bool checkOpenParentheses(string);
		bool checkCloseParentheses(string);
		bool parenthesesCheck(string);
		bool operatorPreSpaceCheck(vector<unsigned int>, string);
		bool operatorPostSpaceCheck(vector<unsigned int>, string);
		bool operatorCheck(string);
		bool validateZeroes(vector<unsigned int>, string);
		bool numberPreSpaceCheck(vector<unsigned int>, string);
		bool numberPostSpaceCheck(vector<unsigned int>, string);
		bool numbersCheck(string);
		bool spacesCheck(string);
	public:
		bool fullValidation(string);
};

#endif
