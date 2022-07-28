#include "BaseGameScene.hpp"

BaseGameScene::BaseGameScene(Engine::Engine &engine) : _engine(&engine) {}

void BaseGameScene::init()
{
    _engine->inputManager.mouseState = "NORMAL";

    _background.setTexture("BACKGROUND");

    _drawModal.setTexture("DRAW", "./Assets/Draw.png");
    _xWinnerModal.setTexture("X WINNER MODAL", "./Assets/Winner X.png");
    _oWinnerModal.setTexture("O WINNER MODAL", "./Assets/Winner O.png");

    _engine->assetManager.loadTexture("X Normal", "./Assets/X Normal.png");
    _engine->assetManager.loadTexture("O Normal", "./Assets/O Normal.png");
    _engine->assetManager.loadTexture("X Win", "./Assets/X Win.png");
    _engine->assetManager.loadTexture("O Win", "./Assets/O Win.png");
    _engine->assetManager.loadTexture("Empty Piece", "./Assets/Empty Piece.png");

    _gameBoard.setTexture("GAME BOARD", "./Assets/Game Board.png");
    _gameBoard.setAtHorizontalCenter(_boardTop);

    _backButton.setTexture("BACK BUTTON", "./Assets/Back Button.png");
    _homeButton.setTexture("HOME BUTTON", "./Assets/Home Button.png");
    _replayButton.setTexture("REPLAY BUTTON", "./Assets/Replay Button.png");
    float gap = 120;
    auto btnBounds = _homeButton.getSprite()->getGlobalBounds();
    float width = btnBounds.width * 2 + gap;
    float left = SCREEN_WIDTH / 2 - width / 2;
    _backButton.setPosition(10, 10);
    _homeButton.setPosition(left, 390);
    _replayButton.setPosition(left + gap + btnBounds.width, 390);

    _playerOActive.setTexture("PLAYER O ACTIVE", "./Assets/Player O Active.png");
    _playerXActive.setTexture("PLAYER X ACTIVE", "./Assets/Player X Active.png");
    _playerOInactive.setTexture("PLAYER O INACTIVE", "./Assets/Player O Inactive.png");
    _playerXInactive.setTexture("PLAYER X INACTIVE", "./Assets/Player X Inactive.png");
    auto boardBounds = _gameBoard.getSprite()->getGlobalBounds();
    auto playerBounds = _playerOActive.getSprite()->getGlobalBounds();
    float val = (SCREEN_WIDTH - boardBounds.width) / 2;
    _playerXInactive.setPosition(val, 120);
    _playerXActive.setPosition(val, 120);
    _playerOInactive.setPosition(val + boardBounds.width - playerBounds.width, 120);
    _playerOActive.setPosition(val + boardBounds.width - playerBounds.width, 120);

    initFn();

    resetGame();
}

void BaseGameScene::update()
{
    updateFn();
}

int BaseGameScene::checkGame(bool noUI)
{
    auto combo = GameUtils::checkGameStatus(_engine, _boardStatus, _winingCombos);

    if (combo == NULL)
    {
        if (GameUtils::checkDraw(_boardStatus))
        {
            _time = _clock.getElapsedTime().asSeconds();
            return STATUS_DRAW;
        }

        return STATUS_PLAYING;
    }

    auto status = _boardStatus[combo[0]][combo[1]];
    _time = _clock.getElapsedTime().asSeconds();

    if (!noUI)
        if (status == STATUS_O_WON)
        {
            _boardSprites[combo[0]][combo[1]].setTexture(_engine->assetManager.getTexture("O Win"));
            _boardSprites[combo[2]][combo[3]].setTexture(_engine->assetManager.getTexture("O Win"));
            _boardSprites[combo[4]][combo[5]].setTexture(_engine->assetManager.getTexture("O Win"));
        }
        else if (status == STATUS_X_WON)
        {
            _boardSprites[combo[0]][combo[1]].setTexture(_engine->assetManager.getTexture("X Win"));
            _boardSprites[combo[2]][combo[3]].setTexture(_engine->assetManager.getTexture("X Win"));
            _boardSprites[combo[4]][combo[5]].setTexture(_engine->assetManager.getTexture("X Win"));
        }

    return status;
}

void BaseGameScene::onBoardClick()
{
    int row = -1, col = -1;
    auto boardBounds = _gameBoard.getSprite()->getGlobalBounds();

    GameUtils::findClickedRowCol(_engine, boardBounds.width, boardBounds.height, _gridGap, _boardTop, row, col);

    if (row != -1 && col != -1)
        if (_boardStatus[row][col] == PIECE_NONE && _engine->inputManager.isMouseOnTop(_boardSprites[row][col], *_engine->window))
            onPieceClick(row, col);

    _gameStatus = checkGame();
}

void BaseGameScene::renderBoardScreen()
{
    _background.render();

    if (_gameStatus == STATUS_PLAYING)
        _backButton.render();

    _gameBoard.render();

    if (_turn == TURN_X)
    {
        _playerXActive.render();
        _playerOInactive.render();
    }
    else
    {
        _playerOActive.render();
        _playerXInactive.render();
    }

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            _engine->window->draw(_boardSprites[i][j]);

    if (_clock.getElapsedTime().asSeconds() - _time > MODAL_WAIT_TIME)
    {
        if (_gameStatus == STATUS_DRAW)
            _drawModal.render();
        else if (_gameStatus == STATUS_O_WON)
            _oWinnerModal.render();
        else if (_gameStatus == STATUS_X_WON)
            _xWinnerModal.render();

        if (_gameStatus != STATUS_PLAYING)
        {
            _replayButton.render();
            _homeButton.render();
        }
    }
}

void BaseGameScene::updateBoardScreen()
{
    auto newTime = _clock.getElapsedTime().asSeconds();
    bool modalButtonsShown = newTime - _time > MODAL_WAIT_TIME && _gameStatus != STATUS_PLAYING;
    bool showHover = (_gameStatus == STATUS_PLAYING && _backButton.isHovered()) ||
                     (modalButtonsShown && (_replayButton.isHovered() || _homeButton.isHovered()));

    if (showHover)
        _engine->inputManager.mouseState = "HOVER";
    else
        _engine->inputManager.mouseState = "NORMAL";
}

void BaseGameScene::handleBoardScreenInput()
{
    if (_gameStatus == STATUS_PLAYING)
    {
        if (_backButton.isClicked())
            goBackFromGameScreen();

        else if (_gameBoard.isClicked())
            onBoardClick();
    }
    else if (_clock.getElapsedTime().asSeconds() - _time > MODAL_WAIT_TIME)
    {
        if (_replayButton.isClicked())
            onReplay();

        else if (_homeButton.isClicked())
        {
            resetGame();
            _engine->sceneManager.setActive("MAIN MENU");
        }
    }
}

void BaseGameScene::render()
{
    _engine->window->clear();

    renderFn();
}

void BaseGameScene::initBoard()
{
    auto boardBounds = _gameBoard.getSprite()->getGlobalBounds();
    auto normalSize = _engine->assetManager.getTexture("X Normal").getSize();

    float left = (SCREEN_WIDTH - boardBounds.width) / 2;

    for (int i = 0; i < 3; i++)
    {
        float vOffset = (normalSize.y + _gridGap) * i;
        for (int j = 0; j < 3; j++)
        {
            float hOffset = (normalSize.x + _gridGap) * j;
            _boardSprites[i][j].setTexture(_engine->assetManager.getTexture("Empty Piece"));
            _boardSprites[i][j].setPosition(left + hOffset, boardBounds.top + vOffset);
            _boardStatus[i][j] = 0;
        }
    }
}

void BaseGameScene::resetGame(int turn)
{
    initBoard();
    _gameStatus = STATUS_PLAYING;
    _turn = turn;
}

void BaseGameScene::handleInput()
{
    handleInputFn();
}