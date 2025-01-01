#ifndef __VIEWS_WIDGETS_SCENEWIDGETS_H__
#define __VIEWS_WIDGETS_SCENEWIDGETS_H__

#include <QPainter>
#include <QWidget>

#include "commons/resources.h"
#include "cores/environment.h"

class SceneWidget : public QWidget
{
    private:
        GameEnvironment* pGameEnvironment;
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
        void setGameEnvironment(GameEnvironment* pGameEnvironment);
        void setGameResources(GameResources* pGameResources);
};
#endif
