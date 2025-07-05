/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** ScoreManager.hpp
*/

#ifndef SCOREMANAGER_HPP
#define SCOREMANAGER_HPP

#include <string>
#include <iostream>

#include <map>

class ScoreManager {
private:
    std::map<std::string, int> scores;
public:
    void saveScore(const std::string &gameName, const std::string &playerName, int score);
};

#endif
