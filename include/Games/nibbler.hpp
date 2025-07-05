/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** nibbler.hpp
*/

#ifndef NIBBLER_HPP
    #define NIBBLER_HPP
    #define RIGHT 0
    #define LEFT 1
    #define UP 2
    #define DOWN 3
    #include "../Interface/IGames.hpp"
    class Nibbler : public IGame {
        private:
            std::vector<std::string> map;
            typedef struct pos {
                int x;
                int y;
            } pos;
            pos snake[100];
            pos food = { rand() % 20, rand() % 20 };
            int snakeSize = 1;
            int score = 0;
            int direction = RIGHT;
            bool gameOver = false;
            int nbFood = 0;
        public:
            Nibbler() {
                snake[0] = {5, 5};
                snakeSize = 1;
                score = 0;
                direction = RIGHT;
            };
            ~Nibbler() = default;
            void init() override;
            void update() override;
            bool isGameOver() const override;
            const char * getGameName() const override;
            int getScore() const override;
            std::vector<std::string> loadMap(const std::string &filename) override;
            void reset() override;
            void handleInput(int key) override;
            void setGameOver(bool gameOver);
            void setDirection(int direction);
            void setSnakeSize(int snakeSize);
            void setScore(int score);
            void setSnake(pos *snake);
            bool getGameOver() const;
            int getDirection() const;
            int getSnakeSize() const;
            pos getFood() const;
            pos* getSnake();
            std::vector<std::string> getMap() const;
            int game(IGraphic *module, int *bestscore) override;
    };

#endif // !NIBBLER_HPP