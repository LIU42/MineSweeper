#include "Graphics.h"

GraphicsWidget::GraphicsWidget(QWidget* parent): QWidget(parent)
{
    loadImages();
    initColors();
}

void GraphicsWidget::setGame(MainGame* pGame)
{
    this->pGame = pGame;
}

void GraphicsWidget::loadImages()
{
    images.block.load(":/Images/block.png");
    images.cover.load(":/Images/cover.png");
    images.error.load(":/Images/error.png");
    images.mine.load(":/Images/mine.png");
    images.mineError.load(":/Images/mine_error.png");
    images.flag.load(":/Images/flag.png");

    for (int i = 0; i < GameImages::NUMBER_COUNT; i++)
    {
        images.number[i].load(QString(":/Images/number_%1.png").arg(i + 1));
    }
}

void GraphicsWidget::initColors()
{
    colors.white.setRgb(GameColors::WHITE);
    colors.black.setRgb(GameColors::BLACK);
    colors.gray.setRgb(GameColors::GRAY);
}

void GraphicsWidget::paintBackgroundOuter(QPainter& painter)
{
    int width = pGame->getTableRows() * GameBlock::SIZE + OUTER_BORDER + OUTER_BORDER;
    int height = pGame->getTableCols() * GameBlock::SIZE + OUTER_BORDER + OUTER_BORDER;

    painter.fillRect(MARGIN - OUTER_BORDER, MARGIN - OUTER_BORDER, width, height, QBrush(colors.black));
}

void GraphicsWidget::paintBackgroundInner(QPainter& painter)
{
    int width = pGame->getTableRows() * GameBlock::SIZE + INNER_BORDER + INNER_BORDER;
    int height = pGame->getTableCols() * GameBlock::SIZE + INNER_BORDER + INNER_BORDER;

    painter.fillRect(MARGIN - INNER_BORDER, MARGIN - INNER_BORDER, width, height, QBrush(colors.gray));
}

void GraphicsWidget::paintBackground(QPainter& painter)
{
    paintBackgroundOuter(painter);
    paintBackgroundInner(painter);
}

void GraphicsWidget::paintBlocksCovered(QPainter& painter, GameBlock& block, int x, int y)
{
    if (block.isCovered && !pGame->getIsCracked())
    {
        painter.drawPixmap(x, y, images.cover);

        if (block.isError)
        {
            painter.drawPixmap(x, y, images.error);
        }
        else if (block.isMarked)
        {
            painter.drawPixmap(x, y, images.flag);
        }
    }
}

void GraphicsWidget::paintBlocksUncovered(QPainter& painter, GameBlock& block, int x, int y)
{
    if (!block.isCovered || pGame->getIsCracked())
    {
        painter.drawPixmap(x, y, images.block);

        if (block.type == BLOCK_NUMBER)
        {
            painter.drawPixmap(x, y, images.number[block.number - 1]);
        }
        else if (block.type == BLOCK_MINE)
        {
            painter.drawPixmap(x, y, (block.isTouched) ? images.mineError : images.mine);
        }
    }
}

void GraphicsWidget::paintBlocks(QPainter& painter)
{
    for (int i = 0; i < pGame->getTableRows(); i++)
    {
        for (int j = 0; j < pGame->getTableCols(); j++)
        {
            GameBlock block = pGame->getBlock(i, j);

            int x = MARGIN + i * GameBlock::SIZE;
            int y = MARGIN + j * GameBlock::SIZE;

            if (pGame->getStatus() == STATUS_PAUSE)
            {
                painter.drawPixmap(x, y, images.cover);
                continue;
            }
            paintBlocksCovered(painter, block, x, y);
            paintBlocksUncovered(painter, block, x, y);
        }
    }
}

void GraphicsWidget::paintEvent(QPaintEvent* pPaintEvent)
{
    Q_UNUSED(pPaintEvent);
    QPainter painter(this);

    paintBackground(painter);
    paintBlocks(painter);
}