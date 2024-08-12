#ifndef __CORES_BLOCK_H__
#define __CORES_BLOCK_H__

enum class BlockType
{
    EMPTY,
    NUMBER,
    MINE,
};

class MineBlock
{
    private:
        BlockType type;

    private:
        int number;
        bool covered;
        bool marked;
        bool mistaken;
        bool touched;

    public:
        void init();
        void setAsMine();
        void addNumber();

    public:
        void setMarked(bool marked);

    public:
        void setUncovered();
        void setMistaken();
        void setTorched();

    public:
        BlockType getType();

    public:
        int getNumber();
        bool isCovered();
        bool isMarked();
        bool isMistaken();
        bool isTouched();
};
#endif
