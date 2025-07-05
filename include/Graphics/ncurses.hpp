/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** ncurses.hpp
*/

#ifndef NCURSES_HPP
    #define NCURSES_HPP
    #include "../Interface/IGraphic.hpp"

class Ncurses : public IGraphic
{
private:
    WINDOW *window;
    bool open = true;
public:
    Ncurses(); 
    ~Ncurses(){};
    void init() override;
    void clearScreen() override;
    void drawText(const std::string &text, int x, int y, int id) override;
;
    void drawSprite(int x, int y, const std::string &sprite) override;
    void refreshScreen() override;
    int getInput() override;
    bool isOpen() const override;
    void close() override;
    int *showMenu(const std::vector<std::string>& gameList, const std::vector<std::string>& gamelib, int scr1, int scr2) override
    {
        (void)gameList;
        (void)gamelib;
        (void)scr1;
        (void)scr2;
        return nullptr;
    }
};


#endif