#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <QWidget>
#include <QPainter>

#include "Models/minesweeper.h"

class GameImages
{
    friend class GraphicsWidget;

    private:
        static const int NUMBER_COUNT = 8;

    private:
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
    friend class GraphicsWidget;

    private:
        static const unsigned int WHITE = 0xFFFFFFFF;
        static const unsigned int BLACK = 0xFF353535;
        static const unsigned int GRAY = 0xFF606060;

    private:
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
        void paintEvent(QPaintEvent*);

    private:
        void displayBackgroundOuter(QPainter&);
        void displayBackgroundInner(QPainter&);
        void displayBlocksUncovered(QPainter&, GameBlock&, int, int);
        void displayBlocksCovered(QPainter&, GameBlock&, int, int);

    private:
        void displayBackground(QPainter&);
        void displayBlocks(QPainter&);

    public:
        GraphicsWidget(QWidget* parent = nullptr);

    public:
        void setGame(MainGame*);
};
#endif