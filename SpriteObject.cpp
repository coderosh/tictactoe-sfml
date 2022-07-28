#include "SpriteObject.hpp"

SpriteObject::SpriteObject(Engine::Engine *engine)
{
    _engine = engine;
}

void SpriteObject::setTexture(std::string texName)
{
    _sprite.setTexture(_engine->assetManager.getTexture(texName));
}

void SpriteObject::setTexture(std::string texName, std::string texPath)
{
    _engine->assetManager.loadTexture(texName, texPath);
    setTexture(texName);
}

bool SpriteObject::isClicked()
{
    return _engine->inputManager.isClicked(_sprite, sf::Mouse::Left, *_engine->window);
}

bool SpriteObject::isHovered()
{
    return _engine->inputManager.isMouseOnTop(_sprite, *_engine->window);
}

void SpriteObject::render()
{
    _engine->window->draw(_sprite);
}

void SpriteObject::setAtCenter()
{
    sf::FloatRect bounds = _sprite.getGlobalBounds();

    float x = SCREEN_WIDTH / 2 - bounds.width / 2;
    float y = SCREEN_HEIGHT / 2 - bounds.height / 2;

    setPosition(x, y);
}

void SpriteObject::setAtHorizontalCenter(float y)
{
    auto bounds = _sprite.getGlobalBounds();

    float x = SCREEN_WIDTH / 2 - bounds.width / 2;

    setPosition(x, y);
}

sf::Sprite *SpriteObject::getSprite()
{
    return &_sprite;
}

void SpriteObject::setPosition(float x, float y)
{
    _sprite.setPosition(x, y);
}