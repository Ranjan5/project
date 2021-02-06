/*
 * person.h
 *
 *  Created on: Dec 31, 2020
 *      Author: aaksh
 */

#ifndef PERSON_H_
#define PERSON_H_

/**
 * Below is the list of all the nessasary #includes needed for the simulation.
 **/

#include <string>
#include <list>
#include <iostream>
#include <cstdbool>
#include <random>
#include <cmath>
#include <chrono>

using namespace std;

class family;

/**
 * Setting up global variables.
 **/

extern int radius;

/**
 * This is the person class.
 */
class person {

	//All the private variables of the class.
private:
	double ID;
	double age;
	int initPos[2];
	int movedPos[2];
	int sinceRet;
	bool infected;
	int recoveryTime;
	int numInfected;
	int immunity;
	short numRelations;
	list<family*> relations;
	bool death;

	//All the public functions.
public:
	void initPerson(bool newInfected);
	void initPerson(double newID, double newAge, int newInitPos[2],
			int newMovedPos[2], int newSinceRet, bool newInfected,
			int newRecoveryTime, int newNumInfected, int newImmunity,
			short newNumRelations, bool newDeath);

	void printPerson();

	void setID(double newID);
	double getID();

	void setAge(double newAge);
	double getAge();

	void setInitPos(int *newInitPos);
	int* getInitPos();

	void setMovedPos(int *newMovedPos);
	int* getMovedPos();

	void setSinceRet(int newSinceRet);
	int getSinceRet();

	void setInfected(bool newInfected);
	bool getInfected();

	void setRecoveryTime(int newRecoveryTime);
	int getRecoveryTime();

	void setNumInfected(int newNumInfected);
	int getNumInfected();

	void setImmunity(double newImmunity);
	int getImmunity();

	void setDeath(bool newDeath);
	bool getDeath();

	void setNumRelations(int newNumRelations);
	int getNumRelations();

	void addRelations(family *newRelations);
	family* getRelations(double relationID);
	list<family*>::iterator getRelations();
};

/**
 * This is the family class.
 */

class family {
	//All the private variables of the class.
private:
	person *member;
	double closeness;

	//All the public functions.
public:
	void setMember(person *newMember);
	person* getMember();

	void setCloseness(double newCloseness);
	double getCloseness();
};

/**
 * This function i used to store the radius of the world in the global variable radius.
 */

void getRadius(int numPeople, double populationDensity);

/**
 * This function is used to call the personRelations function, using recursion.
 */

void initRelations(map<string, person*>::iterator it);

#endif /* PERSON_H_ */
