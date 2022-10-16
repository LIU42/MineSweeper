#include <QApplication>
#include <QDateTime>

#include "minesweeper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainGame game;

	srand(QDateTime::currentDateTime().toMSecsSinceEpoch());

    game.loadImage();
    game.loadAudio();
    game.initColor();
    game.setInterval();
    game.connectTimer();
    game.connectAction();
    game.startTimer();
    game.setEasyLevel();
	game.show();

    return app.exec();
}
