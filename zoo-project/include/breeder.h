#ifndef BREEDER_H
#define BREEDER_H

// forward declared dependencies
class Zoo;
class Animal;

// included dependencies
#include "jaguar.h"
#include "leopard.h"
#include "lion.h"
#include "margay.h"
#include "ocelot.h"
#include "snowleopard.h"
#include "tiger.h"
#include <iostream>

class Breeder {
    static int id;

public:
    // adding randomly initieted animals
    void breedMargay(Zoo zoo);
    void breedOcelot(Zoo zoo);
    void breedSnowLeopard(Zoo zoo);
    void breedLeopard(Zoo zoo);
    void breedJaguar(Zoo zoo);
    void breedTiger(Zoo zoo);
    void breedLion(Zoo zoo);
    void addRandomAnimal(Zoo zoo);

    // crossover functions
    void crossoverMenu(Zoo zoo);
    void crossover(Zoo zoo, float crossoverProbability, float deathProbability);

    // crossover breeding
    // p1 -> parent1, p2 -> parent2
    void breedCrossoverMargay(Zoo zoo, Margay *p1, Animal *p2);
    void breedCrossoverOcelot(Zoo zoo, Ocelot *p1, Animal *p2);
    void breedCrossoverSnowLeopard(Zoo zoo, SnowLeopard *p1, Animal *p2);
    void breedCrossoverJaguar(Zoo zoo, Jaguar *p1, Animal *p2);
    void breedCrossoverTiger(Zoo zoo, Tiger *p1, Animal *p2);
    void breedCrossoverLion(Zoo zoo, Lion *p1, Animal *p2);
    void breedCrossoverLeopard(Zoo zoo, Leopard *p1, Animal *p2);
};

#endif