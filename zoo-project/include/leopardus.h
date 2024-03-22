#ifndef LEOPARDUS_H
#define LEOPARDUS_H

// included dependencies
#include "felidae.h" // parent class
#include <iostream>
#include <string>

class Leopardus : public Felidae {
    std::string furColor;

public:
    // public:
    // constructor:
    Leopardus(std::string furColor, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

extern const char *furColor[7];

#endif