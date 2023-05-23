#include "./../src/infixValidator.hpp"
#include "./../src/expressor.hpp"
#include "./../src/operator.hpp"
#include "./../src/operator.hpp"
#include "./expressionHelpers.hpp"
#include <string>
#include <list>

#include <iostream>

using namespace std;

/*******************************************************************************
** Function: checkIn
** Purpose: Determine if a character is in a string
** Parameters: toCheck - char to check
** 			   validChars - string of valid chars
** Return: Boolean representing validity
*******************************************************************************/
bool checkInP(char toCheck, string validChars) {
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
string removeSpaces(string infix) {
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
** Purpose: Parse an infix string into a list of operators and operands
** Parameters: expContainer - list to store the expression
** 			   infix - expression string
** Return: None
*******************************************************************************/
void parseStringToList(list<Expressor*>* expContainer, string infix) {
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

/*list<Expressor*>::iterator expressionSolver (list<Expressor*>::iterator currPos, list<Expressor*>* expContainer) {

	cout << "Entered expSolv" << endl;

	currPos++;

	//Scan for greatest precedence
	int greatestPrec = 0;
	for (list<Expressor*>::iterator precScan = currPos; precScan != expContainer->end(); ++precScan) {
		if ((*precScan)->getExpType() == "operator") {
			if (static_cast<Operator*>(*precScan)->getPrecedence() > greatestPrec) {
				greatestPrec = static_cast<Operator*>(*precScan)->getPrecedence();
			}
		}
	}
	cout << "Greatest precedence: " << greatestPrec << endl;


	//Check the precedence of our current operator
	if (static_cast<Operator*>(*currPos)->getPrecedence() == greatestPrec) {
		cout << "Current op has greatest precedence" << endl;
		//If we are at the greatest precedence then we can operate
		//If the next position is an operator then it's '('
		currPos++;
		if ((*currPos)->getExpType() == "operator") {
			//If the next position is '(' then we need to evaluate inside there
			//first. * (expr(expr... throws me a little
			cout << "Next op (" << endl;
			list<Expressor*>::iterator savePoint = currPos;
			savePoint--;
			list<Expressor*>::iterator rightChild = generateTree(expContainer, currPos, false);
			currPos = savePoint;
			currPos--;
			list<Expressor*>::iterator leftChild = currPos;
			currPos = savePoint;
			static_cast<Operator*>(*currPos)->assignChildren(*leftChild, *rightChild);
			expContainer->erase(leftChild);
			expContainer->erase(rightChild);
		}
		else {
			cout << "Combining left and right" << endl;
			list<Expressor*>::iterator rightChild = currPos;
			currPos--;
			currPos--;
			list<Expressor*>::iterator leftChild = currPos;
			currPos++;
			static_cast<Operator*>(*currPos)->assignChildren(*leftChild, *rightChild);
			expContainer->erase(leftChild);
			expContainer->erase(rightChild);
		}
	}
	else {
		currPos++;
		if ((*currPos)->getExpType() == "operator") {
			if (static_cast<Operator*>(*currPos)->getSymbol() == '(') {
				//If the next position is '(' then we need to evaluate inside there
				//first.
				cout << "Expressing right then combining" << endl;
				list<Expressor*>::iterator savePoint = currPos;
				savePoint--;
				list<Expressor*>::iterator rightChild = generateTree(expContainer, currPos, false);
				currPos = savePoint;
				currPos--;
				list<Expressor*>::iterator leftChild = currPos;
				currPos = savePoint;
				static_cast<Operator*>(*currPos)->assignChildren(*leftChild, *rightChild);
				expContainer->erase(leftChild);
				expContainer->erase(rightChild);
			}
			else {
				list<Expressor*>::iterator deleteChild = currPos;
				currPos--;
				list<Expressor*>::iterator rightChild = currPos;
				currPos--;
				currPos--;
				list<Expressor*>::iterator leftChild = currPos;
				currPos++;
				static_cast<Operator*>(*currPos)->assignChildren(*leftChild, *rightChild);
				expContainer->erase(leftChild);
				expContainer->erase(rightChild);
				expContainer->erase(deleteChild);
			}
		}
		else {
			list<Expressor*>::iterator savePoint = currPos;
			savePoint--;
			list<Expressor*>::iterator rightChild = expressionSolver(currPos, expContainer);
			currPos = savePoint;
			currPos--;
			list<Expressor*>::iterator leftChild = currPos;
			currPos = savePoint;
			static_cast<Operator*>(*currPos)->assignChildren(*leftChild, *rightChild);
			expContainer->erase(leftChild);
			expContainer->erase(rightChild);

		}
	}
	cout << "Leaving expSolve " << (*currPos)->evaluate() << endl;
	return currPos;
}

list<Expressor*>::iterator generateTree(list<Expressor*>* expContainer, list<Expressor*>::iterator head, bool isTop) {
	list<Expressor*>::iterator iter = head;
	list<Expressor*>::iterator delPare, cleanUp, backChild;
	cout << "Generate tree" << endl;
	while (iter != (--expContainer->end())) {
		for (list<Expressor*>::iterator it = expContainer->begin(); it != expContainer->end(); ++it) {
			if ((*it)->getExpType() == "operator") {
				cout << static_cast<Operator*>(*it)->getSymbol();
			}
			else {
				cout << static_cast<Operand*>(*it)->evaluate();
			}
		}
		cout << endl;

		if ((*iter)->getExpType() == "operator") {
			iter++;
			if ((*iter)->getExpType() == "operand") {
				iter++;
				if (static_cast<Operator*>(*iter)->getSymbol() == ')') {
					iter--;
					cout << "Solo num" << endl;
					delPare = iter;
					delPare++;
					//If the operator following the returned operand is ')', remove it
					cout << "Remove following )" << endl;
					expContainer->erase(delPare);
					break;
				}
				else {
					iter--;
					iter = generateTree(expContainer, iter, false);
				}
			}
			else {
				iter = generateTree(expContainer, iter, false);
			}
		}
		else {
			iter = expressionSolver(iter, expContainer);
		}



		if ((*iter)->getExpType() == "operator") {
			cout << static_cast<Operator*>(*iter)->getSymbol();
		}
		else {
			cout << "Back in generateTree " << static_cast<Operand*>(*iter)->evaluate();
		}
		cout << endl;



		if (iter != (--expContainer->end())) {
			delPare = iter;
			delPare++;
			//If the operator following the returned operand is ')', remove it
			if (static_cast<Operator*>(*delPare)->getSymbol() == ')') {
				cout << "Remove following )" << endl;
				expContainer->erase(delPare);
			}
		}

		if (!isTop) break;
	}

	cout << "Leaving generate tree" << endl;
	if (iter != expContainer->begin()) {
		delPare = iter;
		delPare--;
		//If the operator preceding the returned operand is '(', remove it
		if (static_cast<Operator*>(*delPare)->getSymbol() == '(') {
			cout << "Remove leading (" << endl;
			expContainer->erase(delPare);
		}
	}
	return iter;
}*/

list<Expressor*>::iterator expressionSolver(list<Expressor*>* expContainer, list<Expressor*>::iterator entry) {
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
			nextToken++;
			if (static_cast<Operator*>(*nextToken)->getSymbol() == ')') {
				nextToken--;
				rightChild = nextToken;
				leftChild = iter;
				leftChild--;
				static_cast<Operator*>(*iter)->assignChildren(*leftChild, *rightChild);
				expContainer->erase(leftChild);
				expContainer->erase(rightChild);
			}
			else {
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

list<Expressor*>::iterator generateTree(list<Expressor*>* expContainer, list<Expressor*>::iterator head) {
	list<Expressor*>::iterator iter = head;
	list<Expressor*>::iterator delPare;
	string operators = "+-*/";

	if ((*iter)->getExpType() == "operator") {
		iter++;
		if ((*iter)->getExpType() == "operator") {
			iter = generateTree(expContainer, iter);
			delPare = iter;
			delPare++;
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
			if (static_cast<Operator*>(*iter)->getSymbol() == ')') {
				iter--;
			}
			else {
				iter--;
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

float evaluateExpression(string expression) {
	float result;
	list<Expressor*> expContainer;

	parseStringToList(&expContainer, expression);
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
