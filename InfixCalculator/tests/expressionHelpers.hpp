#ifndef EXPRESSIONHELPERS_H
#define EXPRESSIONHELPERS_H

#include "./../src/infixValidator.hpp"
#include "./../src/expressor.hpp"
#include "./../src/operand.hpp"
#include "./../src/operator.hpp"
#include <string>
#include <list>

using namespace std;

bool checkInP(char, string);
string removeSpaces(string);
void parseStringToList(list<Expressor*>*, string);
void constructTree(list<Expressor*>*);
list<Expressor*>::iterator expressionSolver(list<Expressor*>*, list<Expressor*>::iterator);
list<Expressor*>::iterator generateTree(list<Expressor*>*, list<Expressor*>::iterator);
float evaluateExpression(string);
#endif
