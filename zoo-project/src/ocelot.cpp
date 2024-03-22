#include "../include/ocelot.h"

Ocelot::Ocelot(float bodyLength, std::string furLength, std::string furColor, int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Leopardus(furColor, teeths, id, eyeColor, species, gender) {
    this->bodyLength = bodyLength;
    this->furLength = furLength;
};

const char *furLength[4] = {"short",
                            "long",
                            "very long",
                            "medium"};

void Ocelot::toString() {
    Leopardus::toString();
    std::cout << "  fur length: " << this->furLength << std::endl;
    std::cout << "  body length[m]: " << this->bodyLength << std::endl;
};