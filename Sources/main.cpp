#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    MainGame game;

    window.setGame(&game);
    window.init();
    window.show();

    return app.exec();
}
