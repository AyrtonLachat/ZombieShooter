#include <iostream>

#include "global.hpp"

/*************************************************
* \author Ayrton Lachat
* \file global.cpp
* \date 10.03.22 at 20:08
*************************************************/

SDL_Window *window {nullptr};
SDL_Renderer *renderer {nullptr};

int __windowWidth {16 * 70};
int __windowHeight {9 * 70};

unsigned long long __startTicks {0}, __endTicks {0};

int __getWindowWidth()
{
	return __windowWidth;
}



int __getWindowHeight()
{
	return __windowHeight;
}



int capFPS(int framerate)
{
	__endTicks = SDL_GetTicks64();
	
	#define IDEAL_DT (1000 / framerate)
	int dt = (int)(__endTicks - __startTicks);

	if (dt < IDEAL_DT)
	{
		SDL_Delay(IDEAL_DT - dt);
		dt = IDEAL_DT;
	}

	#undef IDEAL_DT

	__startTicks = SDL_GetTicks64();
	return dt;
}



void __setWindowSize(int w, int h)
{
	__windowWidth = w;
	__windowHeight = h;
}



SDL_FPoint operator+(SDL_FPoint &a, SDL_FPoint &b)
{
	return {a.x + b.x, a.y + b.y};
}



SDL_FPoint operator-(SDL_FPoint &a, SDL_FPoint &b)
{
	return {a.x - b.x, a.y - b.y};
}


