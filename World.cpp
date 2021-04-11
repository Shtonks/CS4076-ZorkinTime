#include <iostream>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <string>
#include <bitset>
using namespace std;
#include "World.h"

//<ISHA> namspaces only have a global scope, any variables declared inside are global as well.
namespace globals{
    string bonus = "same name as another string in file but can be accessed with globals::bonus";
}

//<ISHA> eeeeeeeeeeeeeeeeeeeeeeh
//template <class Item>
//Item ItemLonger(Item *i1, Item *i2){
//    return (i1->getTimeMod() > i2->getTimeMod()) ? i1 : i2;
//}

World::World() : player("player"), shop("shop", 6) {
    createRooms();
    createItems();
}

typedef struct World::roomAttbs {
    string bonus;
    unsigned int dmgBonusNum : 3; //<ISHA> int with 3 bits, range 0-7
    roomAttbs(string b, int d){
        bonus = b; dmgBonusNum = d;
    }
 } roomAttbs;

void World::createRooms()  {
    const int numOfRooms = 16;

    vector<roomAttbs> roomList = {
        roomAttbs("Room of Nothing Extraordinary", NOTHING),
        roomAttbs("Room of Nothing Extraordinary", NOTHING),
        roomAttbs("Room of Nothing Extraordinary", NOTHING),
        roomAttbs("Room of Nothing Extraordinary", NOTHING),
        roomAttbs("Room of Nothing Extraordinary", NOTHING),
        roomAttbs("Room of Nothing Extraordinary", NOTHING),
        roomAttbs("Room of the Sword", SLASHING),
        roomAttbs("Room of the Sword", SLASHING),
        roomAttbs("Room of the Spear", PIERCING),
        roomAttbs("Room of the Spear", PIERCING),
        roomAttbs("Room of the Mace", BLUDGEONING),
        roomAttbs("Room of Flame", FIRE),
        roomAttbs("Room of Flame", FIRE),
        roomAttbs("Room of Frost", COLD),
        roomAttbs("Room of Frost", COLD),
        roomAttbs("Room of the Snake", POISON)};

    // obtain a time-based seed
    //<LUKE> Means complete guarenteed randomness when assigning rooms
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    vector<roomAttbs>::iterator ritb = roomList.begin();
    vector<roomAttbs>::iterator rite = roomList.end();
    shuffle (ritb, rite, default_random_engine(seed));

    for(int i = 0; i < numOfRooms; i++){
        genRooms[i] = new Room(roomList.at(i).bonus, roomList.at(i).dmgBonusNum);
        //cout << genRooms[i]->getDescription() << endl;
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


    //<LUKE> Randomly start the player in a room
    srand(seed);
    int randStartRoom = rand() % numOfRooms;
    setCurrentRoom(genRooms[randStartRoom]);

    int randShopRoom = rand() % numOfRooms;
    shopRoom = genRooms[randShopRoom];

}

string World::getShopRoomLabel(){
    string shopRoomLabel = "";
    for(int i = 0; i < 16; i++){
        if(shopRoom == genRooms[i]){
            if(i+1 < 10) shopRoomLabel = "room0" + std::to_string(i+1);
            else shopRoomLabel = "room" + std::to_string(i+1);
        }
    }
    return shopRoomLabel;
}

Room* World::getCurrentRoom()
{
    return currentRoom;
}

//<LUKE> All the stuff going on with concatenating currentRoomLabel is to be able to find the room named exactly the same in ui file
void World::setCurrentRoom(Room* r)
{
    currentRoom = r;
    for(int i = 0; i < 16; i++){
        if(currentRoom == genRooms[i]){
            if(i+1 < 10) currentRoomLabel = "room0" + std::to_string(i+1);
            else currentRoomLabel = "room" + std::to_string(i+1);
        }
    }
}

string World::getCurrentRoomLabel()
{
    return currentRoomLabel;
}


Room** World::getGenRooms()
{
    return genRooms;
}

int World::getNumMoves(){
    return numMoves;
}

void World::setNumMoves(int n){
    numMoves = n;
}

void World::createItems(){
    //<LUKE> Completely randomly assigned vals by me
    shop.addTrap(new Trap("Pendulum of Regret", "Sharpened blade which swings back and forth, slicing any who dare intrude",
                          8, SLASHING, 20, 50));

    shop.addTrap(new Trap("Barbed Wire", "A seemingly minor thing, which in the right circumstance can make for a very painful day",
                          4, PIERCING, 15, 30));

    shop.addTrap(new Trap("The Protector", "Create a golem who will lay down its life to stop any intruder",
                          10, BLUDGEONING, 30, 60));

    shop.addTrap(new Trap("Ender Dragon’s Breath", "Stolen from a mythical beast, Ender Dragon’s Breath is potent enough to incerate any human in seconds",
                          6, FIRE, 20, 40));

    shop.addTrap(new Trap("White Walker’s Gaze", "Undead creatures which strike an impossible fear and chill into any creature",
                          12, COLD, 35, 50));

    shop.addTrap(new Trap("Mustard Gas", "Acid extracted from a now extinct species known as “Kikimore”, is vapourised to inflict a slow, agonising death",
                          8, POISON, 10, 30));
}

//<LUKE> Basic desc of you having limited time and you must prepare. Too vague??
void World::printWelcome() {
    cout << "You have " << numMoves << " turns before death comes searching for you "
    " and you're crystal"<< endl;
    cout << "Make good use of you're time. Prepare"<< endl;
    cout << endl;
    cout << "You begin in " << currentRoom->getDescription() << endl;
}

//Moves player in chosen direction if pathway exists
bool World::go(string direction) {
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return false;
    else
    {
        setCurrentRoom(nextRoom);
        return true;
    }
}
