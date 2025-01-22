#ifndef __VIEWS_WIDGETS_SCENEWIDGET_H__
#define __VIEWS_WIDGETS_SCENEWIDGET_H__

#include <QPainter>
#include <QWidget>

#include "cores/framework.h"
#include "utils/resources.h"

class SceneWidget : public QWidget
{
    private:
        GameFramework* gameFramework;
        GameResources* gameResources;

    private:
        void paintOuterBackground(QPainter& painter);
        void paintInnerBackground(QPainter& painter);

    private:
        void paintEvent(QPaintEvent*) override;

    public:
        SceneWidget(QWidget* parent = nullptr);

    public:
        void setGameFramework(GameFramework* gameFramework);
        void setGameResources(GameResources* gameResources);
};
#endif
