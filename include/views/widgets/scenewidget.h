#ifndef __VIEWS_WIDGETS_SCENEWIDGETS_H__
#define __VIEWS_WIDGETS_SCENEWIDGETS_H__

#include <QPainter>
#include <QWidget>

#include "commons/resources.h"
#include "cores/controller.h"

class SceneWidget : public QWidget
{
    private:
        GameController* pGameController;
        GameResources* pGameResources;

    private:
        void paintOuterBackground(QPainter& painter);
        void paintInnerBackground(QPainter& painter);

    private:
        void paintUncoveredBlock(QPainter& painter, MineBlock& block, int x, int y);
        void paintCoveredBlock(QPainter& painter, MineBlock& block, int x, int y);

    private:
        void paintEvent(QPaintEvent*) override;

    public:
        SceneWidget(QWidget* parent = nullptr);

    public:
        void setGameController(GameController* pGameController);
        void setGameResources(GameResources* pGameResources);
};
#endif
