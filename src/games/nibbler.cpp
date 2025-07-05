/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** nibbler.cpp
*/

#include <fstream>
#include "../../include/Games/nibbler.hpp"
#include "../../include/Interface/IDisplay.hpp"
std::vector<std::string> Nibbler::loadMap(const std::string &filename)
{
    std::vector<std::string> map;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line))
        map.push_back(line);
    return map;
}

void Nibbler::init()
{
    this->map = this->loadMap("resources/nibbler.txt");
    this->reset();
    for (auto nb : this->map)
        for (auto c : nb)
            if (c == 'o')
                this->nbFood++;
}

void Nibbler::reset()
{
    this->snake[0] = {1, 1};
    this->snakeSize = 4;
    this->score = 0;
    this->direction = RIGHT;
    this->gameOver = false;
}

const char * Nibbler::getGameName() const
{
    return "Nibbler";
}

int Nibbler::getScore() const
{
    return this->score;
}

void Nibbler::handleInput(int key)
{
    if (key == IDisplay::SIX && this->direction != LEFT)
        this->direction = RIGHT;
    else if (key == IDisplay::FOUR && this->direction != RIGHT)
        this->direction = LEFT;
    else if (key == IDisplay::EIGHT && this->direction != DOWN)
        this->direction = UP;
    else if (key == IDisplay::TWO && this->direction != UP)
        this->direction = DOWN;
}

bool Nibbler::isGameOver() const
{
    return this->gameOver;
}

void Nibbler::setGameOver(bool gameOver)
{
    this->gameOver = gameOver;
}

void Nibbler::setDirection(int direction)
{
    this->direction = direction;
}

void Nibbler::setSnakeSize(int snakeSize)
{
    this->snakeSize = snakeSize;
}

void Nibbler::setScore(int score)
{
    this->score = score;
}

void Nibbler::update()
{
    if (this->snakeSize <= 0 || this->map.empty() || this->map[0].empty())
        return;
    int oldX = this->snake[0].x;
    int oldY = this->snake[0].y;
    pos lastTail = this->snake[this->snakeSize - 1];
    for (int i = this->snakeSize - 1; i > 0; i--)
        this->snake[i] = this->snake[i - 1];
    if (this->direction == RIGHT) 
        this->snake[0].x += 1;
    else if (this->direction == LEFT)
        this->snake[0].x -= 1;
    else if (this->direction == UP)
        this->snake[0].y -= 1;
    else if (this->direction == DOWN)
        this->snake[0].y += 1;
    if (this->snake[0].y >= 0 && this->snake[0].y < static_cast<int>(this->map.size()) &&
        this->snake[0].x >= 0 && this->snake[0].x < static_cast<int>(this->map[0].size()) &&
        this->map[this->snake[0].y][this->snake[0].x] == '#') {
        this->snake[0].x = oldX;
        this->snake[0].y = oldY;
        
        for (int i = 1; i < this->snakeSize; i++)
            this->snake[i] = this->snake[i - 1];
        if (this->direction == RIGHT)
            this->direction = DOWN;
        else if (this->direction == LEFT)
            this->direction = UP;
        else if (this->direction == UP)
            this->direction = RIGHT;
        else if (this->direction == DOWN)
            this->direction = LEFT;
        return;
    }
    for (int i = 1; i < this->snakeSize; i++)
        if (this->snake[0].x == this->snake[i].x && this->snake[0].y == this->snake[i].y) {
            setGameOver(true);
            return;
        }
    if (this->nbFood == 0) {
        setGameOver(true);
        return;
    }
    if (this->snake[0].y >= 0 && this->snake[0].y < static_cast<int>(this->map.size()) &&
        this->snake[0].x >= 0 && this->snake[0].x < static_cast<int>(this->map[0].size()) &&
        this->map[this->snake[0].y][this->snake[0].x] == 'o') {
        if (this->snakeSize < 100) {
            this->snake[this->snakeSize] = lastTail;
            this->snakeSize++;
            this->score += 10;
            this->map[this->snake[0].y][this->snake[0].x] = ' ';
            this->nbFood--;
        }
    }
}

Nibbler::pos* Nibbler::getSnake()
{
    return this->snake;
}

int Nibbler::getSnakeSize() const
{
    return this->snakeSize;
}

std::vector<std::string> Nibbler::getMap() const
{
    return this->map;
}

int Nibbler::getDirection() const
{
    return this->direction;
}

bool Nibbler::getGameOver() const
{
    return this->gameOver;
}

Nibbler::pos Nibbler::getFood() const
{
    return this->food;
}

int Nibbler::game(IGraphic *module, int *bestscore)
{
    (void)bestscore;
    module->drawSprite(0, 0, "resources/assets/background.png");
    module->drawSprite(560 + this->getSnake()[0].x * 20, 250 + this->getSnake()[0].y * 20, "resources/assets/player.png");

    for (int i = 1; i < this->getSnakeSize(); i++)
        module->drawSprite(560 + this->getSnake()[i].x * 20, 250 + this->getSnake()[i].y * 20, "resources/assets/player.png");
    std::vector<std::string> map = this->getMap();
    for (size_t y = 0; y < map.size(); y++) {
        for (size_t x = 0; x < map[y].size(); x++) {
            if (map[y][x] == '#')
                module->drawSprite(560 + x * 20, 250 + y * 20, "resources/assets/wall.png");
            else if (map[y][x] == 'o')
                module->drawSprite(560 + x * 20, 250 + y * 20, "resources/assets/apple.png");
        }
    }
    return 2;
}

extern "C" {
    IGame *create() {
        return new Nibbler();
    }
}

extern "C" {
    void destroy(IGame *game) {
        delete game;
    }
}