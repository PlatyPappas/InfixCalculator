#include "./../src/operator.hpp"
#include "./../src/operand.hpp"
#include "./../src/expressor.hpp"
#include <iostream>
#include <string>

using namespace std;

void testGetSymbol(Expressor* testOp, int torId, char expected) {
	if (static_cast<Operator*>(testOp)->getSymbol() == expected) {
		cout << "PASSED: Operator " << torId << " had symbol: " << expected << endl;
	}
	else {
		cout << "FAILED: Operator " << torId << " had symbol: " << static_cast<Operator*>(testOp)->getSymbol()
				<< " when " << expected << "was expected" << endl;
	}
}

void testLeftAssign(Expressor* parentTor, int torId, Expressor* childOp) {
	if (static_cast<Operator*>(parentTor)->getLeftOp() == childOp) {
		cout << "PASSED: Operator " << torId << " had correct left child " << endl;
	}
	else {
		cout << "FAILED: Operator " << torId << " had incorrect left child " << endl;
	}
}

void testRightAssign(Expressor* parentTor, int torId, Expressor* childOp) {
	if (static_cast<Operator*>(parentTor)->getRightOp() == childOp) {
		cout << "PASSED: Operator " << torId << " had correct right child " << endl;
	}
	else {
		cout << "FAILED: Operator " << torId << " had incorrect right child " << endl;
	}
}

void testEval(Expressor* pTor, int torId, float expected) {
	float opEval = pTor->evaluate();
	if (opEval == expected) {
		cout << "PASSED: Operator " << torId << " evaluates to " <<
				expected << endl;
	}
	else {
		cout << "FAILED: Operator " << torId << " didn't evaluate to " <<
				expected << ". Instead evaluated to: " << opEval << endl;
	}
}

void testGetExp(Operator* pTor, int torId, string expType) {
	if (pTor->getExpType() == expType) {
		cout << "PASSED: Operator " << torId << " has type " <<
					expType << endl;
	}
	else {
		cout << "FAILED: Operator " << torId << " didn't have type " <<
					expType << endl;
	}
}

int main () {
	Expressor* opAnd1 = new Operand("3");
	Expressor* opAnd2 = new Operand("5");
	Expressor* opAnd3 = new Operand("45");
	Expressor* opAnd4 = new Operand("10");
	Expressor* opTor1 = new Operator("*");
	Expressor* opTor2 = new Operator("+");
	Expressor* opTor3 = new Operator("/");
	Expressor* opTor4 = new Operator("/");
	string testString;

	cout << "Testing getSymbol" << endl;
	testGetSymbol(opTor1, 1, '*');
	testGetSymbol(opTor2, 2, '+');
	testGetSymbol(opTor3, 3, '/');
	testGetSymbol(opTor4, 4, '/');
	cout << endl;

	cout << "Testing assignChildren" << endl;
	static_cast<Operator*>(opTor1)->assignChildren(opAnd1, opAnd2);
	static_cast<Operator*>(opTor2)->assignChildren(opAnd3, opAnd4);
	static_cast<Operator*>(opTor3)->assignChildren(opTor2, opTor1);
	//cout << "Testing children assignments after assigning" << endl;
	//static_cast<Operator*>(opTor1)->assignLeftOp(opAnd1);
	testLeftAssign(opTor1, 1, opAnd1);
	//static_cast<Operator*>(opTor1)->assignRightOp(opAnd2);
	testRightAssign(opTor1, 1, opAnd2);

	//static_cast<Operator*>(opTor2)->assignLeftOp(opAnd3);
	testLeftAssign(opTor2, 2, opAnd3);
	//static_cast<Operator*>(opTor2)->assignRightOp(opAnd4);
	testRightAssign(opTor2, 2, opAnd4);

	//static_cast<Operator*>(opTor3)->assignLeftOp(opTor2);
	testLeftAssign(opTor3, 3, opTor2);
	//static_cast<Operator*>(opTor3)->assignRightOp(opTor1);
	testRightAssign(opTor3, 3, opTor1);
	cout << endl;

	cout << "Testing getExpType after assignment" << endl;
	testGetExp(static_cast<Operator*>(opTor1), 1, testString = "operand");
	testGetExp(static_cast<Operator*>(opTor2), 2, testString = "operand");
	testGetExp(static_cast<Operator*>(opTor3), 3, testString = "operand");
	cout << endl;

	cout << "Testing operator evaluations" << endl;
	testEval(opTor1, 1, 15);
	testEval(opTor2, 2, 55);
	testEval(opTor3, 3, 40);
	cout << endl;

	delete opTor3;
	delete opTor4;

	return 0;
}
