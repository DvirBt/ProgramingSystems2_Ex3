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
        General(std::string name);
        ~General();
        void preventCoup(Player& player);
        virtual void onArrested();
};

#endif //GENERAL_H
