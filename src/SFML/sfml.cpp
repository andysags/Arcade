/*
** EPITECH PROJECT, 2024
** B-OOP-400-COT-4-1-arcade-andy.sagbo
** File description:
** sfml.cpp
*/

#include "../../include/Graphics/sfml.hpp"
#include "../../include/Interface/IDisplay.hpp"

void Sfml::init()
{
    _window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade-SFML");
    _font = new sf::Font();
    _font->loadFromFile("resources/font.ttf");
}

void Sfml::clearScreen()
{
    _window->clear(sf::Color::Black);
}

void Sfml::drawText(const std::string &text, int x, int y, int id)
{
    (void)id;
    sf::Text _text;
    _text.setFont(*_font);
    _text.setString(text);
    _text.setFillColor(sf::Color::White);
    _text.setOutlineColor(sf::Color::Black);
    _text.setOutlineThickness(4);
    _text.setCharacterSize(23);
    _text.setPosition(x, y);
    _window->draw(_text);
}

void Sfml::drawSprite(int x, int y, const std::string &sprite)
{
    sf::Sprite _sprite = sf::Sprite();
    sf::Texture _texture = sf::Texture();
    _texture.loadFromFile(sprite.c_str());
    _sprite.setTexture(_texture);
    _sprite.setPosition(x, y);
    _window->draw(_sprite);
}

void Sfml::refreshScreen()
{
    _window->display();
}

int Sfml::getInput()
{
    while (_window->pollEvent(_event)) {
        if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            _window->close();
        if (_event.type == sf::Event::KeyPressed) {
            switch (_event.key.code) {
                case sf::Keyboard::Up:
                    return IDisplay::UP_KEY;
                case sf::Keyboard::Down:
                    return IDisplay::DOWN_KEY;
                case sf::Keyboard::Left:
                    return IDisplay::LEFT_KEY;
                case sf::Keyboard::Right:
                    return IDisplay::RIGHT_KEY;
                case sf::Keyboard::Enter:
                    return IDisplay::ENTER;
                case sf::Keyboard::Escape:
                    return IDisplay::ESCAPE;
                case sf::Keyboard::Space:
                    return IDisplay::SPACE;
                case sf::Keyboard::A:
                    return IDisplay::A_KEY;
                case sf::Keyboard::B:
                    return IDisplay::B_KEY;
                case sf::Keyboard::C:
                    return IDisplay::C_KEY;
                case sf::Keyboard::D:
                    return IDisplay::D_KEY;
                case sf::Keyboard::E:
                    return IDisplay::E_KEY;
                case sf::Keyboard::F:
                    return IDisplay::F_KEY;
                case sf::Keyboard::G:
                    return IDisplay::G_KEY;
                case sf::Keyboard::H:
                    return IDisplay::H_KEY;
                case sf::Keyboard::I:
                    return IDisplay::I_KEY;
                case sf::Keyboard::J:
                    return IDisplay::J_KEY;
                case sf::Keyboard::K:
                    return IDisplay::K_KEY;
                case sf::Keyboard::L:
                    return IDisplay::L_KEY;
                case sf::Keyboard::M:
                    return IDisplay::M_KEY;
                case sf::Keyboard::N:
                    return IDisplay::N_KEY;
                case sf::Keyboard::O:
                    return IDisplay::O_KEY;
                case sf::Keyboard::P:
                    return IDisplay::P_KEY;
                case sf::Keyboard::Q:
                    return IDisplay::Q_KEY;
                case sf::Keyboard::R:
                    return IDisplay::R_KEY;
                case sf::Keyboard::S:
                    return IDisplay::S_KEY;
                case sf::Keyboard::T:
                    return IDisplay::T_KEY;
                case sf::Keyboard::U:
                    return IDisplay::U_KEY;
                case sf::Keyboard::V:
                    return IDisplay::V_KEY;
                case sf::Keyboard::W:
                    return IDisplay::W_KEY;
                case sf::Keyboard::X:
                    return IDisplay::X_KEY;
                case sf::Keyboard::Y:
                    return IDisplay::Y_KEY;
                case sf::Keyboard::Z:
                    return IDisplay::Z_KEY;
                case sf::Keyboard::F1:
                    return IDisplay::F1_KEY;
                case sf::Keyboard::F2:
                    return IDisplay::F2_KEY;
                case sf::Keyboard::F3:
                    return IDisplay::F3_KEY;
                case sf::Keyboard::F4:
                    return IDisplay::F4_KEY;
                case sf::Keyboard::F5:
                    return IDisplay::F5_KEY;
                case sf::Keyboard::F6:
                    return IDisplay::F6_KEY;
                case sf::Keyboard::F7:
                    return IDisplay::F7_KEY;
                case sf::Keyboard::F8:
                    return IDisplay::F8_KEY;
                case sf::Keyboard::F9:
                    return IDisplay::F9_KEY;
                case sf::Keyboard::F10:
                    return IDisplay::F10_KEY;
                case sf::Keyboard::F11:
                    return IDisplay::F11_KEY;
                case sf::Keyboard::F12:
                    return IDisplay::F12_KEY;
                case sf::Keyboard::Numpad1:
                    return IDisplay::ONE;
                case sf::Keyboard::Numpad2:
                    return IDisplay::TWO;
                case sf::Keyboard::Numpad3:   
                    return IDisplay::THREE;
                case sf::Keyboard::Numpad4:
                    return IDisplay::FOUR;
                case sf::Keyboard::Numpad5:
                    return IDisplay::FIVE;
                case sf::Keyboard::Numpad6:
                    return IDisplay::SIX;
                case sf::Keyboard::Numpad7:
                    return IDisplay::SEVEN;
                case sf::Keyboard::Numpad8:
                    return IDisplay::EIGHT;
                case sf::Keyboard::Numpad9:
                    return IDisplay::NINE;
                default:
                    return IDisplay::UNKNOWN;
            }
        }
    }
    return 0;
}

bool Sfml::isOpen() const
{
    return _window->isOpen();
}

void Sfml::close()
{
    _window->close();
    delete _window;
    delete _font;
}

extern "C"
IGraphic *create()
{
    return new Sfml();
}

extern "C"
void destroy(IGraphic *module)
{
    delete module;
}
