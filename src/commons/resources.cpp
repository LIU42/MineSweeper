#include "commons/resources.h"

GameResources::GameResources()
{
    pBlockPixmap = new QPixmap(":/images/block.png");
    pCoverPixmap = new QPixmap(":/images/cover.png");
    pErrorPixmap = new QPixmap(":/images/error.png");
    pFlagPixmap = new QPixmap(":/images/flag.png");
    pMinePixmap = new QPixmap(":/images/mine.png");
    pTouchPixmap = new QPixmap(":/images/touch.png");

    for (int i = 0; i < SceneProperties::NUMBER_COUNT; i++)
    {
        pNumberPixmaps[i] = new QPixmap(QString(":/images/number_%1.png").arg(i + 1));
    }

    pBlackBrush = new QBrush(QColor(Colors::BLACK));
    pGrayBrush = new QBrush(QColor(Colors::GRAY));

    pClickSound = new QSoundEffect();
    pSuccessSound = new QSoundEffect();
    pFailureSound = new QSoundEffect();

    pClickSound->setSource(QUrl("qrc:/sounds/click.wav"));
    pFailureSound->setSource(QUrl("qrc:/sounds/failure.wav"));
    pSuccessSound->setSource(QUrl("qrc:/sounds/success.wav"));
}

GameResources::~GameResources()
{
    delete pBlockPixmap;
    delete pCoverPixmap;
    delete pErrorPixmap;
    delete pFlagPixmap;
    delete pMinePixmap;
    delete pTouchPixmap;

    for (int i = 0; i < SceneProperties::NUMBER_COUNT; i++)
    {
        delete pNumberPixmaps[i];
    }

    delete pBlackBrush;
    delete pGrayBrush;

    delete pClickSound;
    delete pSuccessSound;
    delete pFailureSound;
}

QPixmap* GameResources::getBlockPixmap()
{
    return pBlockPixmap;
}

QPixmap* GameResources::getCoverPixmap()
{
    return pCoverPixmap;
}

QPixmap* GameResources::getErrorPixmap()
{
    return pErrorPixmap;
}

QPixmap* GameResources::getFlagPixmap()
{
    return pFlagPixmap;
}

QPixmap* GameResources::getMinePixmap()
{
    return pMinePixmap;
}

QPixmap* GameResources::getTouchPixmap()
{
    return pTouchPixmap;
}

QPixmap* GameResources::getNumberPixmap(int number)
{
    return pNumberPixmaps[number - 1];
}

QBrush* GameResources::getBlackBrush()
{
    return pBlackBrush;
}

QBrush* GameResources::getGrayBrush()
{
    return pGrayBrush;
}

QSoundEffect* GameResources::getClickSound()
{
    return pClickSound;
}

QSoundEffect* GameResources::getFailureSound()
{
    return pFailureSound;
}

QSoundEffect* GameResources::getSuccessSound()
{
    return pSuccessSound;
}
