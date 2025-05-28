// dvirbto@gmail.com

#include "Merchant.h"
using namespace std;

/**
 * This is the constructor of Merchant which uses an initialization list with the Player constructor.
 * @param name the name of the player.
 */
Merchant::Merchant(string name) : Player(name, "Merchant") {}

/**
 * This is the destructor of Merchant.
 */
Merchant::~Merchant() {}

/**
 * This function adds one coin to the Merchant if he has at least 3 coins.
 * @throw logic_error if the player is currently not in the game anymore.
 */
void Merchant::checkEntitled()
{
    // check if he is in the game
    if (!getInGame())
        throw logic_error("This player is not in the game!");

    // if he has at least 3 coins -> entitles to get 1 coin
    if (getCoins() >= 3)
        addCoins(1); // add the coin
}

/**
 * When a Merchant is being arrested he pays 2 coins to the cash box instead of 1 to the player.
 * who arrested him.
 * This function removes 2 coins from the Merchant if he has enough coins.
 * If he does not have enough coins it sets his coins to 0.
 */
void Merchant::onArrested()
{
    // remove coins
    if (getCoins() >= 2) // if he has at least 2 coins -> remove 2 coins
        removeCoins(2);

    else // if he has below 2 coins -> set the coins to 0
        setCoins(0);

    // set the player to be arrested
    setArrested();
}