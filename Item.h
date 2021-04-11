#pragma once

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Item {
    //<LUKE> making them protected so that derived classes can access these things directly
    protected:
		string description;
		string name;
		int timeMod;
        int amount;
        bool owned;

    public:
        Item();
        Item(string name, string description, int timeMod);
        virtual ~Item() = default;
        string getName() const;
        void setName(string name);
		string getDescription();
        void setDescription(string desc);
        int getTimeMod();
		void setTimeMod(int newMod);
        bool operator== (const Item & rhs) const;   // c1 == c2
        string toString();
};
