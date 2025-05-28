// dvirbto@gmail.com

#ifndef BARON_H
#define BARON_H
#include "Player.h"

/**
 * This class represents a Baron role in the game which inherits publicly from a Player.
 * A Baron has a special method which is Invest.
 * Invest - a Baron can risk 3 coins in order to get 6 coins back with a 50% chances.
 * Moreover, when a Baron is being sanctioned he gets 1 coin back.
 * Each function has a description in the cpp file in order to see the hpp file clearly.
 */
class Baron : public Player {
    private:
        bool invested;

    public:
        Baron(std::string name);
        ~Baron();
        void invest();
        const bool isInvested() const;
        virtual void onSanctioned();
};



#endif //BARON_H
