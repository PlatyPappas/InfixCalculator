#include "helperFunctions.hpp"

#include <string>
#include <stack>
#include <vector>

using namespace std;

/*******************************************************************************
** Function: checkIn
** Purpose: Determine if a character is in a string
** Parameters: toCheck - char to check
** 			   validChars - string of valid chars
** Return: Boolean representing validity
*******************************************************************************/
bool checkIn(char toCheck, string validChars) {
	bool isIn = false;

	for (unsigned int i = 0; i < validChars.length(); i++) {
		if (toCheck == validChars[i]) {
			isIn = true;
			break;
		}
	}

	return isIn;
}

/*******************************************************************************
** Function: isValid
** Purpose: Determine if a character is a valid mathematical character
** Parameters: currChar - character being checked
** Return: Boolean representing validity
*******************************************************************************/
bool isValid (char currChar) {
	string validChars = "0123456789+-/*() ";
	return checkIn(currChar, validChars);
}

/*******************************************************************************
** Function: invalidCharCheck
** Purpose: Determine if an expression string contains invalid character
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool invalidCharCheck(string expressionString) {
	bool stringValid = true;
	for (unsigned int i = 0; i < expressionString.length(); i++) {
		if (!isValid(expressionString[i])){
			stringValid = false;
			break;
		}
	}
	return stringValid;
}

/*******************************************************************************
** Function: checkParenthesesPairs
** Purpose: Check if the parentheses in the expression are paired correctly
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool checkParenthesesPairs(string expressionString) {
	bool stringValid = true;

	//Using a stack to make sure pairs are matched properly
	stack<char> pareStack;

	for (unsigned int i = 0; i < expressionString.length(); i++) {
		//Push on open parentheticals
		if (expressionString[i] == '(') pareStack.push('(');
		//If we examine a closing parenthetical we pop
		if (expressionString[i] == ')') {
			//If stack size is empty before popping then we know the string is invalid
			if (pareStack.size() == 0) {
				stringValid = false;
				break;
			}
			pareStack.pop();
		}
	}

	if (pareStack.size() != 0) stringValid = false;

	return stringValid;
}

/*******************************************************************************
** Function: checkOpenParentheses
** Purpose: Check if the open parentheses has correct positioning
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool checkOpenParentheses(string expressionString) {
	bool stringValid = true;
	string validPreceding = " (";
	string validFollowing = "(0123456789";

	if (expressionString.length() == 0) {
		throw "String of invalid size passed to checkOpenParentheses";
	}
	if (expressionString[0] == ' ') {
		throw "String starting with a space passed to checkOpenParentheses";
	}
	if (expressionString[expressionString.length() - 1] == ' ') {
		throw "String ending with a space passed to checkOpenParentheses";
	}

	//Check our base case where the first position is '('
	try {
		if (expressionString[0] == '(') stringValid = checkIn(expressionString[1], validFollowing);
	}
	catch (exception& e) {
		throw e.what();
	}

	for (unsigned int i = 1; i < expressionString.length() && stringValid; i++) {
		if (expressionString[i] == '(') {
			try {
				if (!checkIn(expressionString[i+1], validFollowing) && stringValid) stringValid = false;
			}
			catch (exception& e) {
				throw e.what();
			}
			try {
				if (!checkIn(expressionString[i-1], validPreceding) && stringValid) stringValid = false;
			}
			catch (exception& e) {
				throw e.what();
			}
		}
	}

	return stringValid;
}

/*******************************************************************************
** Function: checkCloseParentheses
** Purpose: Check if the close parentheses has correct positioning
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool checkCloseParentheses(string expressionString) {
	bool stringValid = true;
	string validFollowing = " )";
	string validPreceding = "0123456789)";

	if (expressionString.length() == 0) {
		throw "String of invalid size passed to checkCloseParentheses";
	}
	if (expressionString[0] == ' ') {
		throw "String starting with a space passed to checkCloseParentheses";
	}
	if (expressionString[expressionString.length() - 1] == ' ') {
		throw "String ending with a space passed to checkCloseParentheses";
	}

	for (unsigned int i = 0; i < (expressionString.length() - 1) && stringValid; i++) {
		if (expressionString[i] == ')') {
			try {
				if (!checkIn(expressionString[i+1], validFollowing) && stringValid) stringValid = false;
			}
			catch (exception& e) {
				throw e.what();
			}
			try {
				if (!checkIn(expressionString[i-1], validPreceding) && stringValid) stringValid = false;
			}
			catch (exception& e) {
				throw e.what();
			}
		}
	}

	//Check our base case where the last position is '('
	try {
		if (expressionString[expressionString.length()-1] == ')' && stringValid) stringValid = checkIn(expressionString[expressionString.length()-2], validPreceding);
	}
	catch (exception& e) {
		throw e.what();
	}

	return stringValid;
}

/*******************************************************************************
** Function: parenthesesCheck
** Purpose: Check if the parentheses in the expression are formatted correctly.
** 			Parentheses must be paired correctly. ( must follow a space or ( and
** 			be followed by a number or (. ) must follow ) or a number, and precede
** 			) or a space.
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool parenthesesCheck(string expressionString) {
	bool stringValid = true;

	if (expressionString.length() == 0) {
		throw "String of invalid size passed to parenthesesCheck";
	}
	if (expressionString[0] == ' ') {
		throw "String starting with a space passed to parenthesesCheck";
	}
	if (expressionString[expressionString.length() - 1] == ' ') {
		throw "String ending with a space passed to parenthesesCheck";
	}

	//First check for correct pairing of parentheses
	stringValid = checkParenthesesPairs(expressionString);
	//Second, if still valid check for correct preceding and following characters for '('
	try {
		if (stringValid) stringValid = checkOpenParentheses(expressionString);
	}
	catch (const char* e) {
		throw e;
	}
	//Third, if still valid check for correct preceding and following characters for ')'
	try {
		if (stringValid) stringValid = checkCloseParentheses(expressionString);
	}
	catch (const char* e) {
		throw e;
	}

	return stringValid;
}

/*******************************************************************************
** Function: operatorPostSpaceCheck
** Purpose: Check if the spaces before operators are preceded by valid characters
** Parameters: spaces - vector containing the indices of spaces
** 			   expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool operatorPreSpaceCheck(vector<unsigned int> spaces, string expressionString) {
	bool spacesValid = true;
	string precededBy = "0123456789)";

	for (unsigned int i = 0; i < spaces.size() && spacesValid; i++) {
		if (!checkIn(expressionString[spaces[i]-1], precededBy)) spacesValid = false;
	}

	return spacesValid;
}

/*******************************************************************************
** Function: operatorPostSpaceCheck
** Purpose: Check if the spaces after operators are followed by valid characters
** Parameters: spaces - vector containing the indices of spaces
** 			   expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool operatorPostSpaceCheck(vector<unsigned int> spaces, string expressionString) {
	bool spacesValid = true;
	string followedBy = "0123456789(";

	for (unsigned int i = 0; i < spaces.size() && spacesValid; i++) {
		if (!checkIn(expressionString[spaces[i]+1], followedBy)) spacesValid = false;
	}

	return spacesValid;
}

/*******************************************************************************
** Function: operatorCheck
** Purpose: Check if the operators in the expression are formatted correctly.
** 			Operators must be followed and preceded by spaces. Spaces preceding
** 			must follow numbers or ), spaces following must precede numbers or (
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool operatorCheck(string expressionString) {
	bool stringValid = true;
	vector<unsigned int> preSpaces;
	vector<unsigned int> postSpaces;
	string operators = "+*/-";

	if (expressionString.length() == 0) {
		throw "String of invalid size passed to operatorCheck";
	}
	if (expressionString[0] == ' ') {
		throw "String starting with a space passed to operatorCheck";
	}
	if (expressionString[expressionString.length() - 1] == ' ') {
		throw "String ending with a space passed to operatorCheck";
	}

	//Operators cannot be at the beginning or end of an expression
	if (checkIn(expressionString[0], operators) ||
			checkIn(expressionString[expressionString.length() - 1], operators))
		stringValid = false;

	//If the expression passes the above checks then we can iterate through
	for (unsigned int i = 0; i < expressionString.length() && stringValid; i++) {
		//If we come across an operator, we need to make sure there are spaces on both sides
		//If there are we'll push those spaces into respective vectors to make sure they are
		//followed or preceded by valid characters
		//No try-catch here because the above checks guarantee we'll stay in bounds
		//of our string
		if (checkIn(expressionString[i], operators)) {
			if (expressionString[i+1] != ' ' && stringValid) {
				stringValid = false;
			}
			else {
				postSpaces.push_back(i+1);
			}
			if (expressionString[i-1] != ' ' && stringValid) {
				stringValid = false;
			}
			else {
				preSpaces.push_back(i-1);
			}
		}
	}

	if (stringValid) stringValid = operatorPreSpaceCheck(preSpaces, expressionString);
	if (stringValid) stringValid = operatorPostSpaceCheck(postSpaces, expressionString);

	return stringValid;
}

/*******************************************************************************
** Function: validateZeroes
** Purpose: Check if the zeroes are valid
** Parameters: zeroes - vector containing the indices of zeroes
** 			   expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool validateZeroes(vector<unsigned int> zeroes, string expressionString) {
	bool zeroesValid = true;
	string validFollowing = "0123456789 )";
	string validPreceding = "0123456789";
	string paredString;

	//Taking parentheses around expression string to get around issue of checking
	//out of bounds
	if (expressionString[0] != '(' && expressionString[expressionString.length() - 1] != ')') {
		paredString = "(" + expressionString + ")";
 	}
	else {
		paredString = expressionString;
	}

	//A zero can be by itself, and be the least significant character, but
	//it cannot lead a number
	//First check following chars

	for (unsigned int i = 0; i < zeroes.size() && zeroesValid; i++) {
		if (!checkIn(paredString[zeroes[i] + 1], validFollowing))
			zeroesValid = false;
	}

	//Now check for preceding chars
	//If the zero is not led by a number then we have to check it's surrounded
	//by spaces or () or led by ( and space followed or space led and ) followed
	for (unsigned int i = 0; i < zeroes.size() && zeroesValid; i++) {
		if (!checkIn(paredString[zeroes[i] - 1], validPreceding)) {
			if (!((paredString[zeroes[i] - 1] == ' ' &&
					paredString[zeroes[i] + 1] == ' ') ||
					(paredString[zeroes[i] - 1] == '(' &&
					paredString[zeroes[i] + 1] == ')') ||
					(paredString[zeroes[i] - 1] == '(' &&
					paredString[zeroes[i] + 1] == ' ') ||
					(paredString[zeroes[i] - 1] == ' ' &&
					paredString[zeroes[i] + 1] == ')')))
				zeroesValid = false;
		}
	}

	return zeroesValid;
}

/*******************************************************************************
** Function: numberPreSpaceCheck
** Purpose: Check if the spaces before numbers are preceded by valid characters
** Parameters: spaces - vector containing the indices of spaces
** 			   expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool numberPreSpaceCheck(vector<unsigned int> spaces, string expressionString) {
	bool spacesValid = true;
	string precededBy = "+/*-";

	for (unsigned int i = 0; i < spaces.size() && spacesValid; i++) {
		if (!checkIn(expressionString[spaces[i]-1], precededBy)) spacesValid = false;
	}

	return spacesValid;
}

/*******************************************************************************
** Function: numberPostSpaceCheck
** Purpose: Check if the spaces after numbers are followed by valid characters
** Parameters: spaces - vector containing the indices of spaces
** 			   expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool numberPostSpaceCheck(vector<unsigned int> spaces, string expressionString) {
	bool spacesValid = true;
	string followedBy = "+/*-";

	for (unsigned int i = 0; i < spaces.size() && spacesValid; i++) {
		if (!checkIn(expressionString[spaces[i]+1], followedBy)) spacesValid = false;
	}

	return spacesValid;
}

/*******************************************************************************
** Function: numbersCheck
** Purpose: Check if the numbers in the expression are formatted correctly.
** 			Numbers have to follow spaces, numbers, or (, and precede numbers,
** 			spaces, or ). Zeroes cannot lead numbers unless they are by
** 			themselves
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool numbersCheck(string expressionString) {
	bool stringValid = true;
	vector<unsigned int> preSpaces;
	vector<unsigned int> postSpaces;
	string numbers = "0123456789";
	string validFollowing = "0123456789 )";
	string validPreceding = "0123456789 (";

	//Need a way to store the indices for zeroes because these are special cases
	vector<unsigned int> zeroes;

	if (expressionString.length() == 0) {
		throw "String of invalid size passed to numbersCheck";
	}
	if (expressionString[0] == ' ') {
		throw "String starting with a space passed to numbersCheck";
	}
	if (expressionString[expressionString.length() - 1] == ' ') {
		throw "String ending with a space passed to numbersCheck";
	}

	//Parenthesizing string to resolve boundary issues
	string paredExp = "(" + expressionString + ")";

	for (unsigned int i = 1; i < paredExp.length()-1 && stringValid; i++) {
		//If we come across a number, we need to check if it's followed and
		//preceded correctly
		if (checkIn(paredExp[i], numbers)) {
			//If the character is zero push it since we need to check for special cases
			if (paredExp[i] == '0') zeroes.push_back(i);
			if (!checkIn(paredExp[i-1],validPreceding)) {
				stringValid = false;
			}
			else if (paredExp[i-1] == ' ' && stringValid) {
				preSpaces.push_back(i-1);
			}
			if (!checkIn(paredExp[i+1],validFollowing) && stringValid) {
				stringValid = false;
			}
			else if (paredExp[i+1] == ' ' && stringValid) {
				postSpaces.push_back(i+1);
			}
		}
	}

	//Check if the zeroes and spaces are valid
	if (stringValid) stringValid = validateZeroes(zeroes, paredExp);
	if (stringValid) stringValid = numberPreSpaceCheck(preSpaces, paredExp);
	if (stringValid) stringValid = numberPostSpaceCheck(postSpaces, paredExp);


	return stringValid;
}

/*******************************************************************************
** Function: spacesCheck
** Purpose: Check if the string has a leading or following space
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool spacesCheck(string expressionString) {
	bool stringValid = true;

	if (expressionString.length() == 0) {
			throw "String of invalid size passed to spacesCheck";
	}

	if (expressionString[0] == ' ' || expressionString[expressionString.length() - 1] == ' ')
		stringValid = false;

	return stringValid;
}

/*******************************************************************************
** Function: fullValidation
** Purpose: Check if the string is a valid infix expression
** Parameters: expressionString - string being checked
** Return: Boolean representing validity
*******************************************************************************/
bool fullValidation(string expressionString) {
	bool stringValid = false;

	if (expressionString.length() == 0) {
		throw "String of invalid size passed to spacesCheck";
	}

	stringValid = spacesCheck(expressionString);
	if (stringValid) stringValid = invalidCharCheck(expressionString);
	if (stringValid) stringValid = parenthesesCheck(expressionString);
	if (stringValid) stringValid = operatorCheck(expressionString);
	if (stringValid) stringValid = numbersCheck(expressionString);

	return stringValid;
}
