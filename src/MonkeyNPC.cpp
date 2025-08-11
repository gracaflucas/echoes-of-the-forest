#include "../include/MonkeyNPC.hpp"

MonkeyNPC::MonkeyNPC() : AMonkey(), dialogue("...") {}

MonkeyNPC::MonkeyNPC(int x, int y) : AMonkey(x, y), dialogue("...") {}

MonkeyNPC::MonkeyNPC(const MonkeyNPC& copy) : AMonkey(copy), dialogue(copy.dialogue) {}

MonkeyNPC::~MonkeyNPC() {}

MonkeyNPC& MonkeyNPC::operator=(const MonkeyNPC& other) {
    if (this != &other) {
        AMonkey::operator=(other);
        this->dialogue = other.dialogue;
    }
    return *this;
}

std::string     MonkeyNPC::getDialogue() const {
    return this->dialogue;
}

void            MonkeyNPC::setDialogue(std::string phrase) {
    this->dialogue = phrase;
}

void    MonkeyNPC::wanderRandomly(const std::vector<std::string>& map) {
    int dir = std::rand() % 4;

    switch (dir) {
        case 0: // Up
            if (y > 0 && map[y - 1][x] != '1')
                y--;
            break;
        case 1: // Down
            if (y < static_cast<int>(map.size()) - 1 && map[y + 1][x] != '1')
                y++;
            break;
        case 2: // Left
            if (x > 0 && map[y][x - 1] != '1')
                x--;
            break;
        case 3: // Right
            if (x < static_cast<int>(map[0].size()) - 1 && map[y][x + 1] != '1')
                x++;
            break;
    }
}

void            MonkeyNPC::update(const std::vector<std::string>& map) {
    (void)map;
    // wanders randomly at first, then later runs from poachers, but slower than them
    // talks with player when iteracted with / near them
    // dies when touched by Fire or Poacher, different deaths
}