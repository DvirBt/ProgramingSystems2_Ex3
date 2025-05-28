// dvirbto@gmail.com

#include <iostream>
#include <stdexcept>
#include <vector>

#include "Game.hpp"
#include "Roles/Baron.h"
#include "Roles/General.h"
#include "Roles/Governor.h"
#include "Roles/Judge.h"
#include "Roles/Merchant.h"
#include "Roles/Player.h"
#include "Roles/Spy.h"

using namespace std;

/**
 * This function prints the current player's name, coins and his action.
 * @param game the game object.
 * @param action the action that the player chose to do.
 */
void printTurn(const Game* game, string action)
{
    game->turn(); // print name
    cout << "Role: " << game->getCurrentPlayer().getRole() << endl;
    cout << "Coins:" << game->getCurrentPlayer().getCoins() << endl; // print coins
    cout << action << " performed!" << endl << endl;
}

/**
* This is a Demo of the game "Coup"
*/
int main()
{
    cout << endl;
    cout << "----------------------------" << endl;
    cout << "This is the Demo of the game" << endl;
    cout << "----------------------------" << endl << endl;
    cout << "Players" << endl;
    cout << "-------" << endl;
    cout << "1. Dvir" << endl;
    cout << "2. Shaked" << endl;
    cout << "3. David" << endl;
    cout << "4. Alon" << endl << endl;
    cout << "Start begins" << endl;
    cout << "------------" << endl << endl;

    // init players
    General* general = new General("Dvir");
    Spy* spy = new Spy("Shaked");
    Merchant* merchant = new Merchant("David");
    Governor* governor = new Governor("Alon");
    vector<Player*> players {general, spy, merchant , governor};
    Game* game = new Game(players);


    // all gathers
    // Dvir
    printTurn(game, "Gather");
    game->gatherHandle();
    game->nextTurn();

    // Shaked
    printTurn(game, "Gather");
    game->gatherHandle();
    game->nextTurn();

    // David
    printTurn(game, "Gather");
    game->gatherHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Gather");
    game->gatherHandle();
    game->nextTurn();

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Shaked
    printTurn(game, "Peeked David");
    game->peekHandle(*merchant);
    cout << endl;
    game->nextTurn();

    // still Shaked's turn
    printTurn(game, "Tax");
    // spy->tax();  Alon (Governor) chooses to block (next turn)
    cout << "Shaked Taxed but got blocked by Alon" << endl << endl;
    game->nextTurn();

    // David
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Shaked
    printTurn(game, "Arrested Alon");
    game->arrestHandle(*governor);
    game->nextTurn();

    // David
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Arrested Dvir");
    game->arrestHandle(*general);
    game->nextTurn();

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Shaked
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // David
    printTurn(game, "Couped Shaked");
    game->coupHandle(*spy);
    game->nextTurn();

    // Alon
    printTurn(game, "Bribe");
    game->bribeHandel();
    game->nextTurn();

    // Alon
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Arrested David");
    game->arrestHandle(*merchant);
    game->nextTurn();

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // David
    printTurn(game, "Tax blocked by Alon");
    //game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Dvir
    printTurn(game, "Couped David");
    game->coupHandle(*merchant);
    game->nextTurn();

    // Alon
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Coup Dvir");
    cout << "Coup blocked by Dvir performed!" << endl;
    game->preventCoupHandle(general); //
    game->nextTurn();
    cout << endl;

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Bribe");
    game->bribeHandel();
    game->nextTurn();

    // Alon
    printTurn(game, "Arrested Dvir");
    game->arrestHandle(*general);
    game->nextTurn();

    // Alon
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Gather");
    game->gatherHandle();
    game->nextTurn();

    // Dvir
    printTurn(game, "Tax");
    game->taxHandle();
    game->nextTurn();

    // Alon
    printTurn(game, "Arrested Dvir");
    game->arrestHandle(*general);
    game->nextTurn();

    // Dvir
    printTurn(game, "Couped Alon");
    game->coupHandle(*governor);
    game->nextTurn();

    cout << "The winner is: " << game->winner() << endl << endl;

    // free the memory
    delete game;
    return 0;
}