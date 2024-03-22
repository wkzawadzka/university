#ifndef MARGAY_H
#define MARGAY_H

// included dependencies
#include "leopardus.h" // parent class
#include <iostream>
#include <string>

class Margay : public Leopardus {
    float tailLength;
    std::string activePeriod;

public:
    // constructor:
    Margay(float tailLength, std::string activePeriod, std::string furColor, int teeths, int id, std::string eyeColor, std::string species, std::string gender);

    // methods:
    void toString();
    friend class Breeder;
};

extern const char *activePeriod[3];

#endif