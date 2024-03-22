#include "../include/tiger.h"
#include <ios>

Tiger::Tiger(bool isSocial, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Panthera(canRoar, skullType, teeths, id, eyeColor, species, gender) {
    this->isSocial = isSocial;
};

void Tiger::toString() {
    Panthera::toString();
    std::cout << "  is social?: " << std::boolalpha << this->isSocial << std::noboolalpha << std::endl;
};