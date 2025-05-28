// dvirbto@gmail.com

#include "Baron.h"
using namespace std;

/**
 * This is the constructor of a Baron player in the game which uses an initialization list.
 * @param name the name of the player.
 */
Baron::Baron(string name) : Player(name, "Baron"), invested(false){}

/**
 * This is the destructor of a Baron player in the game.
 */
Baron::~Baron() {}

/**
 * This function represents an investment made by a Baron.
 * The player pays 3 coins and has 50% chance to win 6 coins and 50% chance to get nothing.
 */
void Baron::invest()
{
    // check if the baron has enough coins and if he is still in the game
    validAction(3, "invest");

    // pay for the investment
    removeCoins(3);

    // random a number between 0 and 1 -> 50% chance for 0 or 1
    int invest = rand() % 2; // invest = 0 loses the investment, invest = 1 won the investment

    // the investment succeeded
    if (invest == 1)
    {
        addCoins(6); // add 6 coins
        invested = true; // won
    }

    else // the investment failed
        invested = false; // lost
}

/**
 * This function returns the last result of the gamble made by the Baron.
 * @return true if the last gamble was successful. Otherwise, returns false.
 */
const bool Baron::isInvested() const
{
    return invested;
}

/**
 * This function performs sanction on Baron role.
 * When a Baron is being sanctioned he gets one coin back.
 */
void Baron::onSanctioned()
{
    Player::onSanctioned(); // he is being sanctioned the same way as all the other players
    addCoins(1); // when Baron is sanctioned - he gets 1 coin back
}


