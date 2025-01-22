#include "cores/framework.h"

GameFramework::GameFramework()
{
    for (int i = 0; i < SceneProperties::ROWS_MAX; i++)
    {
        for (int j = 0; j < SceneProperties::COLS_MAX; j++)
        {
            units[i][j] = new MineUnit();
        }
    }
}

GameFramework::~GameFramework()
{
    for (int i = 0; i < SceneProperties::ROWS_MAX; i++)
    {
        for (int j = 0; j < SceneProperties::COLS_MAX; j++)
        {
            delete units[i][j];
        }
    }
}

void GameFramework::setLevel1()
{
    this->level = GameLevel::LEVEL1;
    this->rows = Level1::ROWS;
    this->cols = Level1::COLS;
    this->mineInitCount = Level1::MINE_INIT_COUNT;
}

void GameFramework::setLevel2()
{
    this->level = GameLevel::LEVEL2;
    this->rows = Level2::ROWS;
    this->cols = Level2::COLS;
    this->mineInitCount = Level2::MINE_INIT_COUNT;
}

void GameFramework::setLevel3()
{
    this->level = GameLevel::LEVEL3;
    this->rows = Level3::ROWS;
    this->cols = Level3::COLS;
    this->mineInitCount = Level3::MINE_INIT_COUNT;
}

void GameFramework::setCustomLevel(int rows, int cols, int mineCount)
{
    this->level = GameLevel::CUSTOM;
    this->rows = rows;
    this->cols = cols;
    this->mineInitCount = mineCount;
}

int GameFramework::getRows()
{
    return rows;
}

int GameFramework::getCols()
{
    return cols;
}

void GameFramework::pause()
{
    if (status == GameStatus::PLAYING && !cracking)
    {
        status = GameStatus::PAUSE;
    }
}

void GameFramework::resume()
{
    if (status == GameStatus::PAUSE)
    {
        status = GameStatus::PLAYING;
    }
}

void GameFramework::setCrackStart()
{
    cracking = true;
    cracked = true;
}

void GameFramework::setCrackEnd()
{
    cracking = false;
}

void GameFramework::restart()
{
    status = GameStatus::PLAYING;
    cracking = false;
    cracked = false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            units[i][j]->reset();
        }
    }
    remainFlagCount = mineInitCount;
}

void GameFramework::addMines()
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

        units[x][y]->setAsMine();
        minesLocations.append(QPoint(x, y));
    }
}

void GameFramework::addNumbers()
{
    for (QPoint& location : minesLocations)
    {
        for (int aroundX = -1; aroundX <= 1; aroundX++)
        {
            for (int aroundY = -1; aroundY <= 1; aroundY++)
            {
                int x = location.x() + aroundX;
                int y = location.y() + aroundY;

                if (x >= 0 && x < rows && y >= 0 && y < cols && units[x][y]->getType() != UnitType::MINE)
                {
                    units[x][y]->addNumber();
                }
            }
        }
    }
}

void GameFramework::uncoverEmptyUnits()
{
    emptyLocations.clear();

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (units[x][y]->getType() == UnitType::EMPTY && !units[x][y]->isCovered())
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

                if (x >= 0 && x < rows && y >= 0 && y < cols && !units[x][y]->isMarked())
                {
                    units[x][y]->setUncovered();
                }
            }
        }
    }
}

MineUnit* GameFramework::getUnit(int x, int y)
{
    return units[x][y];
}

int GameFramework::getLevel()
{
    return level;
}

GameStatus GameFramework::getStatus()
{
    return status;
}

bool GameFramework::leftButtonClick(int x, int y)
{
    if (units[x][y]->isCovered() && !units[x][y]->isMarked())
    {
        units[x][y]->setUncovered();
        return true;
    }
    return false;
}

bool GameFramework::rightButtonClick(int x, int y)
{
    if (units[x][y]->isCovered())
    {
        if (units[x][y]->isMarked())
        {
            units[x][y]->setMarked(false);
            remainFlagCount += 1;
        }
        else
        {
            units[x][y]->setMarked(true);
            remainFlagCount -= 1;
        }
        return true;
    }
    return false;
}

int GameFramework::getRemainFlagCount()
{
    return remainFlagCount;
}

bool GameFramework::isCracking()
{
    return cracking;
}

bool GameFramework::isCracked()
{
    return cracked;
}

bool GameFramework::isSuccess()
{
    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (units[x][y]->getType() != UnitType::MINE && units[x][y]->isCovered())
            {
                return false;
            }
        }
    }
    status = GameStatus::SUCCESS;
    return true;
}

bool GameFramework::isFailure(int x, int y)
{
    if (units[x][y]->getType() != UnitType::MINE)
    {
        return false;
    }
    units[x][y]->setTorched();

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            if (units[x][y]->getType() == UnitType::MINE && !units[x][y]->isMarked())
            {
                units[x][y]->setUncovered();
            }
            else if (units[x][y]->getType() != UnitType::MINE && units[x][y]->isMarked())
            {
                units[x][y]->setMistaken();
            }
        }
    }
    status = GameStatus::FAILURE;
    return true;
}
