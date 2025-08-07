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

void            MonkeyNPC::update(const std::vector<std::string>& map) {
    (void)map;
    // wanders randomly at first, then later runs from poachers, but slower than them
    // talks with player when iteracted with / near them
    // dies when touched by Fire or Poacher, different deaths
}