/*******************************************************************************
** File: infixCalculator.cpp
** Purpose: Define functions for infixCalculator class
** Author: Conner Pappas
** Date: 10/06/20
*******************************************************************************/
#include "./../include/ConnerPappasPlexsys/infixCalculator.hpp"
#include "expressor.hpp"
#include "operand.hpp"
#include "operator.hpp"
#include "infixValidator.hpp"
#include <string>
#include <list>

using namespace std;

/*******************************************************************************
** Function: InfixCalculator Constructor
** Purpose: Construct InfixCalculator instance
** Parameters: infixExp - expressing to calculate
** Return: None
*******************************************************************************/
InfixCalculator::InfixCalculator() {
	this->infixExpression = "";
	this->infixValid = false;
	//Establish the expression as set
	this->infixSet = false;;
}

/*******************************************************************************
** Function: InfixCalculator Constructor
** Purpose: Construct InfixCalculator instance
** Parameters: infixExp - expressing to calculate
** Return: None
*******************************************************************************/
InfixCalculator::InfixCalculator(string infixExp) {
	this->infixExpression = infixExp;
	this->infixValid = false;
	//Establish the expression as set
	this->infixSet = true;
}

/*******************************************************************************
** Function: setExpression
** Purpose: Set the expression to be validated and calculated
** Parameters: infixExp - expressing to calculate
** Return: None
*******************************************************************************/
void InfixCalculator::setExpression(string infixExp) {
	this->infixExpression = infixExp;
	this->infixValid = false;
	//Establish the expression as set
	this->infixSet = true;
}

/*******************************************************************************
** Function: validateExpression
** Purpose: Validate the expression passed to the calculator
** Parameters: None
** Return: Bool representing expression validity
*******************************************************************************/
bool InfixCalculator::validateExpression() {
	bool isValid = false;
	string validateString = this->infixExpression;
	if (this->infixSet) {
		isValid = this->inVal.fullValidation(validateString);
	}
	this->infixValid = isValid;
	return isValid;
}

/*******************************************************************************
** Function: checkIn
** Purpose: Determine if a character is in a string
** Parameters: toCheck - char to check
** 			   validChars - string of valid chars
** Return: Boolean representing validity
*******************************************************************************/
bool InfixCalculator::checkInP(char toCheck, string validChars) {
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
** Function: removeSpaces
** Purpose: Remove the spaces from a string
** Parameters: infix - infix expression with spaces
** Return: infixNoSpace
*******************************************************************************/
string InfixCalculator::removeSpaces(string infix) {
	string infixNoSpace = "";
	string placeholder = "";

	for (unsigned int i = 0; i < infix.length(); i++){
		if (infix[i] != ' ') {
			placeholder = infixNoSpace + infix[i];
		}
		infixNoSpace = placeholder;
	}

	return infixNoSpace;
}

/*******************************************************************************
** Function: parseStringToList
** Purpose: Parse an infix string into a list of operators and operands,
** 			basically tokenize it
** Parameters: expContainer - list to store the expression
** 			   infix - expression string
** Return: None
*******************************************************************************/
void InfixCalculator::parseStringToList(list<Expressor*>* expContainer, string infix) {
	string operators = "()+-*/";
	string numbers = "0123456789";
	string newInfix = removeSpaces(infix);
	string numPlaceholder = "";
	string fullNum = "";
	string opAssign = "";

	for (unsigned int i = 0; i < newInfix.length(); i++) {
		//If we come across a non-number it's an operator
		//This is guaranteed by the infix validator
		if (checkInP(newInfix[i], operators)) {
			Expressor* pTemp = new Operator(opAssign = newInfix[i]);
			expContainer->push_back(pTemp);
			pTemp = NULL;
		}
		//If we come across a number, we can't guarantee it's a single digit
		//We'll look ahead to see if the next character is a number, if it is
		//then we'll wait for the next iteration to append it
		if (checkInP(newInfix[i], numbers)) {
			numPlaceholder = fullNum + newInfix[i];
			fullNum = numPlaceholder;
			if (!checkInP(newInfix[i+1], numbers)) {
				Expressor* pTemp = new Operand(opAssign = fullNum);
				expContainer->push_back(pTemp);
				fullNum = "";
			}
		}
	}
}

/*******************************************************************************
** Function: expressionSolver
** Purpose: Resolve the immediate operand. Resolves one operand at a time
** Parameters: expContainer - handler for the list containing the tokens of the
** 			   expression
** 			   entry - the entry point of the container that we are evaluating
** 			   from
** Return: None
*******************************************************************************/
list<Expressor*>::iterator InfixCalculator::expressionSolver(
		list<Expressor*>* expContainer, list<Expressor*>::iterator entry) {
	list<Expressor*>::iterator iter = entry;
	list<Expressor*>::iterator nextToken, leftChild, rightChild;

	//Scan for greatest precedence
	int greatestPrec = 0;
	for (list<Expressor*>::iterator precScan = iter; precScan != expContainer->end(); ++precScan) {
		if ((*precScan)->getExpType() == "operator") {
			if (static_cast<Operator*>(*precScan)->getPrecedence() > greatestPrec) {
				greatestPrec = static_cast<Operator*>(*precScan)->getPrecedence();
			}
		}
	}

	//Need an iterator to peek at next symbol
	iter++;
	nextToken = iter;
	nextToken++;

	if (static_cast<Operator*>(*iter)->getPrecedence() == greatestPrec) {
		//If we have the greatest precedence we take this branch
		//If the next token is an operator it is ( by necessity
		if((*nextToken)->getExpType() == "operator") {
			//If it's a ( then a new tree needs to be generated
			rightChild = generateTree(expContainer, nextToken);
			leftChild = iter;
			leftChild--;
			static_cast<Operator*>(*iter)->assignChildren(*leftChild, *rightChild);
			expContainer->erase(leftChild);
			expContainer->erase(rightChild);
		}
		else {
			//If the next token is an operand we can just operate
			leftChild = iter;
			rightChild = iter;
			leftChild--;
			rightChild++;
			static_cast<Operator*>(*iter)->assignChildren(*leftChild, *rightChild);
			expContainer->erase(leftChild);
			expContainer->erase(rightChild);
		}
	}
	else {
		if((*nextToken)->getExpType() == "operator") {
			//If it's a ( then a new tree needs to be generated
			rightChild = generateTree(expContainer, nextToken);
			leftChild = iter;
			leftChild--;
			static_cast<Operator*>(*iter)->assignChildren(*leftChild, *rightChild);
			expContainer->erase(leftChild);
			expContainer->erase(rightChild);
		}
		else {
			//Need to check if we're at the end of a generating tree
			nextToken++;
			if (static_cast<Operator*>(*nextToken)->getSymbol() == ')') {
				//If we're at the end of a generating tree then we need to
				//resolve the last two operand
				nextToken--;
				rightChild = nextToken;
				leftChild = iter;
				leftChild--;
				static_cast<Operator*>(*iter)->assignChildren(*leftChild, *rightChild);
				expContainer->erase(leftChild);
				expContainer->erase(rightChild);
			}
			else {
				//If there's still an operand with greater precedence then we
				//need to generate a tree from here on
				nextToken--;
				rightChild = generateTree(expContainer, nextToken);
				leftChild = iter;
				leftChild--;
				static_cast<Operator*>(*iter)->assignChildren(*leftChild, *rightChild);
				expContainer->erase(leftChild);
				expContainer->erase(rightChild);
			}
		}
	}
	return iter;
}

/*******************************************************************************
** Function: generateTree
** Purpose: Create a new branch in our evaluation tree
** Parameters: expContainer - handler for the list containing the tokens of the
** 			   expression
** 			   head - the soon to be head of the new tree / entry point for
** 			   this new branch
** Return: None
*******************************************************************************/
list<Expressor*>::iterator InfixCalculator::generateTree(list<Expressor*>* expContainer, list<Expressor*>::iterator head) {
	list<Expressor*>::iterator iter = head;
	list<Expressor*>::iterator delPare;
	string operators = "+-*/";

	//Okay, buckle up

	//Check first if our entry point is an operator
	if ((*iter)->getExpType() == "operator") {
		iter++;
		if ((*iter)->getExpType() == "operator") {
			//If the next token is ( then we generate a new tree branch
			iter = generateTree(expContainer, iter);
			delPare = iter;
			delPare++;
			//When we return with our new tree branch then we solve the next term
			if (delPare != expContainer->end()) {
				if (checkInP(static_cast<Operator*>(*delPare)->getSymbol(),operators)) {
					while (expContainer->size() > 1) {
						iter = expressionSolver(expContainer, iter);
						delPare = iter;
						delPare++;
						if (delPare == expContainer->end() || static_cast<Operator*>(*delPare)->getSymbol() == ')') {
							break;
						}
					}
				}
			}
		}
		else {
			iter++;
			//If the next token is a number and the next token is ) we know
			//we're at the end of a tree branch
			if (static_cast<Operator*>(*iter)->getSymbol() == ')') {
				iter--;
			}
			else {
				iter--;
				//If the next token is an operator then we need to resolve
				//the next term onward
				while (expContainer->size() > 1) {
					iter = expressionSolver(expContainer, iter);
					delPare = iter;
					delPare++;
					if (delPare == expContainer->end() || static_cast<Operator*>(*delPare)->getSymbol() == ')') {
						break;
					}
				}

			}
		}
	}
	else {
		//If the entry point is a number then we resolve it
		if (iter != (--expContainer->end())) {
			while (expContainer->size() > 1) {
				iter = expressionSolver(expContainer, iter);
				delPare = iter;
				delPare++;
				if (delPare == expContainer->end() || static_cast<Operator*>(*delPare)->getSymbol() == ')') {
					break;
				}
			}
		}
	}

	//On the way out of the branch we do some housekeeping and remove
	//the no-longer-relevant parentheses
	if (iter != expContainer->begin()) {
		delPare = iter;
		delPare--;
		//If the operator preceding the returned operand is '(', remove it
		if (static_cast<Operator*>(*delPare)->getSymbol() == '(') {
			expContainer->erase(delPare);
		}
	}
	if (iter != (--expContainer->end())) {
		delPare = iter;
		delPare++;
		//If the operator preceding the returned operand is '(', remove it
		if (static_cast<Operator*>(*delPare)->getSymbol() == ')') {
			expContainer->erase(delPare);
		}
	}

	return iter;
}

/*******************************************************************************
** Function: evaluateExpression
** Purpose: Evaluate the expression given to the calculator
** Parameters: None
** Return: result - float representation of the evaluation
*******************************************************************************/
float InfixCalculator::evaluateExpression() {
	float result;
	list<Expressor*> expContainer;

	//Check first if the string has been validated
	if (!(this->infixValid)) {
		string checkMe = this->infixExpression;
		this->validateExpression();
		if(!(this->infixValid)) {
			//If the string isn't valid, throw exception
			throw "Attempted to evaluate an invalid expression";
		}
	}

	parseStringToList(&expContainer, this->infixExpression);
	list<Expressor*>::iterator iterOp = expContainer.begin();
	while (expContainer.size() > 1) {
		iterOp = expContainer.begin();
		iterOp = generateTree(&expContainer, iterOp);
	}

	result = static_cast<Operator*>(*iterOp)->evaluate();
	delete (*iterOp);
	expContainer.clear();

	return result;
}
