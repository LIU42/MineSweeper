#include "cores/environment.h"

void GameEnvironment::setLevel1()
{
    this->level = GameLevel::LEVEL1;
    this->rows = Level1::ROWS;
    this->cols = Level1::COLS;
    this->mineInitCount = Level1::MINE_INIT_COUNT;
}

void GameEnvironment::setLevel2()
{
    this->level = GameLevel::LEVEL2;
    this->rows = Level2::ROWS;
    this->cols = Level2::COLS;
    this->mineInitCount = Level2::MINE_INIT_COUNT;
}

void GameEnvironment::setLevel3()
{
    this->level = GameLevel::LEVEL3;
    this->rows = Level3::ROWS;
    this->cols = Level3::COLS;
    this->mineInitCount = Level3::MINE_INIT_COUNT;
}

void GameEnvironment::setCustomLevel(int rows, int cols, int mineCount)
{
    this->level = GameLevel::CUSTOM;
    this->rows = rows;
    this->cols = cols;
    this->mineInitCount = mineCount;
}

int GameEnvironment::getRows()
{
    return rows;
}

int GameEnvironment::getCols()
{
    return cols;
}

void GameEnvironment::setPause()
{
    if (status == GameStatus::PLAYING && !cracking)
    {
        status = GameStatus::PAUSE;
    }
}

void GameEnvironment::setResume()
{
    if (status == GameStatus::PAUSE)
    {
        status = GameStatus::PLAYING;
    }
}

void GameEnvironment::setCrackStart()
{
    cracking = true;
    cracked = true;
}

void GameEnvironment::setCrackEnd()
{
    cracking = false;
}

void GameEnvironment::restart()
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

void GameEnvironment::addMines()
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

void GameEnvironment::addNumbers()
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

void GameEnvironment::uncoverEmptyBlocks()
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

MineBlock& GameEnvironment::getBlock(int x, int y)
{
    return blocks[x][y];
}

int GameEnvironment::getLevel()
{
    return level;
}

GameStatus GameEnvironment::getStatus()
{
    return status;
}

bool GameEnvironment::leftButtonClick(int x, int y)
{
    if (blocks[x][y].isCovered() && !blocks[x][y].isMarked())
    {
        blocks[x][y].setUncovered();
        return true;
    }
    return false;
}

bool GameEnvironment::rightButtonClick(int x, int y)
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

int GameEnvironment::getRemainFlagCount()
{
    return remainFlagCount;
}

bool GameEnvironment::isCracking()
{
    return cracking;
}

bool GameEnvironment::isCracked()
{
    return cracked;
}

bool GameEnvironment::isSuccess()
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

bool GameEnvironment::isFailure(int x, int y)
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
