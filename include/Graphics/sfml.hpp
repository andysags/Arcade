/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** sfml.hpp
*/

#ifndef SFML_HPP
#define SFML_HPP

#include "../Interface/IGraphic.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
class Sfml : public IGraphic
{
    public:
        enum InputAction {
            NEXT_GRAPHIC,
            NEXT_GAME,
            RESTART,
            MENU,
            EXIT,    
            NO_ACTION
        };
        
    public:
        Sfml() {};
        ~Sfml() {};
        void init() override;
        void clearScreen() override;
        void drawText(const std::string &text, int x, int y, int id) override;
        void drawSprite(int x, int y, const std::string &sprite) override;
        void refreshScreen() override;
        int getInput() override;
        bool isOpen() const override;
        void close() override;
        int *showMenu(const std::vector<std::string>& gameList, const std::vector<std::string>& gamelib, int scr1, int scr2) override {
            (void)gameList;
            (void)gamelib;
            (void)scr1;
            (void)scr2;
            return nullptr;
        }
    
    private:
        sf::RenderWindow *_window;
        sf::Event _event;
        sf::Font *_font;
        sf::Text *_text;
};
#endif