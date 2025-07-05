##
## EPITECH PROJECT, 2025
## Arcade
## File description:
## Makefile
##

CC = g++

NAME = arcade

FLAGS = -Wall -Wextra -Werror -std=c++20 -fPIC

GRAPHICAL_SRC = src/SFML/sfml.cpp src/SDL/sdl.cpp src/ncurses/ncurses.cpp
GRAPHICAL_LIBS = lib/arcade_sfml.so lib/arcade_sdl2.so lib/arcade_ncurses.so

SFML_FLAG = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system
SDL_FLAG = -lSDL2 -lSDL2_image -lSDL2_ttf 
NCURSE_FLAG = -lncurses

GAME_SRC = src/games/snake.cpp src/games/nibbler.cpp
GAME_LIBS = lib/arcade_snake.so lib/arcade_nibbler.so

SRC = src/main.cpp src/IDisplay.cpp

OBJ = $(SRC:.cpp=.o)
OBJ_GRAPHICAL = $(GRAPHICAL_SRC:.cpp=.o)
OBJ_GAME = $(GAME_SRC:.cpp=.o)

all: core graphicals games

core: $(NAME)

$(NAME): $(OBJ) $(OBJ_GRAPHICAL) $(OBJ_GAME)
	$(CC) -o $(NAME) $(OBJ) $(FLAGS) $(SDL_FLAG) $(NCURSE_FLAG) $(SFML_FLAG)

graphicals: $(GRAPHICAL_LIBS)

lib/arcade_sfml.so: src/SFML/sfml.cpp
	$(CC) -shared -o $@ $< $(SFML_FLAG) $(FLAGS)

lib/arcade_sdl2.so: src/SDL/sdl.cpp
	$(CC) -shared -o $@ $<  $(SDL_FLAG) $(FLAGS)

lib/arcade_ncurses.so: src/ncurses/ncurses.cpp
	$(CC) -shared -o $@ $<  $(NCURSE_FLAG) $(FLAGS)

games: $(GAME_LIBS)

lib/arcade_snake.so: src/games/snake.cpp
	$(CC) -shared -o $@ $< $(FLAGS)

lib/arcade_nibbler.so: src/games/nibbler.cpp
	$(CC) -shared -o $@ $< $(FLAGS)

lib/arcade_pacman.so: src/games/pacman.cpp
	$(CC) -shared -o $@ $< $(FLAGS)

clean:
	rm -f $(OBJ) $(OBJ_GRAPHICAL) $(OBJ_GAME)

fclean: clean
	rm -f $(NAME) $(GRAPHICAL_LIBS) $(GAME_LIBS)

re: fclean all
