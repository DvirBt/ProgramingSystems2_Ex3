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
        explicit Player(std::string name, std::string role); // explicit constructor (don't want unexpected behaviors)
        virtual ~Player(); // virtual prevents memory leak and deletes properly (due to inheritance)

        // getters and setters
        int getPlayerID() const;
        std::string getName() const;
        std::string getRole() const;
        int getCoins() const;
        bool getInGame() const;
        void setInGame(bool status);
        void setCoins(int newCoins);
        void setSettings();
        blockSettings& getBlockStatus(); // modify
        const blockSettings& getBlockStatus() const; // read only
        bool getCanArrest() const;
        void setCanArrest(bool status);
        const void setArrested();

        // methods
        void gather();
        virtual void tax(); // Governor overrides
        void bribe();
        void arrest(Player& player);
        void sanction(Player& player);
        void coup(Player& player);

        // helper functions
        void validAction(int cost, std::string action) const;
        void addCoins(int add);
        void removeCoins(int remove);
        std::vector<std::string> showActions() const;
        const bool mustCoup() const;

        // overriders
        virtual void onSanctioned(); // overridden by Baron and Judge
        virtual void onArrested(); // overridden by General and Merchant
        virtual bool canBlockTax() const; // overridden by Governor
        virtual bool canBlockBribe() const; // overridden by Judge
};

#endif //PLAYER_H

