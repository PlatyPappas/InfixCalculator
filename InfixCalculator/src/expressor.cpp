/*******************************************************************************
** File: operator.cpp
** Purpose: Define functions for expressor abstract class
** Author: Conner Pappas
** Date: 10/05/20
*******************************************************************************/
#include "expressor.hpp"
#include <string>

using namespace std;
/*******************************************************************************
** Function: Expressor constructor
** Purpose: Construct expressor base (?)
** Parameters: expr - string representing the kind of expressor this is,
** 					  will either be "operand" or "operator"
** Return: None
*******************************************************************************/
Expressor::Expressor(string expr) {
	this->expType = expr;
}

/*******************************************************************************
** Function: Expressor destructor
** Purpose: Destroy expressor base. Required for pure virtual classes
** Parameters: None
** Return: None
*******************************************************************************/
Expressor::~Expressor() {}

/*******************************************************************************
** Function: getExpType
** Purpose: Retrieve the type of the expressor
** Parameters: None
** Return: expType
*******************************************************************************/
string Expressor::getExpType() {
	return this->expType;
};
