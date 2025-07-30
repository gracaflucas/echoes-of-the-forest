#include "AMonkey.hpp"

AMonkey::AMonkey() : health(1) {}

AMonkey::AMonkey(const AMonkey& copy) : health(copy.health) {}

AMonkey::~AMonkey() {}

AMonkey& AMonkey::operator=(const AMonkey& other) {
    if (this != &other) {
        this->health = other.health;
    }
    return *this;
}

void            AMonkey::tookDamage(unsigned int amount) {
    if (health > 0) {
        health -= amount;
    }
    if (health == 0)
        this->death();
}

unsigned int    AMonkey::getHealth() const {
    return this->health;
}

void            AMonkey::death() {
    // when touching fire, death by burn
    // when reached by poacher, death by cage
}
