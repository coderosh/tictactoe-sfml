#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

namespace Engine
{
    class InputManager
    {
    public:
        std::string mouseState = "NORMAL"; // track yourself

        bool isClicked(sf::Sprite &object, sf::Mouse::Button button, sf::RenderWindow &window);
        bool isMouseOnTop(sf::Sprite &object, sf::RenderWindow &window);
        sf::Vector2i getMousePosition(sf::RenderWindow &window);
    };

}