#include "Games/MainGame.h"

void MainGame::setEasyLevel()
{
    level = GameLevel::LEVEL_EASY;
    tableRows = GameEasyLevel::ROWS;
    tableCols = GameEasyLevel::COLS;
    mineInitCount = GameEasyLevel::MINE_INIT_COUNT;
}

void MainGame::setNormalLevel()
{
    level = GameLevel::LEVEL_NORMAL;
    tableRows = GameNormalLevel::ROWS;
    tableCols = GameNormalLevel::COLS;
    mineInitCount = GameNormalLevel::MINE_INIT_COUNT;
}

void MainGame::setHighLevel()
{
    level = GameLevel::LEVEL_HIGH;
    tableRows = GameHighLevel::ROWS;
    tableCols = GameHighLevel::COLS;
    mineInitCount = GameHighLevel::MINE_INIT_COUNT;
}

void MainGame::setCustomLevel(int rows, int cols, int mineCount)
{
    level = GameLevel::LEVEL_CUSTOM;
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
    if (status == GameStatus::STATUS_MAINLOOP && !isCracked)
    {
        status = GameStatus::STATUS_PAUSE;
    }
}

void MainGame::setResume()
{
    if (status == GameStatus::STATUS_PAUSE)
    {
        status = GameStatus::STATUS_MAINLOOP;
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
            blockMatrix[i][j].type = BlockType::BLOCK_EMPTY;
            blockMatrix[i][j].number = 0;
            blockMatrix[i][j].isCovered = true;
            blockMatrix[i][j].isMarked = false;
            blockMatrix[i][j].isTouched = false;
            blockMatrix[i][j].isError = false;
        }
    }
    remainFlagCount = mineInitCount;
    status = GameStatus::STATUS_MAINLOOP;
    isCracked = false;
    isHaveCracked = false;
}

void MainGame::addMines()
{
    int tableSize = tableRows * tableCols;

    minePositionList.clear();
    indexList.clear();

    for (int i = 0; i < tableSize; i++)
    {
        indexList.append(i);
    }
    for (int i = 0; i < tableSize; i++)
    {
        qSwap(indexList[i], indexList[QRandomGenerator::global()->bounded(tableSize)]);
    }
    for (int i = 0; i < mineInitCount; i++)
    {
        int x = indexList[i] % tableRows;
        int y = indexList[i] / tableRows;

        blockMatrix[x][y].type = BlockType::BLOCK_MINE;
        minePositionList.append(QPoint(x, y));
    }
}

void MainGame::addNumbers()
{
    for (QPoint& minePosition : minePositionList)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
                int x = minePosition.x() + sideX;
                int y = minePosition.y() + sideY;

                if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && blockMatrix[x][y].type != BlockType::BLOCK_MINE)
                {
                    blockMatrix[x][y].type = BlockType::BLOCK_NUMBER;
                    blockMatrix[x][y].number += 1;
                }
            }
        }
    }
}

void MainGame::uncoverEmptyBlocks()
{
    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
            if (blockMatrix[x][y].type == BlockType::BLOCK_EMPTY && !blockMatrix[x][y].isCovered)
            {
                emptyPositionList.append(QPoint(x, y));
            }
        }
    }
    for (QPoint& emptyPosition : emptyPositionList)
    {
        for (int sideX = -1; sideX <= 1; sideX++)
        {
            for (int sideY = -1; sideY <= 1; sideY++)
            {
                int x = emptyPosition.x() + sideX;
                int y = emptyPosition.y() + sideY;

                if (x >= 0 && x < tableRows && y >= 0 && y < tableCols && !blockMatrix[x][y].isMarked)
                {
                    blockMatrix[x][y].isCovered = false;
                }
            }
        }
    }
    emptyPositionList.clear();
}

GameBlock& MainGame::getBlock(int x, int y)
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
            if (blockMatrix[x][y].type != BlockType::BLOCK_MINE && blockMatrix[x][y].isCovered)
            {
                return false;
            }
        }
    }
    status = GameStatus::STATUS_SUCCESS;
    return true;
}

bool MainGame::isFailure(int x, int y)
{
    if (blockMatrix[x][y].type != BlockType::BLOCK_MINE)
    {
        return false;
    }
    blockMatrix[x][y].isTouched = true;

    for (int x = 0; x < tableRows; x++)
    {
        for (int y = 0; y < tableCols; y++)
        {
            if (blockMatrix[x][y].type == BlockType::BLOCK_MINE && !blockMatrix[x][y].isMarked)
            {
                blockMatrix[x][y].isCovered = false;
            }
            else if (blockMatrix[x][y].type != BlockType::BLOCK_MINE && blockMatrix[x][y].isMarked)
            {
                blockMatrix[x][y].isError = true;
            }
        }
    }
    status = GameStatus::STATUS_FAILURE;
    return true;
}
