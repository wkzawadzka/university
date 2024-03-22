#include "../include/margay.h"

Margay::Margay(float tailLength, std::string activePeriod, std::string furColor, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Leopardus(furColor, teeths, id, eyeColor, species, gender) {
    this->tailLength = tailLength;
    this->activePeriod = activePeriod;
};

const char *activePeriod[3] = {"night", "morning", "afternoon"};

void Margay::toString() {
    Leopardus::toString();
    std::cout << "  active period: " << this->activePeriod << std::endl;
    std::cout << "  tail length[cm]: " << this->tailLength << std::endl;
};