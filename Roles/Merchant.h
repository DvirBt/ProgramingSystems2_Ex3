// dvirbto@gmail.com

#ifndef MERCHANT_H
#define MERCHANT_H
#include "Player.h"

/**
 * This class represents a Merchant role in the game which inherits publicly from a Player.
 * A Merchant entitles to get 1 coin for free if he has at least 3 coins.
 * Moreover, when a Merchant is being arrested - he pays 2 coins to the cash box
 * instead of 1 to the player who arrested him.
 * Each function has a description in the cpp file in order to see the hpp file clearly.
 */
class Merchant : public Player{

    public:

        /**
         * Constructor of a Merchant be a given name.
         */
        Merchant(std::string name);

        /**
         * Destructor of a Merchant.
         */
        ~Merchant();

        /**
         * A Merchant is entitled to get one coin for free if he has at least 3 coins
         * at the beginning of his turn.
         */
        void checkEntitled();

        /**
         * When a Merchant is being arrested - he pays two coins to the check box.
         * If he has less than two coins - he pays what he has.
         */
        virtual void onArrested();
};



#endif //MERCHANT_H
