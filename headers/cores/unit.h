#ifndef __CORES_UNIT_H__
#define __CORES_UNIT_H__

enum class UnitType
{
    EMPTY,
    NUMBER,
    MINE,
};

class MineUnit
{
    private:
        UnitType type;

    private:
        int number;
        bool covered;
        bool marked;
        bool mistaken;
        bool touched;

    public:
        void reset();
        void setAsMine();
        void addNumber();

    public:
        void setMarked(bool marked);

    public:
        void setUncovered();
        void setMistaken();
        void setTorched();

    public:
        UnitType getType();

    public:
        int getNumber();
        bool isCovered();
        bool isMarked();
        bool isMistaken();
        bool isTouched();
};
#endif
