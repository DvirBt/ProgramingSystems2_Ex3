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
        Game(); // constructors
        Game(const std::vector<std::string>& players);
        Game(std::vector<Player*> rolePlayers);
        ~Game(); // destructor

        // getters & setters
        std::vector<Player*> getCurrentPlayers();
        int getCurrentPlayerIndex() const;
        Player& getCurrentPlayer() const;
        const int getAnotherTurns() const;
        void setAnotherTurns(int turns);

        // required methods
        void turn() const;
        std::vector<std::string> players() const;
        std::string winner() const;

        // helper methods
        std::vector<Player*> getActivePlayers() const;
        std::vector<Player*> canBlockPlayers(std::string role, int cost) const;
        std::vector<std::string> allowedActions();
        void nextTurn();
        bool IsGameOver() const;

        // handle actions
        void gatherHandle() const; // all the players can block with sanction (if they have enough coins)
        void taxHandle() const; // governors can block
        void bribeHandel(); // judges can block
        void arrestHandle(Player& player) const;
        void sanctionHandle(Player& player) const;
        void coupHandle(Player& player) const; // generals can block
        void peekHandle(Player& player); // spy can peek
        bool investHandle() const; // baron can invest
        void preventCoupHandle(Player* blocker) const; // general can prevent a coup by other player
        void blockBribeHandle();
};

#endif //GAME_HPP
