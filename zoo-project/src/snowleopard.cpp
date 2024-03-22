#include "../include/snowleopard.h"

SnowLeopard::SnowLeopard(std::string tailType, bool canRoar, std::string skullType, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Panthera(canRoar, skullType, teeths, id, eyeColor, species, gender) {
    this->tailType = tailType;
};

const char *tailType[3] = {"bushy",
                           "long",
                           "short"};

void SnowLeopard::toString() {
    Panthera::toString();
    std::cout << "  tail type: " << this->tailType << std::endl;
};