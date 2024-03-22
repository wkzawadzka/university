#ifndef LEOPARD_H
#define LEOPARD_H

// included dependencies
#include "panthera.h" // parent class
#include <iostream>
#include <string>

class Leopard : public Panthera {
    std::string bellyColor;

public:
    // constructor:
    Leopard(std::string bellyColor, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

extern const char *bellyColor[4];

#endif