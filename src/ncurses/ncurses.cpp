/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** ncurses.cpp
*/

#include "../../include/Graphics/ncurses.hpp"
#include "../../include/Interface/IDisplay.hpp"

Ncurses::Ncurses()
{}

void Ncurses::init()
{
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, FALSE);
    timeout(100);
}

void Ncurses::clearScreen()
{
    werase(stdscr);
}

void Ncurses::drawText(const std::string &text, int x, int y, int id)
{
    (void)id;
    mvwprintw(stdscr, y / 20, x / 10,"%s",text.c_str());
}

void Ncurses::drawSprite(int x, int y, const std::string &sprite)
{
    char displayChar = ' ';
    if (sprite.find("wall") != std::string::npos)
        displayChar = '#';
    else if (sprite.find("player") != std::string::npos)
        displayChar = '@';
    else if (sprite.find("apple") != std::string::npos)
        displayChar = 'o';
    mvwaddch(stdscr, y / 20, x / 10, displayChar);
}

void Ncurses::refreshScreen()
{
    wrefresh(stdscr);
}

int Ncurses::getInput()
{
    int ch = wgetch(stdscr);
    switch (ch) {
        case 10:
            return IDisplay::ENTER;
            break;
        case 27:
            close();
            return IDisplay::ESCAPE;
            break;
        case 32:
            return IDisplay::SPACE;
            break;
        case 97:
            return IDisplay::A_KEY;
            break;
        case 98:
            return IDisplay::B_KEY;
            break;
        case 99:
            return IDisplay::C_KEY;
            break;
        case 100:
            return IDisplay::D_KEY;
            break;
        case 101:
            return IDisplay::E_KEY;
            break;
        case 102:
            return IDisplay::F_KEY;
            break;
        case 103:
            return IDisplay::G_KEY;
            break;
        case 104:
            return IDisplay::H_KEY;
            break;
        case 105:
            return IDisplay::I_KEY;
            break;
        case 106:
            return IDisplay::J_KEY;
            break;
        case 107:
            return IDisplay::K_KEY;
            break;
        case 108:
            return IDisplay::L_KEY;
            break;
        case 109:
            return IDisplay::M_KEY;
            break;
        case 110:
            return IDisplay::N_KEY;
            break;
        case 111:
            return IDisplay::O_KEY;
            break;
        case 112:
            return IDisplay::P_KEY;
            break;
        case 113:
            return IDisplay::Q_KEY;
            break;
        case 114:
            return IDisplay::R_KEY;
            break;
        case 115:
            return IDisplay::S_KEY;
            break;
        case 116:
            return IDisplay::T_KEY;
            break;
        case 117:
            return IDisplay::U_KEY;
            break;
        case 118:
            return IDisplay::V_KEY;
            break;
        case 119:
            return IDisplay::W_KEY;
            break;
        case 120:
            return IDisplay::X_KEY;
            break;
        case 121:
            return IDisplay::Y_KEY;
            break;
        case 122:
            return IDisplay::Z_KEY;
            break;
        case '1':
            return IDisplay::ONE;
            break;
        case '2':
            return IDisplay::TWO;
            break;
        case '3':
            return IDisplay::THREE;
            break;
        case '4':
            return IDisplay::FOUR;
            break;
        case '5':
            return IDisplay::FIVE;
            break;
        case '6':
            return IDisplay::SIX;
            break;
        case '7':
            return IDisplay::SEVEN;
            break;
        case '8':
            return IDisplay::EIGHT;
            break;
        case '9':
            return IDisplay::NINE;
            break;
        case KEY_F(1):
            return IDisplay::F1_KEY;
            break;
        case KEY_F(2):
            return IDisplay::F2_KEY;
            break;
        case KEY_F(3):
            return IDisplay::F3_KEY;
            break;
        case KEY_F(4):
            return IDisplay::F4_KEY;
            break;
        case KEY_F(5):
            return IDisplay::F5_KEY;
            break;
        case KEY_F(6):
            return IDisplay::F6_KEY;
            break;
        case KEY_F(7):
            return IDisplay::F7_KEY;
            break;
        case KEY_F(8):
            return IDisplay::F8_KEY;
            break;
        case KEY_F(9):
            return IDisplay::F9_KEY;
            break;
        case KEY_F(10):
            return IDisplay::F10_KEY;
            break;
        case KEY_F(11):
            return IDisplay::F11_KEY;
            break;
        case KEY_F(12):
            return IDisplay::F12_KEY;
            break;
        default:
            return IDisplay::UNKNOWN;
            break;
    }
}

bool Ncurses::isOpen() const
{
    return open;
}

void Ncurses::close()
{
    open = false;
    keypad(stdscr, FALSE);
    nodelay(stdscr, FALSE);
    endwin();
}

extern "C"
IGraphic *create()
{
    return new Ncurses();
}

extern "C"
void destroy(IGraphic *module)
{
    delete module;
}
