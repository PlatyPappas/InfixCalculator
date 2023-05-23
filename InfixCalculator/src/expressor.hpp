/*******************************************************************************
** File: expressor.hpp
** Purpose: Define abstract expressor class
** Author: Conner Pappas
** Date: 10/04/20
*******************************************************************************/
#ifndef EXPRESSOR_H
#define EXPRESSOR_H

#include <string>

using namespace std;

//Expressor is our base class
//When constructing our expression tree, we want our nodes to be able to point
//to either operators or operands, so having a base class and a way for the
//nodes to know what kind of token they are is what will allow us to build
//a polymorphic expression tree
class Expressor {
	protected:
		string expType;
	public:
		Expressor(string);
		virtual ~Expressor() =0;
		virtual float evaluate() =0;
		string getExpType();
};

#endif
