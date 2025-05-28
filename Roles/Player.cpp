// dvirbto@gmail.com

#include <iostream>
#include "Player.h"
#include <stdexcept>
#include "Baron.h"
using namespace std;

static int ID = 1; // each player will get a unique ID when a new player is being created

// Getters and Setters

/**
 * Gets the ID of this player in the game.
 * @return the player serial number.
 */
int Player::getPlayerID() const
{
    return playerID;
}

/**
 * Gets the player's name.
 * @return the name of the player.
 */
string Player::getName() const
{
    return name;
}

/**
 * Gets the player's role in the game.
 * @return the role name of the player.
 */
string Player::getRole() const
{
    return role;
}

/**
 * Gets the current amount of player's coins.
 * @return the amount of coins the player has.
 */
int Player::getCoins() const
{
    return coins;
}

/**
 * Gets the current in game status of a player.
 * @return true if the player is in the game. Otherwise, returns false.
 */
bool Player::getInGame() const
{
    return inGame;
}

/**
 * Sets the player activeness in the game according to a given status.
 * @param status the new status of the player in the game.
 */
void Player::setInGame(bool status)
{
    inGame = status;
}

/**
 * Sets the amount of coins of a player according to a given number.
 * @param newCoins the new number of coins the player will have.
 */
void Player::setCoins(int newCoins)
{
    coins = newCoins;
}

/**
 * Gets the current status of the player's ability to arrest others.
 * @return true if the player can arrest other players. Otherwise, returns false.
 */
bool Player::getCanArrest() const
{
    return blockStatus.canArrest;
}

/**
 * Sets the status of the player's ability to arrest other players in the game in his turn.
 * @param status the new status of the player's ability to arrest others.
 */
void Player::setCanArrest(bool status)
{
    blockStatus.canArrest = status;
}

/**
 * Gets (can modify) the restrictions this player currently has in his turn.
 * @return the players restrictions in this current turn.
 */
blockSettings& Player::getBlockStatus()
{
    return blockStatus;
}

/**
 * Gets (read-only) the restrictions this player currently has in his turn.
 * @return the players restrictions in this current turn.
 */
const blockSettings& Player::getBlockStatus() const
{
    return blockStatus;
}

/**
 * Sets the BlockStatus of a player to the initial state which means the player can use financial methods,
 * can arrest and did not arrest anyone in the last round.
 */
void Player::setSettings()
{
    blockStatus = blockSettings();
}

/**
 * Sets the player to be arrested
 */
const void Player::setArrested()
{
    blockStatus.arrested = true;
}
//

/**
 * This is the constructor of Player which uses an initialization list tp create the new player.
 * @param name the name of the new player.
 * @param role the role of the new player.
 */
Player::Player(string name, string role) : playerID(ID++), name(name), role(role), coins(0), inGame(true), blockStatus(blockSettings()) {}

/**
 * This is the destructor of Player which is defined as virtual because each role inherits from Player class.
 */
Player::~Player() {}

// methods
/**
 * This function performs Gather method which adds 1 coin to the player.
 * @throw runtime_error if the player can't use financial actions.
 */
void Player::gather()
{
    // check if the player is in the game and has enough coins
    validAction(0, "gather"); // the cost of Gather is 0

    // check if the player is allowed to use Gather or Tax
    if (!blockStatus.canFinance)
        throw runtime_error("Player got sanctioned and can not perform Gather!");

    // add one coin to the player
    coins++;
}

/**
 * This function performs a Tax method which adds 2 coins to the player.
 * Moreover, this function is virtual because Governor implements it differently.
 * @throw runtime_error if the player can't use financial actions.
 */
void Player::tax()
{
    // check if the player is still in the game and has enough coins
    validAction(0, "tax"); // the cost of Tax is 0

    // check if the player can use Gather or Tax
    if (!blockStatus.canFinance)
        throw runtime_error("Player got sanctioned and can not perform Tax!");

    // add 2 coins to the player
    coins += 2;
}

/**
 * This function performs a Bribe method which removes 4 coins from the player.
 * @throw logic_error if the player does not have enough coins to perform the action.
 */
void Player::bribe()
{
    // check if the player is still in the game and has enough coins
    validAction(4, "bribe"); // the cost of Bribe is 0

    // else -> remove the cost of the action (4 coins)
    coins -= 4;
}

/**
 * This function performs an arrest on a given player.
 * @param player the player that will be arrested.
 * @throw logic_error if the chosen player is not the game.
 * @throw logic_error if the current player chooses to arrest the same player twice in a row.
 * @throw logic_error if the current player can not arrest other players.
 */
void Player::arrest(Player& player)
{
    // check if the player is still in the game and has enough coins
    validAction(0, "arrest"); // the cost of Arrest is 0

    // check if the player is active in the game
    if (!player.getInGame())
        throw logic_error("The player you chose is not in game!");

    // check if the current player already arrested the given player in the same turn
    if (blockStatus.arrested == player.getPlayerID())
        throw logic_error("Cannot perform two arrests on the same player in a row!");

    if (!blockStatus.canArrest)
        throw logic_error("You are now allowed to perform arrest action in this turn!");

    // if the player role is NOT Merchant and has enough coins -> get one coin
    if (player.getRole() != "Merchant" && player.getCoins() > 0)
        coins += 1;

    // perform arrest on the given player
    player.onArrested();

    // set the arrested to
    blockStatus.arrested = player.getPlayerID();
}

/**
 * This function performs sanction on a given player.
 * @param player the player that will be sanctioned.
 */
void Player::sanction(Player &player)
{
    // check if the player is still in the game and has enough coins
    validAction(3, "sanction"); // the cost of Sanction is 3

    // remove the cost of the sanction
    coins -= 3;

    // if the chosen player is a Judge and has coins -> remove an extra coin
    if (player.getRole() == "Judge" && coins > 0)
        coins -= 1; // remove another coin

    // perform the sanction on the given player
    player.onSanctioned();
}

/**
 * This function gets a reference to a player and performs coup on him.
 * @param player the player that will get couped.
 */
void Player::coup(Player& player)
{
    // check if the player is still in the game and has enough coins
    validAction(7, "coup"); // the cost of Coup is 7

    coins -= 7; // remove the cost of coup
    player.setInGame(false); // set the couped player off the game
}

// overriders (exclude tax)

/**
 * This function sets the player to not be able to perform financial actions (Gather, Tax).
 * Moreover, this function is virtual because Baron implements it differently.
 */
void Player::onSanctioned()
{
    // block the financial methods - Gather and Tax
    getBlockStatus().canFinance = false;
}

/**
 * This function perform an arrest on the player.
 * Moreover, this function is virtual and each role implements it differently.
 */
void Player::onArrested()
{
    // the player has no coins to give to the player attacking him
    if (coins == 0)
        return;

    // remove the coin
    coins -= 1;
}

/**
 * This function checks if a player can block Tax actions of other players.
 * The function is declared as virtual because Governor is allowed to block such action
 * but not each player is allowed.
 * @return false if the player is not allowed to block Tax action. Otherwise, returns true.
 */
bool Player::canBlockTax() const
{
    return false;
}

/**
 * This function checks if a player can block Bribe actions of other players.
 * The function is declared as virtual because Judge is allowed to block such action
 * but not each player is allowed.
 * @return false if the player is not allowed to block Bribe action. Otherwise, returns true.
 */
bool Player::canBlockBribe() const
{
    return false;
}

/**
 * This function returns the possible actions a player can perform in his turn.
 * @return a vector of string which contains the possible action the current player can make in his turn.
 * @throw logic_error if the player is not in the game anymore.
 */
vector<string> Player::showActions() const
{
    if (!inGame)
        throw logic_error("Player is not active in the game!");

    // this vector will contain the actions that the player can ake in his turn
    vector<string> actions;

    // if the player is a Spy add his spacial method
    // this method costs 0 and does not consider as turn] -> spy can do it when he has 10 coins!
    if (role == "Spy")
        actions.push_back("Peek");

    // check if the player must coup and if so -> insert only coup as an option to play
    if (mustCoup())
    {
        actions.push_back("Coup");
        return actions; // return only Coup as an available action
    }

    // if the player can perform financial actions -> add them to the available actions
    if (blockStatus.canFinance)
    {
        // add the actions Gather and Tax
        actions.push_back("Gather");
        actions.push_back("Tax");
    }

    // if the player can arrest -> add arrest as a valid action to perform
    if (blockStatus.canArrest)
        actions.push_back("Arrest");

    // if the player is a Baron add his special method
    if (role == "Baron" && coins >= 3) // invest costs 3 coins
        actions.push_back("Invest");

    // bribe costs 4 coins
    if (coins >= 4)
        actions.push_back("Bribe");

    // sanction costs 3 coins
    if (coins >= 3)
        actions.push_back("Sanction");

    // coup costs 7 coins
    if (coins >= 7)
        actions.push_back("Coup");

    // return all the available actions
    return actions;
}

/**
 * This function checks if the action of the player is valid by checking if he is still
 * active in the game and has enough coins.
 * @param cost the cost of the action
 * @throw logic_error if the player is not in the game anymore
 * @throw runtime_error if the player can not afford this action
 */
void Player::validAction(int cost, string action) const
{
    // check if the player is still active
    if (!inGame)
        throw logic_error("Player is not active in the game!");

    // if the player has not enough coins
    if (coins < cost)
        throw runtime_error("Not enough coins to perform " + action + "!");
}

/**
 * This function gets an amount of coins and adds it to this player's coins
 * @param add the amount of coins that will be added to this player
 */
void Player::addCoins(int add)
{
    coins += add; // add the coins
}

/**
 * This function gets an amount of coins and reduces it from this player's coins.
 * If the player doesn't have enough coins to remove - his coins will be set to 0
 * @param remove the amount of coins that should be reduced from this player
 */
void Player::removeCoins(int remove)
{
    // if the player doesn't have enough coins -> remove what he has
    if (remove > coins)
        coins = 0; // reset coins
    else
        coins -= remove; // remove the coins
}

/**
 * This functions checks if the current player must perform a coup.
 * @return true if the player must perform coup. Otherwise, returns false
 */
const bool Player::mustCoup() const
{
    // if the player has at least 10 coins he must perform a coup -> return true
    if (coins >= 10)
        return true;

    return false;
}