#include "Monkey.hpp"

Monkey::Monkey() : AMonkey(), bag(0) {}

Monkey::Monkey(const Monkey& copy) : AMonkey(copy), bag(copy.bag) {}

Monkey::~Monkey() {}

Monkey& Monkey::operator=(const Monkey& other) {
    if (this != &other) {
        AMonkey::operator=(other);
        this->bag = other.bag;
    }
    return *this;
}

unsigned int    Monkey::getBag() const {
    return this->bag;
}

void            Monkey::setBag(unsigned int amount) {
    this->bag += amount;
}

void            Monkey::update() {
    // walks with input, interact with npcs
    // gets banannas
    // reaches exit
    // dies when reaching 0 Health
}