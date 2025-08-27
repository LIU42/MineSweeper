#ifndef __CORES_FRAMEWORK_H__
#define __CORES_FRAMEWORK_H__

#include <QRandomGenerator>
#include <QList>
#include <QPoint>

#include "cores/unit.h"
#include "utils/constants.h"

enum class GameStatus
{
    PLAYING,
    PAUSE,
    FAILURE,
    SUCCESS,
};

class GameFramework
{
    private:
        MineUnit* units[SceneProperties::ROWS_MAX][SceneProperties::COLS_MAX];

    private:
        QList<QPoint> minesLocations;
        QList<QPoint> emptyLocations;

    private:
        GameStatus status;

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
        GameFramework();
        ~GameFramework();

    public:
        void setLevel1();
        void setLevel2();
        void setLevel3();
        void setCustomLevel(int rows, int cols, int mineCount);

    public:
        void pause();
        void resume();

    public:
        void setCrackStart();
        void setCrackEnd();

    public:
        void restart();
        void addMines();
        void addNumbers();
        void uncoverEmptyUnits();

    public:
        bool leftButtonClick(int x, int y);
        bool rightButtonClick(int x, int y);

    public:
        MineUnit* getUnit(int x, int y);

    public:
        int getLevel();
        int getRows();
        int getCols();
        int getRemainFlagCount();
        bool isCracking();
        bool isCracked();

    public:
        GameStatus getStatus();

    public:
        bool isSuccess();
        bool isFailure(int x, int y);
};
#endif
