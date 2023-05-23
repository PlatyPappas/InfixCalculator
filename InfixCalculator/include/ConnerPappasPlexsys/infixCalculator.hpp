/*******************************************************************************
** File: infixCalculator.hpp
** Purpose: Define infixCalculator class
** Author: Conner Pappas
** Date: 10/06/20
*******************************************************************************/
#ifndef INFIXCALCULATOR_H
#define INFIXCALCULATOR_H

#include "./../../src/expressor.hpp"
#include "./../../src/operand.hpp"
#include "./../../src/operator.hpp"
#include "./../../src/infixValidator.hpp"
#include <string>
#include <list>

using namespace std;

//This is the main interface

//When instantiated, you can pass a string to the expression
//Otherwise use setExpression to set an expression to evaluate

//validateExpression will return if the expression is valid or not
//It will also set the variable infixValid

//evaluateExpression will only evaluate if the expression is valid
//It will throw a const char* exception otherwise
//If you haven't validated the expression, this method will do it for you
//It's better to validate first before evaluating
class InfixCalculator {
	private:
		infixValidator inVal;
		string infixExpression;
		bool infixValid;
		bool infixSet;
		bool checkInP(char, string);
		string removeSpaces(string);
		void parseStringToList(list<Expressor*>*, string);
		void constructTree(list<Expressor*>*);
		list<Expressor*>::iterator expressionSolver(list<Expressor*>*, list<Expressor*>::iterator);
		list<Expressor*>::iterator generateTree(list<Expressor*>*, list<Expressor*>::iterator);
	public:
		InfixCalculator();
		InfixCalculator(string);
		void setExpression(string);
		float evaluateExpression();
		bool validateExpression();
};

#endif
