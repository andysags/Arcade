/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** sdl.cpp
*/

#include "../../include/Graphics/sdl.hpp"
#include "../../include/Interface/IDisplay.hpp"
#include <SDL2/SDL_image.h>
void Sdl::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    _window = SDL_CreateWindow("Arcade-SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
}

void Sdl::clearScreen()
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    SDL_RenderPresent(_renderer);
}

void Sdl::drawText(const std::string &text, int x, int y, int id)
{
    (void)id;
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("resources/font.ttf", 23);
    if (!font) return;
    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), SDL_Color {255, 255, 255, 255});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Sdl::drawSprite(int x, int y, const std::string &sprite)
{
    SDL_Surface *surface = IMG_Load(sprite.c_str());
    if (!surface) return;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    SDL_RenderCopy(_renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

void Sdl::refreshScreen()
{
    SDL_RenderPresent(_renderer);
}

int Sdl::getInput()
{
    while (SDL_PollEvent(&_event)) {
        if (_event.type == SDL_QUIT) {
            close();
            return 1;
        }
        if (_event.type == SDL_KEYDOWN ) {
            if (_event.key.keysym.sym == SDLK_ESCAPE) {
                close();
                return 1;
            }
        }
        if (_event.type == SDL_KEYDOWN) {
            switch (_event.key.keysym.sym) {
                case SDLK_UP:
                    return IDisplay::UP_KEY;
                case SDLK_DOWN:
                    return IDisplay::DOWN_KEY;
                case SDLK_LEFT:
                    return IDisplay::LEFT_KEY;
                case SDLK_RIGHT:
                    return IDisplay::RIGHT_KEY;
                case SDLK_RETURN:
                    return IDisplay::ENTER;
                case SDLK_ESCAPE:
                    return IDisplay::ESCAPE;
                case SDLK_SPACE:
                    return IDisplay::SPACE;
                case SDLK_a:
                    return IDisplay::A_KEY;
                case SDLK_b:
                    return IDisplay::B_KEY;
                case SDLK_c:
                    return IDisplay::C_KEY;
                case SDLK_d:
                    return IDisplay::D_KEY;
                case SDLK_e:
                    return IDisplay::E_KEY;
                case SDLK_f:
                    return IDisplay::F_KEY;
                case SDLK_g:
                    return IDisplay::G_KEY;
                case SDLK_h:
                    return IDisplay::H_KEY;
                case SDLK_i:
                    return IDisplay::I_KEY;
                case SDLK_j:
                    return IDisplay::J_KEY;
                case SDLK_k:
                    return IDisplay::K_KEY;
                case SDLK_l:
                    return IDisplay::L_KEY;
                case SDLK_m:
                    return IDisplay::M_KEY;
                case SDLK_n:
                    return IDisplay::N_KEY;
                case SDLK_o:
                    return IDisplay::O_KEY;
                case SDLK_p:
                    return IDisplay::P_KEY;
                case SDLK_q:
                    return IDisplay::Q_KEY;
                case SDLK_r:
                    return IDisplay::R_KEY;
                case SDLK_s:
                    return IDisplay::S_KEY;
                case SDLK_t:
                    return IDisplay::T_KEY;
                case SDLK_u:
                    return IDisplay::U_KEY;
                case SDLK_v:
                    return IDisplay::V_KEY;
                case SDLK_w:
                    return IDisplay::W_KEY;
                case SDLK_x:
                    return IDisplay::X_KEY;
                case SDLK_y:
                    return IDisplay::Y_KEY;
                case SDLK_z:
                    return IDisplay::Z_KEY;
                case SDLK_F1:
                    return IDisplay::F1_KEY;
                case SDLK_F2:
                    return IDisplay::F2_KEY;
                case SDLK_F3:
                    return IDisplay::F3_KEY;
                case SDLK_F4:
                    return IDisplay::F4_KEY;
                case SDLK_F5:
                    return IDisplay::F5_KEY;
                case SDLK_F6:
                    return IDisplay::F6_KEY;
                case SDLK_F7:
                    return IDisplay::F7_KEY;
                case SDLK_F8:
                    return IDisplay::F8_KEY;
                case SDLK_F9:
                    return IDisplay::F9_KEY;
                case SDLK_F10:
                    return IDisplay::F10_KEY;
                case SDLK_F11:
                    return IDisplay::F11_KEY;
                case SDLK_F12:
                    return IDisplay::F12_KEY;
                case SDLK_KP_1:
                    return IDisplay::ONE;
                case SDLK_KP_2:
                    return IDisplay::TWO;
                case SDLK_KP_3:
                    return IDisplay::THREE;
                case SDLK_KP_4:
                    return IDisplay::FOUR;
                case SDLK_KP_5:
                    return IDisplay::FIVE;
                case SDLK_KP_6:   
                    return IDisplay::SIX;
                case SDLK_KP_7:
                    return IDisplay::SEVEN;
                case SDLK_KP_8:
                    return IDisplay::EIGHT;
                case SDLK_KP_9:
                    return IDisplay::NINE;
                default:
                    return IDisplay::UNKNOWN;
            }
        }
    }
    return 0;
}

bool Sdl::isOpen() const
{
    return _window != nullptr;
}

void Sdl::close()
{
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
        _renderer = nullptr;
    }
    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }
    SDL_Quit();
}

extern "C"
IGraphic *create()
{
    return new Sdl();
}

extern "C"
void destroy(IGraphic *module)
{
    delete module;
}
