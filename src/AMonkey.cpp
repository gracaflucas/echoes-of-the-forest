#include "../include/AMonkey.hpp"

AMonkey::AMonkey() : health(1) {}

AMonkey::AMonkey(int x, int y) : health(1), x(x), y(y) {}

AMonkey::AMonkey(const AMonkey& copy) : health(copy.health), x(copy.x), y(copy.y) {}

AMonkey::~AMonkey() {}

AMonkey& AMonkey::operator=(const AMonkey& other) {
    if (this != &other) {
        this->health = other.health;
        this->x = other.x;
        this->y = other.y;
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

void    AMonkey::setX(int x) {
    this->x = x;
}

void    AMonkey::setY(int y) {
    this->y = y;
}

int     AMonkey::getX() const {
    return this->x;
}

int     AMonkey::getY() const {
    return this->y;
}