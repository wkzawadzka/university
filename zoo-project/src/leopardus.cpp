#include "../include/leopardus.h"

Leopardus::Leopardus(std::string furColor, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Felidae(teeths, id, eyeColor, species, gender) {
    this->furColor = furColor;
};

void Leopardus::toString() {
    Felidae::toString();
    std::cout << "  fur color: " << this->furColor << std::endl;
};

const char *furColor[7] = {"reddish",
                           "white",
                           "brown",
                           "yellow",
                           "orange",
                           "ginger",
                           "black"};