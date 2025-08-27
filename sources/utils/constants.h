#ifndef __UTILS_CONSTANTS_H__
#define __UTILS_CONSTANTS_H__

class GameLevel
{
    public:
        static constexpr int LEVEL1 = 0;
        static constexpr int LEVEL2 = 1;
        static constexpr int LEVEL3 = 2;
        static constexpr int CUSTOM = 3;
        static constexpr int COUNT = 3;
};

class Level1
{
    public:
        static constexpr int ROWS = 10;
        static constexpr int COLS = 10;
        static constexpr int MINE_INIT_COUNT = 10;
};

class Level2
{
    public:
        static constexpr int ROWS = 15;
        static constexpr int COLS = 15;
        static constexpr int MINE_INIT_COUNT = 30;
};

class Level3
{
    public:
        static constexpr int ROWS = 30;
        static constexpr int COLS = 20;
        static constexpr int MINE_INIT_COUNT = 100;
};

class UnitProperties
{
    public:
        static constexpr int SIZE = 26;
        static constexpr int NUMBER_COUNT = 8;
};

class SceneProperties
{
    public:
        static constexpr int ROWS_MAX = 40;
        static constexpr int COLS_MAX = 25;
        static constexpr int OUTER_BORDER = 5;
        static constexpr int INNER_BORDER = 1;
        static constexpr int MARGIN = 10;
        static constexpr int OUTER_MARGIN = 5;
        static constexpr int INNER_MARGIN = 9;
};

class Colors
{
    public:
        static constexpr unsigned GRAY = 0xFF606060;
        static constexpr unsigned BLACK = 0xFF353535;
};

class TimerInterval
{
    public:
        static constexpr int FRAME = 100;
        static constexpr int CLOCK = 1000;
};

class WindowProperties
{
    public:
        static constexpr int MARGIN_X = 10;
        static constexpr int MARGIN_Y = 74;
};

class RecordProperties
{
    public:
        static constexpr int RECORD_COUNT = 3;
        static constexpr int NAME_WIDTH = 100;
        static constexpr int TIME_WIDTH = 60;
};
#endif
