// dvirbto@gmail.com

#include "General.h"
using namespace std;

/**
 * This is the constructor of General role in the game.
 * @param name the name of the General.
 */
General::General(string name) : Player(name, "General") {}

/**
 * This is the destructor of the General.
 */
General::~General() {}

/**
 * This function prevents a given player to perform a coup on an active player.
 * In this case the General pays 5 coins and the player who couped losses his turn and his 7 coins.
 * @param player the player who chose to coup.
 */
void General::preventCoup(Player &player)
{
    // check if the General has at least 5 coins and alive
    validAction(5, "prevent a coup");

    // remove 5 coins to the General
    removeCoins(5);

    // remove to the player who couped 7 coins
    player.removeCoins(7);
}

/**
 * When a General is arrested he gets back the coin that was given to him.
 */
void General::onArrested()
{
    // if the general has at least one coin -> it will be taken from him
    // Note that if he has 0 coins -> no such coin will be taken from him
    if (getCoins() > 0)
        addCoins(1); // Therefore -> he gets 1 coin back

    // perform the arrest
    Player::onArrested();
}



