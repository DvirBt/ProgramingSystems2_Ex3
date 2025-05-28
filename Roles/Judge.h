// dvirbto@gmail.com

#ifndef JUDGE_H
#define JUDGE_H
#include "Player.h"

/**
 * This class represents a Judge role in the game which inherits publicly from a Player.
 * A Judge can block Bribe actions of other players in the game - which makes the player who performed
 * the bribe action to lose his 4 coins.
 * Moreover, when a Judge is being sanctioned - the player who sanctioned needs to pay another coin.
 * Each function has a description in the cpp file in order to see the hpp file clearly.
 */
class Judge : public Player{

    public:
        Judge(std::string name);
        ~Judge();
        virtual bool canBlockBribe() const;
};

#endif //JUDGE_H
