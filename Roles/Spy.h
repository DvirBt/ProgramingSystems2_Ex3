// dvirbto@gmail.com

#ifndef SPY_H
#define SPY_H
#include "Player.h"

/**
 * This class represents a Spy role in the game which inherits publicly from a Player.
 * A Spy has a special method which is Peek - he chooses a player and:
 * 1. The Spy can see how many coins the player has.
 * 2. Additionally, he prevents from him to use arrest method in his next turn.
 * Each function has a description in the cpp file in order to see the hpp file clearly.
 */
class Spy : public Player {
    public:
        Spy(std::string name);
        ~Spy();
        void peek(Player& player);
};

#endif //SPY_H
