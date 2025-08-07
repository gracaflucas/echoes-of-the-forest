#ifndef POACHER_HPP
# define POACHER_HPP

#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "AMonkey.hpp"

class Poacher {
    private:
        int         monkeyNearby;
        int         x;
        int         y;
        double      movSpeed;

    public:
        Poacher();
        Poacher(int startX, int startY);
        Poacher(const Poacher& copy);
        ~Poacher();

        Poacher& operator=(const Poacher& other);

        int     getX() const;
        int     getY() const;
        void    setX(int x);
        void    setY(int y);

        void    wanderRandomly(const std::vector<std::string>& map);
        void    searchIA(const std::vector<std::string>& map, const std::vector<AMonkey*>& monkeys);
        void    updateIA(int phase, const std::vector<std::string>& map, const std::vector<AMonkey*>& monkeys);
};

#endif