#pragma once

#include "Riskfactor.h"
#include "Room.h"
#include <string>
#include <time.h>
using namespace std;

class BigBad {
private:
    int maxHealth;
    int currHealth;
    unsigned int vulnerability : 3;
    unsigned int resistance : 3;
    void genRisks();
    string typeToString(int dmgType);
public:
    BigBad(int health);
    int getMaxHealth();
    int getCurrHealth();
    void takeDmg(int dmg);
    int getVulnerability();
    string getVulnerabilityString();
    int getResistance();
    string getResistanceString();
    string leaveDungeon(Room* rooms[], int numRooms);
};

