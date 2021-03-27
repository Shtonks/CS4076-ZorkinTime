#include "Globals.h"

//<ISHA> Randomly generate how much time is left? or default set?
//Counter::Counter(){
//    counter = genNum(85,100);
//}

Counter::Counter(int num) : counter{num} {};

int genNum(int min, int max){
    return (max > 0) ? (rand() % (max-min)) + min : 0;
}
