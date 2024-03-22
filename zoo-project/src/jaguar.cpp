#include "../include/jaguar.h"

Jaguar::Jaguar(std::string furPattern, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Panthera(canRoar, skullType, teeths, id, eyeColor, species, gender) {
    this->furPattern = furPattern;
};

void Jaguar::toString() {
    Panthera::toString();
    std::cout << "  fur pattern: " << this->furPattern << std::endl;
};

const char *furPattern[4] = {"dotted",
                             "stripes",
                             "speckled",
                             "solid"};