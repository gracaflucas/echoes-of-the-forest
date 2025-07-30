#ifndef POACHER_HPP
# define POACHER_HPP

class Poacher {
    private:
        int             monkeyNearBy;
        unsigned int    x;
        unsigned int    y; // still have to implement x and y
        double          movSpeed;

    public:
        Poacher();
        Poacher(const Poacher& copy);
        ~Poacher();

        Poacher& operator=(const Poacher& other);

        void    wander();
        void    searchIA();
        void    updateSearchIA(int phase);
};

#endif