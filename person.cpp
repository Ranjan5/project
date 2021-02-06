/*
 * person.cpp
 *
 *  Created on: Dec 31, 2020
 *      Author: Aaksh Ranjan
 */

/**
 * Below is the list of all the nessasary #includes needed for the simulation.
 **/

#include "person.h"

using namespace std;

/**
 * Setting up global variables.
 */

int radius = 0;
static int freeID = 0;

/**
 * Construction a random generator engine from a time-based seed.
 */

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
default_random_engine generator(seed);

/**
 * Creating a uniform 0 to 1 distribution.
 */

uniform_real_distribution<> zeroToOne(0.0, 1.0);

/**
 * Defining functions.
 */

bool runProbability(float probability);
bool relationProbability(int x1, int y1, int x2, int y2);
void getRadius(int numPeople, double populationDensity);
int* randomPosition();
double randomAge();
int randomRecovery(double age);
int randomNumRelations();

/**
 * This is the constructor function for person, without file.
 */
void person::initPerson(bool newInfected) {
	//Setting the values of the internal variable of the class.
	ID = freeID;

	//Incrementing the value of freeID.
	freeID++;

	//Setting the values of the internal variable of the class.
	age = randomAge();

	//Getting an random position.
	int *newPos = randomPosition();

	//Setting the values of the internal variable of the class.
	initPos[0] = newPos[0];
	initPos[1] = newPos[1];

	movedPos[0] = newPos[0];
	movedPos[1] = newPos[1];

	//Freeing newPos.
	free(newPos);

	//Setting the values of the internal variable of the class.
	sinceRet = 0;

	//Checking if this person has to be infected.
	if (newInfected) {
		//Setting the value of infected to newInfected.
		infected = newInfected;

		//Setting the value of recoveryTime to randomRecovery.
		recoveryTime = randomRecovery(age);

		//Setting the value of numInfected to one.
		numInfected = 1;
	} else {
		//Setting the value of infected to !newInfected.
		infected = !newInfected;

		//Setting the value of recoveryTime to zero.
		recoveryTime = 0;

		//Setting the value of numInfected to zero.
		numInfected = 0;
	}

	//Setting the values of the internal variable of the class.
	immunity = 0;

	numRelations = randomNumRelations();

	death = false;
}

/**
 * This is the constructor function for person, without file.
 */
void person::initPerson(double newID, double newAge, int newInitPos[2],
		int newMovedPos[2], int newSinceRet, bool newInfected,
		int newRecoveryTime, int newNumInfected, int newImmunity,
		short newNumRelations, bool newDeath) {
	//Setting the values of the internal variable of the class.
	ID = newID;

	//Setting the value of freeID.
	if (freeID < newID) {
		freeID = newID;
	}

	//Setting the values of the internal variable of the class.
	age = newAge;

	initPos[0] = newInitPos[0];
	initPos[1] = newInitPos[1];

	movedPos[0] = newMovedPos[0];
	movedPos[1] = newMovedPos[1];

	sinceRet = newSinceRet;

	infected = newInfected;

	recoveryTime = newRecoveryTime;

	numInfected = newNumInfected;

	immunity = newImmunity;

	numRelations = newNumRelations;

	death = newDeath;
}

/**
 * This function return a bool with a given probability.
 */

bool runProbability(float probability) {
	//Return a bool value depending on the probability.
	return zeroToOne(generator) <= probability;
}

/**
 * This function is used to find out if someone is a relation or not.
 */

bool relationProbability(int x1, int y1, int x2, int y2) {

	//Using the cumulative function to get a probability of relation.
	float probability = exp(
			-((pow(abs(x1 - x2), 2)) + (pow(abs(y1 - y2), 2)))
					/ (2 * pow(radius, 2)));

	//Use the runProbability function to return a bool value.
	return runProbability(probability);
}

/**
 * This function i used to store the radius of the world in the global variable radius.
 */

void getRadius(int numPeople, double populationDensity) {
	//Getting the are of the world.
	double area = numPeople / populationDensity;

	//Get the radius of the area.
	int stackRadius = sqrt(area / M_PI);

	//Store the radius into the global radius.
	radius = stackRadius;
}

/**
 * This function is used to return a random position.
 * The population density is going to be highest around one thirds of the radius.
 * No person has the same position.
 **/

int* randomPosition() {

	//Creating a normal distribution with mean of radius/3 and standard deviation of radius/3.
	normal_distribution<double> normDistribution((double) (radius / 3),
			(double) (radius / 3));

	//Getting a random position and angle.
	int position = ((int) (normDistribution(generator))) % radius;
	float angle = fmod(rand(), 360);

	//Getting the x and y from position and angle.
	int x = (int) (position * cos((angle / 180) * M_PI));
	int y = (int) (position * sin((angle / 180) * M_PI));

	//Get an array of size two int.
	int *pos = (int*) malloc(sizeof(int) * 2);

	//Storing the x and y value into pos.
	pos[0] = x;
	pos[1] = y;

	//Returning the int pointer pos.
	return pos;
}

/**
 * This function is used to return a random age using normal distribution, with a mean of 29.6 years, standard deviation of 10 and range of 1 to 122.
 **/

double randomAge() {
	//Creating a normal distribution with mean of 29.6 and standard deviation of 10.
	normal_distribution<double> normDistribution(29.6, 10.0);

	//Creating local variable to store a random age.
	double age = normDistribution(generator);

	//While loop to check the result of the normal distribution. Should be within the range to return the value.
	while (age < 0 || age > 122) {
		//If not within the range get a new random age using normal distribution.
		age = normDistribution(generator);
	}

	//Return the age value.
	return age;
}

/**
 * This function is used to return a random number of days to recovery from covid. Depending on the age group the mean
 * and standard deviation of the normal distribution will be different.
 **/

int randomRecovery(double age) {

	//Creating local variable called mean.
	int mean = 0;

	//There are four different age groups.
	if (age <= 20 && age > 0) {
		//If between 0 and 20 years of age, set mean as 7.
		mean = 8;
	} else if (age <= 40 && age > 20) {
		//If between 20 and 40 years of age, set mean as 9.
		mean = 10;
	} else if (age <= 60 && age > 40) {
		//If between 40 and 60 years of age, set mean as 11.
		mean = 12;
	} else {
		//If above 60 years of age, set mean as 14.
		mean = 16;
	}

	//Create the distribution with mean as mean and standard deviation as 1.
	normal_distribution<double> normDistribution(mean, 1);

	//Creating local variable to store a random age.
	double recovery = normDistribution(generator);

	//While loop to check the result of the normal distribution. Should be within the range to return the value.
	while (recovery < 1 || recovery > 30) {
		//If not within the range get a new random closeness using normal distribution.
		recovery = normDistribution(generator);
	}

	//Return the age value.
	return (int) recovery;
}

/**
 * This function is used to return a random int of relations of the person, using a normal distribution with a mean of 3.23
 * and standard deviation of 0.5.
 */

int randomNumRelations() {
	//Local variable to return.
	int numRelations;

	//Create the distribution with mean as mean and standard deviation as 1.
	normal_distribution<double> normDistribution(3.23, 1);

	//While loop to check the result of the normal distribution. Should be within the range to return the value.
	while (numRelations <= 0 || numRelations >= 10) {
		numRelations = normDistribution(generator);
	}

	//Returning the numRelations.
	return (int) numRelations;
}

/**
 * Set and get function of ID.
 */

void person::setID(double newID) {
	ID = newID;
}

double person::getID() {
	return ID;
}

/**
 * Set and get function of age.
 */

void person::setAge(double newAge) {
	age = newAge;
}
double person::getAge() {
	return age;
}

/**
 * Set and get function of initPos.
 */

void person::setInitPos(int *newInitPos) {
	initPos[0] = newInitPos[0];
	initPos[1] = newInitPos[1];
	free(newInitPos);
}
int* person::getInitPos() {
	return initPos;
}

/**
 * Set and get function of movedPos.
 */

void person::setMovedPos(int *newMovedPos) {
	movedPos[0] = newMovedPos[0];
	movedPos[1] = newMovedPos[1];
	free(newMovedPos);
}
int* person::getMovedPos() {
	return movedPos;
}

/**
 * Set and get function of sinceRet.
 */

void person::setSinceRet(int newSinceRet) {
	sinceRet = newSinceRet;
}
int person::getSinceRet() {
	return sinceRet;
}

/**
 * Set and get function of infected
 */

void person::setInfected(bool newInfected) {
	infected = newInfected;
}
bool person::getInfected() {
	return infected;
}

/**
 * Set and get function of recoveryTime
 */

void person::setRecoveryTime(int newRecoveryTime) {
	recoveryTime = newRecoveryTime;
}
int person::getRecoveryTime() {
	return recoveryTime;
}

/**
 * Set and get function of numInfected.
 */

void person::setNumInfected(int newNumInfected) {
	numInfected = newNumInfected;
}
int person::getNumInfected() {
	return numInfected;
}

/**
 * Set and get function of immunity.
 */

void person::setImmunity(double newImmunity) {
	immunity = newImmunity;
}
int person::getImmunity() {
	return immunity;
}

/**
 * Set and get function of death.
 */

void person::setDeath(bool newDeath) {
	death = newDeath;
}
bool person::getDeath() {
	return death;
}

/**
 * Set and get function of numRelations.
 */

void person::setNumRelations(int newNumRelations) {
	numRelations = newNumRelations;
}
int person::getNumRelations() {
	return numRelations;
}

/**
 * Set and get function for relations.
 */

void person::addRelations(family *newRelations) {
	//Get the iterator for the list.
	list<family*>::iterator it = relations.begin();

	//Check if newRelation is already in the list.
	for (it = relations.begin(); it != relations.end(); ++it) {
		if (newRelations->getMember()->getID() == (*it)->getMember()->getID()) {
			//If the newRelations is already added, dont add again.
			return;
		}
	}

	//Add newRelations.
	relations.push_back(newRelations);
}

/**
 * Returns the relations with the ID, else NULL if the relations doesn't exist.
 */

family* person::getRelations(double relationID) {
	//Get the iterator for the list.
	list<family*>::iterator it = relations.begin();

	//Check if newRelation is already in the list.
	for (it = relations.begin(); it != relations.end(); ++it) {
		if (relationID == (*it)->getMember()->getID()) {
			//If the newRelations is already added, dont add again.
			return *it;
		}
	}

	//Return NUll if the relation ID was not found.
	return NULL;
}

/**
 * Returns a pointer to the relations list.
 */
list<family*>::iterator person::getRelations() {
	return relations.begin();
}

/**
 * Set and get function for member.
 */

void family::setMember(person *newMember) {
	member = newMember;
}
person* family::getMember() {
	return member;
}

/**
 * Set and get function of closeness.
 */

void family::setCloseness(double newCloseness) {
	closeness = newCloseness;
}
double family::getCloseness() {
	return closeness;
}

/**
 * This function is used to print details about a person.
 */

void person::printPerson() {

	//Print the newPerson's variables.
	cout << "PID: " << ID << endl;
	cout << "Age: " << age << endl;
	cout << "PIP: " << initPos[0] << " " << initPos[1] << endl;
	cout << "PMP: " << movedPos[0] << " " << movedPos[1] << endl;
	cout << "PSR: " << sinceRet << endl;
	cout << "PIN: " << infected << endl;
	cout << "PRT: " << recoveryTime << endl;
	cout << "PNI: " << numInfected << endl;
	cout << "PIM: " << immunity << endl;
	cout << "PNR: " << numRelations << endl;
	cout << "PD: " << death << endl;
	cout << "PRs: " << endl;

	//Get the iterator for the list of family pointers.
	list<family*>::iterator it = relations.begin();

	//Iteration through relations and print out the ID of relation and closeness.
	for (it = relations.begin(); it != relations.end(); it++) {
		cout << (*it)->getMember()->getID() << " ";
		cout << (*it)->getCloseness() << endl;
	}

	cout << endl;
}

/**
 * This function is used to call the personRelations function for each person in the world.
 */

void initRelations(map<string, person*>::iterator it) {

	//Iteration through world and call personRelations function.
	for (it = world.begin(); it != world.end(); it++) {
		personRelations(it->second, min, max);
	}

}

/**
 * This function is used to initialize relations list for a newPerson, using recursion.
 */

void personRelations(person *newPerson, int min, int max) {

	//Base case of recursion, if max and min are equal.
	if (min == max) {

		//Check if the relations is already full.
		if (newPerson->getNumRelations() == newPerson->getRelations()->size()) {
			//skip, relations already full.
			return;
		}

		//Create a variable to keep track of the angle and angle increment.
		double angle = 0;
		double angleIncrement = M_PI * 2;

		//Special case if min = 0 because we don't want angleIncrement to be infinity.
		if (min == 0) {
			angleIncrement = M_PI * 2;
		} else {
			//Get the angle increment.
			double angleIncrement = M_PI / (4 * min);
		}

		//Creating a for loop to get all positions for that radius.
		for (angle = 0; angle <= M_PI * 2; angle = +angleIncrement) {
			//Getting the x and y from position and angle.
			int x = (int) (min * cos(angle));
			int y = (int) (min * sin(angle));

			//Store the it for the person in that position here.
			map<string, person*>::iterator posIt = world.find(x + " " + y);

			//Checking if a person is at that spot.
			if (posIt == world.end()) {
				//If someone is not at that position skip.
			} else {
				//Calculating the distance between newPerson and the person on that position.
				double distance = sqrt(
						(pow((newPerson->getInitPos())[0] - x, 2)
								+ pow((newPerson->getInitPos())[1] - y, 2)));
				//If someone is at the position check using probability, if this person is can be a family member.
				if (distance <= 14) {
					//If they are really close, check if other person's relations is full.
					if (posIt->second->getNumRelations()
							== posIt->second->getRelations()->size()) {
						//If full skip.
					} else {
						//Create a family node for both newPerson and person on that position.
						family *newsFamily = (family*) malloc(sizeof(family));
						family *possFamily = (family*) malloc(sizeof(family));

						newsFamily->setMember(posIt->second);
						newsFamily->setCloseness(distance / (radius * 2));

						possFamily->setMember(newPerson);
						possFamily->setCloseness(distance / (radius * 2));

						//Add each other as relations.
						newPerson->addRelations(newsFamily);
						posIt->second->addRelations(possFamily);
					}
				} else {
					//If the distance is more than 14 it depends on probability.
					if (randomProbability(
							newPerson->getNumRelations() / numPeople)) {
						//Create a family node for both newPerson and person on that position.
						family *newsFamily = (family*) malloc(sizeof(family));
						family *possFamily = (family*) malloc(sizeof(family));

						newsFamily->setMember(posIt->second);
						newsFamily->setCloseness(distance / (radius * 2));

						possFamily->setMember(newPerson);
						possFamily->setCloseness(distance / (radius * 2));

						//Add each other as relations.
						newPerson->addRelations(newsFamily);
						posIt->second->addRelations(possFamily);
					} else {
						//Skip because not related.
					}
				}
			}
		}
	}

	//Find the difference between start and end and dividing it by two.
	int div = (int) ((max - min) / 2);

	//recursively call the function again.
	personRelations(newPerson, min, min + div);
	personRelations(newPerson, min + div + 1, max);
}
