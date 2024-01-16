#include "Graphics.h"

GameImages::GameImages()
{
    pBlockPixmap = new QPixmap(":/Images/block.png");
    pCoverPixmap = new QPixmap(":/Images/cover.png");
    pErrorPixmap = new QPixmap(":/Images/error.png");
    pFlagPixmap = new QPixmap(":/Images/flag.png");
    pMinePixmap = new QPixmap(":/Images/mine.png");
    pMineErrorPixmap = new QPixmap(":/Images/mine_error.png");

    for (int i = 0; i < GameImages::NUMBER_COUNT; i++)
    {
        pNumberPixmaps[i] = new QPixmap(QString(":/Images/number_%1.png").arg(i + 1));
    }
}

GameImages::~GameImages()
{
    delete pBlockPixmap;
    delete pCoverPixmap;
    delete pErrorPixmap;
    delete pFlagPixmap;
    delete pMinePixmap;
    delete pMineErrorPixmap;

    for (int i = 0; i < GameImages::NUMBER_COUNT; i++)
    {
        delete pNumberPixmaps[i];
    }
}

GameColors::GameColors()
{
    pBlackBrush = new QBrush(QColor(GameColors::BLACK));
    pGrayBrush = new QBrush(QColor(GameColors::GRAY));
}

GameColors::~GameColors()
{
    delete pBlackBrush;
    delete pGrayBrush;
}

GraphicsWidget::GraphicsWidget(QWidget* parent): QWidget(parent)
{
    pImages = new GameImages();
    pColors = new GameColors();
}

GraphicsWidget::~GraphicsWidget()
{
    delete pImages;
    delete pColors;
}

void GraphicsWidget::setMainGame(MainGame* pMainGame)
{
    this->pMainGame = pMainGame;
}

void GraphicsWidget::paintBackgroundOuter(QPainter& painter)
{
    int width = pMainGame->getTableRows() * GameBlock::SIZE + OUTER_BORDER + OUTER_BORDER;
    int height = pMainGame->getTableCols() * GameBlock::SIZE + OUTER_BORDER + OUTER_BORDER;

    painter.fillRect(MARGIN - OUTER_BORDER, MARGIN - OUTER_BORDER, width, height, *pColors->pBlackBrush);
}

void GraphicsWidget::paintBackgroundInner(QPainter& painter)
{
    int width = pMainGame->getTableRows() * GameBlock::SIZE + INNER_BORDER + INNER_BORDER;
    int height = pMainGame->getTableCols() * GameBlock::SIZE + INNER_BORDER + INNER_BORDER;

    painter.fillRect(MARGIN - INNER_BORDER, MARGIN - INNER_BORDER, width, height, *pColors->pGrayBrush);
}

void GraphicsWidget::paintBackground(QPainter& painter)
{
    paintBackgroundOuter(painter);
    paintBackgroundInner(painter);
}

void GraphicsWidget::paintBlocksCovered(QPainter& painter, GameBlock& block, int x, int y)
{
    if (block.isCovered && !pMainGame->getIsCracked())
    {
        painter.drawPixmap(x, y, *pImages->pCoverPixmap);

        if (block.isError)
        {
            painter.drawPixmap(x, y, *pImages->pErrorPixmap);
        }
        else if (block.isMarked)
        {
            painter.drawPixmap(x, y, *pImages->pFlagPixmap);
        }
    }
}

void GraphicsWidget::paintBlocksUncovered(QPainter& painter, GameBlock& block, int x, int y)
{
    if (!block.isCovered || pMainGame->getIsCracked())
    {
        painter.drawPixmap(x, y, *pImages->pBlockPixmap);

        if (block.type == BlockType::BLOCK_NUMBER)
        {
            painter.drawPixmap(x, y, *pImages->pNumberPixmaps[block.number - 1]);
        }
        else if (block.type == BlockType::BLOCK_MINE)
        {
            painter.drawPixmap(x, y, (block.isTouched) ? *pImages->pMineErrorPixmap : *pImages->pMinePixmap);
        }
    }
}

void GraphicsWidget::paintBlocks(QPainter& painter)
{
    for (int rows = 0; rows < pMainGame->getTableRows(); rows++)
    {
        for (int cols = 0; cols < pMainGame->getTableCols(); cols++)
        {
            GameBlock& block = pMainGame->getBlock(rows, cols);

            int x = MARGIN + rows * GameBlock::SIZE;
            int y = MARGIN + cols * GameBlock::SIZE;

            if (pMainGame->getStatus() == GameStatus::STATUS_PAUSE)
            {
                painter.drawPixmap(x, y, *pImages->pCoverPixmap);
                continue;
            }
            paintBlocksCovered(painter, block, x, y);
            paintBlocksUncovered(painter, block, x, y);
        }
    }
}

void GraphicsWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setRenderHints(QPainter::SmoothPixmapTransform);
    paintBackground(painter);
    paintBlocks(painter);
}
