#include "mainwindow.h"

void setHighDPIScalePolicy()
{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
}

int main(int argc, char* argv[])
{
    setHighDPIScalePolicy();

    QApplication app(argc, argv);
    MainWindow window;
    MainGame game;

    window.setGame(&game);
    window.init();
    window.show();

    return app.exec();
}
