#include "../Engine/Scene.hpp"
#include "../Engine/Engine.hpp"
#include "../SpriteObject.hpp"
#include "../DEFINES.hpp"

class SplashScene : public Engine::Scene
{
public:
    SplashScene(Engine::Engine &engine) : _engine(&engine) {}

    void init()
    {
        _engine->inputManager.mouseState = "NORMAL";

        _background.setTexture("BACKGROUND", "./Assets/Background.png");
        _title.setTexture("SPLASH TITLE", "./Assets/Splash Title.png");

        _title.setAtCenter();
    }

    void update()
    {
        if (_clock.getElapsedTime().asSeconds() > SPLASH_TIME)
            _engine->sceneManager.setActive("MAIN MENU");
    }

    void render()
    {
        _engine->window->clear();

        _background.render();
        _title.render();
    }

    void handleInput() {}

private:
    Engine::Engine *_engine;
    sf::Clock _clock;

    SpriteObject _title{_engine};
    SpriteObject _background{_engine};
};
