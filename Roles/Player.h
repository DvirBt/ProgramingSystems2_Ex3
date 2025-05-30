// dvirbto@gmail.com

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ranges>
#include <vector>

/**
 * This struct represents the current status of a player in terms of:
 * 1. If the player is allowed to perform financial actions which are Gather and Tax
 * 2. If the player can arrest others
 * 3. The ID number of the player that he arrested in his last turn (if one's exists)
 * Moreover, it contains a constructor with an initialization list
 */
struct blockSettings
{
    public:
        bool canFinance = true; // true -> can use Gather or Tax, false -> can't user Gather and Tax
        bool canArrest = true; // true -> can arrest other player, false -> can't arrest other players
        int arrested = -1; // the PlayerID of the last player arrested (if one exists)
        blockSettings() : canFinance(true), canArrest(true), arrested(-1) {}
};

/**
 * This class represents a Player in the game.
 * This class is the subclass of all the other roles in the game.
 * It contains all the basic methods that each player can make in the game.
 * Some functions are declared as virtual due to the different implementations for each role.
 * The non-virtual functions are mutual to all the players without relation of their role in the game.
 * Each function is explained in the cpp file in order to create a clear hp file.
 */
class Player {
    protected:
        int playerID; // the playerID
        std::string name; // the name of the player
        std::string role; // the role of the player
        int coins; // the amount of coins the player has
        bool inGame; // true -> the player is still in the game. false -> the player is not in the game
        blockSettings blockStatus; // represents the restrictions of the player

    public:

        /**
         * Constructor of a Player by a given name and a role.
         */
        explicit Player(std::string name, std::string role);
        
        /**
         * Destructor of a Player.
         */
        virtual ~Player(); // virtual prevents memory leak and deletes properly (due to inheritance)

        // getters and setters

        /**
         * Gets the player ID.
         */
        int getPlayerID() const;

        /**
         * Gets the player's name.
         */
        std::string getName() const;

        /**
         * Gets the player's role.
         */
        std::string getRole() const;

        /**
         * Gets the player's amount of coins.
         */
        int getCoins() const;

        /**
         * Gets the player's status in the game.
         * True - still active in the game (not couped).
         * False - not active in the game anymore (couped).
         */
        bool getInGame() const;

        /**
         * Sets the player's status to a given boolean variable.
         * True - still active in the game (not couped).
         * False - not active in the game anymore (couped).
         */
        void setInGame(bool status);

        /**
         * Sets the amount of player's coins to a given integer variable.
         */
        void setCoins(int newCoins);

        /**
         * Resets the current restrictions on the player:
         * He can use financial methods (Gather, Tax).
         * He can arrest other players.
         * He did not arrest any player in this round.
         */
        void setSettings();

        /**
         * Gets the current restrictions of a player and allows modification.
         */
        blockSettings& getBlockStatus();

        /**
         * Gets (read-only) the current restrictions of a player.
         */
        const blockSettings& getBlockStatus() const;

        /**
         * Returns true if the player can arrest other players.
         * Otherwise, returns false.
         */
        bool getCanArrest() const;

        /**
         * Sets the player ability to arrest other players to a given boolean variable.
         */
        void setCanArrest(bool status);

        /**
         * Sets the player to be arrested.
         */
        const void setArrested();

        // methods

        /**
         * The player gets one coin.
         * This action can be blocked by any player who chooses to sanction.
         * This action can not be used if the player is sanctioned.
         */
        void gather();

        /**
         * The player gets two coins.
         * This action can be blocked by Governors.
         * This action can not be used if the player is sanctioned.
         */
        virtual void tax();

        /**
         * This player gets two turns to play.
         * This action costs four coins and can be blocked by a Judge.
         * In this case, the player loses his four coins and has only one turn.
         */
        void bribe();

        /**
         * This player selects an active player and steal one coin from him
         * if he has one.
         * This action can be blocked by a Spy when he peeks.
         */
        void arrest(Player& player);

        /**
         * This player selects an active player and prevents from him to use 
         * financial methods (Gather and Tax).
         * This action costs three coins.
         */
        void sanction(Player& player);

        /**
         * This player selects an active player and eliminates him from the game.
         * This action costs seven coins and it can be blocked by a General who has five coins.
         * In this case, the player loses his turn and his seven coins.
         */
        void coup(Player& player);

        // helper functions

        /**
         * This function checks if the player can perform the action he selected by a given cost 
         * of the action and the given name of the action.
         * If he can not perform the action - the relevant exception is thrown.
         */
        void validAction(int cost, std::string action) const;

        /**
         * Adds to the player's amount of coins the given integer variable.
         */
        void addCoins(int add);

        /**
         * Removes from the player the amount of coins by a given integer variable.
         * If the given variable is greater than the amount of the coins the player has - it removes what he has.
         */
        void removeCoins(int remove);

        /**
         * Returns a vector of strings contains all the available actions the player can perform in his turn.
         * If no actions can be performed - the method moves to the next player turn.
         */
        std::vector<std::string> showActions() const;

        /**
         * A player must perform a coup if he has at least ten coins.
         * Returns true if the player must coup. Otherwise, returns false.
         */
        const bool mustCoup() const;

        // overriders

        /**
         * Baron and Judge overrides sanction action.
         */
        virtual void onSanctioned();

        /**
         * General and Merchant overrides arrest action.
         */
        virtual void onArrested(); 

        /**
         * Governor overrides canBlockTax action.
         */
        virtual bool canBlockTax() const;

        /**
         * Judge overrides canBlockBribe action.
         */
        virtual bool canBlockBribe() const;
};

#endif //PLAYER_H

