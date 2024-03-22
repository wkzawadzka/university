#ifndef TIGER_H
#define TIGER_H

// included dependencies
#include "panthera.h" // parent class
#include <iostream>

class Tiger : public Panthera {
    bool isSocial;

public:
    // constructor:
    Tiger(bool isSocial, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

#endif