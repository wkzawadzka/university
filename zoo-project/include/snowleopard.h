#ifndef SNOWLEOPARD_H
#define SNOWLEOPARD_H

// included dependencies
#include "panthera.h" // parent class
#include <iostream>
#include <string>

class SnowLeopard : public Panthera {
    std::string tailType;

public:
    // constructor:
    SnowLeopard(std::string tailType, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

extern const char *tailType[3];

#endif