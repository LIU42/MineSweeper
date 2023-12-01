#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <QWidget>
#include <QPainter>

#include "Models/MineSweeper.h"

class GameImages
{
    public:
        static const int NUMBER_COUNT = 8;

    public:
        QPixmap block;
        QPixmap cover;
        QPixmap error;
        QPixmap mine;
        QPixmap mineError;
        QPixmap flag;
        QPixmap number[NUMBER_COUNT];
};

class GameColors
{
    public:
        static const unsigned int WHITE = 0xFFFFFFFF;
        static const unsigned int BLACK = 0xFF353535;
        static const unsigned int GRAY = 0xFF606060;

    public:
        QColor white;
        QColor black;
        QColor gray;
};

class GraphicsWidget : public QWidget
{
    private:
        static const int MARGIN = 12;
        static const int OUTER_BORDER = 6;
        static const int INNER_BORDER = 1;

    private:
        MainGame* pGame;

    private:
        GameImages images;
        GameColors colors;

    private:
        void loadImages();
        void initColors();

    private:
        void paintEvent(QPaintEvent* pPaintEvent);

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

    public:
        void setGame(MainGame* pGame);
};
#endif