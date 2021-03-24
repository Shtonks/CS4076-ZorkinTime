#include "Item.h"

Item::Item(){}

Item::Item (string n, string d, int t) {
	name = n;
	description = d;
    timeMod = t;
}

string Item::getName(){
	return name;
}

void Item::setName(string name){
    this->name = name;
}

string Item::getDescription(){
	return description;
}

void Item::setDescription(string desc){
    description = desc;
}

int Item::getTimeMod(){
    return timeMod;
}

void Item::setTimeMod(int newMod){
	timeMod = newMod;
}
