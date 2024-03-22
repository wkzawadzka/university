#include "../include/animal.h"

void Animal::toString() {
    std::cout << "\nanimal: " << this->species << std::endl;
    std::cout << "id: " << this->id << std::endl;
    std::cout << "  gender: " << this->gender << std::endl;
};

Animal::~Animal() = default;

const char *species[7] = {"margay",
                          "ocelot",
                          "snow leopard",
                          "leopard",
                          "jaguar",
                          "tiger",
                          "lion"};

const char *gender[2] = {"male",
                         "female"};