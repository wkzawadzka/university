#ifndef ZOO_H
#define ZOO_H

// forward declared dependencies
class Animal;

// included dependencies
#include "breeder.h"
#include <iostream>
#include <string>
#include <vector>

class Zoo {
    static std::vector<Animal *> animals;

public:
    std::string name;

    // methods:
    void toString();
    void showMenu(Breeder breeder, Zoo zoo);
    template <typename A>
    void operator+=(A *x);
    template <typename A>
    void operator-=(A *x);
    void cast(std::vector<Animal *> animals);
    friend class Breeder;
};

#endif