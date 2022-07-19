#ifndef __CONFIG_H__
#define __CONFIG_H__

#define WINDOW_TITLE "Mine Sweeper"
#define SCREEN_WIDTH 280
#define SCREEN_HEIGHT 310
#define GAME_FPS 10
#define IMG_FORMAT SDL_PIXELFORMAT_RGBA32

#define TABLE_LARGE 10
#define BLOCK_LARGE 26
#define EMPTY_COUNT 80
#define BORDER_X 10
#define BORDER_Y 40

#define MINE_INIT_COUNT 20
#define AROUND_MAX 8
#define INTERVAL 1000

#define FONT_SIZE 15
#define TEXT_RECT_WIDTH 100
#define TEXT_RECT_HEIGHT 15
#define TEXT_POSITION 7
#define TEXT_MAX_LEN 30
#define TEXT_COLOR { 0, 0, 0 }

#define PLAYING 0
#define OVER 1
#define EXIT 2

#define EMPTY 0
#define MINE 1
#define NUMBER 2
#endif