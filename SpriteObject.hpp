#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "./Engine/Engine.hpp"
#include "./DEFINES.hpp"

class SpriteObject
{
public:
    SpriteObject(Engine::Engine *engine);

    void setTexture(std::string texName, std::string texPath);
    void setTexture(std::string texName);

    bool isClicked();
    bool isHovered();

    void render();

    void setAtCenter();
    void setAtHorizontalCenter(float y = 0);
    void setPosition(float x, float y);

    sf::Sprite *getSprite();

private:
    sf::Sprite _sprite;
    Engine::Engine *_engine;
};
