#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <string>
#include <vector>

using namespace std;

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
bool fullValidation(string);

#endif
