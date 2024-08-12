#include "views/widgets/scenewidget.h"

SceneWidget::SceneWidget(QWidget* parent): QWidget(parent)
{
    pGameController = nullptr;
    pGameResources = nullptr;
}

void SceneWidget::setGameController(GameController* pGameController)
{
    this->pGameController = pGameController;
}

void SceneWidget::setGameResources(GameResources* pGameResources)
{
    this->pGameResources = pGameResources;
}

void SceneWidget::paintOuterBackground(QPainter& painter)
{
    int w = pGameController->getRows() * SceneProperties::BLOCK_SIZE + SceneProperties::OUTER_BORDER * 2;
    int h = pGameController->getCols() * SceneProperties::BLOCK_SIZE + SceneProperties::OUTER_BORDER * 2;

    painter.fillRect(SceneProperties::OUTER_MARGIN, SceneProperties::OUTER_MARGIN, w, h, *pGameResources->getBlackBrush());
}

void SceneWidget::paintInnerBackground(QPainter& painter)
{
    int w = pGameController->getRows() * SceneProperties::BLOCK_SIZE + SceneProperties::INNER_BORDER * 2;
    int h = pGameController->getCols() * SceneProperties::BLOCK_SIZE + SceneProperties::INNER_BORDER * 2;

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

    for (int rows = 0; rows < pGameController->getRows(); rows++)
    {
        for (int cols = 0; cols < pGameController->getCols(); cols++)
        {
            MineBlock& block = pGameController->getBlock(rows, cols);

            int x = SceneProperties::MARGIN + rows * SceneProperties::BLOCK_SIZE;
            int y = SceneProperties::MARGIN + cols * SceneProperties::BLOCK_SIZE;

            if (pGameController->getStatus() == GameStatus::PAUSE)
            {
                painter.drawPixmap(x, y, *pGameResources->getCoverPixmap());
            }
            else if (block.isCovered() && !pGameController->isCracking())
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
