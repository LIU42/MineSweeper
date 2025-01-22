#include "views/widgets/scenewidget.h"

SceneWidget::SceneWidget(QWidget* parent): QWidget(parent)
{
    gameFramework = nullptr;
    gameResources = nullptr;
}

void SceneWidget::setGameFramework(GameFramework* gameFramework)
{
    this->gameFramework = gameFramework;
}

void SceneWidget::setGameResources(GameResources* gameResources)
{
    this->gameResources = gameResources;
}

void SceneWidget::paintOuterBackground(QPainter& painter)
{
    int w = gameFramework->getRows() * UnitProperties::SIZE + SceneProperties::OUTER_BORDER * 2;
    int h = gameFramework->getCols() * UnitProperties::SIZE + SceneProperties::OUTER_BORDER * 2;

    painter.fillRect(SceneProperties::OUTER_MARGIN, SceneProperties::OUTER_MARGIN, w, h, QBrush(QColor(Colors::BLACK)));
}

void SceneWidget::paintInnerBackground(QPainter& painter)
{
    int w = gameFramework->getRows() * UnitProperties::SIZE + SceneProperties::INNER_BORDER * 2;
    int h = gameFramework->getCols() * UnitProperties::SIZE + SceneProperties::INNER_BORDER * 2;

    painter.fillRect(SceneProperties::INNER_MARGIN, SceneProperties::INNER_MARGIN, w, h, QBrush(QColor(Colors::GRAY)));
}

void SceneWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    painter.setRenderHints(QPainter::SmoothPixmapTransform | QPainter::Antialiasing);

    paintOuterBackground(painter);
    paintInnerBackground(painter);

    for (int rows = 0; rows < gameFramework->getRows(); rows++)
    {
        for (int cols = 0; cols < gameFramework->getCols(); cols++)
        {
            MineUnit* unit = gameFramework->getUnit(rows, cols);

            int x = SceneProperties::MARGIN + rows * UnitProperties::SIZE;
            int y = SceneProperties::MARGIN + cols * UnitProperties::SIZE;

            if (gameFramework->getStatus() == GameStatus::PAUSE)
            {
                painter.drawPixmap(x, y, *gameResources->getCoverPixmap());
                continue;
            }
            if (unit->isCovered() && !gameFramework->isCracking())
            {
                painter.drawPixmap(x, y, *gameResources->getCoverPixmap());

                if (unit->isMistaken())
                {
                    painter.drawPixmap(x, y, *gameResources->getErrorPixmap());
                }
                else if (unit->isMarked())
                {
                    painter.drawPixmap(x, y, *gameResources->getFlagPixmap());
                }
                continue;
            }
            painter.drawPixmap(x, y, *gameResources->getUncoverPixmap());

            if (unit->getType() == UnitType::NUMBER)
            {
                painter.drawPixmap(x, y, *gameResources->getNumberPixmap(unit->getNumber()));
            }
            else if (unit->getType() == UnitType::MINE)
            {
                if (unit->isTouched())
                {
                    painter.drawPixmap(x, y, *gameResources->getTouchPixmap());
                }
                else
                {
                    painter.drawPixmap(x, y, *gameResources->getMinePixmap());
                }
            }
        }
    }
}
