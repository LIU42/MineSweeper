#include "cores/block.h"

void MineBlock::init()
{
    this->type = BlockType::EMPTY;
    this->number = 0;
    this->covered = true;
    this->mistaken = false;
    this->marked = false;
    this->touched = false;
}

void MineBlock::setAsMine()
{
    this->type = BlockType::MINE;
}

void MineBlock::addNumber()
{
    this->type = BlockType::NUMBER;
    this->number += 1;
}

void MineBlock::setMarked(bool marked)
{
    this->marked = marked;
}

void MineBlock::setUncovered()
{
    this->covered = false;
}

void MineBlock::setMistaken()
{
    this->mistaken = true;
}

void MineBlock::setTorched()
{
    this->touched = true;
}

BlockType MineBlock::getType()
{
    return type;
}

int MineBlock::getNumber()
{
    return number;
}

bool MineBlock::isCovered()
{
    return covered;
}

bool MineBlock::isMarked()
{
    return marked;
}

bool MineBlock::isMistaken()
{
    return mistaken;
}

bool MineBlock::isTouched()
{
    return touched;
}
