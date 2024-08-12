#ifndef __COMMONS_RESOURCES_H__
#define __COMMONS_RESOURCES_H__

#include <QPixmap>
#include <QBrush>
#include <QColor>
#include <QSoundEffect>

#include "commons/constants.h"

class GameResources
{
    private:
        QPixmap* pBlockPixmap;
        QPixmap* pCoverPixmap;
        QPixmap* pErrorPixmap;
        QPixmap* pFlagPixmap;
        QPixmap* pMinePixmap;
        QPixmap* pTouchPixmap;
        QPixmap* pNumberPixmaps[SceneProperties::NUMBER_COUNT];

    private:
        QBrush* pBlackBrush;
        QBrush* pGrayBrush;

    private:
        QSoundEffect* pClickSound;
        QSoundEffect* pFailureSound;
        QSoundEffect* pSuccessSound;

    public:
        GameResources();
        ~GameResources();

    public:
        QPixmap* getBlockPixmap();
        QPixmap* getCoverPixmap();
        QPixmap* getErrorPixmap();
        QPixmap* getFlagPixmap();
        QPixmap* getMinePixmap();
        QPixmap* getTouchPixmap();
        QPixmap* getNumberPixmap(int number);

    public:
        QBrush* getBlackBrush();
        QBrush* getGrayBrush();

    public:
        QSoundEffect* getClickSound();
        QSoundEffect* getFailureSound();
        QSoundEffect* getSuccessSound();
};
#endif