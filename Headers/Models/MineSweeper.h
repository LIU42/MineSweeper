#ifndef __MODELS_MINESWEEPER_H__
#define __MODELS_MINESWEEPER_H__

#include <QVector>
#include <QPoint>

using BlockPointList = QVector<QPoint>;
using NumberList = QVector<int>;

enum GameStatus
{
    STATUS_MAINLOOP,
    STATUS_PAUSE,
    STATUS_FAILURE,
    STATUS_SUCCESS
};

enum GameLevel
{
    LEVEL_EASY,
    LEVEL_NORMAL,
    LEVEL_HIGH,
    LEVEL_CUSTOM
};

enum GameBlockType
{
    BLOCK_EMPTY,
    BLOCK_NUMBER,
    BLOCK_MINE
};

class GameEasyLevel
{
    public:
        static const int ROWS = 10;
        static const int COLS = 10;
        static const int MINE_INIT_COUNT = 10;
};

class GameNormalLevel
{
    public:
        static const int ROWS = 15;
        static const int COLS = 15;
        static const int MINE_INIT_COUNT = 30;
};

class GameHighLevel
{
    public:
        static const int ROWS = 30;
        static const int COLS = 20;
        static const int MINE_INIT_COUNT = 100;
};

class GameBlock
{
    public:
        static const int SIZE = 32;

    public:
        GameBlockType type;

    public:
        int number;
        bool isCovered;
        bool isMarked;
        bool isError;
        bool isTouched;
};

class MainGame
{
    private:
        static const int ROWS_MAX = 40;
        static const int COLS_MAX = 25;

    private:
        GameBlock blockMatrix[ROWS_MAX][COLS_MAX];
        BlockPointList mineList;
        BlockPointList emptyList;
        NumberList numberList;
        GameStatus status;
        GameLevel level;

    private:
        int tableRows;
        int tableCols;
        int mineInitCount;
        int remainFlagCount;
        bool isCracked;
        bool isHaveCracked;

    public:
        void setEasyLevel();
        void setNormalLevel();
        void setHighLevel();
        void setCustomLevel(int, int, int);

    public:
        void setPause();
        void setResume();
        void setCrackStart();
        void setCrackEnd();

    public:
        void restart();
        void addMines();
        void addNumbers();
        void autoUncoverBlocks();

    public:
        bool isLeftButtonClick(int, int);
        bool isRightButtonClick(int, int);

    public:
        GameBlock getBlock(int, int);
        GameLevel getLevel();
        GameStatus getStatus();

    public:
        int getTableRows();
        int getTableCols();
        int getRemainFlagCount();
        bool getIsCracked();
        bool getIsHaveCracked();

    public:
        bool isSuccess();
        bool isFailure(int, int);
};
#endif