/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** games_interface.hpp
*/

#ifndef IGAMES_HPP
    #define IGAMES_HPP
    #include <string>
    #include <iostream>
    #include <vector>
    #include "IGraphic.hpp"
class IGame {
public:
    virtual ~IGame() = default;

    // Initialise le jeu (réinitialise les variables, la carte, etc.)
    virtual void init() = 0;

    // Charge une map à partir d'un fichier
    virtual std::vector<std::string> loadMap(const std::string &filename) = 0;

    // Met à jour l'état du jeu (déplacements, collisions, etc.)
    virtual void update() = 0;

    // Gère les entrées du joueur
    virtual void handleInput(int key) = 0;

    // Vérifie si le jeu est terminé
    virtual bool isGameOver() const = 0;

    // Réinitialise le jeu
    virtual void reset() = 0;

    // Gère le jeu
    virtual int game(IGraphic *module, int *bestscore) = 0;
    // Retourne le nom du jeu (utile pour le menu)
    virtual const char *getGameName() const = 0;

    // Récupère le score du joueur
    virtual int getScore() const = 0;
};

#endif // IGAMES_HPP