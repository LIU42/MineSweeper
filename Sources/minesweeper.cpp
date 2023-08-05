#include "minesweeper.h"

void MainGame::setEasyLevel()
{
    level = LEVEL_EASY;
    tableRows = GameEasyLevel::ROWS;
    tableCols = GameEasyLevel::COLS;
    mineInitCount = GameEasyLevel::MINE_INIT_COUNT;
}

void MainGame::setNormalLevel()
{
    level = LEVEL_NORMAL;
    tableRows = GameNormalLevel::ROWS;
    tableCols = GameNormalLevel::COLS;
    mineInitCount = GameNormalLevel::MINE_INIT_COUNT;
}

void MainGame::setHighLevel()
{
    level = LEVEL_HIGH;
    tableRows = GameHighLevel::ROWS;
    tableCols = GameHighLevel::COLS;
    mineInitCount = GameHighLevel::MINE_INIT_COUNT;
}

void MainGame::setCustomLevel(int rows, int cols, int mineCount)
{
    level = LEVEL_CUSTOM;
    tableRows = rows;
    tableCols = cols;
    mineInitCount = mineCount;
}

int MainGame::getTableRows()
{
    return tableRows;
}

int MainGame::getTableCols()
{
    return tableCols;
}


void MainGame::setPause()
{
    if (status == STATUS_PLAYING && !isCracked)
    {
        status = STATUS_PAUSE;
    }
}

void MainGame::setResume()
{
    if (status == STATUS_PAUSE)
    {
        status = STATUS_PLAYING;
    }
}

void MainGame::setCrackStart()
{
    isCracked = true;
    isHaveCracked = true;
}

void MainGame::setCrackEnd()
{
    isCracked = false;
}

void MainGame::restart()
{
    for (int i = 0; i < tableRows; i++)
    {
        for (int j = 0; j < tableCols; j++)
        {
            blockMatrix[i][j].type = BLOCK_EMPTY;
            blockMatrix[i][j].number = 0;
            blockMatrix[i][j].isCovered = true;
            blockMatrix[i][j].isMarked = false;
            blockMatrix[i][j].isTouched = false;
            blockMatrix[i][j].isError = false;
        }
    }
    remainFlagCount = mineInitCount;
    status = STATUS_PLAYING;
    isCracked = false;
    isHaveCracked = false;
}

void MainGame::addMines()
{
    mineList.clear();
    numberList.clear();

    for (int i = 0; i < tableRows * tableCols; i++)
    {
        numberList.append(i);
    }
    for (int i = 0; i < tableRows * tableCols; i++)
    {
        qSwap(numberList[i], numberList[rand() % (tableRows * tableCols)]);
    }
    for (int i = 0; i < mineInitCount; i++)
    {
        int x = numberList[i] % tableRows;
        int y = numberList[i] / tableRows;

        blockMatrix[x][y].type = BLOCK_MINE;
        mineList.append(QPoint(x, y));
    }
}

void MainGame::addNumbers()
{
    for (int i = 0; i < mineInitCount; i++)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
                int x = mineList[i].x() + sideX;
                int y = mineList[i].y() + sideY;

                if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && blockMatrix[x][y].type != BLOCK_MINE)
                {
                    blockMatrix[x][y].type = BLOCK_NUMBER;
                    blockMatrix[x][y].number += 1;
                }
            }
        }
    }
}

void MainGame::autoUncoverBlocks()
{
    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
            if (blockMatrix[x][y].type == BLOCK_EMPTY && !blockMatrix[x][y].isCovered)
            {
                emptyList.append(QPoint(x, y));
            }
        }
    }
    for (int i = 0; i < emptyList.size(); i++)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
                int x = emptyList[i].x() + sideX;
                int y = emptyList[i].y() + sideY;

                if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && !blockMatrix[x][y].isMarked)
                {
                    blockMatrix[x][y].isCovered = false;
                }
            }
        }
    }
    emptyList.clear();
}

GameBlock MainGame::getBlock(int x, int y)
{
    return blockMatrix[x][y];
}

GameLevel MainGame::getLevel()
{
    return level;
}

GameStatus MainGame::getStatus()
{
    return status;
}

bool MainGame::isLeftButtonClick(int x, int y)
{
    if (blockMatrix[x][y].isCovered && !blockMatrix[x][y].isMarked)
    {
        blockMatrix[x][y].isCovered = false;
        return true;
    }
    return false;
}

bool MainGame::isRightButtonClick(int x, int y)
{
    if (blockMatrix[x][y].isCovered)
    {
        if (!blockMatrix[x][y].isMarked)
        {
            blockMatrix[x][y].isMarked = true;
            remainFlagCount -= 1;
        }
        else if (blockMatrix[x][y].isMarked)
        {
            blockMatrix[x][y].isMarked = false;
            remainFlagCount += 1;
        }
        return true;
    }
    return false;
}

int MainGame::getRemainFlagCount()
{
    return remainFlagCount;
}

bool MainGame::getIsCracked()
{
    return isCracked;
}

bool MainGame::getIsHaveCracked()
{
    return isHaveCracked;
}

bool MainGame::isSuccess()
{
    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
            if (blockMatrix[x][y].type != BLOCK_MINE && blockMatrix[x][y].isCovered)
            {
                return false;
            }
        }
    }
    status = STATUS_SUCCESS;
    return true;
}

bool MainGame::isFailure(int x, int y)
{
    if (blockMatrix[x][y].type != BLOCK_MINE)
    {
        return false;
    }
    blockMatrix[x][y].isTouched = true;

    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
            if (blockMatrix[x][y].type == BLOCK_MINE && !blockMatrix[x][y].isMarked)
            {
                blockMatrix[x][y].isCovered = false;
            }
            else if (blockMatrix[x][y].type != BLOCK_MINE && blockMatrix[x][y].isMarked)
            {
                blockMatrix[x][y].isError = true;
            }
        }
    }
    status = STATUS_FAILURE;
    return true;
}
