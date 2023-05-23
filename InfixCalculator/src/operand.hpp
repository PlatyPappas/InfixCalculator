/*******************************************************************************
** File: operand.hpp
** Purpose: Define operand class, derived from expressor class
** Author: Conner Pappas
** Date: 10/04/20
*******************************************************************************/
#ifndef OPERAND_H
#define OPERAND_H

#include "./expressor.hpp"
#include <string>

using namespace std;

//The simplest of our classes
//Operands are numbers and the leaves of our expression tree
class Operand : public Expressor {
	private:
		float opValue;
	public:
		Operand(string);
		float evaluate();
};

#endif
