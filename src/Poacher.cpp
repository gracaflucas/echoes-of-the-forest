#include "../include/Poacher.hpp"

Poacher::Poacher() {}

Poacher::Poacher(int startX, int startY) : monkeyNearby(-1), x(startX), y(startY) {}

Poacher::Poacher(const Poacher& copy) : monkeyNearby(copy.monkeyNearby), x(copy.x), y(copy.y) {}

Poacher::~Poacher() {}

Poacher& Poacher::operator=(const Poacher& other) {
    if (this != &other) {
        this->monkeyNearby = other.monkeyNearby;
        this->x = other.x;
        this->y = other.y;
    }
    return *this;
}

int     Poacher::getX() const {
    return this->x;
}

int     Poacher::getY() const {
    return this->y;
}

void    Poacher::setX(int x) {
    this->x = x;
}

void    Poacher::setY(int y) {
    this->y = y;
}

void    Poacher::wanderRandomly(const std::vector<std::string>& map) {
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

void    Poacher::searchIA(const std::vector<std::string>& map, const std::vector<AMonkey*>& monkeys) {
    // walk to closest monkey, faster than NPC, slower than player
    // vision?
    monkeyNearby = -1;
    for (const AMonkey* monkey : monkeys) {
        int mx = monkey->getX();
        int my = monkey->getY();

        if (mx == x) {
            if (my < y) {
                bool clear = true;
                for (int i = y - 1; i > my; --i)
                    if (map[i][x] == '1') clear = false;
                if (clear) {
                    monkeyNearby = 0; return;
                }
            } else if (my > y) {
                bool clear = true;
                for (int i = y + 1; i < my; ++i)
                    if (map[i][x] == '1')
                        clear = false;
                if (clear) {
                    monkeyNearby = 1;
                    return;
                }
            }
        } else if (my == y) {
            if (mx < x) {
                bool clear = true;
                for (int i = x - 1; i > mx; --i)
                    if (map[y][i] == '1')
                        clear = false;
                if (clear) {
                    monkeyNearby = 2;
                    return;
                }
            } else if (mx > x) {
                bool clear = true;
                for (int i = x + 1; i < mx; ++i)
                    if (map[y][i] == '1')
                        clear = false;
                if (clear) {
                    monkeyNearby = 3;
                    return;
                }
            }
        }
    }
}

void Poacher::updateIA(int phase, const std::vector<std::string>& map, const std::vector<AMonkey*>& monkeys) {
    switch (phase) {
        case 0:
            // Phase 0: Poacher just wanders randomly.
            wanderRandomly(map);
            break;

        case 1:
            // Phase 1: Poacher wanders but with a chance to pause or change direction less frequently.
            if ((std::rand() % 4) != 0) { // 75% chance to move
                wanderRandomly(map);
            }
            break;

        case 2:
            // Phase 2: Poacher actively searches for monkeys and chases if found, otherwise wanders.
            monkeyNearby = -1;
            searchIA(map, monkeys);
            if (monkeyNearby == -1) {
                wanderRandomly(map);
            } else {
                // Move toward the monkey based on monkeyNearby direction code
                switch (monkeyNearby) {
                    case 0:
                        if (y > 0 && map[y - 1][x] != '1')
                            y--;
                        break;      // up
                    case 1:
                        if (y < static_cast<int>(map.size()) - 1 && map[y + 1][x] != '1')
                            y++;
                        break; // down
                    case 2:
                        if (x > 0 && map[y][x - 1] != '1')
                            x--;
                        break;      // left
                    case 3:
                        if (x < static_cast<int>(map[0].size()) - 1 && map[y][x + 1] != '1')
                            x++;
                        break; // right
                }
            }
            break;

        case 3:
            // Phase 3: Poacher gets more aggressive: moves twice or faster towards monkey.
            monkeyNearby = -1;
            searchIA(map, monkeys);
            if (monkeyNearby == -1) {
                wanderRandomly(map);
            } else {
                // Move two steps if possible towards the monkey
                for (int step = 0; step < 2; ++step) {
                    switch (monkeyNearby) {
                        case 0:
                            if (y > 0 && map[y - 1][x] != '1')
                                y--;
                            break;
                        case 1:
                            if (y < static_cast<int>(map.size()) - 1 && map[y + 1][x] != '1')
                                y++;
                            break;
                        case 2:
                            if (x > 0 && map[y][x - 1] != '1')
                                x--;
                            break;
                        case 3:
                            if (x < static_cast<int>(map[0].size()) - 1 && map[y][x + 1] != '1')
                                x++;
                            break;
                    }
                }
            }
            break;
        default:
            wanderRandomly(map);
            break;
    }
}