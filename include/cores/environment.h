#ifndef __CORES_ENVIRONMENT_H__
#define __CORES_ENVIRONMENT_H__

#include <QRandomGenerator>
#include <QList>
#include <QPoint>

#include "commons/constants.h"
#include "cores/block.h"

enum class GameStatus
{
    PLAYING,
    PAUSE,
    FAILURE,
    SUCCESS,
};

class GameEnvironment
{
    private:
        MineBlock blocks[SceneProperties::ROWS_MAX][SceneProperties::COLS_MAX];
        GameStatus status;

    private:
        QList<QPoint> minesLocations;
        QList<QPoint> emptyLocations;

    private:
        int level;
        int rows;
        int cols;

    private:
        int mineInitCount;
        int remainFlagCount;

    private:
        bool cracking;
        bool cracked;

    public:
        void setLevel1();
        void setLevel2();
        void setLevel3();
        void setCustomLevel(int rows, int cols, int mineCount);

    public:
        void setPause();
        void setResume();
        void setCrackStart();
        void setCrackEnd();

    public:
        void restart();
        void addMines();
        void addNumbers();
        void uncoverEmptyBlocks();

    public:
        bool leftButtonClick(int x, int y);
        bool rightButtonClick(int x, int y);

    public:
        MineBlock& getBlock(int x, int y);
        GameStatus getStatus();

    public:
        int getLevel();
        int getRows();
        int getCols();
        int getRemainFlagCount();
        bool isCracking();
        bool isCracked();

    public:
        bool isSuccess();
        bool isFailure(int x, int y);
};
#endif