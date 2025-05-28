// dvirbto@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <iostream>
#include "../Game.hpp"
#include "../Roles/Baron.h"
#include "../Roles/General.h"
#include "../Roles/Governor.h"
#include "../Roles/Judge.h"
#include "../Roles/Merchant.h"
#include "../Roles/Player.h"
#include "../Roles/Spy.h"
using namespace std;

/**
 * This is the cpp file of all the test that will be conducted on the game Coup.
 * Each object will be tested separately in order to check its functionality.
 * Additionally, a game logic will also be tested (in the Game class).
 */

/**
 * In this test case I will check all the methods of Player
 */
TEST_CASE("Test Player class methods")
{
    // initialize a player
    Player p("Player", "");
    Player temp("Player", "");

    Spy spy("S");
    General general("G");
    Governor governor("G");
    Judge judge("J");
    Baron baron("B");
    Merchant merchant ("M");

    // Helper functions

    SUBCASE("Test validAction function")
    {
        p.setInGame(false); // set p to be not an active player
        p.setCoins(1000);
        CHECK_THROWS(p.validAction(7, "Coup")); // can't perform the most expensive action

        p.setInGame(true); // now p is active in the game
        p.setCoins(-1); // p has not enough coins for any action
        CHECK_THROWS(p.validAction(0, "Gather")); // can't perform a non-cost action

        p.setCoins(10); // now p is in the game and has enough coins for any action
        CHECK_NOTHROW(p.validAction(7, "Coup")); // can perform any action
    }

    // add coins to a player
    SUBCASE("Test addCoins function")
    {
        p.setCoins(0); // p has 0 coins
        p.addCoins(1); // p got 1 coin
        CHECK_EQ(p.getCoins(), 1); // expected to have 1 coin
    }

    // remove coins from a player
    SUBCASE("Test removeCoins function")
    {
        p.setCoins(1); // p has 1 coin
        p.removeCoins(1); // p paid 1 coin
        CHECK_EQ(p.getCoins(), 0); // expected to have 0 coins
        p.removeCoins(1); // p has no coins therefore -> no coins will be reduced
        CHECK_EQ(p.getCoins(), 0); // expected to still have 0 coins
    }

    // show all the available actions to a player
    SUBCASE("Test showActions")
    {
        p.setInGame(false);
        CHECK_THROWS(p.showActions()); // p is not in the game

        // init
        p.setInGame(true);
        p.setSettings();
        p.setCoins(0);

        // p has no coins -> he can only gather, tax or arrest
        vector<string> actions = p.showActions();
        CHECK_EQ(actions.size(), 3);
        CHECK_EQ(actions[0], "Gather");
        CHECK_EQ(actions[1], "Tax");
        CHECK_EQ(actions[2], "Arrest");

        p.setCanArrest(false); // p now can NOT arrest
        // p can only gather or tax
        actions = p.showActions();
        CHECK_EQ(actions.size(), 2);
        CHECK_EQ(actions[0], "Gather");
        CHECK_EQ(actions[1], "Tax");

        p.setSettings(); // reset
        p.setCoins(3); // set coins to 3 -> now can ALSO sanction and
        actions = p.showActions();
        CHECK_EQ(actions.size(), 4);
        CHECK_EQ(actions[0], "Gather");
        CHECK_EQ(actions[1], "Tax");
        CHECK_EQ(actions[2], "Arrest");
        CHECK_EQ(actions[3], "Sanction");

        p.setCoins(4); // set coins to 4 -> now can ALSO bribe and
        actions = p.showActions();
        CHECK_EQ(actions.size(), 5);
        CHECK_EQ(actions[0], "Gather");
        CHECK_EQ(actions[1], "Tax");
        CHECK_EQ(actions[2], "Arrest");
        CHECK_EQ(actions[3], "Bribe");
        CHECK_EQ(actions[4], "Sanction");

        p.setCoins(7); // set coins to 7 -> now can ALSO coup and
        actions = p.showActions();
        CHECK_EQ(actions.size(), 6);
        CHECK_EQ(actions[0], "Gather");
        CHECK_EQ(actions[1], "Tax");
        CHECK_EQ(actions[2], "Arrest");
        CHECK_EQ(actions[3], "Bribe");
        CHECK_EQ(actions[4], "Sanction");
        CHECK_EQ(actions[5], "Coup");

        p.setCoins(10); // set coins to 10 -> now he MUST coup
        actions = p.showActions();
        CHECK_EQ(actions.size(), 1);
        CHECK_EQ(actions[0], "Coup");

        // now check roles with special methods (Spy and Baron)

        actions = spy.showActions();
        // spy has 0 coins and peek does not cost any coins -> can peek, gather, tax or arrest
        CHECK_EQ(actions.size(), 4);
        CHECK_EQ(actions[0], "Peek");
        CHECK_EQ(actions[1], "Gather");
        CHECK_EQ(actions[2], "Tax");
        CHECK_EQ(actions[3], "Arrest");

        spy.setCoins(10);
        // now spy must coup but peek is not considered as a turn so he can use it
        actions = spy.showActions();
        CHECK_EQ(actions.size(), 2);
        CHECK_EQ(actions[0], "Peek");
        CHECK_EQ(actions[1], "Coup");

        // now check Baron
        baron.setCoins(2);
        // baron has 2 coins and Invest costs 3 coins so he can't use invest method
        // he can use gather, tax or arrest
        actions = baron.showActions();
        CHECK_EQ(actions.size(), 3);
        CHECK_EQ(actions[0], "Gather");
        CHECK_EQ(actions[1], "Tax");
        CHECK_EQ(actions[2], "Arrest");

        // now set to 3 coins -> he can use it now
        baron.setCoins(3);
        // now he can use gather, tax, arrest, invest or sanction
        actions = baron.showActions();
        CHECK_EQ(actions.size(), 5);
        CHECK_EQ(actions[0], "Gather");
        CHECK_EQ(actions[1], "Tax");
        CHECK_EQ(actions[2], "Arrest");
        CHECK_EQ(actions[3], "Invest");
        CHECK_EQ(actions[4], "Sanction");
    }

    // if a player has at least 10 coins he has to coup
    SUBCASE("Test mustCoup function")
    {
        // reset settings
        p.setCoins(9);
        p.setSettings();
        vector<string> actions = p.showActions(); // get available actions for player
        CHECK_GT(actions.size(), 1); // check if p has more than 1 action to perform

        p.addCoins(1); // add 1 coin -> now p has 10 coins
        actions = p.showActions(); // now only coup is an option
        CHECK_EQ(actions.size(), 1); // only coup is there
        CHECK_EQ(actions[0], "Coup"); // the only value is the action "Coup"

        // reset
        p.setSettings();
        p.setCoins(0);
    }

    // MAIN METHODS

    // player gets 1 coin when using gather
    SUBCASE("Test Gather method")
    {
        p.setInGame(false); // p is not in the game
        CHECK_THROWS(p.gather()); // p can't play
        CHECK_EQ(p.getCoins(), 0); // p didn't get money
        p.setInGame(true); // reset

        p.gather(); // now p has 1 coin
        CHECK_EQ(p.getCoins(), 1);
        p.setCoins(0); // set coins to 0
    }

    // player gets 2 coins when using tax
    SUBCASE("Test Tax method")
    {
        p.setInGame(false); // p is not in the game
        CHECK_THROWS(p.tax()); // p can't play
        CHECK_EQ(p.getCoins(), 0); // p didn't get money
        p.setInGame(true); // reset

        p.tax(); // now the player has 2 coins
        CHECK_EQ(p.getCoins(), 2);
        p.setCoins(0); // set coins to 0
    }

    // player needs 4 coins to perform bribe
    // the implementation of the 2 turns is implemented in the Game object
    SUBCASE("Test Bribe method")
    {
        // p currently has 0 coins so if he tries to bribe an exception should be thrown
        CHECK_THROWS(p.bribe());

        // let's try to bribe with 3 coins -> also should get exception
        p.setCoins(3);
        CHECK_THROWS(p.bribe());

        p.setInGame(false); // p is not in the game
        CHECK_THROWS(p.bribe()); // p can't play
        p.setInGame(true); // reset

        // now let's try to bribe with the least amount of coins needed (4 coins)
        p.setCoins(4);
        CHECK_NOTHROW(p.bribe());
        CHECK_EQ(p.getCoins(), 0); // he performed the bribe and now he has 0 coins
    }

    // the player can choose a player and arrest him
    SUBCASE("Check Arrest method")
    {
        p.setInGame(false); // p is not in the game
        CHECK_THROWS(p.arrest(temp)); // p can't play
        p.setInGame(true); // reset

        // if the player is not in the game -> throw
        temp.setInGame(false);
        CHECK_THROWS(p.arrest(temp));
        temp.setInGame(true); // reset
        p.setSettings(); // reset the arrested field which contains the ID of the arrested player

        // if the player tries to arrest the same player twice in a row -> throw
        CHECK_NOTHROW(p.arrest(temp)); // arrest 1 times -> not throws
        CHECK_THROWS(p.arrest(temp)); // arrest 2 times -> throws

        // if the player can not arrest due to restriction (peek by a Spy)
        p.setCanArrest(false);
        CHECK_THROWS(p.arrest(temp));

        // reset all the settings
        p.setCoins(0);
        p.setSettings();
        p.setCanArrest(true);

        // perform an arrest on a valid player -> gain 1 coin, player arrested
        CHECK_NOTHROW(p.arrest(temp));
        CHECK_EQ(p.getCoins(), 0); // temp has no coins and therefore p won't get a coin
        CHECK_EQ(p.getBlockStatus().arrested, temp.getPlayerID());
        temp.setCoins(1);
        p.setSettings();
        CHECK_NOTHROW(p.arrest(temp));
        CHECK_EQ(p.getCoins(), 1); // now temp has a coin -> p will get it
        CHECK_EQ(p.getBlockStatus().arrested, temp.getPlayerID());

        // when a Merchant is being arrested, he pays 2 coins to the cash box and not the player
        // if he has enough coins. Otherwise, he pays what he has
        p.setCoins(0); // init p
        merchant.setCoins(3); // init Merchant with 3 coins
        CHECK_NOTHROW(p.arrest(merchant));
        CHECK_EQ(p.getCoins(), 0); // p got no coins
        CHECK_EQ(p.getBlockStatus().arrested, merchant.getPlayerID());
        CHECK_EQ(merchant.getCoins(), 1); // he paid 2 coins -> 3-2 = 1

        // make sure that p can't arrest again the merchant
        CHECK_THROWS(p.arrest(merchant));

        // now let's try to arrest a Merchant with 1 coins
        p.setSettings(); // reset settings
        CHECK_NOTHROW(p.arrest(merchant));
        CHECK_EQ(p.getCoins(), 0); // p still didn't get a coin
        CHECK_EQ(p.getBlockStatus().arrested, merchant.getPlayerID()); // the arrest was made
        CHECK_EQ(merchant.getCoins(), 0); // the merchant paid 1 coin

        // when a General is arrested he gets back one coin IF it was taken from him
        p.setSettings(); // init
        CHECK_NOTHROW(p.arrest(general)); // make arrest
        CHECK_EQ(p.getBlockStatus().arrested, general.getPlayerID()); // the arrest was made
        CHECK_EQ(p.getCoins(), 0); // general didn't have any coins -> p didn't get a coin
        CHECK_EQ(general.getCoins(), 0); // no coin was taken from him -> he didn't get the coin back

        general.setCoins(1); // now general has 1 coin
        p.setSettings(); // p has 0 coins and he didn't arrest anyone
        CHECK_NOTHROW(p.arrest(general)); // make arrest
        CHECK_EQ(p.getBlockStatus().arrested, general.getPlayerID()); // the arrest was made
        CHECK_EQ(p.getCoins(), 1); // general had 1 coin -> p got 1 coin
        CHECK_EQ(general.getCoins(), 1); // 1 coin was taken from him (=0 coins) and he got the coin back from the cash box (=1 coin)
    }

    // sanction costs 3 coins and prevents from the player who got sanctioned to Gather or Tax
    SUBCASE("Test Sanction method")
    {
        p.setSettings(); // init p
        p.setCoins(0);
        temp.setSettings(); // init temp
        temp.setCoins(0);

        p.setInGame(false); // p is not in the game
        CHECK_THROWS(p.sanction(temp)); // p can't play
        p.setInGame(true); // reset

        // p has 0 coins -> throw
        CHECK_THROWS(p.sanction(temp));
        CHECK_NOTHROW(temp.gather()); // +1 coin
        CHECK_EQ(temp.getBlockStatus().canFinance, true); // didn't get sanctioned
        CHECK_EQ(temp.getCoins(), 1);
        CHECK_NOTHROW(temp.tax()); // +2 coins
        CHECK_EQ(temp.getCoins(), 3);

        // now add to p 3 coins and perform the action
        p.setCoins(3);
        temp.setCoins(0);
        CHECK_NOTHROW(p.sanction(temp)); // use the action
        CHECK_EQ(p.getCoins(), 0); // check that the coins reduced from p
        CHECK_EQ(temp.getBlockStatus().canFinance, false); // got sanctioned
        CHECK_THROWS(temp.gather()); // temp can't gather
        CHECK_THROWS(temp.tax()); // temp can't tax
        CHECK_EQ(temp.getCoins(), 0);

        // make sure that temp can do any other action
        temp.setCoins(0);
        CHECK_NOTHROW(temp.arrest(p)); // can arrest
        temp.setCoins(3);
        CHECK_NOTHROW(temp.sanction(p)); // can sanction
        temp.setCoins(4);
        CHECK_NOTHROW(temp.bribe()); // can bribe
        temp.setCoins(7);
        CHECK_NOTHROW(temp.coup(p)); // can coup

        // reset settings
        p.setSettings();
        p.setInGame(true);

        // make sure that Governor also can't use Gather and Tax after sanction
        p.setCoins(3);
        CHECK_NOTHROW(p.sanction(governor));
        CHECK_EQ(governor.getBlockStatus().canFinance, false); // got sanctioned
        CHECK_THROWS(governor.gather()); // governor can't gather
        CHECK_THROWS(governor.tax()); // governor can't tax
        CHECK_EQ(governor.getCoins(), 0); // got no coins

        // make sure that Baron gets 1 coin after sanction
        p.setCoins(3);
        CHECK_NOTHROW(p.sanction(baron));
        CHECK_EQ(baron.getBlockStatus().canFinance, false); // got sanctioned
        CHECK_THROWS(baron.gather()); // baron can't gather
        CHECK_THROWS(baron.tax()); // baron can't tax
        CHECK_EQ(baron.getCoins(), 1); // baron had 0 coins and he got 1 back

        // make sure that after a Judge is being sanctioned -> the player who sanctioned pays 1 more coin IF he has
        p.setCoins(3); // p has exactly 3 coins and will pay another coin (0 will be left)
        CHECK_NOTHROW(p.sanction(judge));
        CHECK_EQ(judge.getBlockStatus().canFinance, false); // got sanctioned
        CHECK_THROWS(judge.gather()); // judge can't gather
        CHECK_THROWS(judge.tax()); // judge can't tax
        CHECK_EQ(judge.getCoins(), 0); // judge had 0 coins
        CHECK_EQ(p.getCoins(), 0); // p paid 3 coins in total

        judge.setSettings();
        p.setCoins(4); // p has exactly 4 coins and will pay another coin (0 will be left)
        CHECK_NOTHROW(p.sanction(judge));
        CHECK_EQ(judge.getBlockStatus().canFinance, false); // got sanctioned
        CHECK_THROWS(judge.gather()); // judge can't gather
        CHECK_THROWS(judge.tax()); // judge can't tax
        CHECK_EQ(judge.getCoins(), 0); // judge had 0 coins
        CHECK_EQ(p.getCoins(), 0); // p paid 4 coins in total

        judge.setSettings();
        p.setCoins(5); // p has exactly 5 coins and will pay another coin (1 will be left)
        CHECK_NOTHROW(p.sanction(judge));
        CHECK_EQ(judge.getBlockStatus().canFinance, false); // got sanctioned
        CHECK_THROWS(judge.gather()); // judge can't gather
        CHECK_THROWS(judge.tax()); // judge can't tax
        CHECK_EQ(judge.getCoins(), 0); // judge had 0 coins
        CHECK_EQ(p.getCoins(), 1); // p paid 4 coins in total
    }

    // coup costs 7 coins and must be performed when a player has at least 10 coins
    SUBCASE("Test Coup action")
    {
        p.setInGame(false); // p is not in the game
        CHECK_THROWS(p.sanction(temp)); // p can't play
        p.setInGame(true); // reset

        p.setSettings();
        p.setCoins(6); // p doesn't have enough coins
        CHECK_THROWS(p.coup(temp)); // coup costs 7 coins and p has 6 coins
        CHECK_EQ(temp.getInGame(), true); // temp still in the game
        CHECK_EQ(p.getCoins(), 6); // didn't pay for the action

        // now p can coup
        p.setCoins(7);
        CHECK_NOTHROW(p.coup(temp));
        CHECK_EQ(temp.getInGame(), false); // temp got couped
        CHECK_EQ(p.getCoins(), 0); // paid 7 coins

        // make sure temp can't perform any action
        temp.setCoins(1000);
        CHECK_THROWS(temp.gather()); // can't gather
        CHECK_THROWS(temp.tax()); // can't tax
        CHECK_THROWS(temp.arrest(p)); // can't arrest
        CHECK_THROWS(temp.sanction(p)); // can't sanction
        CHECK_THROWS(temp.bribe()); // can't bribe
        CHECK_THROWS(temp.coup(p)); // can't coup

        // reset
        temp.setInGame(true);
        temp.setCoins(0);
    }

    // makes the player to not able to use gather or tax
    SUBCASE("Test OnSanctioned")
    {
        // p now can gather and tax
        p.setSettings();
        CHECK_NOTHROW(p.gather());
        CHECK_NOTHROW(p.tax());

        p.onSanctioned();
        // p now sanctioned -> he can't gather or tax
        CHECK_THROWS(p.gather());
        CHECK_THROWS(p.tax());
    }

    // if the player is arrested he pays 1 coin (if he has one)
    SUBCASE("Test OnArrested")
    {
        // init
        p.setSettings();
        p.setCoins(0);

        // got arrested but has no coins
        p.onArrested();
        CHECK_EQ(p.getCoins(), 0);

        p.setCoins(1);
        // got arrested but has 1 coin -> he will have 0 now
        p.onArrested();
        CHECK_EQ(p.getCoins(), 0);

        p.setCoins(2);
        // got arrested but has 2 coins -> he will have 1 now
        p.onArrested();
        CHECK_EQ(p.getCoins(), 1);
    }

    SUBCASE("Test canBlockTax")
    {
        // a regular player can not block
        CHECK_EQ(p.canBlockTax(), false);

        // only a Governor can block tax of others
        CHECK_EQ(governor.canBlockTax(), true);

        // all the others can't block tax
        CHECK_EQ(spy.canBlockTax(), false);
        CHECK_EQ(baron.canBlockTax(), false);
        CHECK_EQ(general.canBlockTax(), false);
        CHECK_EQ(merchant.canBlockTax(), false);
        CHECK_EQ(judge.canBlockTax(), false);
    }

    SUBCASE("Test canBlockBribe")
    {
        // a regular player can not block
        CHECK_EQ(p.canBlockBribe(), false);

        // only a Judge can block tax of others
        CHECK_EQ(judge.canBlockBribe(), true);

        // all the others can't block tax
        CHECK_EQ(spy.canBlockBribe(), false);
        CHECK_EQ(baron.canBlockBribe(), false);
        CHECK_EQ(general.canBlockBribe(), false);
        CHECK_EQ(merchant.canBlockBribe(), false);
        CHECK_EQ(governor.canBlockBribe(), false);
    }
}

/**
 * In this test case I will check all the methods of Baron
 */
TEST_CASE("Test Baron class methods")
{
    Baron baron("B");

    SUBCASE("Test invest method")
    {
        // the baron can invest if he has at least 3 coins and if he is in the game
        baron.setCoins(2); // doesn't have enough
        CHECK_THROWS(baron.invest());

        baron.setCoins(3); // has enough coins
        baron.setInGame(false); // but not in the game
        CHECK_THROWS(baron.invest());

        // valid settings
        baron.setInGame(true);
        CHECK_NOTHROW(baron.invest());

        // now check the logic of invest method
        // the baron has 50-50 chances to either lose the cost (3 coins) or get 6 back (extra 3)
        // we need to check both scenarios
        bool success = false, failed = false;
        while (!success && !failed)
        {
            baron.setCoins(4); // he has 4 coins
            baron.invest(); // make the investment

            // if he won
            if (baron.getCoins() > 4 && !success) // coins changed + check only 1 time
            {
                success = true;
                CHECK_EQ(baron.getCoins(), 7); // he had 4, paid 3, and go 6 back -> 4-3+6 = 7
            }

            // if he lost
            else if (baron.getCoins() < 4 && !failed) // coins change + check only 1 time
            {
                failed = true;
                CHECK_EQ(baron.getCoins(), 1); // he had 4 and lost the cost -> 4-3 = 1
            }
        }
    }

    SUBCASE("Test IsInvested")
    {
        // if the baron won the investment it returns true
        // and if he lost it returns false

        bool success = false, failed = false;
        while (!success && !failed)
        {
            baron.setCoins(4); // he has 4 coins
            baron.invest(); // make the investment

            // if he won
            if (baron.getCoins() > 4 && !success) // coins changed + check only 1 time
            {
                success = true;
                CHECK_EQ(baron.isInvested(), true); // he won -> true
            }

            // if he lost
            else if (baron.getCoins() < 4 && !failed) // coins change + check only 1 time
            {
                failed = true;
                CHECK_EQ(baron.isInvested(), false); // he lost -> false
            }
        }
    }

    SUBCASE("Test OnSanctioned")
    {
        // a baron gets 1 coin when he is being sanctioned
        // he has 0 coins now so he will get 1 coin

        baron.setCoins(0); // he has no coins
        baron.onSanctioned(); // got sanctioned
        CHECK_EQ(baron.getCoins(), 1); // got extra coin
    }
}

/**
 * In this test case I will check all the methods of General
 */
TEST_CASE("Test General class methods")
{
    General general("G");

    SUBCASE("Test OnArrested")
    {
        // when a General is being arrested he gets back the coin that was taken from him
        // IF he had coins
        general.onArrested(); // he has 0 coins -> he will not get back his coin
        CHECK_EQ(general.getCoins(), 0);

        // now test it with a coin
        general.setCoins(1);
        general.onArrested(); // he has 1 coin -> he will get back his coin
        CHECK_EQ(general.getCoins(), 1);
    }

    SUBCASE("Test preventCoup")
    {
        // a General can prevent a coup of other player if he has enough coins
        // he pays 5 coins and the other player losses his 7 coins and his turn
        // Note: the turn is managed by Game object and not in this method

        Player p("P", ""); // init a player
        general.setCoins(4); // he has not enough coins to prevent the coup
        CHECK_THROWS(general.preventCoup(p)); // let's assume p tried to coup

        general.setCoins(8); // now he has enough coins
        general.setInGame(false); // but he is not in the game
        CHECK_THROWS(general.preventCoup(p)); // let's assume p tried to coup

        // now set valid settings
        p.setCoins(8);
        general.setInGame(true);
        CHECK_NOTHROW(general.preventCoup(p)); // let's assume p tried to coup
        CHECK_EQ(general.getCoins(), 3); // he had 8 coins -> 8-5=3
        CHECK_EQ(p.getCoins(), 1); // p had 8 coins and he lost 7

        // NOTE:
        // in my implementation I did that p coups ONLY if all the valid generals in the game
        // decided not to block the action
        // this is why I don't do:
        // p.coup(coupedPlayer) -> general.preventCoup(p)
        // this is also the reason why I don't check if the couped player is still in the game or not
    }
}

/**
 * In this test case I will check all the methods of Governor
 */
TEST_CASE("Test Governor class methods")
{
    Governor governor("G");

    SUBCASE("Test tax method")
    {
        // when a Governor uses tax method he gets 3 coins instead of 2
        // as long as he is in the game and can perform financial actions (not sanctioned)

        // test when he is not in game
        governor.setInGame(false);
        CHECK_THROWS(governor.tax());

        // test when he can't perform financial actions
        governor.setInGame(true);
        governor.onSanctioned();
        CHECK_THROWS(governor.tax());

        // valid settings
        governor.setSettings();
        CHECK_NOTHROW(governor.tax());
        CHECK_EQ(governor.getCoins(), 3); // had 0 coins -> now he got 3
    }

    SUBCASE("Test canBlockTax method")
    {
        // Governor can block tax actions of other players as long as he is in the game

        // not in the game
        governor.setInGame(false);
        CHECK_THROWS(governor.canBlockTax());

        // in the game
        governor.setInGame(true);
        CHECK_EQ(governor.canBlockTax(), true);
    }
}

/**
 * In this test case I will check all the methods of Judge
 */
TEST_CASE("Test Judge class methods")
{
    Judge judge("J");

    SUBCASE("Test canBlockBribe")
    {
        // a Judge can block bribe of other active players as long as he is in the game

        // he is not in the game
        judge.setInGame(false);
        CHECK_THROWS(judge.canBlockBribe());

        // he is in the game
        judge.setInGame(true);
        CHECK_EQ(judge.canBlockBribe(), true);
    }

    // NOTE:
    // when a judge is being sanctioned the player who sanctioned him
    // needs to pay another coin IF he has one
    // I handled this case in sanction method of player
    // which means that the sanction method is responsible to take the extra coin
    // it was tested in the test of sanction
}

/**
 * In this test case I will check all the methods of Merchant
 */
TEST_CASE("Test Merchant class methods")
{
    Merchant merchant("M");

    SUBCASE("Test CheckEntitled method")
    {
        // a Merchant is entitled to get a coin for free if he has at least 3 coins in his turn
        // and if he is still in the game

        // he is not in the game
        merchant.setInGame(false);
        CHECK_THROWS(merchant.checkEntitled());

        // he is in the game // but has only 2 coins
        merchant.setInGame(true);
        merchant.setCoins(2); // not enough coins to be entitled
        CHECK_NOTHROW(merchant.checkEntitled()); // not entitled
        CHECK_EQ(merchant.getCoins(), 2); // didn't get the coin

        merchant.setCoins(3); // now he has 3 coins (the lowest amount required)
        CHECK_NOTHROW(merchant.checkEntitled()); //  entitled
        CHECK_EQ(merchant.getCoins(), 4); // got the coin -> 3+1 = 4
    }

    SUBCASE("Test OnArrest method")
    {
        // when a Merchant is being arrested he pays 2 coins to the cash box and not the player
        // who arrested him
        // if he had less than 2 - his coins set to 0

        merchant.onArrested(); // he has no coins
        CHECK_EQ(merchant.getCoins(), 0);

        merchant.setCoins(1);
        merchant.onArrested(); // he has 1 coin -> it will set to 0
        CHECK_EQ(merchant.getCoins(), 0);

        merchant.setCoins(2);
        merchant.onArrested(); // he has 2 coins -> it will set to 0
        CHECK_EQ(merchant.getCoins(), 0);

        merchant.setCoins(3);
        merchant.onArrested(); // he has 3 coins -> it will set to 1
        CHECK_EQ(merchant.getCoins(), 1);
    }
}

/**
 * In this test case I will check all the methods of Spy
 */
TEST_CASE("Test Spy class methods")
{
    Spy spy("S");
    Player p("P", "");

    SUBCASE("Test peek method")
    {
        // a Spy can peek a player and see their amount of coins and prevent from them to
        // use arrest in their next turn

        // not in the game
        spy.setInGame(false);
        CHECK_THROWS(spy.peek(p));
        CHECK_EQ(p.getCanArrest(), true); // p can arrest

        // now he is in the game
        spy.setInGame(true);
        CHECK_NOTHROW(spy.peek(p));
        CHECK_EQ(p.getCanArrest(), false); // p can not arrest

        // NOTE:
        // the restrictions on p will be removed after his turn
        // which is managed on Game object
        // the spy will get a popup window with the coins of p
        // which is also manged in the GUI
    }
}

/**
 * In this test case I will check all the methods of Game object
 */
TEST_CASE("Game")
{
    // create the object
    Game game({"p1", "p2", "p3"});
    vector<Player*> players = game.getCurrentPlayers();

    SUBCASE("Test Game constructor")
    {
        // the Game can not be initialized if there are less than 2 players
        // or more than 6 players
        // a player must have a name in order to be considered a player in the game

        // check with 1 player, less than 2
        CHECK_THROWS(Game({"p1"}));

        // check with 2 players but 1 is an empty name - only one player
        vector<string> names = {"p1", ""};
        CHECK_THROWS(Game(names)); // one of the players has no name -> throw exception

        // check with 3 players but 1 is an empty name -> 2 players in total
        names = {"p1", "p2", ""};
        CHECK_NOTHROW(Game(names)); // 2 valid players -> not an exception

        // check with 7 players
        CHECK_THROWS(Game({"p1","p2","p3","p4","p5","p6","p7"})); // more than 6

        // check with 7 players but one of them is an empty name, exactly 6 -> not an exception
        CHECK_NOTHROW(Game({"p1","p2","p3","","p5","p6","p7"}));

        // check all the other options -> 2-6 valid players
        names = {"p1", "p2"};
        CHECK_NOTHROW(Game(names)); // exactly 2 -> not an exception
        CHECK_NOTHROW(Game({"p1","p2","p3"})); // exactly 3 -> not an exception
        CHECK_NOTHROW(Game({"p1","p2","p3","p4"})); // exactly 4 -> not an exception
        CHECK_NOTHROW(Game({"p1","p2","p3","p4","p5"})); // exactly 5 -> not an exception
        CHECK_NOTHROW(Game({"p1","p2","p3","p4","p5","p6"})); // exactly 6 -> not an exception
    }

    SUBCASE("Test getActivePlayers method")
    {
        // this functions returns all the players that are active in the game
        // EXCLUDING the current play. this "list" will be given as a list of players that
        // the current player can perform actions on!
        // if all players are not active the game -> an empty vector will be returned

        // 3 active players in total and one of them is playing -> the vector will contain 2 players

        vector<Player*> activePlayers = game.getActivePlayers();
        CHECK_EQ(activePlayers.size(), 2); // p1 can perform actions on p2 or p3 (2 in total)
        // its p1's turn
        CHECK_EQ(activePlayers[0]->getInGame(), true);
        CHECK_EQ(activePlayers[0]->getName(), "p2");
        CHECK_EQ(activePlayers[1]->getInGame(), true);
        CHECK_EQ(activePlayers[1]->getName(), "p3");

        // now set p2 to be out of the game
        players[1]->setInGame(false);

        activePlayers = game.getActivePlayers(); // now only p3 will be here
        CHECK_EQ(activePlayers.size(), 1); // p1 can perform actions only on p3
        // its still p1's turn
        CHECK_EQ(activePlayers[0]->getInGame(), true);
        CHECK_EQ(activePlayers[0]->getName(), "p3");

        // now set p3 to be out of the game as well
        players[2]->setInGame(false);
        activePlayers = game.getActivePlayers(); // now no player will be added
        CHECK_EQ(activePlayers.size(), 0); // p1 can perform actions on nobody
    }

    SUBCASE("Test canBlockPlayers")
    {
        // init a new game with player and roles
        Governor* governor = new Governor("Go");
        General* general = new General("Ge");
        Judge* judge1 = new Judge("J1");
        Merchant* merchant = new Merchant("M");
        Judge* judge2 = new Judge("J2");

        vector<Player*> rolePlayers = {governor, general, judge1, merchant, judge2}; // turns order
        Game* game2 = new Game(rolePlayers);

        // everyone can block gather if they have enough coins (at least 3)
        general->setCoins(4); // has enough
        merchant->setCoins(2); // does not have enough
        judge1->setCoins(5); // has enough
        judge2->setCoins(3); // has enough

        // get all the players who can block
        vector<Player*> blockers = game2->canBlockPlayers("", 3);
        // "" represents no role needed, 3 is the cost to block
        // a total of 3 players can block - the spy and the two judges
        CHECK_EQ(blockers.size(), 3);
        CHECK_EQ(blockers[0]->getInGame(), true);
        CHECK_EQ(blockers[0]->getName(), "Ge");
        CHECK_EQ(blockers[1]->getInGame(), true);
        CHECK_EQ(blockers[1]->getName(), "J1");
        CHECK_EQ(blockers[2]->getInGame(), true);
        CHECK_EQ(blockers[2]->getName(), "J2");

        // let's test the block tax now, only governor can do it, it costs 0
        // but this is still his turn so he can't block himself -> no one will match!
        blockers = game2->canBlockPlayers("Governor", 0);
        CHECK_EQ(blockers.size(), 0); // no one can block

        // now let's move 1 turn forward and now governor will be able to block
        game2->nextTurn();
        blockers = game2->canBlockPlayers("Governor", 0);
        CHECK_EQ(blockers.size(), 1);
        CHECK_EQ(blockers[0]->getInGame(), true);
        CHECK_EQ(blockers[0]->getName(), "Go");

        // and if the governor will be eliminated -> no one will be able to block
        governor->setInGame(false);
        blockers = game2->canBlockPlayers("Governor", 0);
        CHECK_EQ(blockers.size(), 0); // no one can block

        // now let's test bribe, only a judge can do so and it costs 0 coins
        blockers = game2->canBlockPlayers("Judge", 0);
        CHECK_EQ(blockers.size(), 2); // 2 judges and it's not their turn
        CHECK_EQ(blockers[0]->getInGame(), true);
        CHECK_EQ(blockers[0]->getName(), "J1");
        CHECK_EQ(blockers[1]->getInGame(), true);
        CHECK_EQ(blockers[1]->getName(), "J2");

        game2->nextTurn(); // now it's J1's turn
        blockers = game2->canBlockPlayers("Judge", 0);
        CHECK_EQ(blockers.size(), 1); // only J2 can block
        CHECK_EQ(blockers[0]->getInGame(), true);
        CHECK_EQ(blockers[0]->getName(), "J2");

        // and if J2 is not in the game -> no one can block
        judge2->setInGame(false);
        blockers = game2->canBlockPlayers("Judge", 0);
        CHECK_EQ(blockers.size(), 0); // no one can block

        // let's check General now - he can block a coup, it costs 5 coins
        general->setCoins(4); // he has not enough coins
        blockers = game2->canBlockPlayers("General", 5);
        CHECK_EQ(blockers.size(), 0); // no one can block - general too poor

        // now set him with enough coins but not in the game
        general->setInGame(false);
        general->setCoins(5);
        blockers = game2->canBlockPlayers("General", 5);
        CHECK_EQ(blockers.size(), 0); // no one can block - general too poor

        // now set him with good settings
        general->setInGame(true);
        blockers = game2->canBlockPlayers("General", 5);
        CHECK_EQ(blockers.size(), 1); // no one can block - general too poor
        CHECK_EQ(blockers[0]->getName(), "Ge");

        // free the memory
        delete game2;
    }

    SUBCASE("Test allowedActions method")
    {
        // NOTE:
        // this method just calls player->showActions which is checked and tested
        // in the player class methods!
        // therefore there is nothing to check in this function
    }

    SUBCASE("Test nextTurn function")
    {
        // this function manages and controls the turns logic
        // if a player supposes to have another turn (for example after bribe)
        // it gives him another turn(s)

        // after a "regular" action -> the next alive player will be picked
        Governor* governor = new Governor("Go");
        Spy* spy = new Spy("S");
        Judge* judge = new Judge("J");
        Merchant* merchant = new Merchant("M");

        vector<Player*> rolePlayers = {governor, spy, judge, merchant}; // turns order
        Game* game3 = new Game(rolePlayers);

        // set spy to be out of the game -> judge will be the next player to play
        spy->setInGame(false);
        game3->nextTurn(); // spy is out
        CHECK_EQ(game3->getCurrentPlayer().getName(), "J");

        // now judge bribes -> he has two turns
        judge->setCoins(4); // enough coins to bribe
        game3->bribeHandel();
        game3->nextTurn(); // judge's turn
        CHECK_EQ(game3->getCurrentPlayer().getName(), "J");
        game3->nextTurn(); // again judge's turn
        CHECK_EQ(game3->getCurrentPlayer().getName(), "J");
        game3->nextTurn(); // move to the next player -> Merchant
        CHECK_EQ(game3->getCurrentPlayer().getName(), "M");

        // if only 1 player remaining -> a winner window will appear in the GUI
        // and this function just returns to the GUI

        // free memory
        delete game3;
    }

    SUBCASE("Test IsGameOver method")
    {
        // if only 1 player remaining the function returns true
        // else it returns false

        // all 3 players are alive
        CHECK_EQ(players.size(), 3);
        CHECK_EQ(players[0]->getInGame(), true);
        CHECK_EQ(players[1]->getInGame(), true);
        CHECK_EQ(players[2]->getInGame(), true);
        CHECK_EQ(game.IsGameOver(), false); // false, 3 remained

        // 1 player couped
        players[0]->setInGame(false);
        CHECK_EQ(players.size(), 3);
        CHECK_EQ(players[0]->getInGame(), false);
        CHECK_EQ(players[1]->getInGame(), true);
        CHECK_EQ(players[2]->getInGame(), true);
        CHECK_EQ(game.IsGameOver(), false); // false, 2 remained

        // 2 players couped
        players[0]->setInGame(false);
        players[1]->setInGame(false);
        CHECK_EQ(players.size(), 3);
        CHECK_EQ(players[0]->getInGame(), false);
        CHECK_EQ(players[1]->getInGame(), false);
        CHECK_EQ(players[2]->getInGame(), true);
        CHECK_EQ(game.IsGameOver(), true); // true, 1 remained
    }

    SUBCASE("HANDLERS")
    {
        // NOTE:
        // all the handlers (except bribe and peek) just make the call to the
        // related method in Player class - which is checked and tested there
        // I will test only bribe and peek

        // after a bribe action, the field 'anotherTurns' is set to 2
        // which means 2 turns are left to the current player to make

        Governor* governor = new Governor("Go");
        Spy* spy = new Spy("S");
        Judge* judge = new Judge("J");
        Merchant* merchant = new Merchant("M");

        vector<Player*> rolePlayers = {governor, spy, judge, merchant}; // turns order
        Game* game4 = new Game(rolePlayers);

        // no one used any action
        CHECK_EQ(game4->getAnotherTurns(), 0);
        governor->setCoins(4); // the cost of bribe
        game4->bribeHandel(); // the first player has 2 turns
        CHECK_EQ(game4->getAnotherTurns(), 2); // 2 turns left
        game4->nextTurn(); // move to the next turn -> minus 1 turns 2-1 = 1
        CHECK_EQ(game4->getAnotherTurns(), 1); // 1 turn left
        game4->nextTurn(); // move to the next turn -> minus 1 turns = 1-1 = 0
        CHECK_EQ(game4->getAnotherTurns(), 0); // no more turn to make

        // it costs nothing and not considered as a turn
        game4->nextTurn(); // now its spy's turn
        game4->peekHandle(*governor);
        CHECK_EQ(game4->getAnotherTurns(), 1); // no more turn to make

        // now he gets a bribe block
        game4->nextTurn(); // still spy's turn
        spy->setCoins(5); // enough coins to afford bribe
        game4->blockBribeHandle(); // got a bribe block
        CHECK_EQ(game4->getAnotherTurns(), 1);
        CHECK_EQ(spy->getCoins(), 1); // he got 1 coin left (5-4 = 1)

        // free memory
        delete game4;
    }

    // now let's test the required methods
    SUBCASE("Test turn method")
    {
        // NOTE:
        // this method just prints the name of the current player
        // there is nothing to check here
    }

    SUBCASE("Test players method")
    {
        // this function returns the names of all the players in the game

        // players p1, p2 and p3 are in the game -> all of them will be in the vector
        vector<string> activePlayers = game.players();
        CHECK_EQ(activePlayers.size(), 3);
        CHECK_EQ(activePlayers.at(0), "p1");
        CHECK_EQ(activePlayers.at(1), "p2");
        CHECK_EQ(activePlayers.at(2), "p3");

        // players p1 and p2 in the game and p3 out
        players[2]->setInGame(false);
        activePlayers = game.players();
        CHECK_EQ(activePlayers.size(), 2);
        CHECK_EQ(activePlayers.at(0), "p1");
        CHECK_EQ(activePlayers.at(1), "p2");

        // only p1 in the game
        players[1]->setInGame(false);
        activePlayers = game.players();
        CHECK_EQ(activePlayers.size(), 1);
        CHECK_EQ(activePlayers.at(0), "p1");

        // no one in the game
        players[0]->setInGame(false);
        activePlayers = game.players();
        CHECK_EQ(activePlayers.size(), 0);
    }

    SUBCASE("Test winner method")
    {
        // this function returns the name of the winner if there is one
        // else -> throws

        // p1, p2 and p3 are in the game -> no winner -> throws
        CHECK_THROWS(game.winner());

        // coup p1 -> p2 and p3 still in the game
        players[0]->setInGame(false);
        CHECK_THROWS(game.winner()); // still throws

        // coup p2 -> only p3 in the game
        players[1]->setInGame(false);
        CHECK_NOTHROW(game.winner()); // we have a winner - p3
        CHECK_EQ(game.winner(), "p3"); // check if it returns the name
    }
}