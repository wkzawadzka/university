#include "../include/breeder.h"
#include "../include/main.h"
#include "../include/zoo.h"
#include <algorithm> // std::min

// definitions
int Breeder::id = 151900;

void Breeder::addRandomAnimal(Zoo zoo) {
    int randInt = rand() % 7;
    switch (randInt) {
    case 0:
        this->breedMargay(zoo);
        break;
    case 1:
        this->breedOcelot(zoo);
        break;
    case 2:
        this->breedSnowLeopard(zoo);
        break;
    case 3:
        this->breedLeopard(zoo);
        break;
    case 4:
        this->breedJaguar(zoo);
        break;
    case 5:
        this->breedTiger(zoo);
        break;
    case 6:
        this->breedLion(zoo);
        break;
    };
};

void Breeder::breedMargay(Zoo zoo) {
    // generate random characteristics
    float tailLength = 30 + static_cast<float>(rand()) * static_cast<float>(60 - 30) / RAND_MAX;
    int teeths = 20 + rand() % ((35 + 1) - 20);

    // create an animal & add it to the zoo
    zoo += new Margay(tailLength, activePeriod[rand() % 3], furColor[rand() % 7], teeths, this->id, eyeColor[rand() % 6], "margay", gender[rand() % 2]);

    // increase id counter
    this->id++;
};

void Breeder::breedOcelot(Zoo zoo) {
    // generate random characteristics
    float bodyLength = 0.5 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2.5 - 0.5)));
    int teeths = 20 + rand() % ((35 + 1) - 20);

    // create an animal & add it to the zoo
    zoo += new Ocelot(bodyLength, furLength[rand() % 4], furColor[rand() % 7], teeths, this->id, eyeColor[rand() % 6], "ocelot", gender[rand() % 2]);

    // increase id counter
    this->id++;
};

void Breeder::breedSnowLeopard(Zoo zoo) {
    // generate random characteristics
    int teeths = 20 + rand() % ((35 + 1) - 20);

    // create an animal & add it to the zoo
    zoo += new SnowLeopard(tailType[rand() % 3], rand() % 2, skullType[rand() % 4], teeths, this->id, eyeColor[rand() % 6], "snow leopard", gender[rand() % 2]);

    // increase id counter
    this->id++;
};

void Breeder::breedLeopard(Zoo zoo) {
    // generate random characteristics
    int teeths = 20 + rand() % ((35 + 1) - 20);

    // create an animal & add it to the zoo
    zoo += new Leopard(bellyColor[rand() % 4], rand() % 2, skullType[rand() % 4], teeths, this->id, eyeColor[rand() % 6], "leopard", gender[rand() % 2]);

    // increase id counter
    this->id++;
};

void Breeder::breedJaguar(Zoo zoo) {
    // generate random characteristics
    int teeths = 20 + rand() % ((35 + 1) - 20);

    // create an animal & add it to the zoo
    zoo += new Jaguar(furPattern[rand() % 4], rand() % 2, skullType[rand() % 4], teeths, this->id, eyeColor[rand() % 6], "jaguar", gender[rand() % 2]);

    // increase id counter
    this->id++;
};

void Breeder::breedTiger(Zoo zoo) {
    // generate random characteristics
    int teeths = 20 + rand() % ((35 + 1) - 20);

    // create an animal & add it to the zoo
    zoo += new Tiger(rand() % 2, rand() % 2, skullType[rand() % 4], teeths, this->id, eyeColor[rand() % 6], "tiger", gender[rand() % 2]);

    // increase id counter
    this->id++;
};

void Breeder::breedLion(Zoo zoo) {
    // generate random characteristics
    int teeths = 20 + rand() % ((35 + 1) - 20);

    // create an animal & add it to the zoo
    zoo += new Lion(rand() % 2, rand() % 2, skullType[rand() % 4], teeths, this->id, eyeColor[rand() % 6], "lion", gender[rand() % 2]);

    // increase id counter
    this->id++;
};

void Breeder::crossoverMenu(Zoo zoo) {
    float crossoverProbability;
    float deathProbability;
    std::cin.exceptions(std::istream::failbit);

    std::cout << "Note: Animals in " << zoo.name << " will be randomly crossovered until the population reaches 100" << std::endl;

    do {
        try {
            std::cout << "Specify crossover probability: ";
            std::cin >> crossoverProbability;
            if (!((crossoverProbability > 0) && (crossoverProbability <= 1))) {
                throw std::out_of_range("Number not within admissible range. Please try again");
            };
            break;
        } catch (const std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        } catch (...) {
            std::cout << "Not a number. Please try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    } while (true);
    do {
        try {
            std::cout << "Specify death probability: ";
            std::cin >> deathProbability;
            if (!((deathProbability >= 0) && (deathProbability <= 1))) {
                throw std::out_of_range("Number not within admissible range 0-1. Please try again");
            };
            if (deathProbability >= crossoverProbability) {
                throw std::invalid_argument("Crossover probability should be higher than death probability. Please try again");
            };
            break;
        } catch (const std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        } catch (const std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
        } catch (...) {
            std::cout << "Not a number. Please try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
    } while (true);

    this->crossover(zoo, crossoverProbability, deathProbability);
}

void Breeder::crossover(Zoo zoo, float crossoverProbability, float deathProbability) {
    std::cout << "\n*    Breeding...        *" << std::endl;
    float p;
    Animal *randomAnimal, *parent1, *parent2;
    while (zoo.animals.size() < 100) {
        std::cout << "Zoo capacity:    [" << zoo.animals.size() << "/100]" << std::endl;
        p = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        if (deathProbability > p && zoo.animals.size() > 2) {
            randomAnimal = zoo.animals[rand() % zoo.animals.size()];
            std::cout << "\n*Animal no." << randomAnimal->id << " (" << randomAnimal->species << ") has been removed*" << std::endl;
            zoo -= randomAnimal; // remove random animal
        };

        if (crossoverProbability > p) { // crossover
            parent1 = zoo.animals[rand() % zoo.animals.size()];
            parent2 = zoo.animals[rand() % zoo.animals.size()];
            while (parent1->id == parent2->id) {
                parent2 = zoo.animals[rand() % zoo.animals.size()]; // make sure 2 unique animals
            }

            // make the child the species of a random parent
            if (Margay *p1 = dynamic_cast<Margay *>(parent1)) {
                std::cout << "\n----------------------------\nFirst parent:";
                p1->toString();
                this->breedCrossoverMargay(zoo, p1, parent2);
            } else if (Ocelot *p1 = dynamic_cast<Ocelot *>(parent1)) {
                std::cout << "\n----------------------------\nFirst parent:";
                p1->toString();
                this->breedCrossoverOcelot(zoo, p1, parent2);
            } else if (Lion *p1 = dynamic_cast<Lion *>(parent1)) {
                std::cout << "\n----------------------------\nFirst parent:";
                p1->toString();
                this->breedCrossoverLion(zoo, p1, parent2);
            } else if (Tiger *p1 = dynamic_cast<Tiger *>(parent1)) {
                std::cout << "\n----------------------------\nFirst parent:";
                p1->toString();
                this->breedCrossoverTiger(zoo, p1, parent2);
            } else if (SnowLeopard *p1 = dynamic_cast<SnowLeopard *>(parent1)) {
                std::cout << "\n----------------------------\nFirst parent:";
                p1->toString();
                this->breedCrossoverSnowLeopard(zoo, p1, parent2);
            } else if (Leopard *p1 = dynamic_cast<Leopard *>(parent1)) {
                std::cout << "\n----------------------------\nFirst parent:";
                p1->toString();
                this->breedCrossoverLeopard(zoo, p1, parent2);
            } else if (Jaguar *p1 = dynamic_cast<Jaguar *>(parent1)) {
                std::cout << "\n----------------------------\nFirst parent:";
                p1->toString();
                this->breedCrossoverJaguar(zoo, p1, parent2);
            };
        };
    }
}

void Breeder::breedCrossoverJaguar(Zoo zoo, Jaguar *p1, Animal *parent2) {
    if (Margay *p2 = dynamic_cast<Margay *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Jaguar(p1->furPattern, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "jaguar", gender[rand() % 2]);
    } else if (Ocelot *p2 = dynamic_cast<Ocelot *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Jaguar(p1->furPattern, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "jaguar", gender[rand() % 2]);
    } else if (Lion *p2 = dynamic_cast<Lion *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Jaguar(p1->furPattern, p1->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "jaguar", gender[rand() % 2]);
    } else if (Tiger *p2 = dynamic_cast<Tiger *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Jaguar(p1->furPattern, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p1->eyeColor, "jaguar", gender[rand() % 2]);
    } else if (SnowLeopard *p2 = dynamic_cast<SnowLeopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Jaguar(p1->furPattern, p1->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "jaguar", gender[rand() % 2]);
    } else if (Leopard *p2 = dynamic_cast<Leopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Jaguar(p1->furPattern, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "jaguar", gender[rand() % 2]);
    } else if (Jaguar *p2 = dynamic_cast<Jaguar *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Jaguar(p1->furPattern, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p1->eyeColor, "jaguar", gender[rand() % 2]);
    };
    this->id++;
}

void Breeder::breedCrossoverOcelot(Zoo zoo, Ocelot *p1, Animal *parent2) {
    float bodyLengthOffset = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (0.29)));
    if (Margay *p2 = dynamic_cast<Margay *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Ocelot(std::min((float)0.1, (float)abs(p1->bodyLength - bodyLengthOffset)), p1->furLength, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "ocelot", gender[rand() % 2]);
    } else if (Ocelot *p2 = dynamic_cast<Ocelot *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Ocelot(std::min((float)0.1, (float)abs(p1->bodyLength - bodyLengthOffset)), p1->furLength, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "ocelot", gender[rand() % 2]);
    } else if (Lion *p2 = dynamic_cast<Lion *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Ocelot(std::min((float)0.1, (float)abs(p1->bodyLength - bodyLengthOffset)), p1->furLength, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "ocelot", gender[rand() % 2]);
    } else if (Tiger *p2 = dynamic_cast<Tiger *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Ocelot(std::min((float)0.1, (float)abs(p1->bodyLength - bodyLengthOffset)), p1->furLength, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "ocelot", gender[rand() % 2]);
    } else if (SnowLeopard *p2 = dynamic_cast<SnowLeopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Ocelot(std::min((float)0.1, (float)abs(p1->bodyLength - bodyLengthOffset)), p1->furLength, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "ocelot", gender[rand() % 2]);
    } else if (Leopard *p2 = dynamic_cast<Leopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Ocelot(std::min((float)0.1, (float)abs(p1->bodyLength - bodyLengthOffset)), p1->furLength, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "ocelot", gender[rand() % 2]);
    } else if (Jaguar *p2 = dynamic_cast<Jaguar *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Ocelot(std::min((float)0.1, (float)abs(p1->bodyLength - bodyLengthOffset)), p1->furLength, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "ocelot", gender[rand() % 2]);
    };
    this->id++;
}

void Breeder::breedCrossoverSnowLeopard(Zoo zoo, SnowLeopard *p1, Animal *parent2) {
    if (Margay *p2 = dynamic_cast<Margay *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new SnowLeopard(p1->tailType, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "snow leopard", gender[rand() % 2]);
    } else if (Ocelot *p2 = dynamic_cast<Ocelot *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new SnowLeopard(p1->tailType, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "snow leopard", gender[rand() % 2]);
    } else if (Lion *p2 = dynamic_cast<Lion *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new SnowLeopard(p1->tailType, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p1->eyeColor, "snow leopard", gender[rand() % 2]);
    } else if (Tiger *p2 = dynamic_cast<Tiger *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new SnowLeopard(p1->tailType, p2->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "snow leopard", gender[rand() % 2]);
    } else if (SnowLeopard *p2 = dynamic_cast<SnowLeopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new SnowLeopard(p1->tailType, p2->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "snow leopard", gender[rand() % 2]);
    } else if (Leopard *p2 = dynamic_cast<Leopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new SnowLeopard(p1->tailType, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p1->eyeColor, "snow leopard", gender[rand() % 2]);
    } else if (Jaguar *p2 = dynamic_cast<Jaguar *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new SnowLeopard(p1->tailType, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "snow leopard", gender[rand() % 2]);
    };
    this->id++;
}

void Breeder::breedCrossoverLeopard(Zoo zoo, Leopard *p1, Animal *parent2) {
    if (Margay *p2 = dynamic_cast<Margay *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Leopard(p1->bellyColor, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "leopard", gender[rand() % 2]);
    } else if (Ocelot *p2 = dynamic_cast<Ocelot *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Leopard(p1->bellyColor, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "leopard", gender[rand() % 2]);
    } else if (Lion *p2 = dynamic_cast<Lion *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Leopard(p1->bellyColor, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "leopard", gender[rand() % 2]);
    } else if (Tiger *p2 = dynamic_cast<Tiger *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Leopard(p1->bellyColor, p1->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "leopard", gender[rand() % 2]);
    } else if (SnowLeopard *p2 = dynamic_cast<SnowLeopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Leopard(p1->bellyColor, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "leopard", gender[rand() % 2]);
    } else if (Leopard *p2 = dynamic_cast<Leopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Leopard(p1->bellyColor, p2->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p1->eyeColor, "leopard", gender[rand() % 2]);
    } else if (Jaguar *p2 = dynamic_cast<Jaguar *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Leopard(p1->bellyColor, p2->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "leopard", gender[rand() % 2]);
    };
    this->id++;
}

void Breeder::breedCrossoverLion(Zoo zoo, Lion *p1, Animal *parent2) {
    if (Margay *p2 = dynamic_cast<Margay *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Lion(p1->canSwim, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "lion", gender[rand() % 2]);
    } else if (Ocelot *p2 = dynamic_cast<Ocelot *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Lion(p1->canSwim, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "lion", gender[rand() % 2]);
    } else if (Lion *p2 = dynamic_cast<Lion *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Lion(p1->canSwim, p2->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "lion", gender[rand() % 2]);
    } else if (Tiger *p2 = dynamic_cast<Tiger *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Lion(p1->canSwim, p1->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p1->eyeColor, "lion", gender[rand() % 2]);
    } else if (SnowLeopard *p2 = dynamic_cast<SnowLeopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Lion(p1->canSwim, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "lion", gender[rand() % 2]);
    } else if (Leopard *p2 = dynamic_cast<Leopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Lion(p1->canSwim, p1->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "lion", gender[rand() % 2]);
    } else if (Jaguar *p2 = dynamic_cast<Jaguar *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Lion(p1->canSwim, p2->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p1->eyeColor, "lion", gender[rand() % 2]);
    };
    this->id++;
}

void Breeder::breedCrossoverTiger(Zoo zoo, Tiger *p1, Animal *parent2) {
    if (Margay *p2 = dynamic_cast<Margay *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Tiger(p1->isSocial, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "tiger", gender[rand() % 2]);
    } else if (Ocelot *p2 = dynamic_cast<Ocelot *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Tiger(p1->isSocial, p1->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "tiger", gender[rand() % 2]);
    } else if (Lion *p2 = dynamic_cast<Lion *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Tiger(p1->isSocial, p2->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "tiger", gender[rand() % 2]);
    } else if (Tiger *p2 = dynamic_cast<Tiger *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Tiger(p1->isSocial, p1->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "tiger", gender[rand() % 2]);
    } else if (SnowLeopard *p2 = dynamic_cast<SnowLeopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Tiger(p1->isSocial, p2->canRoar, p1->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p1->eyeColor, "tiger", gender[rand() % 2]);
    } else if (Leopard *p2 = dynamic_cast<Leopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Tiger(p1->isSocial, p2->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "tiger", gender[rand() % 2]);
    } else if (Jaguar *p2 = dynamic_cast<Jaguar *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Tiger(p1->isSocial, p1->canRoar, p2->skullType, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "tiger", gender[rand() % 2]);
    };
    this->id++;
}

void Breeder::breedCrossoverMargay(Zoo zoo, Margay *p1, Animal *parent2) {
    float tailOffset = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1));
    if (Margay *p2 = dynamic_cast<Margay *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Margay(std::min((float)10, (float)abs(p1->tailLength - tailOffset)), p1->activePeriod, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "margay", gender[rand() % 2]);
    } else if (Ocelot *p2 = dynamic_cast<Ocelot *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Margay(std::min((float)10, (float)abs(p1->tailLength - tailOffset)), p1->activePeriod, p2->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "margay", gender[rand() % 2]);
    } else if (Lion *p2 = dynamic_cast<Lion *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Margay(std::min((float)10, (float)abs(p1->tailLength - tailOffset)), p1->activePeriod, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "margay", gender[rand() % 2]);
    } else if (Tiger *p2 = dynamic_cast<Tiger *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Margay(std::min((float)10, (float)abs(p1->tailLength - tailOffset)), p1->activePeriod, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "margay", gender[rand() % 2]);
    } else if (SnowLeopard *p2 = dynamic_cast<SnowLeopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Margay(std::min((float)10, (float)abs(p1->tailLength - tailOffset)), p1->activePeriod, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "margay", gender[rand() % 2]);
    } else if (Leopard *p2 = dynamic_cast<Leopard *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Margay(std::min((float)10, (float)abs(p1->tailLength - tailOffset)), p1->activePeriod, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "margay", gender[rand() % 2]);
    } else if (Jaguar *p2 = dynamic_cast<Jaguar *>(parent2)) {
        std::cout << "\nSecond parent:";
        p2->toString();
        std::cout << "----------------------------";
        zoo += new Margay(std::min((float)10, (float)abs(p1->tailLength - tailOffset)), p1->activePeriod, p1->furColor, (int)((p1->teeths + p2->teeths) / 2), this->id, p2->eyeColor, "margay", gender[rand() % 2]);
    };
    this->id++;
}
