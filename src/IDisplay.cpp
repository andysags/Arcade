/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** IDisplay.cpp
*/

#include "../include/Interface/IDisplay.hpp"
#include <iostream>
#include "../include/Interface/DLLoader.hpp"
#include "../include/Interface/Error.hpp"
#include "../include/Interface/IDisplay.hpp"
#include "../include/Interface/IGames.hpp"
#include "../include/Interface/IGraphic.hpp"
#include "../include/Graphics/ncurses.hpp"
#include "../include/Graphics/sdl.hpp"
#include "../include/Graphics/sfml.hpp"
#include "../include/Interface/ScoreManager.hpp"
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

std::string askPlayerName()
{
    std::string name;
    std::cout << "Entrez votre nom de joueur: ";
    std::getline(std::cin, name);
    return name;
}

void ScoreManager::saveScore(const std::string &gameName, const std::string &playerName, int score)
{
    std::ofstream outFile("Score", std::ios::app);
    if (!outFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }
    
    outFile <<gameName + "   " +  playerName + "   " << score << std::endl;
    outFile.close();
}

void IDisplay::print(IGraphic *module, int h, std::string PlayerName)
{
    std::ifstream file("Score");
    std::ostringstream scr;
    std::string line;
    int i = 0;
    module->drawSprite(0, 0, "resources/assets/back.png");
    if (!file.is_open()) {
        std::ofstream outFile("Score", std::ios::app);
    } else {
        scr << file.rdbuf();
        std::istringstream input(scr.str());
        while (std::getline(input, line)) {
            module->drawText(line, 850, 200 + i, 0);
            i += 30;
        }
    }

    module->drawText("Nom du joueur: " + PlayerName, 100, 100, 0);
    module->drawText("Librairies graphiques :", 100, 150, 0);
    module->drawText(h == 0 ? "> SFML" : "SFML", 100, 190, 0);
    module->drawText(h == 1 ? "> SDL" : "SDL", 100, 230, 0);
    module->drawText(h == 2 ? "> Ncurses" : "Ncurses", 100, 270, 0);
    module->drawText("ARCADE --CORE DHF :", 850, 10, 0);
    module->drawText("Score", 900, 150, 0);
    module->drawText("Liste des jeux :", 1500, 150, 0);
    module->drawText("Commandes :", 200, 500, 0);
    module->drawText("Appuyez sur Esc pour fermer la fenetre.", 60, 550, 0);
    module->drawText("Appuyez sur F2 ou F3 pour changer de graphisme.", 60, 600, 0);
    module->drawText("Appuyez sur F6 ou F7 pour changer de jeux.", 60, 650, 0);
}

void IDisplay::loadGame(std::string lib, IGraphic *module, IGame *gameModule, int h, std::string playerName)
{
    ScoreManager *score;
    gameModule->init(); 
    bool pause = false;
    int *b = nullptr;
    int p = 200;
    while (module->isOpen()) {
        if (h != 1)
            module->clearScreen();
        gameModule->game(module, b);
        module->drawText(gameModule->getGameName(), 100, 100, 0);
        module->drawText("Score : " + std::to_string(gameModule->getScore()), 900, 120, 0);
        module->drawText("Time : " + std::to_string(p), 100, 150, 0);
        module->drawText("Appuyez sur F1 pour quitter le jeu.", 80, 280, 0);
        module->drawText("Appuyez sur P pour mettre le jeu en pause.", 80, 320, 0);
        module->drawText("Appuyez sur R pour reprendre le jeu.", 80, 360, 0);
        module->drawText("Appuyez sur Esc pour fermer la fenetre.", 80, 400, 0);
        int i = module->getInput();
        gameModule->handleInput(i);
        if (i == IDisplay::F1_KEY || gameModule->isGameOver() || p == 0) {
            module->clearScreen();
            return;
        }
        if (i == IDisplay::R_KEY) {
            gameModule->reset();
            p = 200;
        }
        if (i == IDisplay::P_KEY)
            pause = !pause;
        if (!pause) {
            gameModule->update();
            p--;
        } else {
            module->drawText("Pause", 900, 90, 0);
        }
        module->refreshScreen();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void IDisplay::display(std::string lib, int h)
{
    ScoreManager *score;
    std::string libraries[] = {"./lib/arcade_sfml.so", "./lib/arcade_sdl2.so", "./lib/arcade_ncurses.so"};
    std::string games[] = {"./lib/arcade_nibbler.so", "./lib/arcade_snake.so"};
    std::string playerName = askPlayerName();
    DLLoader<IGraphic> loader(lib.c_str());
    IGraphic *module = loader.getInstance();
    module->init();
    bool a = false;
    while (module->isOpen()) {
        if (h > 2)
            h = 0;
        else if (h < 0)
            h = 2;
        print(module, h, playerName);
        int i = module->getInput();
        if (i == IDisplay::F6_KEY || i == IDisplay::F7_KEY)
            a = !a;
        if (a == false) {
            if (i == IDisplay::ENTER)
                setLaunch(true);
            if (launch) {
                std::string selectedGame = games[1]; 
                DLLoader<IGame> gameLoader(selectedGame.c_str());
                IGame *game = gameLoader.getInstance();
                module->clearScreen();
                loadGame(selectedGame, module, game, h, playerName);
                score->saveScore(game->getGameName(), playerName, game->getScore());
                delete game;
                setLaunch(false); 
            }
            module->drawText("Snake", 1500, 190, 0);
            module->drawText("_____", 1500, 199, 0);
            module->drawText("Nibbler", 1700, 190, 0);
            } else {
                if (i == IDisplay::ENTER)
                    setLaunch(true);
            if (launch) {
                std::string selectedGame = games[0]; 
                DLLoader<IGame> gameLoader(selectedGame.c_str());
                IGame *game = gameLoader.getInstance();
                loadGame(selectedGame, module, game, h, playerName);
                score->saveScore(game->getGameName(), playerName, game->getScore());
                delete game;
                setLaunch(false); 
            }
            module->drawText("Snake", 1500, 190, 0);
            module->drawText("Nibbler", 1700, 190, 0);
            module->drawText("______", 1700, 199, 0);
            }
            module->refreshScreen();
        if (i == IDisplay::F3_KEY) {
            if (h != 0) {
                module->close();
                loader.destroyInstance(module);
                h--;
                display(libraries[h], h);
                return;
            } else {
                module->close();
                loader.destroyInstance(module);
                h = 2;
                display(libraries[2], h);
                return;
            }
        }
        if (i == IDisplay::F2_KEY) {
            if (h != 2) {
                module->close();
                loader.destroyInstance(module);
                h++;
                display(libraries[h], h);
                return;
            } else {
                module->close();
                loader.destroyInstance(module);
                h = 0;
                display(libraries[0], h);
                return;
            }
        }
    }
    loader.destroyInstance(module);
}

void IDisplay::run(char **av)
{
    const std::string libraries[] = {"./lib/arcade_sfml.so", "./lib/arcade_sdl2.so", "./lib/arcade_ncurses.so", "./lib/arcade_irrlicht.so"};
    int h = 0;
    if (av[1] == libraries[0])
        h = 0;
    else if (av[1] == libraries[1])
        h = 1;
    else if (av[1] == libraries[2])
        h = 2;
    display(av[1], h);
}