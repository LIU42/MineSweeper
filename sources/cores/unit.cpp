#include "cores/unit.h"

void MineUnit::reset()
{
    this->type = UnitType::EMPTY;
    this->number = 0;
    this->covered = true;
    this->mistaken = false;
    this->marked = false;
    this->touched = false;
}

void MineUnit::setAsMine()
{
    this->type = UnitType::MINE;
}

void MineUnit::addNumber()
{
    this->type = UnitType::NUMBER;
    this->number += 1;
}

void MineUnit::setMarked(bool marked)
{
    this->marked = marked;
}

void MineUnit::setUncovered()
{
    this->covered = false;
}

void MineUnit::setMistaken()
{
    this->mistaken = true;
}

void MineUnit::setTorched()
{
    this->touched = true;
}

UnitType MineUnit::getType()
{
    return type;
}

int MineUnit::getNumber()
{
    return number;
}

bool MineUnit::isCovered()
{
    return covered;
}

bool MineUnit::isMarked()
{
    return marked;
}

bool MineUnit::isMistaken()
{
    return mistaken;
}

bool MineUnit::isTouched()
{
    return touched;
}
