#ifndef JAGUAR_H
#define JAGUAR_H

// included dependencies
#include "panthera.h" // parent class
#include <iostream>
#include <string>

class Jaguar : public Panthera {
    std::string furPattern;

public:
    // constructor:
    Jaguar(std::string furPattern, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

extern const char *furPattern[4];

#endif
