// dvirbto@gmail.com

#include "Governor.h"
using namespace std;

/**
 * This is the constructor of Governor which is using initialization list with a given name.
 * @param name the name of the new Governor.
 */
Governor::Governor(string name) : Player(name, "Governor") {}

/**
 * This is the destructor of the Governor.
 */
Governor::~Governor() {}

/**
 * When a Governor performs Tax action he gets 3 coins instead of 3.
 * Note that this function is defined virtually in the Player class.
 * @throw runtime_error if the player can't use financial actions.
 */
void Governor::tax()
{
    // check if the player is still in the game and has enough coins
    validAction(0, "tax"); // the cost of Tax is 0

    if (!getBlockStatus().canFinance)
        throw runtime_error("Player got sanctioned and can not perform Tax!");

    // add 3 coins
    addCoins(3);
}

/**
 * A Governor is allowed to block Taxes of other players.
 * This method is also defined virtually in Player class and returns false.
 * @return true.
 * @throw logic_error if the player is currently not in the game.
 */
bool Governor::canBlockTax() const
{
    // if not in the game
    if (!getInGame())
        throw logic_error("Player is not in the game!");

    return true;
}