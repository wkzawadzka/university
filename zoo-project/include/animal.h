#ifndef ANIMAL_H
#define ANIMAL_H

// included dependencies
#include <iostream>
#include <string>

class Animal {
    int id;
    std::string species;
    std::string gender;

public:
    // constructor:
    Animal(int id, std::string species, std::string gender) {
        this->id = id;
        this->species = species;
        this->gender = gender;
    };
    virtual ~Animal();

    // methods:
    void toString();
    friend class Breeder;
};

extern const char *species[7];
extern const char *gender[2];

#endif