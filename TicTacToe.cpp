#include "Engine/Engine.hpp"

#include "./Scenes/SplashScene.cpp"
#include "./Scenes/MainMenuScene.cpp"
#include "./Scenes/HumanVsHumanScene.cpp"
#include "./Scenes/HumanVsComputerScene.cpp"

class TicTacToe : public Engine::Engine
{
public:
    using Engine::Engine::Engine;
    SplashScene splashScene = SplashScene(*this);
    MainMenuScene mainMenuScene = MainMenuScene(*this);
    HumanVsHumanScene humanVsHumanScene = HumanVsHumanScene(*this);
    HumanVsComputerScene humanVsComputerScene = HumanVsComputerScene(*this);
    sf::Image icon;

    void start()
    {
        window->setFramerateLimit(60);
        window->setMouseCursorVisible(false);

        icon.loadFromFile("./Assets/Icon.png");

        window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

        sceneManager.registerScene("SPLASH", &splashScene);
        sceneManager.registerScene("MAIN MENU", &mainMenuScene);
        sceneManager.registerScene("HUMAN VS HUMAN", &humanVsHumanScene);
        sceneManager.registerScene("HUMAN VS COMPUTER", &humanVsComputerScene);

        sceneManager.setActive("SPLASH");

        assetManager.loadTexture("CURSOR NORMAL", "./Assets/Cursor Normal.png");
        assetManager.loadTexture("CURSOR HOVER", "./Assets/Cursor Hover.png");

        _normalCursor.setTexture(assetManager.getTexture("CURSOR NORMAL"));
        _hoverCursor.setTexture(assetManager.getTexture("CURSOR HOVER"));
    }

    void update()
    {
        if (inputManager.mouseState == "NORMAL")
        {
            _normalCursor.setPosition(static_cast<sf::Vector2f>(inputManager.getMousePosition(*window)));
            window->draw(_normalCursor);
        }
        else
        {
            _hoverCursor.setPosition(static_cast<sf::Vector2f>(inputManager.getMousePosition(*window)));
            window->draw(_hoverCursor);
        }
    }

private:
    sf::Sprite _normalCursor;
    sf::Sprite _hoverCursor;
};