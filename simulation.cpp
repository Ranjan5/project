/*
 * simulation.cpp
 *
 *  Created on: Dec 31, 2020
 *      Author: Aaksh Ranjan
 */

/**
 * Below is the list of all the nessasary #includes needed for the simulation.
 **/

#include "simulation.h"

using namespace std;

/**
 * Setting up global variables.
 **/

int numPeople = 0;
double populationDensity = 0;
int runPeriod = 0;
int daysInSimulation = 0;

int main(int argc, char **argv) {
	//Local variables.
	string option;
	string fileName;
	string numPeopleString;
	string populationDensityString;
	string runPeriodString;

	//Print statement to ask for the type of input.
	cout << "1: Load a File." << endl;
	cout << "2: Create New Simulation." << endl << endl;
	cout << "Please Enter your Option: ";
	cin >> option;
	cout << endl << endl;

	if (option.compare("1") == 0) {
		//Asking to enter file name.
		cout << "Enter file name: ";
		cin >> fileName;

		//Calling a function to load the file.

	} else if (option.compare("2") == 0) {
		//Ask the user for simulation arguments (Population).
		cout << "Please enter the population of the simulation: \n";
		cin >> numPeopleString;

		//Change numPeopleString into a int and store value in numPeople.
		numPeople = stoi(numPeopleString);

		//Ask the user for simulation arguments (Population Density).
		cout
				<< "Please enter the population density (people per squared meter) of the simulation: \n";
		cin >> populationDensityString;

		//Change numPeopleString into a int and store value in populationDensity.
		populationDensity = stod(populationDensityString);

		//Ask the user for simulation arguments (Run Period).
		cout << "Please enter the run period of the simulation: \n";
		cin >> runPeriodString;

		//Change numPeopleString into a int and store value in runPeriod.
		runPeriod = stoi(runPeriodString);

		//Calling a function to initialize a new simulation.
		initWorld();

		//Calling function to initialize the relations.
		initRelations(0, radius);

		//Print the world.
		printWorld();
	} else {
		cout << "Incorrect entry!" << endl;
	}

	return 0;
}
