/*******************************************************************************
** File: operand.cpp
** Purpose: Define functions for operand class
** Author: Conner Pappas
** Date: 10/04/20
*******************************************************************************/
#include "./operand.hpp"
#include "./expressor.hpp"
#include <string>

using namespace std;

string EXP_KIND_AND = "operand";
/*******************************************************************************
** Function: Operand constructor
** Purpose: Construct operand (?)
** Parameters: valString - string representing the number to be assigned
** Return: None
*******************************************************************************/
Operand::Operand(string valString) : Expressor (EXP_KIND_AND) {
	this->opValue = stof(valString);
}

/*******************************************************************************
** Function: evaluate
** Purpose: Return the value of the operand, overwrites virtual function
** Parameters: None
** Return: opValue
*******************************************************************************/
float Operand::evaluate() {
	return this->opValue;
}
