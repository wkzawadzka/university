#ifndef FELIDAE_H
#define FELIDAE_H

// included dependencies
#include "animal.h" // parent class
#include <iostream>
#include <string>

class Felidae : public Animal {
    int teeths;
    std::string eyeColor;

public:
    // constructor:
    Felidae(int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

extern const char *eyeColor[6];

#endif