#include "../include/leopard.h"

Leopard::Leopard(std::string bellyColor, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Panthera(canRoar, skullType, teeths, id, eyeColor, species, gender) {
    this->bellyColor = bellyColor;
};

void Leopard::toString() {
    Panthera::toString();
    std::cout << "  belly color: " << this->bellyColor << std::endl;
};

const char *bellyColor[4] = {
    "white",
    "black",
    "brown",
    "yellowish",
};