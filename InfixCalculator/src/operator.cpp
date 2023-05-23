/*******************************************************************************
** File: operator.cpp
** Purpose: Define functions for operand class
** Author: Conner Pappas
** Date: 10/04/20
*******************************************************************************/
#include "operator.hpp"
#include "expressor.hpp"
#include <string>
#include <stdexcept>

using namespace std;

string EXP_KIND_TOR = "operator";
/*******************************************************************************
** Function: Operator constructor
** Purpose: Construct operator (?)
** Parameters: valString - string representing the symbol to be assigned
** Return: None
*******************************************************************************/
Operator::Operator(string valString) : Expressor (EXP_KIND_TOR) {
	this->opSymbol = valString[0];
	this->leftOp = NULL;
	this->rightOp = NULL;
	if (this->opSymbol == '+') {
		this->precedence = 1;
	}
	else if (this->opSymbol == '-') {
		this->precedence = 1;
	}
	else if (this->opSymbol == '*') {
		this->precedence = 2;
	}
	else if (this->opSymbol == '/'){
		this->precedence = 2;
	}
	else {
		this->precedence = 0;
	}
}

/*******************************************************************************
** Function: Operator destructor
** Purpose: Destroy operator (?)
** Parameters: valString - string representing the symbol to be assigned
** Return: None
*******************************************************************************/
Operator::~Operator() {
	delete this->leftOp;
	delete this->rightOp;
}

/*******************************************************************************
** Function: assignLeftOp
** Purpose: Assign the left child of the operator
** Parameters: opLeft - pointer to the assignee child
** Return: None
*******************************************************************************/
void Operator::assignLeftOp(Expressor* opLeft) {
	this->leftOp = opLeft;
}

/*******************************************************************************
** Function: assignRightOp
** Purpose: Assign the right child of the operator
** Parameters: opRight - pointer to the assignee child
** Return: None
*******************************************************************************/
void Operator::assignRightOp(Expressor* opRight) {
	this->rightOp = opRight;
}

/*******************************************************************************
** Function: assignChildren
** Purpose: Assign the left and right child of the operator, change to operand
** Parameters: opLeft - pointer to the left assignee child
** 			   opRight - pointer to the right assignee child
** Return: None
*******************************************************************************/
void Operator::assignChildren(Expressor* opLeft, Expressor* opRight) {
	this->assignLeftOp(opLeft);
	this->assignRightOp(opRight);
	this->expType = "operand";
}

/*******************************************************************************
** Function: getLeftOp
** Purpose: Retrieve the left child of the operator
** Parameters: None
** Return: leftOp
*******************************************************************************/
Expressor* Operator::getLeftOp() {
	return this->leftOp;
}

/*******************************************************************************
** Function: getRightOp
** Purpose: Retrieve the right child of the operator
** Parameters: None
** Return: rightOp
*******************************************************************************/
Expressor* Operator::getRightOp() {
	return this->rightOp;
}

/*******************************************************************************
** Function: evaluate
** Purpose: Return the value of the operator on its children
** Parameters: None
** Return: retVal - float representation of the operation
*******************************************************************************/
float Operator::evaluate() {
	float retVal = 0;

	if (!(this->leftOp) || !(this->rightOp)) {
		throw out_of_range("Invalid child");
	}

	if (this->opSymbol == '+') {
		retVal = this->leftOp->evaluate() + this->rightOp->evaluate();
	}
	else if (this->opSymbol == '-') {
		retVal = this->leftOp->evaluate() - this->rightOp->evaluate();
	}
	else if (this->opSymbol == '*') {
		retVal = this->leftOp->evaluate() * this->rightOp->evaluate();
	}
	else {
		retVal = this->leftOp->evaluate() / this->rightOp->evaluate();
	}

	return retVal;
}

/*******************************************************************************
** Function: getSymbol
** Purpose: Retrieve the symbol of the operator
** Parameters: None
** Return: opSymbol
*******************************************************************************/
char Operator::getSymbol() {
	return this->opSymbol;
}

/*******************************************************************************
** Function: getPrecedence
** Purpose: Retrieve the precedence of the operator
** Parameters: None
** Return: opSymbol
*******************************************************************************/
int Operator::getPrecedence() {
	return this->precedence;
}
