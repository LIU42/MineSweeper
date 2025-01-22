#include "utils/resources.h"

GameResources::GameResources()
{
    uncoverPixmap = new QPixmap(":/images/uncover.png");
    coverPixmap = new QPixmap(":/images/cover.png");
    errorPixmap = new QPixmap(":/images/error.png");
    touchPixmap = new QPixmap(":/images/touch.png");
    flagPixmap = new QPixmap(":/images/flag.png");
    minePixmap = new QPixmap(":/images/mine.png");

    for (int i = 0; i < UnitProperties::NUMBER_COUNT; i++)
    {
        numberPixmaps[i] = new QPixmap(QString(":/images/number_%1.png").arg(i + 1));
    }

    clickSound = new QSoundEffect();
    successSound = new QSoundEffect();
    failureSound = new QSoundEffect();

    clickSound->setSource(QUrl("qrc:/sounds/click.wav"));
    failureSound->setSource(QUrl("qrc:/sounds/failure.wav"));
    successSound->setSource(QUrl("qrc:/sounds/success.wav"));
}

GameResources::~GameResources()
{
    delete uncoverPixmap;
    delete coverPixmap;
    delete errorPixmap;
    delete touchPixmap;
    delete flagPixmap;
    delete minePixmap;

    for (int i = 0; i < UnitProperties::NUMBER_COUNT; i++)
    {
        delete numberPixmaps[i];
    }

    delete clickSound;
    delete successSound;
    delete failureSound;
}

QPixmap* GameResources::getUncoverPixmap()
{
    return uncoverPixmap;
}

QPixmap* GameResources::getCoverPixmap()
{
    return coverPixmap;
}

QPixmap* GameResources::getErrorPixmap()
{
    return errorPixmap;
}

QPixmap* GameResources::getTouchPixmap()
{
    return touchPixmap;
}

QPixmap* GameResources::getFlagPixmap()
{
    return flagPixmap;
}

QPixmap* GameResources::getMinePixmap()
{
    return minePixmap;
}

QPixmap* GameResources::getNumberPixmap(int number)
{
    return numberPixmaps[number - 1];
}

QSoundEffect* GameResources::getClickSound()
{
    return clickSound;
}

QSoundEffect* GameResources::getFailureSound()
{
    return failureSound;
}

QSoundEffect* GameResources::getSuccessSound()
{
    return successSound;
}
