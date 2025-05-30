// dvirbto@gmail.com

#ifndef GENERAL_H
#define GENERAL_H
#include "Player.h"

/**
 * This class represents a General role in the game which inherits publicly from a Player.
 * A General has a special method which is preventCoup.
 * preventCoup - a General can pay 5 coins and prevent a coup made by the current player
 * on any active player. In this case the player who couped losses his turn and his 7 coins.
 * Moreover, when a Baron is being arrested he gets back the coin that was taken from him.
 * Each function has a description in the cpp file in order to see the hpp file clearly.
 */
class General : public Player{
    public:

        /**
         * Constructor of a General by a given name.
         */
        General(std::string name);

        /**
         * Destructor of a General.
         */
        ~General();

        /**
         * A General can prevent a Coup made by a player on any of the active players in the game
         * if he has at least 5 coins.
         * In this case the attacker loses his 7 coins and his turn.
         */
        void preventCoup(Player& player);

        /**
         * When a General is arrested - he gets back the coin that was taken from him 
         * iff the coin indeed was taken.
         */
        virtual void onArrested();
};

#endif //GENERAL_H
