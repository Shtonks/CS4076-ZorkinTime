#pragma once

#include "Riskfactor.h"
#include "Room.h"
#include <string>
#include <time.h>
using namespace std;

class BigBad {
private:
    int health;
    unsigned int vulnerability : 3;
    unsigned int resistance : 3;
    void genRisks();
    string typeToString(int dmgType);
public:
    BigBad(int health);
    int getHealth();
    int getVulnerability();
    string getVulnerabilityString();
    int getResistance();
    string getResistanceString();
    void leaveDungeon(Room* rooms[], int numRooms);
};

