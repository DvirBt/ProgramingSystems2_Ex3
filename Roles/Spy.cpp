// dvirbto@gmail.com

#include "Spy.h"
using namespace std;

/**
 * This is the constructor of the Spy role in the game which is using initialization list with a given name.
 * @param name the name of the new Spy.
 */
Spy::Spy(string name) : Player(name, "Spy") {}

/**
 * This is the destructor of the Spy.
 */
Spy::~Spy() {}

/**
 * A Spy can select a player and peek him which reveals how many coins the selected player has
 * and prevents from him to use arrest method in his next turn.
 * @param player the player that will be peeked on.
 * @throw logic_error if the player is currently not in the game anymore.
 */
void Spy::peek(Player& player)
{
    if (!getInGame())
        throw logic_error("Player is currently not in the game!");

    cout << "Player " << player.getPlayerID() << ": " << player.getName()
    << " has " << player.getCoins() << " coins." << endl;
    player.setCanArrest(false);
}