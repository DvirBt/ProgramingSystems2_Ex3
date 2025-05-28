// dvirbto@gmail.com

#include "Judge.h"
using namespace std;


/**
 * This is the constructor of Judge which uses an initialization list with a given name.
 * @param name the name of the new Judge.
 */
Judge::Judge(string name) : Player(name, "Judge") {}

/**
 * This is the destructor of the Judge.
 */
Judge::~Judge() {}

/**
 * A judge is allowed to block bribes of other players.
 * Note that this function is defined virtually in Player class and returns false.
 * @return true.
 * @throw logic_error if the player is currently not in the game.
 */
bool Judge::canBlockBribe() const
{
    // if not in the game
    if (!getInGame())
        throw logic_error("Player is not in the game!");

    return true;
}





