#include "../include/lion.h"
#include <ios>

Lion::Lion(bool canSwim, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Panthera(canRoar, skullType, teeths, id, eyeColor, species, gender) {
    this->canSwim = canSwim;
};

void Lion::toString() {
    Panthera::toString();
    std::cout << "  can swim?: " << std::boolalpha << this->canSwim << std::noboolalpha << std::endl;
};