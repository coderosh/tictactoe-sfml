#include <SFML/Graphics.hpp>
#include <limits>

#include "../Engine/Scene.hpp"
#include "../Engine/Engine.hpp"
#include "../DEFINES.hpp"
#include "../utils.hpp"
#include "../SpriteObject.hpp"
#include "./BaseGameScene.hpp"

class HumanVsComputerScene : public BaseGameScene
{
    using BaseGameScene::BaseGameScene;

    void initFn()
    {
        _diffTitle.setTexture("DIFF TITLE", "./Assets/Difficulty Title.png");
        _diffEasyBtn.setTexture("DIFF EASY", "./Assets/Difficulty Easy.png");
        _diffHardBtn.setTexture("DIFF HARD", "./Assets/Difficulty Hard.png");
        _diffMediumBtn.setTexture("DIFF MEDIUM", "./Assets/Difficulty Medium.png");
        _diffTitle.setAtHorizontalCenter(100);
        _diffEasyBtn.setAtHorizontalCenter(300);
        _diffMediumBtn.setAtHorizontalCenter(450);
        _diffHardBtn.setAtHorizontalCenter(600);

        _choosePieceTitle.setTexture("CHOOSE PIECE", "./Assets/Choose Your Piece.png");
        _selectOBtn.setTexture("SELECT O", "./Assets/Select O.png");
        _selectXBtn.setTexture("SELECT X", "./Assets/Select X.png");
        _choosePieceTitle.setAtHorizontalCenter(100);
        _selectOBtn.setAtHorizontalCenter(300);
        _selectXBtn.setAtHorizontalCenter(600);
    };

    void updateDiffScreen()
    {
        if (_backButton.isHovered() || _diffEasyBtn.isHovered() || _diffMediumBtn.isHovered() || _diffHardBtn.isHovered())
            _engine->inputManager.mouseState = "HOVER";
        else
            _engine->inputManager.mouseState = "NORMAL";
    }

    void updateChoosePieceScreen()
    {
        if (_selectOBtn.isHovered() || _selectXBtn.isHovered() || _backButton.isHovered())
            _engine->inputManager.mouseState = "HOVER";
        else
            _engine->inputManager.mouseState = "NORMAL";
    }

    void updateFn()
    {
        if (_currentScreen == SCREEN_DIFFICULTY)
            updateDiffScreen();
        else if (_currentScreen == SCREEN_CHOOSE_PIECE)
            updateChoosePieceScreen();
        else if (_currentScreen == SCREEN_VSCOMPUTER_GAME)
            updateBoardScreen();
    }

    void onReplay()
    {
        resetGame(_playerSelection == PIECE_O ? TURN_O : TURN_X);

        if (_playerSelection == PIECE_O)
        {
            int row = 0, col = 0;
            findComputerMove(row, col);
            addMoveToBoard(row, col, PIECE_X);
        }
    }

    void renderDiffScreen()
    {
        _background.render();
        _backButton.render();
        _diffTitle.render();
        _diffEasyBtn.render();
        _diffMediumBtn.render();
        _diffHardBtn.render();
    }

    void renderChoosePieceScreen()
    {
        _background.render();
        _backButton.render();
        _choosePieceTitle.render();
        _selectOBtn.render();
        _selectXBtn.render();
    }

    void renderFn()
    {
        if (_currentScreen == SCREEN_DIFFICULTY)
            renderDiffScreen();
        else if (_currentScreen == SCREEN_CHOOSE_PIECE)
            renderChoosePieceScreen();
        else if (_currentScreen == SCREEN_VSCOMPUTER_GAME)
            renderBoardScreen();
    }

    void handleDiffScreenInput()
    {
        if (_backButton.isClicked())
        {
            resetGame();
            _engine->sceneManager.setActive("MAIN MENU");
        }

        else if (_diffEasyBtn.isClicked())
        {
            _diffLevel = DIFFICULTY_EASY;
            _engine->inputManager.mouseState = "NORMAL";
            _currentScreen = SCREEN_CHOOSE_PIECE;
        }
        else if (_diffMediumBtn.isClicked())
        {
            _diffLevel = DIFFICULTY_MEDIUM;
            _engine->inputManager.mouseState = "NORMAL";
            _currentScreen = SCREEN_CHOOSE_PIECE;
        }
        else if (_diffHardBtn.isClicked())
        {
            _diffLevel = DIFFICULTY_HARD;
            _engine->inputManager.mouseState = "NORMAL";
            _currentScreen = SCREEN_CHOOSE_PIECE;
        }
    }

    void goBackFromGameScreen()
    {
        resetGame(_playerSelection == PIECE_O ? TURN_O : TURN_X);
        _currentScreen = SCREEN_CHOOSE_PIECE;
    }

    void handleBoardScreenInput()
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
                _currentScreen = SCREEN_DIFFICULTY;
            }
        }
    }

    void handleChooseScreenInput()
    {
        if (_backButton.isClicked())
        {
            _engine->inputManager.mouseState = "NORMAL";
            _currentScreen = SCREEN_DIFFICULTY;
        }

        else if (_selectOBtn.isClicked())
        {
            _engine->inputManager.mouseState = "NORMAL";
            _playerSelection = PIECE_O;
            _currentScreen = SCREEN_VSCOMPUTER_GAME;
            _turn = TURN_O;

            int row = 0, col = 0;
            findComputerMove(row, col);
            addMoveToBoard(row, col, PIECE_X);
        }
        else if (_selectXBtn.isClicked())
        {
            _engine->inputManager.mouseState = "NORMAL";
            _playerSelection = PIECE_X;
            _turn = TURN_X;
            _currentScreen = SCREEN_VSCOMPUTER_GAME;
        }
    }

    void handleInputFn()
    {
        if (_currentScreen == SCREEN_DIFFICULTY)
            handleDiffScreenInput();
        else if (_currentScreen == SCREEN_CHOOSE_PIECE)
            handleChooseScreenInput();
        else if (_currentScreen == SCREEN_VSCOMPUTER_GAME)
            handleBoardScreenInput();
    }

    void addMoveToBoard(int row, int col, int piece)
    {
        if (piece == PIECE_O)
            _boardSprites[row][col].setTexture(_engine->assetManager.getTexture("O Normal"));
        else
            _boardSprites[row][col].setTexture(_engine->assetManager.getTexture("X Normal"));

        _boardStatus[row][col] = piece;
    }

    void onPieceClick(int row, int col)
    {
        addMoveToBoard(row, col, _playerSelection);

        _gameStatus = checkGame();

        if (_gameStatus == STATUS_PLAYING)
        {
            int computerSelection = _playerSelection == PIECE_O ? PIECE_X : PIECE_O;

            findComputerMove(row, col);
            addMoveToBoard(row, col, computerSelection);
        }
    }

    void findComputerMove(int &row, int &col)
    {
        if (_diffLevel == DIFFICULTY_EASY)
            findEasyDiffMove(row, col);
        else if (_diffLevel == DIFFICULTY_MEDIUM)
            findMediumDiffMove(row, col);
        else if (_diffLevel == DIFFICULTY_HARD)
            findHardDiffMove(row, col);
    }

    void dumbAI(int &row, int &col)
    {
        bool shouldBreak = false;
        for (int i = 0; i < 3; i++)
        {
            if (shouldBreak)
                break;
            for (int j = 0; j < 3; j++)
            {
                if (shouldBreak)
                    break;

                if (_boardStatus[i][j] == PIECE_NONE)
                {
                    row = i;
                    col = j;
                    shouldBreak = (std::rand() % 10) > 5;
                }
            }
        }
    }

    void unbeatableAI(int &row, int &col)
    {
        int i = 0, j = 0;
        minimax(i, j);
        row = i;
        col = j;
    }

    void findEasyDiffMove(int &row, int &col)
    {
        bool shouldUseMinimax = (std::rand() % 100) > 70;

        if (shouldUseMinimax)
            unbeatableAI(row, col);
        else
            dumbAI(row, col);
    }

    void findMediumDiffMove(int &row, int &col)
    {
        int emptyPieces = GameUtils::countEmpty(_boardStatus);
        bool shouldUseMiniMax = (std::rand() % 100) > 50 && emptyPieces < 7;

        if (shouldUseMiniMax)
            unbeatableAI(row, col);
        else
            dumbAI(row, col);
    }

    void findHardDiffMove(int &row, int &col)
    {
        unbeatableAI(row, col);
    }

    // MODIFIED FROM https://codereview.stackexchange.com/questions/183594/simple-tic-tac-toe-with-minimax-algorithm
    void minimax(int &row, int &col)
    {
        int aiWinStatus = _playerSelection == PIECE_O ? STATUS_X_WON : STATUS_O_WON;
        int playerWinStatus = _playerSelection == PIECE_O ? STATUS_O_WON : STATUS_X_WON;
        int status = checkGame(true);

        int score = std::numeric_limits<int>::max();
        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (_boardStatus[i][j] == PIECE_NONE)
                {
                    _boardStatus[i][j] = _playerSelection == PIECE_O ? PIECE_X : PIECE_O;

                    int temp = maxSearch();

                    if (temp < score)
                    {
                        score = temp;
                        row = i;
                        col = j;
                    }
                    _boardStatus[i][j] = PIECE_NONE;
                }
            }
        }
    }

    int maxSearch()
    {
        int aiWinStatus = _playerSelection == PIECE_O ? STATUS_X_WON : STATUS_O_WON;
        int playerWinStatus = _playerSelection == PIECE_O ? STATUS_O_WON : STATUS_X_WON;
        int status = checkGame(true);

        if (status == playerWinStatus)
            return 10;
        else if (status == aiWinStatus)
            return -10;
        else if (status == STATUS_DRAW)
            return 0;

        int score = std::numeric_limits<int>::min();

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (_boardStatus[i][j] == PIECE_NONE)
                {
                    _boardStatus[i][j] = _playerSelection;
                    score = std::max(score, minSearch());
                    _boardStatus[i][j] = PIECE_NONE;
                }
            }
        }

        return score;
    }

    int minSearch()
    {
        int aiWinStatus = _playerSelection == PIECE_O ? STATUS_X_WON : STATUS_O_WON;
        int playerWinStatus = _playerSelection == PIECE_O ? STATUS_O_WON : STATUS_X_WON;
        int status = checkGame(true);

        if (status == playerWinStatus)
            return 10;
        else if (status == aiWinStatus)
            return -10;
        else if (status == STATUS_DRAW)
            return 0;

        int score = std::numeric_limits<int>::max();

        for (unsigned int i = 0; i < 3; i++)
        {
            for (unsigned int j = 0; j < 3; j++)
            {
                if (_boardStatus[i][j] == PIECE_NONE)
                {
                    _boardStatus[i][j] = _playerSelection == PIECE_O ? PIECE_X : PIECE_O;
                    score = std::min(score, maxSearch());
                    _boardStatus[i][j] = PIECE_NONE;
                }
            }
        }

        return score;
    }

private:
    SpriteObject _diffTitle{_engine};
    SpriteObject _diffEasyBtn{_engine};
    SpriteObject _diffMediumBtn{_engine};
    SpriteObject _diffHardBtn{_engine};

    SpriteObject _choosePieceTitle{_engine};
    SpriteObject _selectOBtn{_engine};
    SpriteObject _selectXBtn{_engine};

    float _currentScreen = SCREEN_DIFFICULTY;
    int _playerSelection = PIECE_X;
    int _diffLevel = DIFFICULTY_EASY;
};
