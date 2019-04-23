#include "utility.h"

void _delay(uint64_t time) {

    uint64_t timeToReach = millis() + time;
    while(millis() < timeToReach);
}

void _delayMs(uint64_t time) {

    uint64_t timeToReach = micros() + time;
    while(micros()< timeToReach);
}