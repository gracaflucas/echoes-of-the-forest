#ifndef MONKEYNPC_HPP
# define MONKEYNPC_HPP

#include "AMonkey.hpp"

class MonkeyNPC : public AMonkey {
    private:
        std::string     dialogue;

    public:
        MonkeyNPC();
        MonkeyNPC(int x, int y);
        MonkeyNPC(const MonkeyNPC& copy);
        ~MonkeyNPC();

        MonkeyNPC& operator=(const MonkeyNPC& other);

        std::string     getDialogue() const;
        void            setDialogue(std::string phrase);
        void            wanderRandomly(const std::vector<std::string>& map);
        void            update(const std::vector<std::string>& map);
};

#endif