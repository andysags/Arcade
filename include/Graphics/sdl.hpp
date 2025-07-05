/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** sdl.hpp
*/

#ifndef SDL_HPP
    #define SDL_HPP
    #include "../Interface/IGraphic.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
extern DECLSPEC int SDLCALL TTF_Init(void);
#define TTF_GetError    SDL_GetError
class Sdl : public IGraphic
{
    public:
        Sdl() {};
        ~Sdl() {};
        void init() override;
        void clearScreen() override;
        void drawText(const std::string &text, int x, int y, int id) override;
;
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
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        // SDL_Texture *_texture;
        // SDL_Surface *_surface;
        //TTF_Font *_font;    
        SDL_Event _event;
};
#endif