/*******************************************************************************
** File: operator.hpp
** Purpose: Define operator class, derived from expressor class
** Author: Conner Pappas
** Date: 10/04/20
*******************************************************************************/
#ifndef OPERATOR_H
#define OPERATOR_H

#include "./expressor.hpp"
#include <string>

using namespace std;

//Operators act as nodes in our expression tree
//an operator will either have another operator or an operand as children
class Operator : public Expressor {
	private:
		char opSymbol;
		int precedence;
		Expressor* leftOp;
		Expressor* rightOp;
	public:
		Operator(string);
		~Operator();
		void assignLeftOp(Expressor*);
		void assignRightOp(Expressor*);
		void assignChildren(Expressor*, Expressor*);
		Expressor* getLeftOp();
		Expressor* getRightOp();
		float evaluate();
		char getSymbol();
		int getPrecedence();
};

#endif
