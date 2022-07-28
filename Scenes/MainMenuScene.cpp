
#include "../Engine/Scene.hpp"
#include "../Engine/Engine.hpp"
#include "../DEFINES.hpp"
#include "../SpriteObject.hpp"

class MainMenuScene : public Engine::Scene
{
public:
    MainMenuScene(Engine::Engine &engine) : _engine(&engine) {}

    void init()
    {
        _engine->inputManager.mouseState = "NORMAL";

        _background.setTexture("BACKGROUND");

        _title.setTexture("GAME TITLE", "./Assets/Game Title.png");
        _title.setAtHorizontalCenter(100);

        _vsHumanButton.setTexture("VS HUMAN BUTTON", "./Assets/Human vs Human.png");
        _vsHumanButton.setAtHorizontalCenter(_vsHumanButtonYPosition);

        _vsComputerButton.setTexture("VS COMPUTER BUTTON", "./Assets/Human vs Computer.png");
        _vsComputerButton.setAtHorizontalCenter(_vsComputerButtonYPosition);
    }

    void handleInput()
    {
        if (_vsHumanButton.isClicked())
            _engine->sceneManager.setActive("HUMAN VS HUMAN");

        else if (_vsComputerButton.isClicked())
            _engine->sceneManager.setActive("HUMAN VS COMPUTER");
    }

    void update()
    {
        if (_vsHumanButton.isHovered() || _vsComputerButton.isHovered())
            _engine->inputManager.mouseState = "HOVER";
        else
            _engine->inputManager.mouseState = "NORMAL";
    }

    void render()
    {
        _engine->window->clear();

        _background.render();
        _title.render();

        _vsHumanButton.render();
        _vsComputerButton.render();
    }

private:
    Engine::Engine *_engine;

    SpriteObject _background{_engine};
    SpriteObject _title{_engine};

    SpriteObject _vsHumanButton{_engine};
    SpriteObject _vsComputerButton{_engine};

    float _vsHumanButtonYPosition = 400;
    float _vsComputerButtonYPosition = 550;
};
