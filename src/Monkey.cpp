#include "../include/Monkey.hpp"
#include <SFML/Window/Keyboard.hpp>

Monkey::Monkey() : AMonkey(), name("") {
    this->health = 3;
}

Monkey::Monkey(std::string name) : AMonkey(), name(name) {
    this->health = 3;
}

Monkey::Monkey(const Monkey& copy) : AMonkey(copy), name(copy.name) {}

Monkey::~Monkey() {}

Monkey& Monkey::operator=(const Monkey& other) {
    if (this != &other) {
        AMonkey::operator=(other);
        this->name = other.name;
    }
    return *this;
}

std::string Monkey::getName() const {
    return this->name;
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

void Monkey::update(const std::vector<std::string>& map) {
    (void)map;
    // Here you can add logic for animations, health regen, interactions etc.
    // walks with input, interact with npcs
    // gets banannas
    // reaches exit
    // dies when reaching 0 Health
}