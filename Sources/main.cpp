#include "mainwindow.h"

void setHighDPIScalePolicy()
{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
}

void setRandomSeed()
{
    srand((unsigned)time(NULL));
}

int main(int argc, char* argv[])
{
    setHighDPIScalePolicy();
    setRandomSeed();

    QApplication app(argc, argv);
    MainGame game;
    MainWindow window;

    window.setGame(&game);
    window.initialize();
    window.show();

    return app.exec();
}
