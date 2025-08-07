#ifndef MONKEY_HPP
# define MONKEY_HPP

#include "AMonkey.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <vector>

class Monkey : public AMonkey {
    private:
        std::string name;

    public:
        Monkey();
        Monkey(std::string name);
        Monkey(const Monkey& copy);
        ~Monkey();

        Monkey& operator=(const Monkey& other);

        std::string getName() const;
        void            handleInput(sf::Keyboard::Key key, const std::vector<std::string>& map);
        void            update(const std::vector<std::string>& map);
};

#endif