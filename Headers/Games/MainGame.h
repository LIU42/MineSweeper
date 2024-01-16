#ifndef __GAMES_MAINGAME_H__
#define __GAMES_MAINGAME_H__

#include <QRandomGenerator>
#include <QList>
#include <QPoint>

enum class GameStatus
{
    STATUS_MAINLOOP,
    STATUS_PAUSE,
    STATUS_FAILURE,
    STATUS_SUCCESS
};

enum class GameLevel
{
    LEVEL_EASY,
    LEVEL_NORMAL,
    LEVEL_HIGH,
    LEVEL_CUSTOM
};

enum class BlockType
{
    BLOCK_EMPTY,
    BLOCK_NUMBER,
    BLOCK_MINE
};

class GameEasyLevel
{
    public:
        static constexpr int ROWS = 10;
        static constexpr int COLS = 10;
        static constexpr int MINE_INIT_COUNT = 10;
};

class GameNormalLevel
{
    public:
        static constexpr int ROWS = 15;
        static constexpr int COLS = 15;
        static constexpr int MINE_INIT_COUNT = 30;
};

class GameHighLevel
{
    public:
        static constexpr int ROWS = 30;
        static constexpr int COLS = 20;
        static constexpr int MINE_INIT_COUNT = 100;
};

class GameBlock
{
    public:
        static constexpr int SIZE = 26;

    public:
        BlockType type;
        int number;
        bool isCovered;
        bool isMarked;
        bool isError;
        bool isTouched;
};

class MainGame
{
    private:
        static constexpr int ROWS_MAX = 40;
        static constexpr int COLS_MAX = 25;

    private:
        GameBlock blockMatrix[ROWS_MAX][COLS_MAX];
        GameStatus status;
        GameLevel level;

    private:
        QList<QPoint> minePositionList;
        QList<QPoint> emptyPositionList;
        QList<int> indexList;

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
        bool isLeftButtonClick(int x, int y);
        bool isRightButtonClick(int x, int y);

    public:
        GameBlock& getBlock(int x, int y);
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
        bool isFailure(int x, int y);
};
#endif