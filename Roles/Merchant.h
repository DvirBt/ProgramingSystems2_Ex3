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
    Merchant(std::string name);
    ~Merchant();
    void checkEntitled();
    virtual void onArrested();
};



#endif //MERCHANT_H
