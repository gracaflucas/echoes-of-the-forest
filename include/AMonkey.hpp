#ifndef AMONKEY_HPP
# define AMONKEY_HPP

#include <iostream>
#include <string>
#include <vector>

class AMonkey {
    protected:
        unsigned int    health;
        int    x;
        int    y;
        double          movSpeed;

    public:
        AMonkey();
        AMonkey(int x, int y);
        AMonkey(const AMonkey& copy);
        virtual ~AMonkey();
        AMonkey& operator=(const AMonkey& other);

        void            tookDamage(unsigned int amount);
        unsigned int    getHealth() const;
        void            death();
        virtual void    update(const std::vector<std::string>& map) = 0;

        void            setX(int x);
        void            setY(int y);
        int             getX() const;
        int             getY() const;
};

#endif
