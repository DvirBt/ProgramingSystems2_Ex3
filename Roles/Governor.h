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
        Governor(std::string name);
        ~Governor();
        virtual void tax(); // overrides, virtual is not a must, but it helps to understand
        virtual bool canBlockTax() const;
};

// methods



#endif //GOVENOR_H
