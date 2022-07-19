#ifndef __MINESWEEPER_H__
#define __MINESWEEPER_H__

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include <time.h>

#include "config.h"
#include "resource.h"

using namespace std;

struct Point
{
	int x;
	int y;
};

struct Data
{
	int type;
	int number;
	bool isCovered;
	bool isMarked;
	bool isError;
	bool isTouched;
};

struct Image
{
	SDL_PixelFormat* format;
	SDL_Surface* surface;
	SDL_Surface* background;
	SDL_Surface* block;
	SDL_Surface* cover;
	SDL_Surface* mine;
	SDL_Surface* mineError;
	SDL_Surface* flag;
	SDL_Surface* error;
	SDL_Surface* number[AROUND_MAX];
};

struct Rect
{
	SDL_Rect screen;
	SDL_Rect block;
};

class MainGame
{
	public:
		HINSTANCE hInstance;
		SDL_Window* window;
		SDL_Event events;
		SDL_TimerID timer;
		TTF_Font* font;

	public:
		Image image;
		Rect rect;

	public:
		Data tableData[TABLE_LARGE][TABLE_LARGE];
		Point mineList[MINE_INIT_COUNT];
		Point emptyList[EMPTY_COUNT];

	public:
		int status;
		int flagCount;
		int time;
		bool isWin;

	public:
		SDL_RWops* getResource(HINSTANCE, LPCWSTR, LPCWSTR);
		SDL_Surface* loadSurface(int);

	public:
		void initWindow();
		void initGame();
		void loadImage();
		void loadFont();
		void addTimer();
		void freeImage();
		void freeFont();
		void removeTimer();
		void close();

	public:
		void addMine();
		void addNumber();
		void gameoverWin();
		void gameoverLose(int, int);
		void update();
		void control();
		void displayText(const char*, int, int);
		void displayBlock();
		void displayInfo();
		void display();
};

extern MainGame game;
#endif