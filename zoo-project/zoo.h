#ifndef ZOO_H
#define ZOO_H
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

class Animal {
    int id;

public:
    Animal(int id){}; // constructor
    void toPrint();
    virtual void info(); // just for dev
};

class Felidae : public Animal {
    int teeths;

public:
    using Animal::Animal;
    void info(); // just for dev
    // Felidae(int id);
};

class Leopardus : public Felidae {
public:
    using Felidae::Felidae;
    void info();
    // Leopardus(int id);
};

class Panthera : public Felidae {
public:
    using Felidae::Felidae;
    void info();
    // Panthera(int id);
};

class Margay : public Leopardus {
public:
    using Leopardus::Leopardus;
    // Margay(int id);
    // void info() {
    //     cout << "margay" << endl;
    // }
};

class Ocelot : public Leopardus {
public:
    using Leopardus::Leopardus;
    // Ocelot(int id);
    // void info() {
    //     cout << "ocelot" << endl;
    //     ;
    // }
};

class SnowLeopard : public Panthera {
public:
    using Panthera::Panthera;
    // SnowLeopard(int id);
    // void info() {
    //     cout << "snowleopard" << endl;
    // }
};

class Leopard : public Panthera {
public:
    using Panthera::Panthera;
    // Leopard(int id);
};

class Jaguar : public Panthera {
public:
    using Panthera::Panthera;
    // Jaguar(int id);
};

class Lion : public Panthera {
public:
    using Panthera::Panthera;
    // Lion(int id);
};

class Tiger : public Panthera {
public:
    using Panthera::Panthera;
    // Tiger(int id);
};

class Zoo { // (SINGLETON) OR THIS SHOULD BE A TEMPLATE, GENERIC CLASS! wft thy caps lock
    static vector<Animal> animals;

public:
    const char *species[7] = {"margay", "ocelot", "snow leopard", "leopard", "jaguar", "tiger", "lion"};
    string name;
    void toPrint();
    void showMenu(); // shows user menu (display statistics / breed randomly / exit)
    void operator+=(Animal x) {
        this->animals.push_back(x);
    }
    void operator-=(Animal x) {
        // vector<int>::iterator position = find(animals.begin(), animals.end(), x);
        // if (position != animals.end()) // == animals.end() means the element was not found
        //     animals.erase(position);
    }
};
vector<Animal> Zoo::animals;

class Breeder {
    static int id;

public:
    void breedMargay(Zoo zoo) {
        id = this->id;
        cout << " [" << id << "]" << endl;
        zoo += Margay(id);
        this->id++;
    }
    void breedOcelot(Zoo zoo) {
        id = this->id;
        cout << " [" << id << "]" << endl;
        zoo += Ocelot(id);
        this->id++;
    }
    void breedSnowLeopard(Zoo zoo) {
        id = this->id;
        cout << " [" << id << "]" << endl;
        zoo += SnowLeopard(id);
        this->id++;
    }
    void breedLeopard(Zoo zoo) {
        id = this->id;
        cout << " [" << id << "]" << endl;
        zoo += Leopard(id);
        this->id++;
    }
    void breedJaguar(Zoo zoo) {
        id = this->id;
        cout << " [" << id << "]" << endl;
        zoo += Jaguar(id);
        this->id++;
    }
    void breedTiger(Zoo zoo) {
        id = this->id;
        cout << " [" << id << "]" << endl;
        zoo += Tiger(id);
        this->id++;
    }
    void breedLion(Zoo zoo) {
        id = this->id;
        cout << " [" << id << "]" << endl;
        zoo += Lion(id);
        this->id++;
    }
    void addRandomAnimal(Zoo zoo);
};
int Breeder::id = 151900;

void initializePopulation(int size);

// namespace MyAppGlobalConstants
// {
//     //declare constants here
// }

#endif