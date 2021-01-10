/*
 * simulation.h
 *
 *  Created on: Dec 31, 2020
 *      Author: aaksh
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

/**
 * Below is the list of all the nessasary #includes needed for the simulation.
 **/

#include "world.h"

/**
 * Setting up global variables to be shared.
 **/
extern int numPeople;
extern double populationDensity;
extern int radius;
extern int runPeriod;
extern int daysInSimulation;

using namespace std;

#endif /* SIMULATION_H_ */
