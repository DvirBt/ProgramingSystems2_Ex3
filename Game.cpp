// dvirbto@gmail.com

#include "Game.hpp"
#include <stdexcept>
#include <vector>
#include <cstdlib> // for random number
#include <ctime> // used to reset the random each round
#include "Roles/Governor.h"
#include "Roles/Spy.h"
#include "Roles/Baron.h"
#include "Roles/General.h"
#include "Roles/Judge.h"
#include "Roles/Merchant.h"
#include <iostream>


using namespace std;

/**
 * This is a default constructor for Game object.
 */
Game::Game() : currentPlayers() ,currentPlayerIndex(0), anotherTurns(0) {}

/**
 * This is the constructor of Game object which gets a list of the players.
 * The game must have at least 2 players and limited to 6 players at the most.
 * @param rolePlayers a vector of the players in the order of their registration.
 * @throw runtime_error if there are less than 2 players or more than 6 players.
 */
Game::Game(vector<Player*> rolePlayers) : currentPlayers(rolePlayers) ,currentPlayerIndex(0), anotherTurns(0)
{
    // if there are not enough players in the game -> throw exception
    if (currentPlayers.size() < 2)
        throw runtime_error("At least 2 players are required to start the game!");

    // if there are too many players in the game -> throw exception
    if (currentPlayers.size() > 6)
        throw runtime_error("The game is limited to 7 players!");
}

/**
 * This is the constructor of Game object which gets a list of the names of each player and
 * randomly generates him a role. After that a new instance of the role that was generated is
 * being created and pushed to the vector of the players.
 * The game must have at least 2 players and limited to 6 players at the most.
 * @param players a vector of the names of the players in the order of their registration.
 * @throw logic_error if the generated random number (role) is not between 0 and 6.
 * @throw runtime_error if there are less than 2 valid players or more than 6 players.
 */
Game::Game(const vector<string> &players) : currentPlayerIndex(0), anotherTurns(0)
{
    // check all the valid names
    int counter = 0;
    for (int i = 0; i < players.size(); i++)
    {
        if (players.at(i) != "")
            counter++;
    }

    // if there are not enough players in the game -> throw exception
    if (counter < 2)
        throw runtime_error("At least 2 players are required to start the game!");

    // if there are too many players in the game -> throw exception
    if (counter > 6)
        throw runtime_error("The game is limited to 7 players!");

    // reset the random each time
    srand(time(nullptr));

    // loop over all the given names
    for (int i = 0; i < players.size(); i++)
    {
        // for each player with a valid name (not empty name)
        if (!players.at(i).empty()) // <=> player.name != ""
        {
            // create a pointer to a player
            Player* p;

            // generate a number between 0 to 6
            int role = rand() % 6;

            // by the random number -> create a different role
            switch (role)
            {
                case 0:
                    p = new Governor(players.at(i));
                    break;
                case 1:
                    p = new Spy(players.at(i));
                    break;
                case 2:
                    p = new Judge(players.at(i));
                    break;
                case 3:
                    p = new Baron(players.at(i));
                    break;
                case 4:
                    p = new General(players.at(i));
                    break;
                case 5:
                    p = new Merchant(players.at(i));
                    break;
                default:
                    throw logic_error("Invalid role");
            }

            // insert the new player to the vector of players
            currentPlayers.emplace_back(p);
        }
    }
}

/**
 * This is the destructor of the Game object which deletes all the players
 * that were created on the heap.
 */
Game::~Game()
{
    // for each player -> delete    
    for (Player* p : currentPlayers)
        delete p; // Now deleting nothing — or worse, from invalid memory
  
}

// GETTERS & SETTERS
/**
 * Gets all the players in the game both active and eliminated.
 * @return all the players registered to the game.
 */
vector<Player*> Game::getCurrentPlayers()
{
    return currentPlayers;
}

/**
 * Gets the index (ID) of the player in this current turn.
 * @return the current player index.
 */
int Game::getCurrentPlayerIndex() const
{
    return currentPlayerIndex;
}

/**
 * Gets the number of turns of the current player.
 * @return the number of additionally turns of the current player in the game.
 */
const int Game::getAnotherTurns() const
{
    return anotherTurns;
}

/**
 * Sets the additional turns of a player to a given number.
 * @param turns the new amount of turns the current player has.
 */
void Game::setAnotherTurns(int turns)
{
    anotherTurns = turns;
}

/**
 * Gets the player in this current turn.
 * @return the player of this turn.
 */
Player& Game::getCurrentPlayer() const
{
    return *currentPlayers[currentPlayerIndex];
}
// END OF GETTERS & SETTERS

/**
 * This function sets the currentPlayerIndex to be the next player to perform an action in the game.
 */
void Game::nextTurn()
{
    // if the player still can perform an action (like after bribe or peek) -> he can do another turn
    if (anotherTurns > 0)
    {
        anotherTurns--; // reduce one turn
        return; // the index stays the same and the current player has another turn
    }

    // remove past restrictions
    currentPlayers[currentPlayerIndex]->setSettings();

    // save the last player index
    int lastPlayer = currentPlayerIndex++;

    // loop over all the players in the
    while (lastPlayer != currentPlayerIndex)
    {
        // if reached to the last player
        if (currentPlayerIndex == currentPlayers.size())
            currentPlayerIndex = 0; // start over the counting

        // if the next player is still in the game -> return
        if (currentPlayers[currentPlayerIndex]->getInGame())
            break;

        currentPlayerIndex++; // check the next player
    }

    // check if the game is finished
    if (lastPlayer == currentPlayerIndex)
        return;

    // if the player is Merchant -> check if he deserves to get a coin for free
    // use dynamic cast like instance of to perform entitled method of Merchant
    if (currentPlayers[currentPlayerIndex]->getRole() == "Merchant") // static
        dynamic_cast<Merchant*>(currentPlayers[currentPlayerIndex])->checkEntitled(); // instance of
}

/**
 * This function prints the name of the current player.
 */
void Game::turn() const
{
    cout << currentPlayers[currentPlayerIndex]->getName() << endl;
}

/**
 * This function returns all the names of the players who are still in the game.
 * @return a vector of string contains all the names of the players who are currently still in the game.
 */
vector<string> Game::players() const
{
    // create a vector of strings
    vector<string> names;

    // loop over all the players
    for (int i = 0; i < currentPlayers.size(); i++)
    {
        // if the player is still active -> push to the vector
        if (currentPlayers[i]->getInGame())
            names.push_back(currentPlayers[i]->getName());
    }

    // return the names of the active players
    return names;
}

/**
 * This function checks if there is only one player remaining and returns his name.
 * @return the name of the winner if one exists.
 * @throw runtime_error if the game is not over yet (more than one player is active).
 */
string Game::winner() const
{
    // if the game is not over -> throw exception
    if (!IsGameOver())
        throw runtime_error("Game is not over yet!");

    // loop over all the players and return the name of the one who is still active
    for (int i = 0; i < currentPlayers.size(); i++)
    {
        if (currentPlayers[i]->getInGame())
            return currentPlayers[i]->getName();
    }

    // should never be reached
    return "No such player was found";
}

/**
 * This function checks if the game is over by checking if only one player is currently active.
 * @return true if the game is over. Otherwise, returns false.
 */
bool Game::IsGameOver() const
{
    // set a counter
    int countAlive = 0;

    // loop over all the players and add 1 to the counter for each player that is active
    for (int i = 0; i < currentPlayers.size(); i++)
    {
        if (currentPlayers[i]->getInGame())
            countAlive++;
    }

    // if only 1 player is active -> he is the only one remaining -> return true
    if (countAlive == 1)
        return true;

    // at least 2 players are still active -> return false
    return false;
}

// HANDLERS

/**
 * When a player chooses to perform Gather this handle perform this action.
 */
void Game::gatherHandle() const
{
    // perform gather
    currentPlayers[currentPlayerIndex]->gather();
}

/**
 * When a player chooses to perform Tax this handle perform this action.
 * Note that this action is virtual and implemented differently when a Governor performs Tax.
 */
void Game::taxHandle() const
{
    // perform tax
    currentPlayers[currentPlayerIndex]->tax();
}

/**
 * This function returns a list of all the players who are still in the game WITHOUT the current player.
 * @return a list of players who are currently active excluding the current player.
 */
vector<Player*> Game::getActivePlayers() const
{
    // set a vector of pointer to players
    vector<Player*> alivePlayers;

    // loop over all the players
    for (int i = 0; i < currentPlayers.size(); i++)
    {
        // if the player is still in the game and not the current player -> add to the vector
        if (currentPlayers[i]->getInGame() && i != currentPlayerIndex)
            alivePlayers.push_back(currentPlayers[i]);
    }

    // return all the active players
    return alivePlayers;
}

/**
 * This function returns a list of all the players who can block the current player EXCLUDING him.
 * @param role the required role to block a specific action.
 * @param cost the cost required to block.
 * @return a list of active players who can block the action of the current player excluding him.
 */
std::vector<Player*> Game::canBlockPlayers(std::string role, int cost) const
{
    // set a vector of pointer to player
    vector<Player*> canBlockPlayers;

    // loop over all the players
    for (int i = 0; i < currentPlayers.size(); i++)
    {
        // if the player is still in the game, has enough coins and not the current player -> check his role
        if (currentPlayers[i]->getInGame() && currentPlayers[i]->getCoins() >= cost && i != currentPlayerIndex)
        {
            // no specific role is required -> push anyways
            if (role == "")
                canBlockPlayers.push_back(currentPlayers[i]);

            // a specific role is required, if he has the required role -> push him
            else if (currentPlayers[i]->getRole() == role) // has the required role
                canBlockPlayers.push_back(currentPlayers[i]);
        }
    }

    // return the players who can block
    return canBlockPlayers;
}

/**
 * When a player chooses to perform Bribe this handle perform this action.
 * Note that this function adds to the current players two turns to play.
 */
void Game::bribeHandel()
{
    anotherTurns += 2; // adds to the player 2 turns to play
    currentPlayers[currentPlayerIndex]->bribe(); // perform bribe action
}

/**
 * When a player chooses to perform Arrest this handle perform this action.
 * @param player the player that will be arrested.
 */
void Game::arrestHandle(Player& player) const
{
    // perform arrest action on the given player
    currentPlayers[currentPlayerIndex]->arrest(player);
}

/**
 * When a player chooses to perform Sanction this handle perform this action.
 * @param player the player that will be sanctioned.
 */
void Game::sanctionHandle(Player& player) const
{
    // the current player sanctions a given player
    currentPlayers[currentPlayerIndex]->sanction(player);
}

/**
 * When a player chooses to perform Coup this handle perform this action.
 * @param player the player that will be couped (not active anymore).
 */
void Game::coupHandle(Player& player) const
{
    // the current player coups a given player
    currentPlayers[currentPlayerIndex]->coup(player);
}

/**
 * When a Spy player chooses to perform Peek this handle perform this action.
 * @param player the player that will be peeked by the Spy which is the current player.
 */
void Game::peekHandle(Player &player)
{
    anotherTurns += 1; // peek does not cost a turn -> adds 1 turn
    // cast the current player as a Spy in order to perform the peek action
    dynamic_cast<Spy*>(currentPlayers[currentPlayerIndex])->peek(player);
}

/**
 * When a Baron player chooses to perform invest this handle perform this action.
 * @return true if the investment succeeded. Otherwise, return false.
 */
bool Game::investHandle() const
{
    // cast the current player as a Baron in order to perform the invest action
    dynamic_cast<Baron*>(currentPlayers[currentPlayerIndex])->invest();

    // return the result of the investment
    return dynamic_cast<Baron*>(currentPlayers[currentPlayerIndex])->isInvested();
}

/**
 * When a General player chooses to prevent a coup this handle perform this action.
 * @param blocker the player (General) who blocked the current player Coup action.
 */
void Game::preventCoupHandle(Player* blocker) const
{
    // cast the current player as a General in order to perform the preventCoup method
    // dynamic cast works like instance of in java
    dynamic_cast<General*>(blocker)->preventCoup(*currentPlayers[currentPlayerIndex]); // cast it to General
}

/**
 * When a player gets a bribe block he loses the cost of the action (4 coins)
 * but he still has another turn to play.
 */
void Game::blockBribeHandle()
{
    anotherTurns += 1; // he has another turn to play even if he got blocked
    currentPlayers[currentPlayerIndex]->removeCoins(4); // he lost his 4 coins
}
// END OF HANDLERS

/**
 * This function returns all the possible actions of the current player.
 * If a player has no moves (which are considered as a turn) - his turn is skipped.
 * @return a vector of strings contains all the actions that a player can perform in his turn.
 */
std::vector<std::string> Game::allowedActions()
{
    // check if this player has turns to play
    while (currentPlayers[currentPlayerIndex]->showActions().size() <= 1)
    {
        // if there is an action to make -> make sure it's not a peek
        if (currentPlayers[currentPlayerIndex]->showActions().size() == 1)
        {
            // if the action is not a peek -> it's a turn -> break and return
            if (currentPlayers[currentPlayerIndex]->showActions().at(0) != "Peek")
                break;
        }

        // move to the next turn and print a message
        cout << "Player " << currentPlayerIndex << " turn was skipped - no available moves!" << endl;
        nextTurn();
    }

    // return valid turns
    return currentPlayers[currentPlayerIndex]->showActions();
}