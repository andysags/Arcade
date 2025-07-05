/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** graphics_interface.hpp
*/

#ifndef IGRAPHICS_HPP
    #define IGRAPHICS_HPP
    #include <string>
    #include <iostream>
    #include <vector>
    #include <ncurses.h>
#ifdef KEY_CANCEL
#undef KEY_CANCEL
#endif
#ifdef KEY_HELP
#undef KEY_HELP
#endif
#ifdef KEY_NEXT
#undef KEY_NEXT
#endif
#ifdef KEY_END
#undef KEY_END
#endif      
#ifdef KEY_HOME
#undef KEY_HOME
#endif
#ifdef KEY_LEFT
#undef KEY_LEFT
#endif
#ifdef KEY_UP
#undef KEY_UP
#endif
#ifdef KEY_RIGHT
#undef KEY_RIGHT
#endif
#ifdef KEY_DOWN
#undef KEY_DOWN
#endif
#ifdef KEY_SELECT
#undef KEY_SELECT
#endif
#ifdef KEY_PRINT
#undef KEY_PRINT
#endif
#ifdef KEY_CLEAR
#undef KEY_CLEAR
#endif
    
class IGraphic {
    public:
        virtual ~IGraphic() = default;

        // Initialise les ressources graphiques
        virtual void init() = 0;
        // Efface l'écran
        virtual void clearScreen() = 0;
        // Affiche du texte aux coordonnées spécifiées
        virtual void drawText(const std::string &text, int x, int y, int id) = 0;
        // Affiche un élément du jeu (joueur, ennemis, obstacles...)
        virtual void drawSprite(int x, int y, const std::string &sprite) = 0;
        // Rafraîchit l'affichage
        virtual void refreshScreen() = 0;
        // Récupère une entrée utilisateur (ex: touche pressée)
        virtual int getInput() = 0;
        // Vérifie si la fenêtre est toujours ouverte
        virtual bool isOpen() const = 0;
        // Ferme la bibliothèque graphique et libère les ressources
        virtual void close() = 0;
        virtual int *showMenu(const std::vector<std::string>& gameList, const std::vector<std::string>& gamelib, int scr1, int scr2) = 0;
};

#endif // GRAPHICS_HPP