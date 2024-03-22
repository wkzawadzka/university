#include "../include/panthera.h"
#include <ios>

Panthera::Panthera(bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Felidae(teeths, id, eyeColor, species, gender) {
    this->canRoar = canRoar;
    this->skullType = skullType;
};

const char *skullType[4] = {"flattish",
                            "roundish",
                            "anormal",
                            "normal"};

void Panthera::toString() {
    Felidae::toString();
    std::cout << "  skull type: " << this->skullType << std::endl;
    std::cout << "  car roar?: " << std::boolalpha << this->canRoar << std::noboolalpha << std::endl;
};