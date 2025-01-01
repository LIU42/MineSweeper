#include "views/widgets/scenewidget.h"

SceneWidget::SceneWidget(QWidget* parent): QWidget(parent)
{
    pGameEnvironment = nullptr;
    pGameResources = nullptr;
}

void SceneWidget::setGameEnvironment(GameEnvironment* pGameEnvironment)
{
    this->pGameEnvironment = pGameEnvironment;
}

void SceneWidget::setGameResources(GameResources* pGameResources)
{
    this->pGameResources = pGameResources;
}

void SceneWidget::paintOuterBackground(QPainter& painter)
{
    int w = pGameEnvironment->getRows() * SceneProperties::BLOCK_SIZE + SceneProperties::OUTER_BORDER * 2;
    int h = pGameEnvironment->getCols() * SceneProperties::BLOCK_SIZE + SceneProperties::OUTER_BORDER * 2;

    painter.fillRect(SceneProperties::OUTER_MARGIN, SceneProperties::OUTER_MARGIN, w, h, *pGameResources->getBlackBrush());
}

void SceneWidget::paintInnerBackground(QPainter& painter)
{
    int w = pGameEnvironment->getRows() * SceneProperties::BLOCK_SIZE + SceneProperties::INNER_BORDER * 2;
    int h = pGameEnvironment->getCols() * SceneProperties::BLOCK_SIZE + SceneProperties::INNER_BORDER * 2;

    painter.fillRect(SceneProperties::INNER_MARGIN, SceneProperties::INNER_MARGIN, w, h, *pGameResources->getGrayBrush());
}

void SceneWidget::paintCoveredBlock(QPainter& painter, MineBlock& block, int x, int y)
{
    painter.drawPixmap(x, y, *pGameResources->getCoverPixmap());

    if (block.isMistaken())
    {
        painter.drawPixmap(x, y, *pGameResources->getErrorPixmap());
    }
    else if (block.isMarked())
    {
        painter.drawPixmap(x, y, *pGameResources->getFlagPixmap());
    }
}

void SceneWidget::paintUncoveredBlock(QPainter& painter, MineBlock& block, int x, int y)
{
    painter.drawPixmap(x, y, *pGameResources->getBlockPixmap());

    if (block.getType() == BlockType::NUMBER)
    {
        painter.drawPixmap(x, y, *pGameResources->getNumberPixmap(block.getNumber()));
    }
    else if (block.getType() == BlockType::MINE)
    {
        if (block.isTouched())
        {
            painter.drawPixmap(x, y, *pGameResources->getTouchPixmap());
        }
        else
        {
            painter.drawPixmap(x, y, *pGameResources->getMinePixmap());
        }
    }
}

void SceneWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setRenderHints(QPainter::SmoothPixmapTransform);

    paintOuterBackground(painter);
    paintInnerBackground(painter);

    for (int rows = 0; rows < pGameEnvironment->getRows(); rows++)
    {
        for (int cols = 0; cols < pGameEnvironment->getCols(); cols++)
        {
            MineBlock& block = pGameEnvironment->getBlock(rows, cols);

            int x = SceneProperties::MARGIN + rows * SceneProperties::BLOCK_SIZE;
            int y = SceneProperties::MARGIN + cols * SceneProperties::BLOCK_SIZE;

            if (pGameEnvironment->getStatus() == GameStatus::PAUSE)
            {
                painter.drawPixmap(x, y, *pGameResources->getCoverPixmap());
            }
            else if (block.isCovered() && !pGameEnvironment->isCracking())
            {
                paintCoveredBlock(painter, block, x, y);
            }
            else
            {
                paintUncoveredBlock(painter, block, x, y);
            }
        }
    }
}
