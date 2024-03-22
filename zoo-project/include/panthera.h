#ifndef PANTHERA_H
#define PANTHERA_H

// included dependencies
#include "felidae.h" // parent class
#include <iostream>
#include <string>

class Panthera : public Felidae {
    bool canRoar;
    std::string skullType;

public:
    // constructor:
    Panthera(bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

extern const char *skullType[4];

#endif