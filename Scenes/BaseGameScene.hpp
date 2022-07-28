#pragma once

#include <SFML/Graphics.hpp>

#include "../Engine/Scene.hpp"
#include "../Engine/Engine.hpp"
#include "../DEFINES.hpp"
#include "../utils.hpp"
#include "../SpriteObject.hpp"

class BaseGameScene : public Engine::Scene
{
public:
    BaseGameScene(Engine::Engine &engine);

    virtual void initFn() = 0;
    virtual void updateFn() = 0;
    virtual void renderFn() = 0;
    virtual void handleInputFn() = 0;
    virtual void onPieceClick(int row, int col) = 0;
    virtual void goBackFromGameScreen() = 0;
    virtual void onReplay() = 0;

    void init();
    void update();
    void render();
    void handleInput();

    void renderBoardScreen();
    void updateBoardScreen();
    void handleBoardScreenInput();

    int checkGame(bool noUI = false);
    void onBoardClick();
    void initBoard();
    void resetGame(int turn = TURN_X);

protected:
    float _time;
    sf::Clock _clock;
    Engine::Engine *_engine;

    int _gridGap = 15;
    int _boardTop = 300;

    SpriteObject _gameBoard{_engine};
    SpriteObject _background{_engine};

    SpriteObject _drawModal{_engine};
    SpriteObject _xWinnerModal{_engine};
    SpriteObject _oWinnerModal{_engine};

    SpriteObject _homeButton{_engine};
    SpriteObject _backButton{_engine};
    SpriteObject _replayButton{_engine};

    SpriteObject _playerOInactive{_engine};
    SpriteObject _playerXInactive{_engine};

    SpriteObject _playerOActive{_engine};
    SpriteObject _playerXActive{_engine};

    int _turn = TURN_O;
    int _gameStatus = STATUS_PLAYING;

    int _boardStatus[3][3];
    sf::Sprite _boardSprites[3][3];

    int _winingCombos[8][6] = {
        {0, 0, 1, 0, 2, 0},
        {0, 1, 1, 1, 2, 1},
        {0, 2, 1, 2, 2, 2},
        {0, 0, 0, 1, 0, 2},
        {1, 0, 1, 1, 1, 2},
        {2, 0, 2, 1, 2, 2},
        {0, 0, 1, 1, 2, 2},
        {0, 2, 1, 1, 2, 0},
    };
};
