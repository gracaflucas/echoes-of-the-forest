#include "../include/Poacher.hpp"

Poacher::Poacher() : monkeyNearBy(0) {}

Poacher::Poacher(const Poacher& copy) : monkeyNearBy(copy.monkeyNearBy) {}

Poacher::~Poacher() {}

Poacher& Poacher::operator=(const Poacher& other) {
    if (this != &other) {
        this->monkeyNearBy = other.monkeyNearBy;
    }
    return *this;
}

void    Poacher::wander() {
    // no monkey nearby, just wander randomly
}

void    Poacher::searchIA() {
    // walk to closest monkey, faster than NPC, slower than player
    // vision?
}

void    Poacher::updateSearchIA(int phase) {
    (void)phase;
    // changes through phases
}