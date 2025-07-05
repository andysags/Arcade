/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** main.cpp
*/
#include <iostream>
#include "../include/Interface/DLLoader.hpp"
#include "../include/Interface/Error.hpp"
#include "../include/Interface/IDisplay.hpp"
#include "../include/Interface/IGames.hpp"
#include "../include/Interface/IGraphic.hpp"
#include "../include/Graphics/ncurses.hpp"
#include "../include/Graphics/sdl.hpp"
#include "../include/Graphics/sfml.hpp"
#include <cstring>
#include <vector>
#include <thread>
#include <chrono>


int main(int ac, char **av) 
{
    IDisplay core;
    try {
        if (ac != 2)
            throw Error("Usage: ./arcade <library_path>");
        const std::string libraries[] = {"./lib/arcade_sfml.so", "./lib/arcade_sdl2.so", "./lib/arcade_ncurses.so"};
        if (std::strcmp(av[1], libraries[0].c_str()) != 0 && std::strcmp(av[1], libraries[1].c_str()) != 0 && std::strcmp(av[1], libraries[2].c_str()) != 0)
            throw Error("The available graphics libraries are: arcade_sdl2, arcade_sfml, arcade_ncurses");
        try {
            core.run(av);
        } catch (const std::exception &e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return 84;
        }
    } catch (const Error &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
