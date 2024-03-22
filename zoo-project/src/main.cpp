#include "../include/main.h"

void initializePopulation(Breeder breeder, Zoo zoo) {
    int size, tempsize;
    std::cin.exceptions(std::istream::failbit);

    do {
        try {
            std::cout << "Specify initial population size (under 100): ";
            std::cin >> size;
            if (!((size >= 2) && (size <= 100))) {
                throw std::out_of_range("Number not within admissible range. Please try again");
            };
            break;
        } catch (const std::out_of_range &e) {
            std::cout << e.what() << std::endl;
        } catch (...) {
            std::cout << "Not a number. Please try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    } while (true);

    for (int i = 0; i < size; i++) {
        breeder.addRandomAnimal(zoo);
    };
};

int main() {
    Zoo catZoo;
    Breeder breeder;
    catZoo.name = "Cat Zoo";
    std::cout << "*  Welcome to " << catZoo.name << "!    *" << std::endl;
    std::cout << "*  Current capacity: [0/100]                 *" << std::endl;
    initializePopulation(breeder, catZoo);
    catZoo.showMenu(breeder, catZoo);
    return (0);
};