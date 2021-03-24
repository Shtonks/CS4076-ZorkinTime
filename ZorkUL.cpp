#include <iostream>
//<LUKE>move all these??
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <string>

using namespace std;
#include "ZorkUL.h"

int main() {
	ZorkUL temp;
	temp.play();
	return 0;
}

ZorkUL::ZorkUL() {
	createRooms();
}

void ZorkUL::createRooms()  {
    const int numOfRooms = 16;
    string dmgBonusRooms[numOfRooms] = {"Room of Nothing Extraordinary",
                              "Room of Nothing Extraordinary",
                              "Room of Nothing Extraordinary",
                              "Room of Nothing Extraordinary",
                              "Room of Nothing Extraordinary",
                              "Room of Nothing Extraordinary",
                              "Room of the Sword",
                              "Room of the Sword",
                              "Room of the Spear",
                              "Room of the Spear",
                              "Room of the Mace",
                              "Room of Flame",
                              "Room of Flame",
                              "Room of Frost",
                              "Room of Frost",
                              "Room of the Snake"};

    // obtain a time-based seed
    //<LUKE> Means complete guarenteed randomness when assigning rooms
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    shuffle (dmgBonusRooms, dmgBonusRooms + numOfRooms, std::default_random_engine(seed));

    for(int i = 0; i < numOfRooms; i++){
        genRooms.push_back(new Room(dmgBonusRooms[i]));
        cout << genRooms[i]->getDescription() << endl;
    }


    //<LUKE> rooms set out so ALL join together at start
    //(N, E, S, W)
    genRooms[0]->setExits(NULL, genRooms[1], genRooms[4], NULL);
    genRooms[1]->setExits(NULL, genRooms[2], genRooms[5], genRooms[0]);
    genRooms[2]->setExits(NULL, genRooms[3], genRooms[6], genRooms[1]);
    genRooms[3]->setExits(NULL, NULL, genRooms[7], genRooms[2]);

    genRooms[4]->setExits(genRooms[0], genRooms[5], genRooms[8], NULL);
    genRooms[5]->setExits(genRooms[1], genRooms[6], genRooms[9], genRooms[4]);
    genRooms[6]->setExits(genRooms[2], genRooms[7], genRooms[10], genRooms[5]);
    genRooms[7]->setExits(genRooms[6], NULL, genRooms[11], genRooms[6]);

    genRooms[8]->setExits(genRooms[4], genRooms[9], genRooms[12], NULL);
    genRooms[9]->setExits(genRooms[5], genRooms[10], genRooms[13], genRooms[8]);
    genRooms[10]->setExits(genRooms[6], genRooms[11], genRooms[14], genRooms[9]);
    genRooms[11]->setExits(genRooms[7], NULL, genRooms[15], genRooms[10]);

    genRooms[12]->setExits(genRooms[8], genRooms[13], NULL, NULL);
    genRooms[13]->setExits(genRooms[9], genRooms[14], NULL, genRooms[12]);
    genRooms[14]->setExits(genRooms[10], genRooms[15], NULL, genRooms[13]);
    genRooms[15]->setExits(genRooms[11], NULL, NULL, genRooms[14]);


    //<LUKE> Random room I've picked for now. Could be randomised
    currentRoom = genRooms[10];


}

/**
 *  Main play routine.  Loops until end of play.
 */
void ZorkUL::play() {
	printWelcome();


	bool finished = false;
	while (!finished) {
		// Create pointer to command and give it a command.
		Command* command = parser.getCommand();
		// Pass dereferenced command and check for end of game.
		finished = processCommand(*command);
		// Free the memory allocated by "parser.getCommand()"
		//   with ("return new Command(...)")
		delete command;
	}
	cout << endl;
	cout << "end" << endl;
}

//<LUKE> Basic desc of you having limited time and you must prepare. Too vague??
void ZorkUL::printWelcome() {
    cout << "You have " << numMoves << " before death comes searching for you "
    " and you're crystal"<< endl;
    cout << "Make good use of you're time. Prepare"<< endl;
	cout << endl;
    cout << "You begin in " << currentRoom->getDescription() << endl;
}


string ZorkUL::go(string direction) {
	Room* nextRoom = currentRoom->nextRoom(direction);
	if (nextRoom == NULL)
		return("direction null");
	else
	{
		currentRoom = nextRoom;
        return currentRoom->getDescription();
    }
}
