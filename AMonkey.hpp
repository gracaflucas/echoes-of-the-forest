#ifndef AMONKEY_HPP
# define AMONKEY_HPP

#include <iostream>
#include <string>

class AMonkey {
    protected:
        unsigned int    health;
        unsigned int    x; // still need to add x and y
        unsigned int    y;
        double          movSpeed;

    public:
        AMonkey();
        AMonkey(const AMonkey& copy);
        virtual ~AMonkey();
        AMonkey& operator=(const AMonkey& other);

        void            tookDamage(unsigned int amount);
        unsigned int    getHealth() const;
        void            death();
        virtual void    update() = 0;
};

#endif
