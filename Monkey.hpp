#ifndef MONKEY_HPP
# define MONKEY_HPP

#include "AMonkey.hpp"

class Monkey : public AMonkey {
    private:
        unsigned int    bag;

    public:
        Monkey();
        Monkey(const Monkey& copy);
        ~Monkey();

        Monkey& operator=(const Monkey& other);

        unsigned int    getBag() const;
        void            setBag(unsigned int amount);
        void            update();
};

#endif