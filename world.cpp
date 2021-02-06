/*
 * world.cpp
 *
 *  Created on: Dec 31, 2020
 *      Author: aaksh
 */

/**
 * Below is the list of all the nessasary #includes needed for the simulation.
 **/

#include "world.h"

/**
 * Setting up global variables.
 **/

map<string, person*> world;
map<string, person*>::iterator it;

/**
 * Defining functions.
 */

void initRadius();
void initWorld();
void printWorld();

/**
 * This function is used to initialize the world, where the person nodes will be stored.
 */

void initWorld() {
	//Initialize the radius.
	initRadius();

	//Add the infected to the list first.
	person *infPerson = (person*) malloc(sizeof(person));

	//Construct the infected person.
	infPerson->initPerson(true);

	//Convert the infected person position to string.
	string pos = infPerson->getInitPos()[0] + " " + infPerson->getInitPos()[1];

	//Add infected person to the world.
	world[pos] = infPerson;

	//Add the rest of the person to the world, using for loop.
	for (int i = 1; i <= numPeople; i++) {
		//Add the infected to the list first.
		person *normPerson = (person*) malloc(sizeof(person));

		//Construct the infected person.
		normPerson->initPerson(false);

		//Convert the infected person position to string.
		pos = normPerson->getInitPos()[0] + " " + normPerson->getInitPos()[1];

		//Add infected person to the world.
		world[pos] = normPerson;
	}
}

/**
 * This function is used to print the world out.
 */

void printWorld() {
	//Setting up the for loop with a literator.
	for (it = world.begin(); it != world.end(); it++) {
		it->second->printPerson();
	}
}
