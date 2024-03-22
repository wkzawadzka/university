#include "zoo.h"

void Zoo::showMenu() {
    int choice;
    cout << "\n****************************" << endl;
    cout << "*  What do you want to do? *" << endl;
    cout << "*    1) Display statistics *" << endl;
    cout << "*    2) Breed randomly     *" << endl;
    cout << "*    0) Exit               *" << endl;
    cout << "****************************" << endl;
    cout << "Menu$ ";
    cin >> choice;
    switch (choice) {
    case 1:
        cout << "*    Stats of " << this->name << ":  *" << endl;
        this->toPrint();
        break;
    case 2:
        cout << "*    Breeding...        *" << endl;
        break;
    case 0:
        cout << "Exiting..." << endl;
        exit(0);
        break;
    default:
        cout << "Invalid choice" << endl;
    }
    this->showMenu(); // display again the menu unitl not exited
}

void Zoo::toPrint() {
    cout << "Number of animals: " << this->animals.size() << endl;
    for (Animal a : this->animals) {
        a.info();
    }
}

void Animal::toPrint() {
    cout << "id: " << id << endl;
}

void Animal::info() { // just for dev
    cout << "animal->";
}

void Felidae::info() { // just for dev

    cout << "felidae->";
}

void Leopardus::info() { // just for dev

    cout << "leopardus->";
}

void Panthera::info() { // just for dev
    cout << "panthera->";
}

void Breeder::addRandomAnimal(Zoo zoo) {
    int choice = rand() % (6 + 1);
    cout << "new animal: " << zoo.species[choice];
    switch (choice) {
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
    }
}

void initializePopulation(Breeder breeder, Zoo zoo) {
    int size;
    cout << "Specify initial population size: "; // protect against user input! <100
    cin >> size;

    for (int i = 0; i < size; i++) {
        breeder.addRandomAnimal(zoo);
    }
}

int main() {
    Zoo catZoo;
    Breeder breeder;
    catZoo.name = "Cat Zoo";
    cout << "*  Welcome to " << catZoo.name << "!    *" << endl;
    cout << "*  Maximum capacity: 100                 *" << endl;
    initializePopulation(breeder, catZoo);
    catZoo.showMenu();
    return (0);
}
