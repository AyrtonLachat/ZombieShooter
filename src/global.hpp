#if !defined(__GLOBAL_HPP__)
#define __GLOBAL_HPP__

#include <SDL2/SDL.h>

#define WINDOW_WIDTH __getWindowWidth()
#define WINDOW_HEIGHT __getWindowHeight()
#define FWINDOW_WIDTH ((float)__getWindowWidth())
#define FWINDOW_HEIGHT ((float)__getWindowHeight())

/*************************************************
* \author Ayrton Lachat
* \file global.hpp
* \date 10.03.22 at 20:05
*************************************************/

extern SDL_Window *window;
extern SDL_Renderer *renderer;


int __getWindowWidth();
int __getWindowHeight();

int capFPS(int framerate);


#ifdef __ENABLE_WINDOW_SIZE_SETTING
	void __setWindowSize(int w, int h);
#endif

SDL_FPoint operator+(SDL_FPoint &a, SDL_FPoint &b);
SDL_FPoint operator-(SDL_FPoint &a, SDL_FPoint &b);

#endif