#include "minesweeper.h"

using namespace std;

SDL_RWops* MainGame::getResource(HINSTANCE hInst, LPCWSTR name, LPCWSTR type)
{
	HRSRC hRsrc = FindResource(hInst, name, type);
	DWORD size = SizeofResource(hInst, hRsrc);
	LPVOID data = LockResource(LoadResource(hInst, hRsrc));
	return SDL_RWFromConstMem(data, size);
}

SDL_Surface* MainGame::loadSurface(int id)
{
	SDL_RWops* src = getResource(hInstance, MAKEINTRESOURCE(id), TEXT("PNG"));
	SDL_Surface* originSurface = IMG_LoadPNG_RW(src);
	SDL_Surface* convertSurface = SDL_ConvertSurface(originSurface, image.format, NULL);
	SDL_FreeSurface(originSurface);
	SDL_FreeRW(src);
	return convertSurface;
}

void MainGame::initWindow()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	hInstance = GetModuleHandle(0);
	window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_GetWindowSize(window, &rect.screen.w, &rect.screen.h);
}

void MainGame::initGame()
{
	for (int i = 0; i < TABLE_LARGE; i++)
	{
		for (int j = 0; j < TABLE_LARGE; j++)
		{
			tableData[i][j].type = EMPTY;
			tableData[i][j].number = 0;
			tableData[i][j].isCovered = true;
			tableData[i][j].isMarked = false;
			tableData[i][j].isTouched = false;
			tableData[i][j].isError = false;
		}
	}
	status = PLAYING;
	flagCount = MINE_INIT_COUNT;
	time = 0;
	isWin = false;
	addMine();
	addNumber();
}

void MainGame::loadImage()
{
	image.format = SDL_AllocFormat(IMG_FORMAT);
	image.surface = SDL_GetWindowSurface(window);
	image.background = loadSurface(IDB_PNG1);
	image.block = loadSurface(IDB_PNG2);
	image.cover = loadSurface(IDB_PNG3);
	image.mine = loadSurface(IDB_PNG4);
	image.mineError = loadSurface(IDB_PNG5);
	image.flag = loadSurface(IDB_PNG6);
	image.error = loadSurface(IDB_PNG7);
	for (int i = 0; i < AROUND_MAX; i++) { image.number[i] = loadSurface(IDB_PNG8 + i); }
}

void MainGame::loadFont()
{
	TTF_Init();
	font = TTF_OpenFontRW(getResource(hInstance, MAKEINTRESOURCE(IDR_FONT1), RT_FONT), 1, FONT_SIZE);
}

Uint32 timerCallback(Uint32 interval, void* param)
{
	if (game.status == PLAYING) { game.time += 1; }
	return interval;
}

void MainGame::addTimer() { timer = SDL_AddTimer(INTERVAL, timerCallback, NULL); }

void MainGame::freeImage()
{
	SDL_FreeFormat(image.format);
	SDL_FreeSurface(image.background);
	SDL_FreeSurface(image.block);
	SDL_FreeSurface(image.cover);
	SDL_FreeSurface(image.mine);
	SDL_FreeSurface(image.mineError);
	SDL_FreeSurface(image.flag);
	SDL_FreeSurface(image.error);
	for (int i = 0; i < AROUND_MAX; i++) { SDL_FreeSurface(image.number[i]); }
}

void MainGame::freeFont() { TTF_CloseFont(font); }

void MainGame::removeTimer() { SDL_RemoveTimer(timer); }

void MainGame::close()
{
	SDL_DestroyWindow(window);
	removeTimer();
	freeImage();
	freeFont();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void MainGame::addMine()
{
	for (int i = 0; i < MINE_INIT_COUNT; i++)
	{
		int x = rand() % TABLE_LARGE;
		int y = rand() % TABLE_LARGE;

		if (tableData[x][y].type == MINE) { i--; }
		else
		{
			tableData[x][y].type = MINE;
			mineList[i] = { x, y };
		}
	}
}

void MainGame::addNumber()
{
	for (int i = 0; i < MINE_INIT_COUNT; i++)
	{
		for (int sideX = -1; sideX <= 1; sideX++)
		{
			for (int sideY = -1; sideY <= 1; sideY++)
			{
				int posX = mineList[i].x + sideX;
				int posY = mineList[i].y + sideY;

				if (posX >= 0 && posX < TABLE_LARGE && posY >= 0 && posY < TABLE_LARGE && tableData[posX][posY].type != MINE)
				{
					tableData[posX][posY].type = NUMBER;
					tableData[posX][posY].number += 1;
				}
			}
		}
	}
}

void MainGame::gameoverWin()
{
	int markCount = 0;
	bool isAllUncovered = true;

	for (int x = 0; x < TABLE_LARGE; x++)
	{
		for (int y = 0; y < TABLE_LARGE; y++)
		{
			if (tableData[x][y].type == MINE && tableData[x][y].isMarked) { markCount += 1; }
			else if (tableData[x][y].type != MINE && tableData[x][y].isCovered) { isAllUncovered = false; }
		}
	}
	if (markCount == MINE_INIT_COUNT && isAllUncovered)
	{
		status = OVER;
		isWin = true;
	}
}

void MainGame::gameoverLose(int x, int y)
{
	for (int x = 0; x < TABLE_LARGE; x++)
	{
		for (int y = 0; y < TABLE_LARGE; y++)
		{
			if (tableData[x][y].type == MINE && tableData[x][y].isMarked == false) { tableData[x][y].isCovered = false; }
			else if (tableData[x][y].type != MINE && tableData[x][y].isMarked == true) { tableData[x][y].isError = true; }
		}
	}
	tableData[x][y].isTouched = true;
	status = OVER;
}

void MainGame::update()
{
	int emptyCount = 0;

	for (int x = 0; x < TABLE_LARGE; x++)
	{
		for (int y = 0; y < TABLE_LARGE; y++)
		{
			if (tableData[x][y].type == EMPTY && !tableData[x][y].isCovered)
			{
				emptyList[emptyCount] = { x,y };
				emptyCount += 1;
			}
		}
	}
	for (int i = 0; i < emptyCount; i++)
	{
		for (int sideX = -1; sideX <= 1; sideX++)
		{
			for (int sideY = -1; sideY <= 1; sideY++)
			{
				int posX = emptyList[i].x + sideX;
				int posY = emptyList[i].y + sideY;

				if (posX >= 0 && posX < TABLE_LARGE && posY >= 0 && posY < TABLE_LARGE && !tableData[posX][posY].isMarked)
				{
					tableData[posX][posY].isCovered = false;
				}
			}
		}
	}
}

void MainGame::control()
{
	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_QUIT) { status = EXIT; }
		if (events.type == SDL_MOUSEBUTTONDOWN)
		{
			if (status == PLAYING)
			{
				int mouseX = events.motion.x;
				int mouseY = events.motion.y;

				if (mouseX >= BORDER_X && mouseX <= SCREEN_WIDTH - BORDER_X && mouseY >= BORDER_Y && mouseY <= SCREEN_HEIGHT - BORDER_X)
				{
					int x = ((mouseX - BORDER_X) / BLOCK_LARGE);
					int y = ((mouseY - BORDER_Y) / BLOCK_LARGE);

					if (events.button.button == SDL_BUTTON_LEFT)
					{
						if (tableData[x][y].isCovered && !tableData[x][y].isMarked)
						{
							if (tableData[x][y].type == MINE) { gameoverLose(x, y); }
							tableData[x][y].isCovered = false;
						}
					}
					else if (events.button.button == SDL_BUTTON_RIGHT)
					{
						if (!tableData[x][y].isMarked && tableData[x][y].isCovered)
						{
							tableData[x][y].isMarked = true;
							flagCount -= 1;
						}
						else if (tableData[x][y].isMarked && tableData[x][y].isCovered)
						{
							tableData[x][y].isMarked = false;
							flagCount += 1;
						}
					}
				}
				gameoverWin();
			}
			else { initGame(); }
		}
	}
}

void MainGame::displayText(const char* text, int x, int y)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, TEXT_COLOR);
	SDL_Rect textRect = { x, y, TEXT_RECT_WIDTH, TEXT_RECT_HEIGHT };
	SDL_BlitSurface(textSurface, NULL, image.surface, &textRect);
	SDL_FreeSurface(textSurface);
}

void MainGame::displayBlock()
{
	for (int i = 0; i < TABLE_LARGE; i++)
	{
		for (int j = 0; j < TABLE_LARGE; j++)
		{
			int x = BORDER_X + i * BLOCK_LARGE;
			int y = BORDER_Y + j * BLOCK_LARGE;
			rect.block = { x, y, BLOCK_LARGE, BLOCK_LARGE };

			if (tableData[i][j].isCovered)
			{
				SDL_BlitSurface(image.cover, NULL, image.surface, &rect.block);

				if (tableData[i][j].isError)
				{
					SDL_BlitSurface(image.error, NULL, image.surface, &rect.block);
				}
				else if (tableData[i][j].isMarked)
				{
					SDL_BlitSurface(image.flag, NULL, image.surface, &rect.block);
				}
			}
			else
			{
				SDL_BlitSurface(image.block, NULL, image.surface, &rect.block);

				switch (tableData[i][j].type)
				{
					case NUMBER: SDL_BlitSurface(image.number[tableData[i][j].number - 1], NULL, image.surface, &rect.block); break;
					case MINE: SDL_BlitSurface((tableData[i][j].isTouched) ? image.mineError : image.mine, NULL, image.surface, &rect.block); break;
				}
			}
		}
	}
}

void MainGame::displayInfo()
{
	static char text[TEXT_MAX_LEN];

	SDL_snprintf(text, TEXT_MAX_LEN, "TIME: %d", time);
	displayText(text, BORDER_X, TEXT_POSITION);

	switch (status)
	{
		case PLAYING: SDL_snprintf(text, TEXT_MAX_LEN, "MINES: %d", flagCount); break;
		case OVER: SDL_snprintf(text, TEXT_MAX_LEN, (isWin) ? "Success!" : "BOOM!"); break;
	}
	displayText(text, SCREEN_WIDTH - 80, TEXT_POSITION);
}

void MainGame::display()
{
	SDL_BlitSurface(image.background, NULL, image.surface, &rect.screen);
	displayBlock();
	displayInfo();
	SDL_UpdateWindowSurface(window);
}