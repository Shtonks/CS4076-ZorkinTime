#ifndef CHARACTER_H_
#define CHARACTER_H_
#include "ZorkUL.h"

#include <string>
using namespace std;
#include <vector>
//using std::vector;


class Character {
private:
    string description;
    vector <Item> itemsInCharacter;
public:
    Character(string description);
    void addItem(Item);
    string shortDescription();
	string longDescription();

};

#endif /*CHARACTER_H_*/
