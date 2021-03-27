#pragma once

#include <string>
using namespace std;

#define SLASHING 1
#define PIERCING 2
#define BLUDGEONING 3
#define FIRE 4
#define ICE 5
#define POISON 6

//<ISHA> idk if counter should be a class or a struct??

class Counter {
private:
    int counter;
public:
    Counter(int);
    Counter() : counter(/*the default number?*/ 100) {} //<ISHA>For initializer list
    int getCounter();
    void adjustCounter(int difference); //<ISHA> positive to increase, negative for decrease
};

int genNum(int min, int max);
