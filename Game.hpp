// dvirbto@gmail.com

#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Roles/Player.h"
#include <vector>

/**
 *  This class represents a Game object (and logic) in the game.
 *  This class contains:
 *  @param currentPlayers - a vector of pointers to players playing the game.
 *  @param currentPlayerIndex - an index (related to the vector) of the current player.
 *  @param anotherTurns - an integer which represents the number of turns the current player has.
 *  Each function is explained in the cpp file in order to keep this API clear.
 */
class Game {

    private:
        std::vector<Player*> currentPlayers;
        int currentPlayerIndex;
        int anotherTurns;

    // methods
    public:

        /**
         * Default constructor. 
         */
        Game();

        /**
         * Constructor by a vector of names (strings).
         */
        Game(const std::vector<std::string>& players);

        /**
         * Constructor by a vector of Player* (player with roles).
         */
        Game(std::vector<Player*> rolePlayers);

        /**
         * Destructor - deletes all the new players that were created.
         */
        ~Game();

        // getters & setters

        /**
         * Gets all the current players.
         */
        std::vector<Player*> getCurrentPlayers();

        /**
         * Get the current playerID.
         */
        int getCurrentPlayerIndex() const;

        /**
         * Get the current player.
         */
        Player& getCurrentPlayer() const;

        /**
         * Get all the additional turns.
         */
        const int getAnotherTurns() const;

        /**
         * Set additional turns.
         */
        void setAnotherTurns(int turns);

        // required methods
        /**
         * Prints the current player's name.
         */
        void turn() const;

        /**
         * Returns all the names of the active players.
         */
        std::vector<std::string> players() const;

        /**
         * Prints the name of the winner if the game is finished.
         * Otherwise, an exception is thrown.
         */
        std::string winner() const;

        // helper methods

        /**
         * Returns all the active players.
         */
        std::vector<Player*> getActivePlayers() const;

        /**
         * Returns all the players in the game who can block the current player
         * base on a given role and a cost.
         */
        std::vector<Player*> canBlockPlayers(std::string role, int cost) const;

        /**
         * Returns all the allowed actions of the current player if such exist.
         * Otherwise, skips to the next player's turn.
         */
        std::vector<std::string> allowedActions();
        void nextTurn();

        /**
         * Returns true if only one player is in game.
         * Otherwise, returns false.
         */
        bool IsGameOver() const;

        // handle actions

        /**
         * Handels the Gather action.
         * All the players are allowed to block if they can afford saction.
         */
        void gatherHandle() const;

        /**
         * Handels the Tax action.
         * Only Governors can block this action.
         */
        void taxHandle() const;

        /**
         * Handels the Bribe action.
         * Only Judges can block this action.
         * Moreover, this handle adds two turns to the current player.
         */
        void bribeHandel();

        /**
         * Handels the Arrest action.
         */
        void arrestHandle(Player& player) const;

        /**
         * Handels the Sanction action.
         */
        void sanctionHandle(Player& player) const;

        /**
         * Handels the Coup action.
         * Only Generals can block this action if they have at least 5 coins.
         */
        void coupHandle(Player& player) const;

        /**
         * Handels the Peek action.
         * This action can be performed only by a Spy and it does not considered as a turn.
         */
        void peekHandle(Player& player);

        /**
         * Handels the Invest action.
         * Only Barons can invest if the have at least 3 coins.
         */
        bool investHandle() const; // baron can invest

        /**
         * Handels the preventCoup action.
         * Only Generals can perform this action if they have at least 5 coins.
         */
        void preventCoupHandle(Player* blocker) const;

        /**
         * Handels the blockBribe action.
         * Only Judges can block this action and the current player loses 4 coins.
         */
        void blockBribeHandle();
};

#endif //GAME_HPP
