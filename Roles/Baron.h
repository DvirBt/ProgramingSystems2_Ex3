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

        /**
         * Construct of a Baron by a given name.
         */
        Baron(std::string name);

        /**
         * Destructor of a Baron.
         */
        ~Baron();

        /**
         * A Baron can choose to make an Investment in his turn if he has at least three coins.
         * When he does, he has 50-50 precent of either win back six coins or win nothing.
         */
        void invest();

        /**
         * Returns the last result of the investment.
         * If he won - returns true.
         * If he lost - returns false.
         */
        const bool isInvested() const;

        /**
         * When a Baron is being sanctioned he gets back one coin.
         */
        virtual void onSanctioned();
};



#endif //BARON_H
