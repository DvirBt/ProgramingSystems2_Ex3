// dvirbto@gmail.com

#ifndef GOVENOR_H
#define GOVENOR_H
#include "Player.h"

/**
 * This class represents a Governor role in the game which inherits publicly from a Player.
 * A Governor gets 3 coins instead of 2 when he uses Tax.
 * Therefore, the Tax action of Governor is implemented (virtually) differently than other players.
 * Moreover, he can prevent Tax actions of other players.
 * Each function has a description in the cpp file in order to see the hpp file clearly.
 */
class Governor : public Player
{
    public:

        /**
         * Constructor of a Governor by a given name.
         */
        Governor(std::string name);

        /**
         * Destructor of a Govenrnor.
         */
        ~Governor();

        /**
         * A Governor gets three coins instead of two when he performs Tax action.
         */
        virtual void tax();

        /**
         * A Governor can block Tax actions of other players - returns true.
         */
        virtual bool canBlockTax() const;
};

// methods



#endif //GOVENOR_H
