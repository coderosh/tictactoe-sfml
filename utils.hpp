#pragma once

#include "./DEFINES.hpp"
#include "./Engine/Engine.hpp"
#include "SpriteObject.hpp"

class GameUtils
{

public:
    static int countEmpty(int (&boardStatus)[3][3])
    {
        int count = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (boardStatus[i][j] != PIECE_NONE)
                    count++;
        return count;
    }

    static bool checkDraw(int (&boardStatus)[3][3])
    {
        return countEmpty(boardStatus) == 9;
    }

    static int *checkGameStatus(Engine::Engine *engine, int (&boardStatus)[3][3], int (&winingCombos)[8][6])
    {
        for (int i = 0; i < 8; i++)
        {
            auto combo = winingCombos[i];
            int firstC = boardStatus[combo[0]][combo[1]];
            int second = boardStatus[combo[2]][combo[3]];
            int third = boardStatus[combo[4]][combo[5]];

            if (firstC != PIECE_NONE && firstC == second && second == third)
                return combo;
        }

        return NULL;
    }

    static void findClickedRowCol(Engine::Engine *engine, int boardWidth, int boardHeight, int gridGap, int boardTop, int &row, int &col)
    {
        auto mousePosition = engine->inputManager.getMousePosition(*engine->window);

        float pieceX = (boardHeight - gridGap * 2) / 3;
        float pieceY = (boardHeight - gridGap * 2) / 3;

        float left = (SCREEN_WIDTH - boardHeight) / 2;

        float mouseX = mousePosition.x - left;
        float mouseY = mousePosition.y - boardTop;

        if (mouseX < pieceX)
            col = 0;
        else if (mouseX > (pieceX + gridGap) && mouseX < (pieceX * 2 + gridGap))
            col = 1;
        else if (mouseX > (pieceX + gridGap) * 2)
            col = 2;

        if (mouseY < pieceY)
            row = 0;
        else if (mouseY > (pieceY + gridGap) && mouseY < (pieceY * 2 + gridGap))
            row = 1;
        else if (mouseY > (pieceY + gridGap) * 2)
            row = 2;
    }
};
