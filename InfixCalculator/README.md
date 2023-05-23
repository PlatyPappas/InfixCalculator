Conner Pappas - Infix Calculator

Problem: 
Create a program that parses and evaluates infix arithmetic expressions without 
using the Shunting-Yard algorithm

Solution: 
Create an algorithm that evaluates an infix expression from left to right while 
maintaining precedence. I thought the best way to accomplish this would be 
through constructing an expression tree.

Tools: Eclipse IDE, developed on Ubuntu

Steps:
First, I had to create a tool for validating expressions to ensure we received
correctly formatted expressions. Rules are below. The files infixValidator.hpp
and infixValidator.cpp define this tool. This was fun to make.

After making an expression validator I was ready to tackle the evaluation
problem. I have a base class defined by expressor.hpp that operand.hpp and
operator.hpp derive from. Because I'm constructing a tree I need pointers that
can point to both derived classes when combining nodes. Operands and operators
are basically tokens in an expression; when an expression string is parsed,
it's changed into a list of these tokens.

How the algorithm works (in a nutshell). We always start with the intent of
generating a tree. If the first token is '(' then we generate a new tree
starting with the next token. If the first token is a number then we need to see
if it's all on its lonesome, if it is we return, else we resolve it with the 
next token in the list. If the first token is ')' we know we're at the end of a
branch, return. When resolving operands, if the next operand has the greatest
precedence then we can evaluate if the other operand is a number, and generate
a new tree if the next token is '('. If the next operand has lesser precedence
than other operands, generate a tree with the rest of the expression before
evaluating. Do this until the last element in the list is the head.

This is all defined in infixCalculator.cpp (infixCalculator.hpp is in 
./include/ConnerPappasPlexsys). infixCalculator is a class. When instantiated,
you can pass it a string representing the expression. It can be evaluated
immediately with evaluateExpression() which returns a float, but will throw
an exception if you try to evaluate an invalid expression. You can choose
to call validateExpression() to ensure your expression is valid. If you
want to change expressions, call setExpression().

Interface:
Constructors:
InfixCalculator(); - instantiate without an expression. Must use setExpression
in order to utilize functionality

InfixCalculator(string); - instantiate with an expression

void setExpression(string); - set the expression

float evaluateExpression(); - evaluate the expression. Will throw an exception
							of type const char* if expression is invalid

bool validateExpression(); - validate the expression. Returns a bool
							representing validity

If you use the include and src folders, you can make your own programs with
this solution.

I've included a demo.

Instructions:

To make the demo driver of the calculator type into the console: 
make demo

The resulting executable is named infixCalculatorDriver

The input has rules (non-comprehensive, will provide examples):
1) Spaces before and after every operator unless it is a parenthese
2) Spaces before and after numbers unless it is next to a parenthese
3) No leading or trailing spaces
4) No multiple spaces
5) Only the following characters can make an expression: 0123456789/*-+()

Example input:
(1 + 1)
3 * 6 + (70)
2 / 2 + 9
(4 * 5 * (5 - 7) + ((4 - 3) / (2) + 5)) * (4 * (3 - 1))

If you want to see the tests then type:
make tests