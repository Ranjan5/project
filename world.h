/*
 * world.h
 *
 *  Created on: Dec 31, 2020
 *      Author: aaksh
 */

#ifndef WORLD_H_
#define WORLD_H_

/**
 * Below is the list of all the nessasary #includes needed for the simulation.
 **/

#include <map>
#include "person.h"

/**
 * Setting up global variables to be shared.
 **/

extern map<int, person*> world;
extern map<int, person*>::iterator it;

using namespace std;

/**
 * This function is used to initialize the world, where the person nodes will be stored.
 */
void initWorld();

/**
 * This function is used to print the world out.
 */

void printWorld();

#endif /* WORLD_H_ */
