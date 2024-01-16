#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <QWidget>
#include <QPainter>

#include "Games/MainGame.h"

class GameImages
{
    private:
        static constexpr int NUMBER_COUNT = 8;

    public:
        QPixmap* pBlockPixmap;
        QPixmap* pCoverPixmap;
        QPixmap* pErrorPixmap;
        QPixmap* pFlagPixmap;
        QPixmap* pMinePixmap;
        QPixmap* pMineErrorPixmap;
        QPixmap* pNumberPixmaps[NUMBER_COUNT];

    public:
        GameImages();
        ~GameImages();
};

class GameColors
{
    private:
        static constexpr unsigned BLACK = 0xFF353535;
        static constexpr unsigned GRAY = 0xFF606060;

    public:
        QBrush* pBlackBrush;
        QBrush* pGrayBrush;

    public:
        GameColors();
        ~GameColors();
};

class GraphicsWidget : public QWidget
{
    private:
        static constexpr int MARGIN = 10;
        static constexpr int OUTER_BORDER = 5;
        static constexpr int INNER_BORDER = 1;

    private:
        MainGame* pMainGame;
        GameImages* pImages;
        GameColors* pColors;

    private:
        void paintEvent(QPaintEvent*) override;

    private:
        void paintBackgroundOuter(QPainter& painter);
        void paintBackgroundInner(QPainter& painter);
        void paintBlocksUncovered(QPainter& painter, GameBlock& block, int x, int y);
        void paintBlocksCovered(QPainter& painter, GameBlock& block, int x, int y);

    private:
        void paintBackground(QPainter& painter);
        void paintBlocks(QPainter& painter);

    public:
        GraphicsWidget(QWidget* parent = nullptr);
        ~GraphicsWidget();

    public:
        void setMainGame(MainGame* pMainGame);
};
#endif