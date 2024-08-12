#include "cores/controller.h"

void GameController::setLevel1()
{
    this->level = GameLevel::LEVEL1;
    this->rows = Level1::ROWS;
    this->cols = Level1::COLS;
    this->mineInitCount = Level1::MINE_INIT_COUNT;
}

void GameController::setLevel2()
{
    this->level = GameLevel::LEVEL2;
    this->rows = Level2::ROWS;
    this->cols = Level2::COLS;
    this->mineInitCount = Level2::MINE_INIT_COUNT;
}

void GameController::setLevel3()
{
    this->level = GameLevel::LEVEL3;
    this->rows = Level3::ROWS;
    this->cols = Level3::COLS;
    this->mineInitCount = Level3::MINE_INIT_COUNT;
}

void GameController::setCustomLevel(int rows, int cols, int mineCount)
{
    this->level = GameLevel::CUSTOM;
    this->rows = rows;
    this->cols = cols;
    this->mineInitCount = mineCount;
}

int GameController::getRows()
{
    return rows;
}

int GameController::getCols()
{
    return cols;
}

void GameController::setPause()
{
    if (status == GameStatus::PLAYING && !cracking)
    {
        status = GameStatus::PAUSE;
    }
}

void GameController::setResume()
{
    if (status == GameStatus::PAUSE)
    {
        status = GameStatus::PLAYING;
    }
}

void GameController::setCrackStart()
{
    cracking = true;
    cracked = true;
}

void GameController::setCrackEnd()
{
    cracking = false;
}

void GameController::restart()
{
    status = GameStatus::PLAYING;
    cracking = false;
    cracked = false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            blocks[i][j].init();
        }
    }
    remainFlagCount = mineInitCount;
}

void GameController::addMines()
{
    QList<int> flattenIndices(rows * cols);

    minesLocations.clear();
    minesLocations.reserve(mineInitCount);

    for (int i = 0; i < flattenIndices.size(); i++)
    {
        flattenIndices[i] = i;
    }
    for (int i = 0; i < flattenIndices.size(); i++)
    {
        qSwap(flattenIndices[i], flattenIndices[QRandomGenerator::global()->bounded(flattenIndices.size())]);
    }
    for (int i = 0; i < mineInitCount; i++)
    {
        int x = flattenIndices[i] % rows;
        int y = flattenIndices[i] / rows;

        blocks[x][y].setAsMine();
        minesLocations.append(QPoint(x, y));
    }
}

void GameController::addNumbers()
{
    for (QPoint& location : minesLocations)
    {
        for (int aroundX = -1; aroundX <= 1; aroundX++)
        {
            for (int aroundY = -1; aroundY <= 1; aroundY++)
            {
                int x = location.x() + aroundX;
                int y = location.y() + aroundY;

                if (x >= 0 && x < rows && y >= 0 && y < cols && blocks[x][y].getType() != BlockType::MINE)
                {
                    blocks[x][y].addNumber();
                }
            }
        }
    }
}

void GameController::uncoverEmptyBlocks()
{
    emptyLocations.clear();

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (blocks[x][y].getType() == BlockType::EMPTY && !blocks[x][y].isCovered())
            {
                emptyLocations.append(QPoint(x, y));
            }
        }
    }
    for (QPoint& location : emptyLocations)
    {
        for (int aroundX = -1; aroundX <= 1; aroundX++)
        {
            for (int aroundY = -1; aroundY <= 1; aroundY++)
            {
                int x = location.x() + aroundX;
                int y = location.y() + aroundY;

                if (x >= 0 && x < rows && y >= 0 && y < cols && !blocks[x][y].isMarked())
                {
                    blocks[x][y].setUncovered();
                }
            }
        }
    }
}

MineBlock& GameController::getBlock(int x, int y)
{
    return blocks[x][y];
}

int GameController::getLevel()
{
    return level;
}

GameStatus GameController::getStatus()
{
    return status;
}

bool GameController::leftButtonClick(int x, int y)
{
    if (blocks[x][y].isCovered() && !blocks[x][y].isMarked())
    {
        blocks[x][y].setUncovered();
        return true;
    }
    return false;
}

bool GameController::rightButtonClick(int x, int y)
{
    if (blocks[x][y].isCovered())
    {
        if (blocks[x][y].isMarked())
        {
            blocks[x][y].setMarked(false);
            remainFlagCount += 1;
        }
        else
        {
            blocks[x][y].setMarked(true);
            remainFlagCount -= 1;
        }
        return true;
    }
    return false;
}

int GameController::getRemainFlagCount()
{
    return remainFlagCount;
}

bool GameController::isCracking()
{
    return cracking;
}

bool GameController::isCracked()
{
    return cracked;
}

bool GameController::isSuccess()
{
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (blocks[x][y].getType() != BlockType::MINE && blocks[x][y].isCovered())
            {
                return false;
            }
        }
    }
    status = GameStatus::SUCCESS;
    return true;
}

bool GameController::isFailure(int x, int y)
{
    if (blocks[x][y].getType() != BlockType::MINE)
    {
        return false;
    }
    blocks[x][y].setTorched();

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (blocks[x][y].getType() == BlockType::MINE && !blocks[x][y].isMarked())
            {
                blocks[x][y].setUncovered();
            }
            else if (blocks[x][y].getType() != BlockType::MINE && blocks[x][y].isMarked())
            {
                blocks[x][y].setMistaken();
            }
        }
    }
    status = GameStatus::FAILURE;
    return true;
}
