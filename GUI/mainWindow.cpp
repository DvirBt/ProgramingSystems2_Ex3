// dvirbto@gmail.com

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
//#include "mainWindow.hpp"
#include <functional>
#include "../Game.hpp"
#include "../Roles/Baron.h"

struct ActionButton {
    sf::RectangleShape shape;
    sf::Text label;
    std::string action;
};

// a window to select a player out of a list
Player* showSelectPlayerWindow(sf::Font& font, const std::vector<Player*>& activePlayers) {
    sf::RenderWindow selectWin(sf::VideoMode(400, 100 + 60 * activePlayers.size()), "Select Player");
    selectWin.setFramerateLimit(60);
    sf::Color bgColor(245, 245, 245);

    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> labels;

    for (size_t i = 0; i < activePlayers.size(); ++i) {
        sf::RectangleShape button(sf::Vector2f(300, 40));
        button.setFillColor(sf::Color(100, 149, 237));
        button.setPosition(50, 30 + i * 60);
        buttons.push_back(button);

        sf::Text label(activePlayers[i]->getName(), font, 20);
        label.setFillColor(sf::Color::White);
        label.setPosition(
            button.getPosition().x + 150 - label.getGlobalBounds().width / 2,
            button.getPosition().y + 8
        );
        labels.push_back(label);
    }

    while (selectWin.isOpen()) {
        sf::Event event;
        while (selectWin.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                selectWin.close();
                return nullptr;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                for (size_t i = 0; i < buttons.size(); ++i) {
                    if (buttons[i].getGlobalBounds().contains(mousePos)) {
                        selectWin.close();
                        return activePlayers[i];
                    }
                }
            }
        }

        selectWin.clear(bgColor);
        for (size_t i = 0; i < buttons.size(); ++i) {
            selectWin.draw(buttons[i]);
            selectWin.draw(labels[i]);
        }
        selectWin.display();
    }

    return nullptr;
}

// a popup window that shows all the active players
std::vector<std::string> showPlayersWindow(sf::Font& font) {
    sf::RenderWindow playerWin(sf::VideoMode(600, 700), "Players");
    playerWin.setFramerateLimit(60);
    sf::Color bgColor(240, 248, 255);

    int playerCount = 2;
    const int minPlayers = 2, maxPlayers = 6;
    std::vector<std::string> playerNames(playerCount, "");

    int activeBox = -1; // Index of selected text box

    sf::Text title("Players", font, 36);
    title.setFillColor(sf::Color(0, 51, 102));
    title.setPosition(300 - title.getGlobalBounds().width / 2, 30);

    // + and - buttons
    sf::RectangleShape plusBtn({40, 40});
    plusBtn.setFillColor(sf::Color(60, 179, 113));
    plusBtn.setPosition(400, 560);

    sf::Text plusText("+", font, 28);
    plusText.setFillColor(sf::Color::White);
    plusText.setPosition(plusBtn.getPosition().x + 10, plusBtn.getPosition().y + 2);

    sf::RectangleShape minusBtn({40, 40});
    minusBtn.setFillColor(sf::Color(220, 20, 60));
    minusBtn.setPosition(160, 560);

    sf::Text minusText("-", font, 28);
    minusText.setFillColor(sf::Color::White);
    minusText.setPosition(minusBtn.getPosition().x + 13, minusBtn.getPosition().y + 2);

    // Submit button
    sf::RectangleShape submitBtn({200, 50});
    submitBtn.setFillColor(sf::Color(0, 120, 215));
    submitBtn.setPosition(200, 620);

    sf::Text submitText("Submit", font, 24);
    submitText.setFillColor(sf::Color::White);
    submitText.setPosition(
        submitBtn.getPosition().x + 100 - submitText.getGlobalBounds().width / 2,
        submitBtn.getPosition().y + 10
    );

    while (playerWin.isOpen()) {
        sf::Event event;
        while (playerWin.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                playerWin.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                activeBox = -1;

                for (int i = 0; i < playerCount; ++i) {
                    sf::FloatRect boxBounds(200, 100 + i * 60, 300, 35);
                    if (boxBounds.contains(mousePos)) {
                        activeBox = i;
                        break;
                    }
                }

                if (plusBtn.getGlobalBounds().contains(mousePos) && playerCount < maxPlayers) {
                    playerCount++;
                    playerNames.emplace_back("");
                }

                if (minusBtn.getGlobalBounds().contains(mousePos) && playerCount > minPlayers) {
                    playerCount--;
                    playerNames.pop_back();
                }

                if (submitBtn.getGlobalBounds().contains(mousePos)) {
                    playerWin.close();
                    return playerNames;
                }
            }

            if (event.type == sf::Event::TextEntered && activeBox != -1) {
                if (event.text.unicode == '\b') {
                    if (!playerNames[activeBox].empty())
                        playerNames[activeBox].pop_back();
                } else if (event.text.unicode < 128 && event.text.unicode >= 32) {
                    playerNames[activeBox] += static_cast<char>(event.text.unicode);
                }
            }
        }

        playerWin.clear(bgColor);
        playerWin.draw(title);

        for (int i = 0; i < playerCount; ++i) {
            sf::Text label("Player " + std::to_string(i + 1) + ":", font, 20);
            label.setFillColor(sf::Color::Black);
            label.setPosition(100, 100 + i * 60);

            sf::RectangleShape box({300, 35});
            box.setFillColor(sf::Color::White);
            box.setOutlineColor(i == activeBox ? sf::Color::Blue : sf::Color::Black);
            box.setOutlineThickness(2);
            box.setPosition(200, 100 + i * 60);

            sf::Text inputText(playerNames[i], font, 20);
            inputText.setFillColor(sf::Color::Black);
            inputText.setPosition(205, 105 + i * 60);

            playerWin.draw(label);
            playerWin.draw(box);
            playerWin.draw(inputText);
        }

        playerWin.draw(plusBtn);
        playerWin.draw(plusText);
        playerWin.draw(minusBtn);
        playerWin.draw(minusText);
        playerWin.draw(submitBtn);
        playerWin.draw(submitText);
        playerWin.display();
    }

    return playerNames;
}

// opens a popup window for each player who can block the current action
Player* showBlockWindow(sf::Font& font, const std::vector<Player*>& blockers) {
    for (Player* blocker : blockers) {
        sf::RenderWindow blockWin(sf::VideoMode(400, 200), blocker->getName() + " - Block?");
        blockWin.setFramerateLimit(60);
        blockWin.setPosition(sf::Vector2i(200, 200)); // ensure visibility

        sf::Color bgColor(255, 255, 255);

        // Prompt text
        sf::Text prompt(blocker->getName() + ", would you like to block?", font, 24);
        prompt.setFillColor(sf::Color::Black);
        prompt.setPosition(400 / 2 - prompt.getGlobalBounds().width / 2, 30);

        // Yes button
        sf::RectangleShape yesBtn(sf::Vector2f(120, 50));
        yesBtn.setFillColor(sf::Color(60, 179, 113));
        yesBtn.setPosition(50, 120);

        sf::Text yesText("Yes", font, 20);
        yesText.setFillColor(sf::Color::White);
        yesText.setPosition(
            yesBtn.getPosition().x + 60 - yesText.getGlobalBounds().width / 2,
            yesBtn.getPosition().y + 10
        );

        // No button
        sf::RectangleShape noBtn(sf::Vector2f(120, 50));
        noBtn.setFillColor(sf::Color(220, 20, 60));
        noBtn.setPosition(230, 120);

        sf::Text noText("No", font, 20);
        noText.setFillColor(sf::Color::White);
        noText.setPosition(
            noBtn.getPosition().x + 60 - noText.getGlobalBounds().width / 2,
            noBtn.getPosition().y + 10
        );

        while (blockWin.isOpen()) {
            sf::Event event;
            while (blockWin.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    blockWin.close();
                    break;
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                    if (yesBtn.getGlobalBounds().contains(mousePos)) {
                        blockWin.close();
                        return blocker;
                    }

                    if (noBtn.getGlobalBounds().contains(mousePos)) {
                        blockWin.close();
                        break;
                    }
                }
            }

            blockWin.clear(bgColor);
            blockWin.draw(prompt);
            blockWin.draw(yesBtn);
            blockWin.draw(yesText);
            blockWin.draw(noBtn);
            blockWin.draw(noText);
            blockWin.display();
        }
    }

    return nullptr; // nobody blocked
}

// opens a popup window with the name of the winner
void showWinnerWindow(sf::Font& font, const std::string& winnerName) {
    sf::RenderWindow winWindow(sf::VideoMode(400, 250), "Game Over");
    winWindow.setFramerateLimit(60);
    sf::Color bgColor(255, 255, 255);

    // Title text
    sf::Text title("The winner is", font, 28);
    title.setFillColor(sf::Color(20, 40, 80));
    title.setPosition(200 - title.getGlobalBounds().width / 2, 30);

    // Winner name
    sf::Text winnerText(winnerName, font, 32);
    winnerText.setFillColor(sf::Color(60, 179, 113));
    winnerText.setPosition(200 - winnerText.getGlobalBounds().width / 2, 80);

    // Exit button
    sf::RectangleShape exitBtn(sf::Vector2f(200, 50));
    exitBtn.setFillColor(sf::Color(220, 20, 60));
    exitBtn.setPosition(100, 160);

    sf::Text exitText("Exit", font, 24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(
        exitBtn.getPosition().x + 100 - exitText.getGlobalBounds().width / 2,
        exitBtn.getPosition().y + 10
    );

    while (winWindow.isOpen()) {
        sf::Event event;
        while (winWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                winWindow.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (exitBtn.getGlobalBounds().contains(mousePos)) {
                    winWindow.close();
                    std::exit(0); // Exit entire program
                }
            }
        }

        winWindow.clear(bgColor);
        winWindow.draw(title);
        winWindow.draw(winnerText);
        winWindow.draw(exitBtn);
        winWindow.draw(exitText);
        winWindow.display();
    }
}

// opens a popup window with the active players who can be peeked by the current player (Spy)
void showSpyWindow(sf::Font& font, Player* targetPlayer) {
    sf::RenderWindow spyWin(sf::VideoMode(400, 250), "Spy Report");
    spyWin.setFramerateLimit(60);
    sf::Color bgColor(245, 245, 245);

    std::string name = targetPlayer->getName();
    int coins = targetPlayer->getCoins();

    // Title Text
    sf::Text title("Player " + name + " has " + std::to_string(coins) + " coins!", font, 20);
    title.setFillColor(sf::Color::Black);
    title.setPosition(400 / 2 - title.getGlobalBounds().width / 2, 50);

    // Info Text
    sf::Text info(name + " cannot arrest for the next turn!", font, 18);
    info.setFillColor(sf::Color(80, 0, 0));
    info.setPosition(400 / 2 - info.getGlobalBounds().width / 2, 100);

    // Exit Button
    sf::RectangleShape exitBtn(sf::Vector2f(120, 40));
    exitBtn.setFillColor(sf::Color(220, 20, 60));
    exitBtn.setPosition(140, 170);

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(
        exitBtn.getPosition().x + 60 - exitText.getGlobalBounds().width / 2,
        exitBtn.getPosition().y + 7
    );

    while (spyWin.isOpen()) {
        sf::Event event;
        while (spyWin.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                spyWin.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (exitBtn.getGlobalBounds().contains(mousePos)) {
                    spyWin.close();
                }
            }
        }

        spyWin.clear(bgColor);
        spyWin.draw(title);
        spyWin.draw(info);
        spyWin.draw(exitBtn);
        spyWin.draw(exitText);
        spyWin.display();
    }
}

// opens a popup window with the result of the investment made by the current player (Baron)
void showBaronWindow(sf::Font& font, bool investmentSuccess) {
    sf::RenderWindow baronWin(sf::VideoMode(400, 200), "Baron Investment");
    baronWin.setFramerateLimit(60);
    sf::Color bgColor(250, 250, 240);

    std::string titleText = investmentSuccess ? "Investment succeeded!" : "Investment failed!";
    std::string messageText = investmentSuccess ? "You won 6 coins!" : "You did not win any coins!";

    // Title
    sf::Text title(titleText, font, 22);
    title.setFillColor(investmentSuccess ? sf::Color::Green : sf::Color(180, 0, 0));
    title.setPosition(400 / 2 - title.getGlobalBounds().width / 2, 50);

    // Message
    sf::Text message(messageText, font, 18);
    message.setFillColor(sf::Color::Black);
    message.setPosition(400 / 2 - message.getGlobalBounds().width / 2, 90);

    // Exit Button
    sf::RectangleShape exitBtn(sf::Vector2f(120, 40));
    exitBtn.setFillColor(sf::Color(100, 149, 237));  // Cornflower Blue
    exitBtn.setPosition(140, 140);

    sf::Text exitText("Exit", font, 20);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(
        exitBtn.getPosition().x + 60 - exitText.getGlobalBounds().width / 2,
        exitBtn.getPosition().y + 7
    );

    while (baronWin.isOpen()) {
        sf::Event event;
        while (baronWin.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                baronWin.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (exitBtn.getGlobalBounds().contains(mousePos)) {
                    baronWin.close();
                }
            }
        }

        baronWin.clear(bgColor);
        baronWin.draw(title);
        baronWin.draw(message);
        baronWin.draw(exitBtn);
        baronWin.draw(exitText);
        baronWin.display();
    }
}

// create buttons
void createActionButtons(const std::vector<std::string>& actions, sf::Font& font, std::vector<ActionButton>& buttons);

// the main window
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Coup Game");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("GUI/Assets/fonts/static/OpenSans-Italic.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::Color backgroundColor(173, 216, 230);

    sf::Text currentPlayerText("", font, 24);
    currentPlayerText.setFillColor(sf::Color::Black);
    currentPlayerText.setPosition(20, 550);

    sf::Text currentCoinsText("", font, 24);
    currentCoinsText.setFillColor(sf::Color::Black);
    currentCoinsText.setPosition(600, 550);

    sf::Text title("Let's play Coup!", font, 48);
    title.setFillColor(sf::Color(20, 40, 80));
    title.setPosition(400 - title.getGlobalBounds().width / 2, 50);

    sf::RectangleShape startButton(sf::Vector2f(300, 60));
    startButton.setFillColor(sf::Color(40, 20, 50));
    startButton.setPosition(250, 200);

    sf::Text startText("Start Game", font, 24);
    startText.setFillColor(sf::Color::White);
    startText.setPosition(
        startButton.getPosition().x + 150 - startText.getGlobalBounds().width / 2,
        startButton.getPosition().y + 15
    );

    sf::RectangleShape exitButton(sf::Vector2f(300, 60));
    exitButton.setFillColor(sf::Color(220, 20, 60));
    exitButton.setPosition(250, 300);

    sf::Text exitText("Exit", font, 24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(
        exitButton.getPosition().x + 150 - exitText.getGlobalBounds().width / 2,
        exitButton.getPosition().y + 15
    );

    bool inGame = false;
    Game* game = nullptr;
    std::vector<ActionButton> actionButtons;
    std::vector<std::string> lastActions;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if (!inGame) {
                    if (startButton.getGlobalBounds().contains(mousePos)) {
                        auto players = showPlayersWindow(font);
                        for (const auto& name : players) {
                            if (name != "")
                                std::cout << "Player: " << name << '\n';
                        }

                        game = new Game(players);
                        game->turn(); // print the name of the current player
                        currentPlayerText.setString("Current Player: " + game->getCurrentPlayer().getName() + " - " + game->getCurrentPlayer().getRole());
                        currentCoinsText.setString("Coins: " + std::to_string(game->getCurrentPlayer().getCoins()));
                        lastActions = game->allowedActions();
                        createActionButtons(lastActions, font, actionButtons);
                        inGame = true;
                    }

                    if (exitButton.getGlobalBounds().contains(mousePos)) {
                        window.close();
                    }
                } else {
                    for (const auto& btn : actionButtons) {
                        if (btn.shape.getGlobalBounds().contains(mousePos)) {
                            std::cout << "Action selected: " << btn.action << '\n';
                            if (btn.action == "Gather") {
                                std::vector<Player*> blockers = game->canBlockPlayers("", 3);
                                Player* blocker = showBlockWindow(font, blockers);
                                if (blocker) {
                                    std::cout << blocker->getName() << " chose to block!\n";
                                    blocker->sanction(game->getCurrentPlayer());
                                } else {
                                    std::cout << "Gather performed!.\n";
                                    game->gatherHandle();
                                }

                            } else if (btn.action == "Tax") {
                                std::vector<Player*> blockers = game->canBlockPlayers("Governor", 0);
                                Player* blocker = showBlockWindow(font, blockers);
                                if (blocker) {
                                    std::cout << blocker->getName() << " chose to block!\n";
                                } else {
                                    std::cout << "Tax performed!.\n";
                                    game->taxHandle();
                                }

                            } else if (btn.action == "Peek") {
                                Player* chosen = showSelectPlayerWindow(font, game->getActivePlayers());
                                game->peekHandle(*chosen);
                                showSpyWindow(font, chosen);  // open spy window
                                std::cout << "Peek performed!.\n";

                            } else if (btn.action == "Invest") {
                                std::cout << "Invest performed!.\n";
                                bool result = game->investHandle();
                                showBaronWindow(font, result);

                            } else if (btn.action == "Bribe") {
                                std::vector<Player*> blockers = game->canBlockPlayers("Judge", 0);
                                Player* blocker = showBlockWindow(font, blockers);
                                if (blocker) {
                                    std::cout << blocker->getName() << " chose to block!\n";
                                    game->blockBribeHandle();
                                } else {
                                    std::cout << "Bribe performed!.\n";
                                    game->bribeHandel();
                                }

                            } else if (btn.action == "Arrest") {
                                Player* chosen = showSelectPlayerWindow(font, game->getActivePlayers());
                                game->arrestHandle(*chosen);

                            } else if (btn.action == "Sanction") {
                                Player* chosen = showSelectPlayerWindow(font, game->getActivePlayers());
                                game->sanctionHandle(*chosen);

                            } else if (btn.action == "Coup") {
                                Player* chosen = showSelectPlayerWindow(font, game->getActivePlayers());
                                std::vector<Player*> blockers = game->canBlockPlayers("General", 5);
                                Player* blocker = showBlockWindow(font, blockers);
                                if (blocker) {
                                    std::cout << blocker->getName() << " chose to block!\n";
                                    game->preventCoupHandle(blocker);
                                } else {
                                    std::cout << "Coup performed!.\n";
                                    game->coupHandle(*chosen);
                                }
                            }
                            
                            game->nextTurn(); // next turn
                            if (game->IsGameOver())
                                showWinnerWindow(font, game->winner());

                            game->turn(); // print the name of the current player
                            currentPlayerText.setString("Current Player: " + game->getCurrentPlayer().getName() + " - " + game->getCurrentPlayer().getRole());
                            currentCoinsText.setString("Coins: " + std::to_string(game->getCurrentPlayer().getCoins()));
                            lastActions = game->allowedActions();
                            createActionButtons(lastActions, font, actionButtons);

                            break;
                        }
                    }
                }
            }
        }


        window.clear(backgroundColor);

        if (!inGame) {
            window.draw(title);
            window.draw(startButton);
            window.draw(startText);
            window.draw(exitButton);
            window.draw(exitText);
        } else if (game != nullptr) {
            title.setString("Choose an action");
            title.setPosition(400 - title.getGlobalBounds().width / 2, 20);
            window.draw(title);
            window.draw(currentPlayerText);
            window.draw(currentCoinsText);

            auto currentActions = game->allowedActions();
            if (currentActions != lastActions) {
                lastActions = currentActions;
                createActionButtons(currentActions, font, actionButtons); // CHANGED HERE currentActions
            }

            for (const auto& btn : actionButtons) {
                window.draw(btn.shape);
                window.draw(btn.label);
            }
        }

        window.display();
    }

    delete game;
    return 0;
}

// create action buttons
void createActionButtons(const std::vector<std::string>& actions, sf::Font& font, std::vector<ActionButton>& buttons) {
    buttons.clear();

    float buttonWidth = 200;
    float buttonHeight = 50;
    float spacing = 20;
    float totalHeight = actions.size() * (buttonHeight + spacing) - spacing;
    float startY = 325 - totalHeight / 2;

    for (size_t i = 0; i < actions.size(); ++i) {
        ActionButton btn;
        btn.action = actions[i];

        btn.shape.setSize({buttonWidth, buttonHeight});
        btn.shape.setFillColor(sf::Color(100, 149, 237));
        btn.shape.setPosition(300, startY + i * (buttonHeight + spacing));

        btn.label.setFont(font);
        btn.label.setString(actions[i]);
        btn.label.setCharacterSize(20);
        btn.label.setFillColor(sf::Color::White);
        btn.label.setPosition(
            btn.shape.getPosition().x + (buttonWidth - btn.label.getGlobalBounds().width) / 2,
            btn.shape.getPosition().y + 10
        );

        buttons.push_back(btn);
    }
}
