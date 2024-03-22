#ifndef OCELOT_H
#define OCELOT_H

// included dependencies
#include "leopardus.h" // parent class
#include <iostream>
#include <string>

class Ocelot : public Leopardus {
    std::string furLength;
    float bodyLength;

public:
    // constructor:
    Ocelot(float bodyLength, std::string furLength, std::string furColor, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();

    friend class Breeder;
};

extern const char *furLength[4];

#endif