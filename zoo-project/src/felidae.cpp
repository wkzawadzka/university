#include "../include/felidae.h"

Felidae::Felidae(int teeths, int id, std::string eyeColor, std::string species, std::string gender) : Animal(id, species, gender) {
    this->teeths = teeths;
    this->eyeColor = eyeColor;
};

void Felidae::toString() {
    Animal::toString();
    std::cout << "  teeths: " << this->teeths << std::endl;
    std::cout << "  eye color: " << this->eyeColor << std::endl;
}

const char *eyeColor[6] = {"black",
                           "green",
                           "yellow",
                           "orange",
                           "brown",
                           "blue"};