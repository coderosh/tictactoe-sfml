#include "InputManager.hpp"
#include <iostream>

namespace Engine
{
    bool InputManager::isClicked(sf::Sprite &object, sf::Mouse::Button button, sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(button) && isMouseOnTop(object, window))
            return true;
        return false;
    }

    bool InputManager::isMouseOnTop(sf::Sprite &object, sf::RenderWindow &window)
    {
        sf::Vector2i mousePosition = getMousePosition(window);
        return object.getGlobalBounds().contains(mousePosition.x, mousePosition.y);
    }

    sf::Vector2i InputManager::getMousePosition(sf::RenderWindow &window)
    {
        return sf::Mouse::getPosition(window);
    }

}