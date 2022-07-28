#include "AssetManager.hpp"

namespace Engine
{

    void AssetManager::loadTexture(std::string textureName, std::string filePath)
    {
        if (_textures.count(textureName) == 0)
        {
            sf::Texture texture;

            if (texture.loadFromFile(filePath))
                this->_textures[textureName] = texture;
        }
    }

    sf::Texture &AssetManager::getTexture(std::string textureName)
    {
        return this->_textures.at(textureName);
    }

    void AssetManager::loadFont(std::string fontName, std::string filePath)
    {
        if (_fonts.count(fontName) == 0)
        {
            sf::Font font;

            if (font.loadFromFile(filePath))
                this->_fonts[fontName] = font;
        }
    }

    sf::Font &AssetManager::getFont(std::string fontName)
    {
        return this->_fonts.at(fontName);
    }
}
