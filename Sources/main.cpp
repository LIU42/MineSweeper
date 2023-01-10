#include "minesweeper.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainGame game;

	game.init();
	game.show();

    return app.exec();
}
