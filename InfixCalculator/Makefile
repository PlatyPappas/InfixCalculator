demo: infixCalculatorDriver

tests: infixValidatorTestDriver helperTestDriver operandTestDriver operatorTestDriver expressionHelperTestDriver infixCalculatorTestDriver

infixCalculatorDriver: infixCalculator.o infixCalculatorDriver.o infixValidator.o operator.o operand.o expressor.o
	g++ infixCalculator.o infixCalculatorDriver.o infixValidator.o operator.o operand.o expressor.o -o infixCalculatorDemo

infixValidatorTestDriver: infixValidatorTest.o infixValidator.o
	g++ -g infixValidatorTest.o infixValidator.o -o infixValidatorTestDriver

helperTestDriver: helperFunctions.o helperFunctionTests.o
	g++ -g helperFunctions.o helperFunctionTests.o -o helperTestDriver

operandTestDriver: operand.o expressor.o operandTest.o
	g++ -g operand.o expressor.o operandTest.o -o operandTestDriver

operatorTestDriver: operator.o operand.o expressor.o operatorTest.o
	g++ -g operator.o operand.o expressor.o operatorTest.o -o operatorTestDriver

expressionHelperTestDriver: operator.o operand.o expressor.o expressionHelpers.o expressionHelpersTests.o
	g++ operator.o operand.o expressor.o expressionHelpers.o expressionHelpersTests.o -o expressionHelperTestDriver

infixCalculatorTestDriver: infixCalculator.o infixCalculatorTest.o infixValidator.o operator.o operand.o expressor.o
	g++ infixCalculator.o infixCalculatorTest.o infixValidator.o operator.o operand.o expressor.o -o infixCalculatorTestDriver

infixCalculatorDriver.o: ./infixCalculatorDriver.cpp ./include/ConnerPappasPlexsys/infixCalculator.hpp
	g++ -c ./infixCalculatorDriver.cpp

infixValidatorTest.o: ./tests/infixValidatorTest.cpp ./src/infixValidator.hpp
	g++ -c ./tests/infixValidatorTest.cpp ./src/infixValidator.cpp
	
infixValidator.o: ./src/infixValidator.cpp ./src/infixValidator.hpp
	g++ -c ./src/infixValidator.cpp
	
helperFunctionTests.o: ./tests/helperFunctionTests.cpp ./tests/helperFunctions.hpp
	g++ -c ./tests/helperFunctionTests.cpp ./tests/helperFunctions.cpp

helperFunctions.o: ./tests/helperFunctions.cpp ./tests/helperFunctions.hpp
	g++ -c ./tests/helperFunctions.cpp

operandTest.o: ./tests/operandTest.cpp ./src/operand.hpp ./src/expressor.hpp
	g++ -c ./tests/operandTest.cpp ./src/operand.cpp ./src/expressor.cpp

operatorTest.o: ./tests/operatorTest.cpp ./src/operator.hpp ./src/operand.hpp ./src/expressor.hpp
	g++ -c ./tests/operatorTest.cpp ./src/operator.cpp ./src/operand.cpp ./src/expressor.cpp

expressionHelpers.o: ./tests/expressionHelpers.cpp ./tests/expressionHelpers.hpp ./src/operator.hpp ./src/operand.hpp ./src/expressor.hpp
	g++ -c ./tests/expressionHelpers.cpp

expressionHelpersTests.o: ./tests/expressionHelpersTests.cpp ./tests/expressionHelpers.hpp ./src/operator.hpp ./src/operand.hpp ./src/expressor.hpp
	g++ -c ./tests/expressionHelpersTests.cpp

infixCalculator.o: ./src/infixCalculator.cpp ./include/ConnerPappasPlexsys/infixCalculator.hpp ./src/infixValidator.hpp ./src/operator.hpp ./src/operand.hpp ./src/expressor.hpp
	g++ -c ./src/infixCalculator.cpp ./src/infixValidator.cpp ./src/operator.cpp ./src/operand.cpp ./src/expressor.cpp

infixCalculatorTest.o: ./tests/infixCalculatorTest.cpp ./include/ConnerPappasPlexsys/infixCalculator.hpp
	g++ -c ./tests/infixCalculatorTest.cpp

expressor.o: ./src/expressor.cpp ./src/expressor.hpp
	g++ -c ./src/expressor.cpp

operand.o: ./src/operand.cpp ./src/operand.hpp ./src/expressor.hpp
	g++ -c ./src/operand.cpp ./src/expressor.cpp

operator.o: ./src/operator.cpp ./src/operator.hpp ./src/expressor.hpp
	g++ -c ./src/operator.cpp ./src/expressor.cpp

clean:
	rm -f *.o infixValidatorTestDriver helperTestDriver operatorTestDriver operandTestDriver expressionHelperTestDriver infixCalculatorTestDriver infixCalculatorDemo