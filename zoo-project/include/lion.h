#ifndef LION_H
#define LION_H

// included dependencies
#include "panthera.h" // parent class
#include <iostream>

class Lion : public Panthera {
    bool canSwim;

public:
    // constructor:
    Lion(bool canSwim, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

#endif