#include "Item.h"

Item::Item(){}

Item::Item(string n, string d, int t) {
	name = n;
	description = d;
    timeMod = t;
}

string Item::getName() const{
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

//Operator overloading
bool Item::operator== (const Item & rhs) const {
   return (name == rhs.getName());
}

//Template function to find maximum num
template <typename T>
T getMax(T num1, T num2) {
    int max = num1;
    if(num1 < num2){
        max = num2;
    }
    return max;
}
