#include "../include/zoo.h"
#include "../include/animal.h"
#include <vector>

// definitions
std::vector<Animal *> Zoo::animals;

void Zoo::cast(std::vector<Animal *> animals) {
    for (auto it = std::begin(animals); it != std::end(animals); ++it) {
        Animal *p = (*it);
        if (Margay *t1 = dynamic_cast<Margay *>(p)) {
            t1->toString();
        } else if (Ocelot *t2 = dynamic_cast<Ocelot *>(p)) {
            t2->toString();
        } else if (Lion *t3 = dynamic_cast<Lion *>(p)) {
            t3->toString();
        } else if (Tiger *t4 = dynamic_cast<Tiger *>(p)) {
            t4->toString();
        } else if (SnowLeopard *t5 = dynamic_cast<SnowLeopard *>(p)) {
            t5->toString();
        } else if (Leopard *t6 = dynamic_cast<Leopard *>(p)) {
            t6->toString();
        } else if (Jaguar *t7 = dynamic_cast<Jaguar *>(p)) {
            t7->toString();
        };
    }
}

void Zoo::toString() {
    int i;
    std::cout << "Information about the animals:" << std::endl;
    this->cast(this->animals);
    std::cout << "\nCapacity: [" << this->animals.size() << "/100]" << std::endl;
};

void Zoo::showMenu(Breeder breeder, Zoo zoo) {
    int choice;
    std::cin.exceptions(std::istream::failbit);

    std::cout << "\n****************************" << std::endl;
    std::cout << "*  What do you want to do? *" << std::endl;
    std::cout << "*    1) Display information *" << std::endl;
    std::cout << "*    2) Breed randomly     *" << std::endl;
    std::cout << "*    0) Exit               *" << std::endl;
    std::cout << "****************************" << std::endl;

    do {
        try {
            std::cout << "Menu$ ";
            std::cin >> choice;
            if (!((choice >= 0) && (choice <= 2))) {
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

    switch (choice) {
    case 1:
        std::cout << "*    Stats of " << this->name << ":  *" << std::endl;
        this->toString();
        break;
    case 2:
        breeder.crossoverMenu(zoo);
        break;
    case 0:
        std::cout << "Exiting..." << std::endl;
        exit(0);
        break;
    default:
        std::cout << "Invalid choice" << std::endl;
    }
    this->showMenu(breeder, zoo); // display again the menu until not exited
};

template <typename A>
void Zoo::operator+=(A *x) {
    std::cout << "\nadding..." << std::endl;
    x->toString();
    this->animals.push_back(x);
};

template void Zoo::operator+=<Margay>(Margay *);
template void Zoo::operator+=<Ocelot>(Ocelot *);
template void Zoo::operator+=<Lion>(Lion *);
template void Zoo::operator+=<SnowLeopard>(SnowLeopard *);
template void Zoo::operator+=<Leopard>(Leopard *);
template void Zoo::operator+=<Tiger>(Tiger *);
template void Zoo::operator+=<Jaguar>(Jaguar *);

template <typename A>
void Zoo::operator-=(A *x) {
    int i = 0;
    for (auto it = std::begin(this->animals); it != std::end(this->animals); ++it) {
        Animal *p = (*it);
        if (p == x) {
            this->animals.erase(this->animals.begin() + i);
            break;
        }
        i++;
    };
};

template void Zoo::operator-=<Animal>(Animal *);