#ifndef MONKEY_HPP
# define MONKEY_HPP

#include "AMonkey.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <vector>

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
        void            handleInput(sf::Keyboard::Key key, const std::vector<std::string>& map);
        void            update();
};

#endif