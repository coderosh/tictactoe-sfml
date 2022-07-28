#include <SFML/Graphics.hpp>

#include "../Engine/Scene.hpp"
#include "../Engine/Engine.hpp"
#include "../DEFINES.hpp"
#include "../utils.hpp"
#include "../SpriteObject.hpp"
#include "./BaseGameScene.hpp"

class HumanVsHumanScene : public BaseGameScene
{
    using BaseGameScene::BaseGameScene;

    void initFn(){};

    void updateFn()
    {
        updateBoardScreen();
    }

    void renderFn()
    {
        renderBoardScreen();
    }

    void onReplay()
    {
        resetGame();
    }

    void goBackFromGameScreen()
    {
        resetGame();
        _engine->sceneManager.setActive("MAIN MENU");
    }

    void handleInputFn()
    {
        handleBoardScreenInput();
    }

    void onPieceClick(int row, int col)
    {
        if (_turn == TURN_X)
            _boardSprites[row][col].setTexture(_engine->assetManager.getTexture("X Normal"));
        else
            _boardSprites[row][col].setTexture(_engine->assetManager.getTexture("O Normal"));

        _boardStatus[row][col] = _turn == TURN_X ? PIECE_X : PIECE_O;
        _turn = _turn == TURN_X ? TURN_O : TURN_X;
    }
};
