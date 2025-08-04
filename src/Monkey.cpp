#include "../include/Monkey.hpp"
#include <SFML/Window/Keyboard.hpp>

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

void Monkey::handleInput(sf::Keyboard::Key key, const std::vector<std::string>& map) {
    int newX = static_cast<int>(x);
    int newY = static_cast<int>(y);

    if (key == sf::Keyboard::W)
        newY--;
    else if (key == sf::Keyboard::S)
        newY++;
    else if (key == sf::Keyboard::A)
        newX--;
    else if (key == sf::Keyboard::D)
        newX++;

    // Check boundaries and walls
    if (newY >= 0 && newY < static_cast<int>(map.size()) &&
        newX >= 0 && newX < static_cast<int>(map[0].size()) &&
        map[newY][newX] != '1') {
        x = newX;
        y = newY;
    }
}

void Monkey::update() {
    // Here you can add logic for animations, health regen, interactions etc.
    // walks with input, interact with npcs
    // gets banannas
    // reaches exit
    // dies when reaching 0 Health
}