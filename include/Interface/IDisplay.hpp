/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** IDisplay.hpp
*/

#ifndef IDisplay_HPP
    #define IDisplay_HPP
    #include "IGames.hpp"
    #include "IGraphic.hpp"
    #include "DLLoader.hpp"
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <string>
    #include <iomanip>
    #include <cstring>
    #include <cctype>
    #include <vector>
    #include <curses.h>
    #include <ncurses.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>
    #include <unistd.h>
    #include <stdarg.h>
    #include <fcntl.h>
    #include <memory>
    #include <dirent.h>
    #include <sys/stat.h>
    #include <stdarg.h>
    #include <string.h>
    #include <math.h>
    #include <signal.h>
    #include <fstream>
    #include <sstream>
    #include <thread>
    #include <vector>
    #include <iostream>
class IDisplay {
private:
    IGraphic *graphics;
    IGame *game;
    // DLLoader<IGraphic> graphicsLoader;
    // DLLoader<IGame> gameLoader;
    std::string playerName;
    bool launch;

public:
    IDisplay() {
        this->graphics = nullptr;
    }
    ~IDisplay() {
        delete this->graphics;
    }
    void print(IGraphic *module, int h, std::string PlayerName);
    void display(std::string lib, int h);
    void loadGame(std::string lib, IGraphic *module, IGame *gameModule, int h, std::string playerName);
    void setLaunch(bool launch) {
        this->launch = launch;
    }
    void run(char **av);
            enum type {
            UP_KEY,
            DOWN_KEY,
            LEFT_KEY,
            RIGHT_KEY,
            ENTER,
            ESCAPE,
            SPACE,
            A_KEY,
            B_KEY,
            C_KEY,
            D_KEY,
            E_KEY,
            F_KEY,
            G_KEY,
            H_KEY,
            I_KEY,
            J_KEY,
            K_KEY,
            L_KEY,
            M_KEY,
            N_KEY,
            O_KEY,
            P_KEY,
            Q_KEY,
            R_KEY,
            S_KEY,
            T_KEY,
            U_KEY,
            V_KEY,
            W_KEY,
            X_KEY,
            Y_KEY,
            Z_KEY,
            F1_KEY,
            F2_KEY,
            F3_KEY,
            F4_KEY,
            F5_KEY,
            F6_KEY,
            F7_KEY,
            F8_KEY,
            F9_KEY,
            F10_KEY,
            F11_KEY,
            F12_KEY,
            ONE,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            UNKNOWN
        };
};

#endif
