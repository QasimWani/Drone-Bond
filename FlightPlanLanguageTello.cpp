#include "pch.h"
#include <iostream>
#include "FlightPlanLanguage.h"
#include "TelloApi.h"


// Flight Plan Language class version 1.2

// The FlightPlanLanguageTello subset of the FlightPlanLanguage member functions concentrates
// on communicating with the Tello drone.


using namespace std;


// The FPL destructor deallocates the Tello object if it was created.

FlightPlanLanguage::~FlightPlanLanguage()
{
	if (tello_drone != nullptr) {
		delete tello_drone;
		tello_drone = nullptr;
	}
}


// Execute the Tello command appearing at the specified index in the drone_command_table.
// A Tello object will be created when an "<initialize>" drone command occurs.

void FlightPlanLanguage::executeTelloCommand(int index)
{
	string command = indexToDroneCommand(index);

	if (command == "<initialize>") {
		if (tello_drone == nullptr) {
			tello_drone = new Tello();
		}
		if (!(tello_drone->canInitialize())) {
			cout << "Tello initialization failed" << endl;
			delete tello_drone;
			tello_drone = nullptr;
		}
	}
	else {
		if (tello_drone == nullptr) {
			cout << "Tello not initialized before " << command << endl;
		}
		else {
			if (command.substr(0, 6) == "<move ") {
				// Insert your code here
				string cmd = command.substr(5);
				string delimiter = " %";

				size_t pos = 0;
				string token;
				int i = 0;
				int positions[3];
				
				while ((pos = cmd.find(delimiter)) != string::npos) {
					token = cmd.substr(0, pos);
					cmd.erase(0, pos + delimiter.length());
					if (token != "\0")
					{
						positions[i] = int_variable_table[lookupIntVariable(token)].value;
						i++;
					}
				}
				positions[i] = int_variable_table[lookupIntVariable(cmd)].value;
				

				Coordinates move_tello;
				move_tello.x = positions[0];
				move_tello.y = positions[1];
				move_tello.z = positions[2];

				tello_drone->move(move_tello);
			}
			else if (command == "<arm>") {
				tello_drone->arm();
			}
			else if (command == "<takeoff>") {
				tello_drone->takeoff();
			}
			else if (command == "<land>") {
				tello_drone->land();
			}
			else {
				cout << "Unrecognized Tello \"" << command << "\" command" << endl;
			}
		}
	}
}
