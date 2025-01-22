#ifndef __UTILS_RESOURCES_H__
#define __UTILS_RESOURCES_H__

#include <QPixmap>
#include <QSoundEffect>

#include "utils/constants.h"

class GameResources
{
    private:
        QPixmap* uncoverPixmap;
        QPixmap* coverPixmap;
        QPixmap* errorPixmap;
        QPixmap* touchPixmap;
        QPixmap* flagPixmap;
        QPixmap* minePixmap;
        QPixmap* numberPixmaps[UnitProperties::NUMBER_COUNT];

    private:
        QSoundEffect* clickSound;
        QSoundEffect* failureSound;
        QSoundEffect* successSound;

    public:
        GameResources();
        ~GameResources();

    public:
        QPixmap* getUncoverPixmap();
        QPixmap* getCoverPixmap();
        QPixmap* getErrorPixmap();
        QPixmap* getTouchPixmap();
        QPixmap* getFlagPixmap();
        QPixmap* getMinePixmap();
        QPixmap* getNumberPixmap(int number);

    public:
        QSoundEffect* getClickSound();
        QSoundEffect* getFailureSound();
        QSoundEffect* getSuccessSound();
};
#endif