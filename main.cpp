#include "minesweeper.h"

using namespace std;

MainGame game;

int main(int argc, char* argv[])
{
	Uint32 startTick;
	Uint32 endTick;
	INT32 delayTick;

	srand((unsigned)time(NULL));

	game.initWindow();
	game.initGame();
	game.loadImage();
	game.loadFont();
	game.addTimer();

	while (game.status != EXIT)
	{
		startTick = SDL_GetTicks();

		game.update();
		game.control();
		game.display();

		endTick = SDL_GetTicks();
		delayTick = (1000 / GAME_FPS) - (endTick - startTick);

		SDL_Delay((delayTick > 0) ? delayTick : 0);
	}
	game.close();
	return 0;
}