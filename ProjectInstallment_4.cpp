#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "FlightPlanLanguage.h"


// Provides an example of using version 1.2 of the FlightPlanLanguage class, which
// supports FPL parsing, optional execution tracing, and optional drone communication.
// The program prompts for the name of a FPL file, parses the file, displays the
// parse tables generated, and possibly executes the FPL program according to the
// modes selected in the FPL class constructor.


using namespace std;

/**
Building Unit Test Set.
Part 1. FPLParse.cpp
Part 2. FPLTello.cpp
Part 3. FPLExecute.cpp
**/

int test_isVariable(string variable)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);
	if (!FLP.isVariable(variable))
	{
		cout << "\"" << variable  << "\"" << " is not a variable.\tTest Failed." << endl;
		return 1;

	}
	return 0;
}

int test_isIntConstant(string number)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);
	if (!FLP.isIntConstant(number))
	{
		cout << "\"" << number << "\"" << " is not a number.\tTest Failed." << endl;
		return 1;
	}
	return 0;
}

int test_isLabel(string label)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);

	if (!FLP.isLabel(label))
	{
		cout << "\"" << label << "\"" << " is not a label.\tTest Failed." << endl;
		return 1;
	}
	return 0;
}

int test_isOpcode(string opcode)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);
	if (!FLP.isOpcode(opcode))
	{
		cout << "\"" << opcode << "\"" << " is not a valid opcode.\tTest Failed." << endl;
		return 1;
	}
	return 0;
}

int test_isDroneCommand(string command)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);
	if (!FLP.isDroneCommand(command))
	{
		cout << "\"" << command << "\"" << " is not a drone command" << endl;
		return 1;
	}
	return 0;
}

int main()
{
	FlightPlanLanguage flight_plan(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);

	string file_name;

	cout << "Enter FPL file name: ";

	cin >> file_name;

	ifstream fppl_file(file_name);

	if (fppl_file.is_open()) {
		string line;
		while (getline(fppl_file, line)) {
			flight_plan.parseLine(line);
		}
		flight_plan.displayIntVariables();
		flight_plan.displayLabels();
		flight_plan.displayDroneCommands();
		flight_plan.displayInstructions();
		flight_plan.executeProgram();
	}
	else {
		cout << "File " << file_name << " not found" << endl;
	}
	
	struct Parse_test
	{
		string is_int;
		string is_const;
		string is_label;
		string is_opcode;
		string is_drone_command;
	};
	struct Full_Unit_Test
	{
		Parse_test test_parse;
	};

	Full_Unit_Test unitTests;
	unitTests.test_parse.is_int = "var";
	unitTests.test_parse.is_const = "+3";
	unitTests.test_parse.is_label = "right:";
	unitTests.test_parse.is_opcode = "set";
	unitTests.test_parse.is_drone_command = "<takeoff>";

	cout << "\n\n\nInitializing Test cases: \n" << endl;

	cout << "Testing Parse.cpp" << endl << endl;

	int result = test_isVariable(unitTests.test_parse.is_int) + test_isIntConstant(unitTests.test_parse.is_const) + test_isLabel(unitTests.test_parse.is_label) + test_isOpcode(unitTests.test_parse.is_opcode) + test_isDroneCommand(unitTests.test_parse.is_drone_command);

	cout << "\n\n\nTotal Tests : 5\t" << "Passed : " << 5 - result << "\tFailed : " << result << endl;

	if(result > 0)
	{
		return -1;
	}
	return 0;
}