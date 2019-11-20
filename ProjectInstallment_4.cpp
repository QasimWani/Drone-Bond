#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "FlightPlanLanguage.h"
#include "TelloApi.h"


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
int case_num = 1;

// Part 1. Parse.cpp

int test_isVariable(string variable)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);
	if (!FLP.isVariable(variable))
	{
		cout << case_num << ". " << "\"" << variable  << "\"" << " is not a variable.\tTest Failed." << endl;
		return 1;

	}
	else
	{
		cout << case_num << ". " << "test_isVariable passed." << endl;
	}
	case_num++;
	return 0;
}

int test_isIntConstant(string number)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);
	if (!FLP.isIntConstant(number))
	{
		cout << case_num << "\"" << number << "\"" << " is not a number.\tTest Failed." << endl;
		return 1;
	}
	else
	{
		cout << case_num << ". " << "test_isIntConstant passed." << endl;
	}
	case_num++;
	return 0;
}

int test_isLabel(string label)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);

	if (!FLP.isLabel(label))
	{
		cout << case_num << "\"" << label << "\"" << " is not a label.\tTest Failed." << endl;
		return 1;
	}
	else
	{
		cout << case_num << ". " << "test_isLabel passed." << endl;
	}
	case_num++;
	return 0;
}

int test_isOpcode(string opcode)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);
	if (!FLP.isOpcode(opcode))
	{
		cout << case_num << "\"" << opcode << "\"" << " is not a valid opcode.\tTest Failed." << endl;
		return 1;
	}
	else
	{
		cout << case_num << ". " << "test_isOpcode passed." << endl;
	}
	case_num++;
	return 0;
}

int test_isDroneCommand(string command)
{
	FlightPlanLanguage FLP(TRACE_ALL_OPCODES_MODE, NO_DRONE_MODE);
	if (!FLP.isDroneCommand(command))
	{
		cout << case_num << "\"" << command << "\"" << " is not a drone command.\tTest failed." << endl;
		return 1;
	}
	else
	{
		cout << case_num << ". " << "test_isDroneCommand passed." << endl;
	}
	case_num++;
	return 0;
}

// Part 2. Tello.cpp
int test_is_Tello_Created(Tello *tello_pointer, Tello *compare_with)
{
	if (tello_pointer == nullptr || compare_with == nullptr)
	{
		cout << case_num << ". Null Pointer Detected. Object not created.\tTest Failed." << endl;
		return 1;
	}
	else if(tello_pointer == compare_with)
	{
		cout << case_num << ". Object created. However, same pointer location detected. Pointer Location : " << tello_pointer << "\tTest Failed." << endl;
		return 1;
	}
	else
	{
		cout << case_num << ". Object created. Pointer location different and none null pointer.\tTest passed." << endl;
		return 1;
	}
	case_num++;
	return 0;
}

int test_tello_initialization(Tello tello, string expected)
{
	if (!tello.canInitialize() || &tello == nullptr)
	{
		cout << case_num << ". Tello not successfully initialized. Possible errors:\t1.Not connected via TCP/UDP connection. Configure via your IP v4. address.\t2. Null pointer location passed.\tTest failed." << endl;
		return 1;
	}
	else
	{
		cout << case_num << ". Tello initialization successful. Socket Connection instantiated.\tTest passed." << endl;
	}
	case_num++;
	return 0;
}

int test_virtual_tello_initialization(enum DroneMode drone_mode, string command, int case_val)
{
	FlightPlanLanguage fpl(TRACE_ALL_OPCODES_MODE, drone_mode);
	/**
	if (!tellow->canInitialize())
	{
		cout << case_num << ". Tello not successfully initialized. Possible errors:\t1.Not connected via TCP/UDP connection. Configure via your IP v4. address.\t2. Null pointer location passed.\tTest failed." << endl;
		return 1;
	}
	else
	{
		cout << case_num << ". Tello initialization successful. Socket Connection instantiated.\tTest passed." << endl;
	}
	case_num++;
	**/
	fpl.drone_command_table[0] = command;
	fpl.executeTelloCommand(0);
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

	//Part 2. Tello Implementation
	
	struct type_drone_commands
	{
		string init;
		string move;
		string random_value;
	};
	 
	struct Tello_test
	{
		Tello *location;
		Tello tello_drone;
		type_drone_commands Tello_move;
	};
	
	struct Full_Unit_Test
	{
		Parse_test test_parse;
		Tello_test test_tello;
	};

	Full_Unit_Test unitTests;
	
	//Part 1 implementation
	unitTests.test_parse.is_int = "var";
	unitTests.test_parse.is_const = "+3";
	unitTests.test_parse.is_label = "right:";
	unitTests.test_parse.is_opcode = "set";
	unitTests.test_parse.is_drone_command = "<takeoff>";


	cout << "\n\n\nInitializing Test cases: \n" << endl;

	cout << "Testing Parse.cpp..." << endl << endl;

	int result_1 = test_isVariable(unitTests.test_parse.is_int) + test_isIntConstant(unitTests.test_parse.is_const) + test_isLabel(unitTests.test_parse.is_label) + test_isOpcode(unitTests.test_parse.is_opcode) + test_isDroneCommand(unitTests.test_parse.is_drone_command);

	cout << "\Parse Test Results : 5\tPassed : " << 5 - result_1 << "\tFailed : " << result_1 << endl;

	//Part 2 implementation

	unitTests.test_tello.location = nullptr;
	unitTests.test_tello.Tello_move.move = "<move %x %y %z>";
	unitTests.test_tello.Tello_move.init = "<initialize>";

	unitTests.test_tello.Tello_move.random_value = "<engineering>";
	
	
	int result_2 = test_is_Tello_Created(unitTests.test_tello.location, &unitTests.test_tello.tello_drone) + test_tello_initialization(unitTests.test_tello.tello_drone, "expect-null");
	

	test_virtual_tello_initialization(VIRTUAL_DRONE_MODE, unitTests.test_tello.Tello_move.init, 2);
	
	if(result_1  + result_2 > 0)
	{
		return -1;
	}
	return 0;
}